/*
	Russian Roulette
	Copyright (C) 2016-2017, NamelessGhoul0

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <psp2/ctrl.h>
#include <psp2/display.h>
#include <psp2/kernel/processmgr.h>
#include <vita2d.h>

#include "audio.h"

#define BLACK   RGBA8(0, 0, 0, 255)
#define WHITE	RGBA8(255, 255, 255, 255)
#define RED		RGBA8(255, 0, 0, 255)

/*
	TODO:
	- Make Menu
	- Add sounds and maybe some chill background music
	- Some animations, blood, etc when the game is over
	- Fix audio loop
*/

struct {
	int bullet_pos;
	int barrel_pos;
} game;

void gen_bullet_pos() {
	// generate random number 1-6
	srand(time(0));
	game.bullet_pos = (rand() % 6 + 1);
}

void gen_barrel_pos() {
	srand(time(0));
	game.barrel_pos = (rand() % 6 + 1);
}

int main(void) {
	SceCtrlData ctrl;
	vita2d_pgf *pgf;
	int game_played_once = 0;

	// init
	vita2d_init();
	vita2d_set_clear_color(BLACK);
	pgf = vita2d_load_default_pgf();
	audio_init();

	gen_bullet_pos();

	while (1) {
		sceCtrlPeekBufferPositive(0, &ctrl, 1);

		// start render
		vita2d_start_drawing();
		vita2d_clear_screen();

		if (ctrl.buttons & SCE_CTRL_CROSS) {
			gen_barrel_pos();
			game_played_once = 1;
		}

		vita2d_pgf_draw_textf(pgf, 100, 100, WHITE, 1.0f, "bullet_pos = %d", game.bullet_pos);
		vita2d_pgf_draw_textf(pgf, 100, 130, WHITE, 1.0f, "barrel_pos = %d", game.barrel_pos);

		if (game.bullet_pos == game.barrel_pos) {
			play_gunshot();
			vita2d_pgf_draw_textf(pgf, 100, 160, RED, 1.0f, "YOU ARE DEAD");
		} else if (game_played_once == 1) {
			vita2d_pgf_draw_textf(pgf, 100, 160, RED, 1.0f, "You live to see another day. Try again?");
		}

		// end render
		vita2d_end_drawing();
		vita2d_swap_buffers();
		sceDisplayWaitVblankStart();
	}

	vita2d_fini();
	sceKernelExitProcess(0);

    return 0;
}
