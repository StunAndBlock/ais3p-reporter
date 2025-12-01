#include "internal/Logger/LoggerBase.hpp"

namespace logger {
    LoggerBase::LoggerBase(Core* core, const std::string& name, Core::LOGGER_LEVEL level){
        // levelMap_ = {
        //     {"PRODUCTION", LEVEL::PRODUCTION},
        //     {"DEVELOPMENT",LEVEL::DEVELOPMENT},
        //     {"DEBUG", LEVEL::DEBUG}
        // };
        // level_ = LEVEL::STARTUP;
        // levelRepr_ = "STARTUP";
        core_ = core;
        name_ = name;
        level_ = level;
        // workerThread_ = std::thread(&Logger::process, this);
    }


    void LoggerBase::info(const std::string& msg) {
        core_->log(Core::EVENT_LEVEL::INFO, msg, name_);
        return;
    }

    void LoggerBase::warn(const std::string& msg) {
        core_->log(Core::EVENT_LEVEL::WARN, msg, name_);
        return;
    }

    void LoggerBase::error(const std::string& msg) {
        core_->log(Core::EVENT_LEVEL::ERROR, msg, name_);
        return;
    }
    void LoggerBase::error(const error::error& err) {
        core_->log(Core::EVENT_LEVEL::ERROR, err.msg(), name_);
        return;
    }

    void LoggerBase::fatal(const std::string& msg) {
        core_->log(Core::EVENT_LEVEL::FATAL, msg, name_);
        return;
    }

    void LoggerBase::fatal(const error::error& err) {
        core_->log(Core::EVENT_LEVEL::FATAL, err.msg(), name_);
        return;
    }
}