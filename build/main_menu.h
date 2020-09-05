
//{{BLOCK(main_menu)

//======================================================================
//
//	main_menu, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 236 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 15104 + 2048 = 17664
//
//	Time-stamp: 2020-09-06, 00:00:57
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.16
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MAIN_MENU_H
#define GRIT_MAIN_MENU_H

#define main_menuTilesLen 15104
extern const unsigned int main_menuTiles[3776];

#define main_menuMapLen 2048
extern const unsigned short main_menuMap[1024];

#define main_menuPalLen 512
extern const unsigned short main_menuPal[256];

#endif // GRIT_MAIN_MENU_H

//}}BLOCK(main_menu)
