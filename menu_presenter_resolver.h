#pragma once

#include "game_menu.h"
#include "menu_builder_table.h"
#include "accessory.h"
#include "device_state.h"

struct menu_presenter* mpres_main(struct menu_builder_table* mbt);

struct menu_presenter* mpres_default(struct menu_builder_table* mbt, u8 i_slot);

struct menu_presenter* mpres_acc(struct menu_builder* mb, struct accessory* acc);

u8 mpres_try_acc(struct menu_builder_table* mbt, struct device_state* dev, u8 i_slot, struct menu_presenter** result);