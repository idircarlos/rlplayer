#ifndef _utils_h_
#define _utils_h_

#include <stdio.h>
#include <stdlib.h>

char* FormatTime(float time) {
    time = time != time ? 0.0f : time; // Check if time is NaN
    int minutes = (int)time / 60;
    int seconds = (int)time % 60;
    char *timeStr = (char*)malloc(10);
    sprintf(timeStr, "  %02d:%02d  ", minutes, seconds);
    return timeStr;
}

#endif // _utils_h_