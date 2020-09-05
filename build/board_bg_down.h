
//{{BLOCK(board_bg_down)

//======================================================================
//
//	board_bg_down, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 33 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 2112 + 2048 = 4672
//
//	Time-stamp: 2020-09-06, 00:00:55
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.16
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BOARD_BG_DOWN_H
#define GRIT_BOARD_BG_DOWN_H

#define board_bg_downTilesLen 2112
extern const unsigned int board_bg_downTiles[528];

#define board_bg_downMapLen 2048
extern const unsigned short board_bg_downMap[1024];

#define board_bg_downPalLen 512
extern const unsigned short board_bg_downPal[256];

#endif // GRIT_BOARD_BG_DOWN_H

//}}BLOCK(board_bg_down)
