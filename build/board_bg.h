
//{{BLOCK(board_bg)

//======================================================================
//
//	board_bg, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 4 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 256 + 2048 = 2816
//
//	Time-stamp: 2020-08-08, 14:39:05
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.16
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BOARD_BG_H
#define GRIT_BOARD_BG_H

#define board_bgTilesLen 256
extern const unsigned int board_bgTiles[64];

#define board_bgMapLen 2048
extern const unsigned short board_bgMap[1024];

#define board_bgPalLen 512
extern const unsigned short board_bgPal[256];

#endif // GRIT_BOARD_BG_H

//}}BLOCK(board_bg)
