#pragma once

#include <stddef.h>

#include "menu_state.h"
#include "root_menu.h"
#include "device_state.h"


// TODO consider converting to enum
// TODO consider renaming to ROOT_MENU
#define ROOT_MENU					0
// TODO consider renaming to SLOT_MENU
#define SLOT_MENU			 		1
#define MAX_MENUS 	SLOT_MENU  + 	1


struct menu_tree
{
	struct device_state* dev;

	struct menu_state* ms;
	struct root_menu* rm;
};


struct menu_tree mt_new(struct device_state* ds);

void mt_update(struct menu_tree* mt);
void mt_draw(struct menu_tree* mt);