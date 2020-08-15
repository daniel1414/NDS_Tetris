
@{{BLOCK(t_square)

@=======================================================================
@
@	t_square, 16x16@8, 
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
	.global t_squareTiles		@ 256 unsigned chars
	.hidden t_squareTiles
t_squareTiles:
	.word 0x04040404,0x04040404,0x04040404,0x04040404,0x01010404,0x01010101,0x02010404,0x02020202
	.word 0x02010404,0x02020202,0x02010404,0x02020202,0x02010404,0x02020202,0x02010404,0x02020202
	.word 0x04040404,0x04040404,0x04040404,0x04040404,0x01010101,0x04040101,0x02020202,0x04040302
	.word 0x02020202,0x04040302,0x02020202,0x04040302,0x02020202,0x04040302,0x02020202,0x04040302
	.word 0x02010404,0x02020202,0x02010404,0x02020202,0x02010404,0x02020202,0x02010404,0x02020202
	.word 0x02010404,0x02020202,0x03010404,0x03030303,0x04040404,0x04040404,0x04040404,0x04040404
	.word 0x02020202,0x04040302,0x02020202,0x04040302,0x02020202,0x04040302,0x02020202,0x04040302
	.word 0x02020202,0x04040302,0x03030303,0x04040303,0x04040404,0x04040404,0x04040404,0x04040404

	.section .rodata
	.align	2
	.global t_squarePal		@ 16 unsigned chars
	.hidden t_squarePal
t_squarePal:
	.hword 0x0000,0x45CA,0x5AB3,0x7779,0x0001,0x0000,0x0000,0x0000

@}}BLOCK(t_square)
