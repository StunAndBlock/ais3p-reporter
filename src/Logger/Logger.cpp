#include "internal/Logger/Logger.hpp"
#include <iostream>
#include <chrono>
Logger::Logger(){
   levelMap_ = {
        {"PRODUCTION", LEVEL::PRODUCTION},
        {"DEVELOPMENT",LEVEL::DEVELOPMENT},
        {"DEBUG", LEVEL::DEBUG}
    };
    level_ = LEVEL::STARTUP;
    levelRepr_ = "STARTUP";

    workerThread_ = std::thread(&Logger::process, this);
}

Logger::~Logger(){
    stopFlag_ = true;
    condition_.notify_all();
    if (workerThread_.joinable()) {
        workerThread_.join();
    } 
}

void Logger::setLevel(const std::string& level){
    //std::lock_guard<std::mutex> levelLock(levelMutex_);
    if(const auto& it = levelMap_.find(level); it != levelMap_.end()){
        this->info(utils::prettyf("Logger level changed, level: %s", level.c_str()));
        
        //yes im lazy bitch :() fuck data race
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        level_ = levelMap_[level];
        levelRepr_ = it->first.c_str();
        return;
    }
    this->warn(utils::prettyf("Logger level was not changed, unknown level: %s, set to: %s", level.c_str(),"PRODUCTION"));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    level_ = LEVEL::PRODUCTION;
    levelRepr_ = "PRODUCATION";
    return;
}



LoggerDebug Logger::debug(){
    return LoggerDebug(this, (LEVEL::DEBUG >= level_));
}

void Logger::info(const std::string& msg) {
    struct event ev{event::LEVEL::INFO, msg};
    this->log(ev);
    return;
}

void Logger::warn(const std::string& msg) {
    struct event ev{event::LEVEL::WARN, msg};
    this->log(ev);
    return;
}

void Logger::error(const std::string& msg) {
    struct event ev{event::LEVEL::ERROR, msg};
    this->log(ev);
    return;
}

void Logger::error(const error::error& err) {
    struct event ev{event::LEVEL::FATAL, err.msg()};
    this->log(ev);
    return;
}

void Logger::fatal(const std::string& msg) {
    struct event ev{event::LEVEL::FATAL, msg};
    this->log(ev);
    return;
}

void Logger::fatal(const error::error& err) {
    struct event ev{event::LEVEL::FATAL, err.msg()};
    this->log(ev);
    return;
}

void Logger::log(struct event ev){
    {
        std::lock_guard<std::mutex> lock(queueMutex_);
        queueEvent_.push(ev);
    }
    condition_.notify_one();
    return;
}

void Logger::process() {
    bool running = true;
    while (running) {
        if (running){
            std::unique_lock<std::mutex> lock(queueMutex_);
            condition_.wait(lock, [this]() { 
                return !queueEvent_.empty() || stopFlag_; 
            });

            while (!queueEvent_.empty()) {
                Logger::event ev = queueEvent_.front();
                queueEvent_.pop();
                lock.unlock();
                FILE* stream;
                const char* eventLevel;
                switch (ev.level)
                {
                case event::LEVEL::INFO:
                    stream = stdout;
                    eventLevel = "INFO";
                    break;
                case event::LEVEL::WARN:
                    stream = stdout;
                    eventLevel = "WARN";
                    break;
                case event::LEVEL::ERROR:
                    stream = stderr;
                    eventLevel = "ERROR";
                    break;
                case event::LEVEL::FATAL:
                    stream = stderr;
                    eventLevel = "FATAL";
                    break;
                default:
                    stream = stderr;
                    eventLevel = "FATAL";
                    break;
                }

                // std::string lockedLevelRepr;
                // {
                //     std::lock_guard<std::mutex> levelLock(levelMutex_);
                //     lockedLevelRepr = levelRepr_;
                // }

                fprintf(stream,"[LOG | %s | %s ] %s\n",levelRepr_, eventLevel,ev.msg.c_str());
                lock.lock();
            }

            if (stopFlag_ && queueEvent_.empty()) {
                running = false;
            }
        }
    }
    return;
}


LoggerDebug::LoggerDebug(ILogger* logger, bool allowed)  {
    logger_= logger;
    allowed_ = allowed;
};


void LoggerDebug::info(const std::string& msg) {
    if (allowed_){
        logger_->info(msg);
    }
    return;
}

void LoggerDebug::warn(const std::string& msg) {
    if (allowed_){
        logger_->warn(msg);
    }
    return;
}

void LoggerDebug::error(const std::string& msg) {
    if (allowed_){
        logger_->error(msg);
    }
    return;
}

void LoggerDebug::error(const error::error& err) {
    if (allowed_){
        logger_->error(err);
    }
    return;
}

void LoggerDebug::fatal(const std::string& msg) {
    if (allowed_){
        logger_->info(msg);
    }
    return;
}

void LoggerDebug::fatal(const error::error& err) {
     if (allowed_){
        logger_->fatal(err);
    }
    return;
}