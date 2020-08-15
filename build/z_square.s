
@{{BLOCK(z_square)

@=======================================================================
@
@	z_square, 16x16@8, 
@	Transparent color : 00,00,00
@	+ palette 8 entries, not compressed
@	+ 4 tiles not compressed
@	Total size: 16 + 256 = 272
@
@	Time-stamp: 2020-08-09, 18:13:12
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.16
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global z_squareTiles		@ 256 unsigned chars
	.hidden z_squareTiles
z_squareTiles:
	.word 0x04040404,0x04040404,0x04040404,0x04040404,0x01010404,0x01010101,0x03020404,0x03030303
	.word 0x03020404,0x03030303,0x03020404,0x03030303,0x03020404,0x03030303,0x03020404,0x03030303
	.word 0x04040404,0x04040404,0x04040404,0x04040404,0x01010101,0x04040101,0x03030303,0x04040103
	.word 0x03030303,0x04040103,0x03030303,0x04040103,0x03030303,0x04040103,0x03030303,0x04040103
	.word 0x03020404,0x03030303,0x03020404,0x03030303,0x03020404,0x03030303,0x03020404,0x03030303
	.word 0x03020404,0x03030303,0x02020404,0x02020202,0x04040404,0x04040404,0x04040404,0x04040404
	.word 0x03030303,0x04040103,0x03030303,0x04040103,0x03030303,0x04040103,0x03030303,0x04040103
	.word 0x03030303,0x04040103,0x02020202,0x04040102,0x04040404,0x04040404,0x04040404,0x04040404

	.section .rodata
	.align	2
	.global z_squarePal		@ 16 unsigned chars
	.hidden z_squarePal
z_squarePal:
	.hword 0x0000,0x128B,0x2F72,0x1AED,0x0401,0x0000,0x0000,0x0000

@}}BLOCK(z_square)
