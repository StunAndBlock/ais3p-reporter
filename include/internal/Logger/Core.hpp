#ifndef LOGGER_CORE_HPP
#define LOGGER_CORE_HPP

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include "internal/Error/Error.hpp"
#include <unordered_map>
#include "internal/Utils/Utils.hpp"

namespace logger {

class Core {
    public:
        Core();
        ~Core();
        enum class EVENT_LEVEL {
            INFO,
            WARN,
            ERROR,
            FATAL
        };
        enum class LOGGER_LEVEL {
            STARTUP,
            DEBUG,
            DEVELOPMENT,
            PRODUCTION
        };    
        void log(EVENT_LEVEL, const std::string, LOGGER_LEVEL, const std::string);
        void log(EVENT_LEVEL, const std::string, const std::string);
        void setLevel(const std::string&);
    private:
        struct event{
            const EVENT_LEVEL eLevel;
            const std::string msg;
            const LOGGER_LEVEL lLevel;
            const std::string loggerName;
        };

        std::queue<struct event> queueEvent_;
        std::mutex queueMutex_;
        std::condition_variable condition_;
        std::atomic<bool> stopFlag_{false};
        std::thread workerThread_;
        // std::unordered_map<std::string, LOGGER_LEVEL> levelMap_;
        // LOGGER_LEVEL level_;
        // const char *levelRepr_;
        void process();

};

}
#endif //!LOGGER_CORE_HPP