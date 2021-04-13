#include "memory_pak.h"

#include <stdlib.h>
#include <string.h>


static void mpk_update(struct game_object* go);

const struct _go_vtable MPK[] = { { mpk_update } };


struct memory_pak* mpk_new(u8 i_slot)
{
	struct memory_pak* mpk = malloc(sizeof * mpk);

	_acc_init(&mpk->base, MPK, i_slot);

	mpk->base.type = ACCESSORY_MEMPAK;

	return mpk;
}


static void mpk_update(struct game_object* go)
{
	go->_base->_vtable->update(go);
}


void mpk_format(struct memory_pak* mpk)
{
	// TODO convert this to signal an acc_update
	//		rather than doing it directly here.
	format_mempak(mpk->base.i_slot);
	mpk_update((struct game_object*)mpk);
}
