#include "internal/Logger/LoggerChild.hpp"


namespace logger {

    LoggerChild::LoggerChild(Core* core, const std::string& name, Core::LOGGER_LEVEL level) : LoggerBase(core, name, level ){
    }

    LoggerDebug LoggerChild::debug(){
        return LoggerDebug(core_, name_, level_);
    }

    LoggerChild LoggerChild::named(const std::string& name){
        return LoggerChild(core_, utils::sformat("%s.%s",name_.c_str(),name.c_str()), level_);
    }
}