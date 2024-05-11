#ifndef INCLUDE_LOGGER_HPP
#define INCLUDE_LOGGER_HPP

#include <iostream>
#include <sstream>

enum class LogLevel{
    ERR = 0,
    WARN = 1,
    INFO = 2,
    DEBUG = 3  
};

/*
file: logs to a file
term: as in terminal, it logs to the terminal
all: it logs in both file and term
*/
struct LogType{
    bool file;
    bool terminal;
};

struct logProperties{
    LogType type;
    LogLevel level;
    std::string text;    
};


class Logger
{
private:
    LogLevel m_logLevel; 
    LogType m_logType;

    logProperties m_info;

public:

    Logger(LogLevel level = LogLevel::DEBUG, bool terminalLog = true, bool fileLog = false);

    void setLogLevel(LogLevel level);

    void setLogType(LogType type);

    
    template<typename... Args>
    void customLog(LogLevel level, const Args&... args)
    {
        std::ostringstream oss;
        // Use initializer list and fold expression to append all arguments to the stringstream
        (oss << ... << args);

        // Output the constructed log message
        m_info.text = oss.str();
        m_info.level = level;
        doLogging(m_info);
    }

private:
    // template <typename T>
    // void logToFile(const T &value);

    // template <typename T>
    // void logToTerminal(const T &value);

    void doLogging(logProperties &info);

};

#endif