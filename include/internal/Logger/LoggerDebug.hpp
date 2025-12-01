#ifndef LOGGER_LOGGERDEBUG_HPP
#define LOGGER_LOGGERDEBUG_HPP

#include "internal/Logger/LoggerBase.hpp"

namespace logger {
    
    class LoggerDebug : public LoggerBase {
    public:
        LoggerDebug(Core*, const std::string&, Core::LOGGER_LEVEL);
        void info(const std::string&) override;
        void warn(const std::string&) override;
        void error(const std::string&) override;
        void error(const error::error&) override;
        void fatal(const std::string&) override;
        void fatal(const error::error&) override;

    };
}
#endif //!LOGGER_LOGGERDEBUG_HPP




