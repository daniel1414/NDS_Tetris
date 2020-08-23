
@{{BLOCK(menu_cursor)

@=======================================================================
@
@	menu_cursor, 16x16@8, 
@	Transparent color : 00,00,00
@	+ palette 8 entries, not compressed
@	+ 4 tiles not compressed
@	Total size: 16 + 256 = 272
@
@	Time-stamp: 2020-08-23, 16:00:45
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.16
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global menu_cursorTiles		@ 256 unsigned chars
	.hidden menu_cursorTiles
menu_cursorTiles:
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x01010100,0x00000000,0x01010101
	.word 0x01000000,0x02020101,0x01010000,0x02020201,0x01010000,0x02020202,0x01010000,0x02020202
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00010101,0x00000000,0x01010101,0x00000000
	.word 0x01010202,0x00000001,0x01020202,0x00000101,0x02020202,0x00000101,0x02020202,0x00000101
	.word 0x01010000,0x02020202,0x01010000,0x02020202,0x01010000,0x02020201,0x01000000,0x02020101
	.word 0x00000000,0x01010101,0x00000000,0x01010100,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x02020202,0x00000101,0x02020202,0x00000101,0x01020202,0x00000101,0x01010202,0x00000001
	.word 0x01010101,0x00000000,0x00010101,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000

	.section .rodata
	.align	2
	.global menu_cursorPal		@ 16 unsigned chars
	.hidden menu_cursorPal
menu_cursorPal:
	.hword 0x0000,0x4616,0x4E7C,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(menu_cursor)
