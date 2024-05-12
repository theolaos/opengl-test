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


// From what level and above should the logger inform to you.
Logger::Logger(LogLevel level, bool terminalLog, bool fileLog)
    :m_logLevel(level), 
     m_logInfo({{terminalLog, fileLog}})
{}


void Logger::setLogLevel(LogLevel level)
{
    m_logLevel = level;
}


void Logger::setLogType(LogType type)
{
    m_logType = type;
}


// private functions
void Logger::doLogging(logProperties &logInfo)
{
    loggerTermText logPrefix = getColorLogLevel(logInfo.level); 

    if ( logInfo.level >= m_logInfo.level ) {
        if ( logInfo.type.terminal ){
            // just do the did in the terminal
            std::cout << colorText( logPrefix.typeText, logPrefix.text_color ) << logInfo.text << std::endl;
        }

        if ( logInfo.type.file ){
            // just use the logPrefix.typeText
            std::cout << colorText( "[WARNING] ", color::yellow ) << "File logging is not implemented yet." << std::endl;
        }
    }

}
