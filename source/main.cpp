#include <stdio.h>
#include <nds.h>
#include <nds/arm9/sprite.h>
#include <nds/system.h>
#include <nds/arm9/keyboard.h>
#include <nds/arm9/background.h>
#include <nds/timers.h>

#include <vector>

#include "TetrisTile.h"
#include "Square.h"
#include "Board.h"

#include "i_square.h"
#include "o_square.h"

bool waiting_tim_0 = false;
u16 waiting_ticks_0 = 20000;
void timer_callback();

int main(void) {

	videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);
	vramSetBankA(VRAM_A_MAIN_SPRITE);
	vramSetBankB(VRAM_B_MAIN_BG_0x06000000);
	vramSetBankC(VRAM_C_SUB_BG_0x06200000);
	vramSetBankD(VRAM_D_SUB_SPRITE);
	oamInit(&oamMain, SpriteMapping_1D_128, false);
	oamInit(&oamSub, SpriteMapping_1D_128, false);
	lcdMainOnBottom();
	timerStart(0, ClockDivider_1024, 65535 - waiting_ticks_0, timer_callback);

	Board b;
	/*TetrisTile I(0, 0, TILE_TYPE::TILE_I);
	TetrisTile J(0, 4, TILE_TYPE::TILE_J);
	TetrisTile L(0, 8, TILE_TYPE::TILE_L);
	TetrisTile S(4, 0, TILE_TYPE::TILE_S);
	TetrisTile Z(4, 4, TILE_TYPE::TILE_Z);
	TetrisTile O(4, 8, TILE_TYPE::TILE_O); */

	int keys_down;
	int keys_held;
	while(1) {
		waiting_tim_0 = true;
		timerStart(0, ClockDivider_1024, 65535 - waiting_ticks_0, timer_callback);
		while (waiting_tim_0)
		{
			scanKeys();
			keys_down = keysDown();
			keys_held = keysHeld();
			b.process_input(keys_down, keys_held);

			swiWaitForVBlank();
			oamUpdate(&oamSub);
			oamUpdate(&oamMain);
		}
		b.fall_cur_tile();
	}
	return 0;
}

void timer_callback()
{
	waiting_tim_0 = false;
	if (waiting_ticks_0 > 5000) {
		waiting_ticks_0 -= 100;
	}
}