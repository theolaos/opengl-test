// #include <string>

enum color
{
    red, green, white, reset
};

const char *getColorTxt(color tcolor);

// no std::endl, uses std::cout
void coloredText(const char *text, color tcolor = color::reset, const bool endLine = false, const bool bReset = true);

// uses std::cout
void cleanupColoredText(const bool endLine = false);

// returns a std::string. use cleanup to return to default color
std::string colorText(const char *txt, color tcolor, bool cleanup = false);