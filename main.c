#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <libdragon.h>

#include "game_object.h"
#include "device_manager.h"
#include "controller_manager.h"
#include "pinwheel.h"
#include "fps_counter.h"
#include "color_palette.h"
#include "types.h"
#include "math.h"
#include "menu_state.h"
#include "menu_tree.h"
#include "main_menu.h"
#include "console.h"


#define TITLE			"EverPak64"
#define VERSION			"0.1.0.1"

// render pinwheel @ ~15Hz
#define FIFTEEN_FPS		66
// render fps counter @ 0.5Hz
#define HALF_FPS		2000

#define RENDERER		Gx2D
#define BIT_DEPTH		DEPTH_32_BPP

#define BG_COLOR 		BLACK(BIT_DEPTH)
#define BG_TEXT_COLOR	TRANS
#define FG_TEXT_COLOR	LIME(BIT_DEPTH, RENDERER)


// #### TODO MOVE THIS ####
void sleep(unsigned long ms)
{
	unsigned start_ms = get_ticks_ms();

	while (get_ticks_ms() - start_ms < ms);
}
// #### TODO MOVE THIS ####



static inline void update(struct menu_tree* mt)
{
	mt_update(mt);
}



static inline void draw_header(char pinwheel, float fps)
{
	cprintf("(%c) %.1f fps [%s v%s]\n\n", pinwheel, fps, TITLE, VERSION);
}

static inline void draw(struct menu_tree* mt)
{
	mt_draw(mt);
}



static void set_up(void)
{
	/* enable interrupts (on the CPU) */
	init_interrupts();

	/* Initialize peripherals */
	cs_init(RENDERER, BIT_DEPTH);

	controller_init();
}



int main(void)
{
	set_up();

	char pinwheel = 0;
	pw_init(FIFTEEN_FPS, 0, &pinwheel);

	float fps = 0;
	fps_init(HALF_FPS, &fps);

	graphics_set_color(FG_TEXT_COLOR, BG_TEXT_COLOR);

	struct device_state dev = dev_new();
	struct controller_manager* cman = cman_new(&dev);

	struct menu_tree mt = mt_new(&dev, cman);

	while (1)
	{
		pw_update();
		fps_update();

		dev_poll(&dev);
		cman_update(cman);

		update(&mt);

		cs_clear(BG_COLOR);

		draw_header(pinwheel, fps);

		draw(&mt);

		cs_render();
	}

	return 0;
}