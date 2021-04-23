#include "game_menu.h"

#include "math.h"
#include "console.h"


static void gm_update(struct game_object* go);

const struct _go_vtable GM[] = { { gm_update } };


void _gm_init(struct game_menu* gm, const struct _go_vtable* vtable, struct device_state* dev, struct menu_state* ms)
{
	_go_init(&gm->go, vtable, GM);

	gm->go.can_update = 1;
	gm->go.can_draw = 1;

	gm->dev = dev;
	gm->ms = ms;
}

struct game_menu* gm_new(struct menu_state* ms, struct device_state* dev)
{
	struct game_menu* gm = malloc(sizeof * gm);

	gm->go._vtable = GM;

	gm->ms = ms;
	gm->dev = dev;

	return gm;
}

void _gm_hover_prev(struct game_menu* gm)
{
	gm->i_hovered_item = cmod(gm->i_hovered_item - 1, gm->n_items);
}

void _gm_hover_next(struct game_menu* gm)
{
	gm->i_hovered_item = cmod(gm->i_hovered_item + 1, gm->n_items);
}

void _gm_draw_header(struct accessory acc)
{
	u8 sn = acc.i_slot + 1;
	char* acc_name = accessory_names[acc.type];

	cprintf("Controller %u [%s]", sn, acc_name);
	cprintf("Back (B)");
}


static void gm_update(struct game_object* go)
{

}