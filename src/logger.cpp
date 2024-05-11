#include <iostream>
#include <sstream>
#include "logger.hpp"
#include "colortxt.hpp"

struct loggerTermText
{
    color text_color;
    std::string typeText;  
};


static loggerTermText getColorLogLevel(LogLevel level)
{
    loggerTermText termText;

    switch (level)
    {
    case LogLevel::ERR:
        termText.text_color = color::red;
        termText.typeText = "[ERROR] ";
        break;
    
    case LogLevel::WARN:
        termText.text_color = color::yellow;
        termText.typeText = "[WARNING] ";
        break;

    case LogLevel::INFO:
        termText.text_color = color::light_blue;
        termText.typeText = "[INFO] ";
        break;
    
    case LogLevel::DEBUG:
        termText.text_color = color::white;
        termText.typeText = "[DEBUG] ";
        break;

    default:
        break;
    }

    return termText;
}


// public functions
// Logger Logger::operator<<(){

// }

Logger::Logger(LogLevel level, bool terminalLog, bool fileLog)
{
    m_logLevel = level;
    m_info.type.terminal = terminalLog;
    m_info.type.file = fileLog;
}



void Logger::setLogLevel(LogLevel level)
{
    m_logLevel = level;
}


void Logger::setLogType(LogType type)
{
    m_logType = type;
}


// private functions
void Logger::doLogging(logProperties &info)
{
    loggerTermText logPrefix = getColorLogLevel(info.level); 

    if (info.type.terminal){
        // just do the did in the terminal
        std::cout << colorText( logPrefix.typeText, logPrefix.text_color, true) << info.text << std::endl;
    }

    if (info.type.file){
        // just use the logPrefix.typeText
    }

}
