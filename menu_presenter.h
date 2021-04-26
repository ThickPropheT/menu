#pragma once

#include "game_menu.h"

struct menu_presenter
{
	const struct mp_type* mp_type;

	struct game_menu* gm;
};

struct mp_type
{
	void (*entering)(struct menu_presenter* mp);
	void (*leaving)(struct menu_presenter* mp);
};

struct menu_presenter* mp_new(struct game_menu* gm);

static inline void mp_entering(struct menu_presenter* mp)
{
	void (*entering)(struct menu_presenter*) = mp->mp_type->entering;

	if (entering == NULL)
		return;

	entering(mp);
}

static inline void mp_leaving(struct menu_presenter* mp)
{
	void (*leaving)(struct menu_presenter*) = mp->mp_type->leaving;

	if (leaving == NULL)
		return;

	leaving(mp);
}

void mp_free(struct menu_presenter* mp);