
@{{BLOCK(j_square)

@=======================================================================
@
@	j_square, 16x16@8, 
@	Transparent color : 00,00,00
@	+ palette 8 entries, not compressed
@	+ 4 tiles not compressed
@	Total size: 16 + 256 = 272
@
@	Time-stamp: 2020-08-08, 19:13:28
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.16
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global j_squareTiles		@ 256 unsigned chars
	.hidden j_squareTiles
j_squareTiles:
	.word 0x04040404,0x04040404,0x04040404,0x04040404,0x02010404,0x02020202,0x03010404,0x03030303
	.word 0x03010404,0x03030303,0x03010404,0x03030303,0x03010404,0x03030303,0x03010404,0x03030303
	.word 0x04040404,0x04040404,0x04040404,0x04040404,0x02020202,0x04040202,0x03030303,0x04040203
	.word 0x03030303,0x04040203,0x03030303,0x04040203,0x03030303,0x04040203,0x03030303,0x04040203
	.word 0x03010404,0x03030303,0x03010404,0x03030303,0x03010404,0x03030303,0x03010404,0x03030303
	.word 0x03010404,0x03030303,0x01010404,0x01010101,0x04040404,0x04040404,0x04040404,0x04040404
	.word 0x03030303,0x04040203,0x03030303,0x04040203,0x03030303,0x04040203,0x03030303,0x04040203
	.word 0x03030303,0x04040203,0x01010101,0x04040101,0x04040404,0x04040404,0x04040404,0x04040404

	.section .rodata
	.align	2
	.global j_squarePal		@ 16 unsigned chars
	.hidden j_squarePal
j_squarePal:
	.hword 0x0000,0x448E,0x6DB7,0x58F2,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(j_square)
