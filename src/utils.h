#ifndef _utils_h_
#define _utils_h_

#include <stdio.h>
#include <stdlib.h>

#define VOL_FORMAT  "  %d%%"
#define TIME_FORMAT "  %02d:%02d  "
#define NO_TIME_FORMAT "  --:--  "

char *FormatVolume(float percentage, char *formatted) {
    sprintf(formatted, VOL_FORMAT, (int)(100*percentage));
    return formatted;
}

char *FormatTime(float time, char *formatted) {
    if (time < 0) {
        sprintf(formatted, NO_TIME_FORMAT);
    }
    else {
        int minutes = (int)time / 60;
        int seconds = (int)time % 60;
        sprintf(formatted, TIME_FORMAT, minutes, seconds);
    }
    return formatted;
}

#endif // _utils_h_