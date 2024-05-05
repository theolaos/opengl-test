// for logging
#include <iostream> 
#include "colortxt.h"


const char *getColorTxt(color tcolor){
    switch (tcolor)
    {
    case red:
        return "\033[38;2;255;0;0m";
        break;
    
    case green:
        return "\033[38;2;0;255;0m";
        break;

    case white:
        return "\033[38;2;255;255;255m";
        break;

    default:
        return "\033[0m";
        break;
    }
}

// no std::endl
void coloredText(const char *text, color tcolor, const bool endLine, const bool bReset)
{
    const char *tclr = getColorTxt(tcolor);

    std::cout << tclr << text;
    if (bReset){
        std::cout << getColorTxt(reset);
    }

    if (endLine) {
        std::cout << std::endl;
    }
}

void cleanupColoredText(const bool endLine)
{
    std::cout << getColorTxt(reset);
    if (endLine) {
        std::cout << std::endl;
    }
}