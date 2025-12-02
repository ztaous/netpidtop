#ifndef UI_H
#define UI_H

#include "common.h"

void ui_init(void);
void ui_display_connections(connection_t *connections, int count);
int ui_handle_input(void);
void ui_cleanup(void);

#endif // UI_H