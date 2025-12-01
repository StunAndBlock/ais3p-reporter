#ifndef LOGGER_HPP_
#define LOGGER_HPP_
// #include <thread>
// #include <queue>
// #include <mutex>
// #include <condition_variable>
// #include <atomic>
// #include "internal/Error/Error.hpp"
// #include <unordered_map>
// #include "internal/Utils/Utils.hpp"
#include <vector>
#include "internal/Logger/LoggerChild.hpp"
namespace logger {
    class Logger : public LoggerChild {
        public:
            Logger(Core*, const std::string&, Core::LOGGER_LEVEL);
            Logger(const std::string&, Core::LOGGER_LEVEL);
            Logger(const std::string&);
            ~Logger();
        // void setLevel(const std::string &);
            // LoggerInterface* debug();
            // LoggerChild* named(const std::string&);
    };


}
#endif //! LOGGER_HPP_