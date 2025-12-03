
#include <iostream>
#include <chrono>
#include "internal/Logger/Logger.hpp"

namespace logger
{
    Logger::Logger(Core* core, const std::string& name, Core::LOGGER_LEVEL level) : LoggerChild(core, name, level) {
    }
    Logger::Logger(const std::string& name, Core::LOGGER_LEVEL level) : LoggerChild(nullptr, name, level) {
        core_ = new Core();
    }
    Logger::Logger(const std::string& name) : LoggerChild(nullptr, name, Core::LOGGER_LEVEL::STARTUP) {
        core_ = new Core();
    }
 

    Logger::~Logger(){
        delete core_;
    }

    Logger& Logger::operator=(const Logger& other) {
        if (this != &other){
            delete core_;
            core_ = new Core();
            name_ = other.name_;
            level_ = other.level_;
        }
        return *this;
    }



} // namespace logger