#ifndef LOGGER_LOGGERCHILD_HPP_
#define LOGGER_LOGGERCHILD_HPP_

#include "internal/Logger/LoggerBase.hpp"
#include "internal/Logger/LoggerDebug.hpp"
#include "internal/Utils/Utils.hpp"
namespace logger {
    class LoggerChild : public LoggerBase {
        public:
            LoggerChild(Core*, const std::string&, Core::LOGGER_LEVEL);
            ~LoggerChild() = default;
            // void setLevel(const std::string &);
            LoggerDebug debug();
            LoggerChild named(const std::string&);
    };


}
#endif //!LOGGER_LOGGERCHILD_HPP_