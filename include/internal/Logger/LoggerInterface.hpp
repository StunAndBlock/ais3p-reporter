#ifndef LOGGER_INTERFACE_HPP
#define LOGGER_INTERFACE_HPP
#include "internal/Error/Error.hpp"

namespace logger {
    class LoggerInterface {
    public:
        virtual ~LoggerInterface() = default;
        virtual void info(const std::string&) = 0;
        virtual void warn(const std::string&) = 0;
        virtual void error(const std::string&) = 0;
        virtual void error(const error::error&) = 0;
        virtual void fatal(const std::string&) = 0;
        virtual void fatal(const error::error&) = 0;
    };

}



#endif //!LOGGER_INTERFACE_HPP