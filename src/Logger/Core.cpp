#include "internal/Logger/Core.hpp"

namespace logger {
    Core::Core(){
        workerThread_ = std::thread(&Core::process, this);
    }
    Core::~Core(){
        {
        std::lock_guard<std::mutex> lock(queueMutex_);
        stopFlag_ = true;
        }
        condition_.notify_all();
        if (workerThread_.joinable()) {
            workerThread_.join();
        } 
    }
    void Core::process() {
        bool running = true;
        while (running) {
            if (running){
                std::unique_lock<std::mutex> lock(queueMutex_);
                condition_.wait(lock, [this]() { 
                    return !queueEvent_.empty() || stopFlag_; 
                });
                if (stopFlag_ && queueEvent_.empty()) {
                    running = false;
                } else {
                    while (!queueEvent_.empty()) {
                        Core::event ev = queueEvent_.front();
                        queueEvent_.pop();
                        lock.unlock();
                        FILE* stream;
                        const char* eventLevel;
                        switch (ev.eLevel)
                        {
                        case Core::EVENT_LEVEL::INFO:
                            stream = stdout;
                            eventLevel = "INFO";
                            break;
                        case Core::EVENT_LEVEL::WARN:
                            stream = stdout;
                            eventLevel = "WARN";
                            break;
                        case Core::EVENT_LEVEL::ERROR:
                            stream = stderr;
                            eventLevel = "ERROR";
                            break;
                        case Core::EVENT_LEVEL::FATAL:
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
                        if (ev.lLevel == LOGGER_LEVEL::DEBUG){
                            fprintf(stream,"[%s | %s ][DEBUG] %s\n",ev.loggerName.c_str(), eventLevel, ev.msg.c_str());
                        } else {
                            fprintf(stream,"[%s | %s ] %s\n",ev.loggerName.c_str(), eventLevel, ev.msg.c_str());
                        }
                        lock.lock();
                    }
                }
            }
        }
        return;
    }

    void Core::log(EVENT_LEVEL eLevel, const std::string msg, LOGGER_LEVEL lLevel, const std::string loggerName){
        {
            std::lock_guard<std::mutex> lock(queueMutex_);
            queueEvent_.push(Core::event{eLevel, msg, lLevel, loggerName});
        }
        condition_.notify_one();
        return;
    }
    void Core::log(EVENT_LEVEL eLevel, const std::string msg, const std::string loggerName){   
        this->log(eLevel, msg, LOGGER_LEVEL::PRODUCTION, loggerName);
        return;
    }



}