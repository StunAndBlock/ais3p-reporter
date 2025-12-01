#include "internal/Logger/LoggerDebug.hpp"

namespace logger {
   LoggerDebug::LoggerDebug(Core* core, const std::string& name, Core::LOGGER_LEVEL level) : LoggerBase(core, name, level){
   };


    void LoggerDebug::info(const std::string& msg) {
        if (Core::LOGGER_LEVEL::DEBUG >= level_){
            core_->log(Core::EVENT_LEVEL::INFO, msg, Core::LOGGER_LEVEL::DEBUG, name_);
        } 
        return;
    }

    void LoggerDebug::warn(const std::string& msg) {
        if (Core::LOGGER_LEVEL::DEBUG >= level_){
            core_->log(Core::EVENT_LEVEL::WARN, msg, Core::LOGGER_LEVEL::DEBUG, name_);
        } 
        return;
    }

    void LoggerDebug::error(const std::string& msg) {
        if (Core::LOGGER_LEVEL::DEBUG >= level_){
            core_->log(Core::EVENT_LEVEL::ERROR, msg, Core::LOGGER_LEVEL::DEBUG, name_);
        }

        return;
    }

    void LoggerDebug::error(const error::error& err) {
        if (Core::LOGGER_LEVEL::DEBUG >= level_){
            core_->log(Core::EVENT_LEVEL::ERROR, err.msg(), Core::LOGGER_LEVEL::DEBUG, name_);
        } 
        return;
    }

    void LoggerDebug::fatal(const std::string& msg) {
        if (Core::LOGGER_LEVEL::DEBUG >= level_){
            core_->log(Core::EVENT_LEVEL::INFO, msg, Core::LOGGER_LEVEL::DEBUG, name_);
        }
        return;
    }

    void LoggerDebug::fatal(const error::error& err) {
        if (Core::LOGGER_LEVEL::DEBUG >= level_){
            core_->log(Core::EVENT_LEVEL::INFO, err.msg(), Core::LOGGER_LEVEL::DEBUG, name_);
        }
        return;
    }
}