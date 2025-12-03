
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
        Logger temp(other);
        std::swap(*this, temp); 
        return *this;        
    }



} // namespace logger