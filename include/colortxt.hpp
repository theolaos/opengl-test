#ifndef INCLUDE_COLORTXT_HPP
#define INCLUDE_COLORTXT_HPP

// #include <string>

enum class color
{
    red, green, white, yellow, light_blue, orange, 
    reset
};

const char *getColorTxt(color tcolor);

// no std::endl, uses std::cout
void coloredText(const char *text, color tcolor = color::reset, const bool endLine = false, const bool bReset = true);

// uses std::cout
void cleanupColoredText(const bool endLine = false);

// returns a std::string. default is cleanup to return to default color
std::string colorText(const std::string &txt, color tcolor, bool cleanup = true);

#endif