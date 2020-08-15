
@{{BLOCK(o_square)

@=======================================================================
@
@	o_square, 16x16@8, 
@	Transparent color : 00,00,00
@	+ palette 8 entries, not compressed
@	+ 4 tiles not compressed
@	Total size: 16 + 256 = 272
@
@	Time-stamp: 2020-08-08, 19:13:29
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.16
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global o_squareTiles		@ 256 unsigned chars
	.hidden o_squareTiles
o_squareTiles:
	.word 0x04040404,0x04040404,0x04040404,0x04040404,0x03030404,0x03030303,0x02030404,0x02020202
	.word 0x02030404,0x02020202,0x02030404,0x02020202,0x02030404,0x02020202,0x02030404,0x02020202
	.word 0x04040404,0x04040404,0x04040404,0x04040404,0x03030303,0x04040103,0x02020202,0x04040102
	.word 0x02020202,0x04040102,0x02020202,0x04040102,0x02020202,0x04040102,0x02020202,0x04040102
	.word 0x02030404,0x02020202,0x02030404,0x02020202,0x02030404,0x02020202,0x02030404,0x02020202
	.word 0x02030404,0x02020202,0x01010404,0x01010101,0x04040404,0x04040404,0x04040404,0x04040404
	.word 0x02020202,0x04040102,0x02020202,0x04040102,0x02020202,0x04040102,0x02020202,0x04040102
	.word 0x02020202,0x04040102,0x01010101,0x04040101,0x04040404,0x04040404,0x04040404,0x04040404

	.section .rodata
	.align	2
	.global o_squarePal		@ 16 unsigned chars
	.hidden o_squarePal
o_squarePal:
	.hword 0x0000,0x5A65,0x732B,0x7773,0x0400,0x0000,0x0000,0x0000

@}}BLOCK(o_square)
