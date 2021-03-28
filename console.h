#pragma once

#include <libdragon.h>

#include "types.h"
#include "renderer.h"

#define BUFFER_LEN 128

#define cs_printfln(c, ...) { \
	sprintf(c.buf, __VA_ARGS__); \
	cs_println(&c); \
}

struct console_context
{
	display_context_t dc;
	u8 c;
	u8 r;

	char buf[BUFFER_LEN];
};

struct console_context cs_init(enum renderer r, bitdepth_t d);

void cs_clear(struct console_context* cc, uint32_t bg_color);

void cs_println(struct console_context* cc);

void cs_render(struct console_context* cc);