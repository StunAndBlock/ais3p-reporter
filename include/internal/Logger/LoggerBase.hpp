#ifndef LOGGER_BASELOGGER_HPP
#define LOGGER_BASELOGGER_HPP



#include "internal/Logger/Core.hpp"
#include "internal/Logger/LoggerInterface.hpp"



namespace logger {
    class LoggerBase : public LoggerInterface {
        public:
            LoggerBase(Core*, const std::string&, Core::LOGGER_LEVEL);
            ~LoggerBase() = default;
            //void setLevel(const std::string &);
            void error(const std::string &) override;
            void error(const error::error &) override;
            void warn(const std::string &) override;
            void info(const std::string &) override;
            void fatal(const std::string &) override;
            void fatal(const error::error &) override;
        protected:    
            Core* core_;
            std::string name_;
            Core::LOGGER_LEVEL level_;
    };
}
















#endif //!LOGGER_BASELOGGER_HPP