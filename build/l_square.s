
@{{BLOCK(l_square)

@=======================================================================
@
@	l_square, 16x16@8, 
@	Transparent color : 00,00,00
@	+ palette 8 entries, not compressed
@	+ 4 tiles not compressed
@	Total size: 16 + 256 = 272
@
@	Time-stamp: 2020-09-06, 00:00:57
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.16
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global l_squareTiles		@ 256 unsigned chars
	.hidden l_squareTiles
l_squareTiles:
	.word 0x04040404,0x04040404,0x04040404,0x04040404,0x02020404,0x02020202,0x03020404,0x03030303
	.word 0x03020404,0x03030303,0x03020404,0x03030303,0x03020404,0x03030303,0x03020404,0x03030303
	.word 0x04040404,0x04040404,0x04040404,0x04040404,0x02020202,0x04040102,0x03030303,0x04040103
	.word 0x03030303,0x04040103,0x03030303,0x04040103,0x03030303,0x04040103,0x03030303,0x04040103
	.word 0x03020404,0x03030303,0x03020404,0x03030303,0x03020404,0x03030303,0x03020404,0x03030303
	.word 0x03020404,0x03030303,0x01010404,0x01010101,0x04040404,0x04040404,0x04040404,0x04040404
	.word 0x03030303,0x04040103,0x03030303,0x04040103,0x03030303,0x04040103,0x03030303,0x04040103
	.word 0x03030303,0x04040103,0x01010101,0x04040101,0x04040404,0x04040404,0x04040404,0x04040404

	.section .rodata
	.align	2
	.global l_squarePal		@ 16 unsigned chars
	.hidden l_squarePal
l_squarePal:
	.hword 0x0000,0x0674,0x3BBE,0x1719,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(l_square)
