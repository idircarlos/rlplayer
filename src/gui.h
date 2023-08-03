#ifndef _gui_h_
#define _gui_h_

#include <raylib.h>
#include <raygui.h>

#define BG_COLOR        GetColor(0x1A1A1AFF)
#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   800
#define APP_NAME        "RLPlayer"


void InitGUI();
void UpdateGUI();

#endif // _gui_h_