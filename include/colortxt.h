enum color
{
    red, green, white, reset
};

const char *getColorTxt(color tcolor);

void coloredText(const char *text, color tcolor = reset, const bool endLine = false, const bool bReset = true);

void cleanupColoredText(const bool endLine = false);
