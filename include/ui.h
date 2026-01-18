#ifndef UI_H
#define UI_H

#include "../vendor/clay/clay.h"
#include <raylib.h>
#include "app.h"

void UI_Update(void);

Clay_RenderCommandArray UI_Draw(const App *app);

#endif
