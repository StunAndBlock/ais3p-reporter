#ifndef LOGGER_HPP_
#define LOGGER_HPP_
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include "internal/Error/Error.hpp"
#include <unordered_map>
#include "internal/Utils/Utils.hpp"
class ILogger
{
public:
    virtual ~ILogger() = default;
    virtual void info(const std::string &) = 0;
    virtual void warn(const std::string &) = 0;
    virtual void error(const std::string &) = 0;
    virtual void error(const error::error &) = 0;
    virtual void fatal(const std::string &) = 0;
    virtual void fatal(const error::error &) = 0;
};

class LoggerDebug : public ILogger
{
public:
    explicit LoggerDebug(ILogger *, bool);
    void info(const std::string &) override;
    void warn(const std::string &) override;
    void error(const std::string &) override;
    void error(const error::error &) override;
    void fatal(const std::string &) override;
    void fatal(const error::error &) override;

private:
    ILogger *logger_;
    bool allowed_;
};

class Logger : public ILogger
{
public:
    Logger();
    ~Logger();
    void setLevel(const std::string &);
    void error(const std::string &) override;
    void error(const error::error &) override;
    void warn(const std::string &) override;
    void info(const std::string &) override;
    void fatal(const std::string &) override;
    void fatal(const error::error &) override;
    LoggerDebug debug();

private:
    std::string name_;
    struct event
    {
        enum class LEVEL
        {
            INFO,
            WARN,
            ERROR,
            FATAL
        };
        const LEVEL level;
        const std::string msg;
    };
    enum class LEVEL
    {
        STARTUP,
        DEBUG,
        DEVELOPMENT,
        PRODUCTION
    };
    std::queue<struct event> queueEvent_;
    std::mutex queueMutex_;
    std::condition_variable condition_;
    std::atomic<bool> stopFlag_{false};
    std::thread workerThread_;
    std::unordered_map<std::string, LEVEL> levelMap_;
    LEVEL level_;
    const char *levelRepr_;
    // mutable std::mutex levelMutex_;
    void log(const struct event);
    void process();
};

#endif //! LOGGER_HPP_