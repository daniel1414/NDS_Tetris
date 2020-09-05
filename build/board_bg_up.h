
//{{BLOCK(board_bg_up)

//======================================================================
//
//	board_bg_up, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 47 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 3008 + 2048 = 5568
//
//	Time-stamp: 2020-09-06, 00:00:55
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.16
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BOARD_BG_UP_H
#define GRIT_BOARD_BG_UP_H

#define board_bg_upTilesLen 3008
extern const unsigned int board_bg_upTiles[752];

#define board_bg_upMapLen 2048
extern const unsigned short board_bg_upMap[1024];

#define board_bg_upPalLen 512
extern const unsigned short board_bg_upPal[256];

#endif // GRIT_BOARD_BG_UP_H

//}}BLOCK(board_bg_up)
