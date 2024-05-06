// for logging
#include <iostream> 
#include "colortxt.h"


const char *getColorTxt(color tcolor){
    switch (tcolor)
    {
    case color::red:
        return "\033[38;2;255;0;0m";
        break;
    
    case color::green:
        return "\033[38;2;0;255;0m";
        break;

    case color::white:
        return "\033[38;2;255;255;255m";
        break;

    default:
        return "\033[0m";
        break;
    }
}


void coloredText(const char *text, color tcolor, const bool endLine, const bool bReset)
{
    const char *tclr = getColorTxt(tcolor);

    std::cout << tclr << text;
    if (bReset){
        std::cout << getColorTxt(color::reset);
    }

    if (endLine) {
        std::cout << std::endl;
    }
}

void cleanupColoredText(const bool endLine)
{
    std::cout << getColorTxt(color::reset);
    if (endLine) {
        std::cout << std::endl;
    }
}

std::string colorText(const char *txt, color tcolor, bool cleanup)
{
    std::string text = txt;

    std::string tc = getColorTxt(tcolor);

    std::string reset = "";
    if (cleanup) {
        reset = getColorTxt(color::reset);
    }

    return  tc + text + reset; 
}