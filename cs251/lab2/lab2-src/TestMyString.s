	.file	"TestMyString.cc"
gcc2_compiled.:
.section	".rodata"
	.align 8
.LLC0:
	.asciz	"Hello world"
	.align 8
.LLC1:
	.asciz	"%s:%u: failed assertion `%s'\n"
	.align 8
.LLC2:
	.asciz	"TestMyString.cc"
	.align 8
.LLC3:
	.asciz	"!strcmp(ms1.cStr(),s1 )"
	.align 8
.LLC4:
	.asciz	"s1=\"%s\"\n"
	.align 8
.LLC5:
	.asciz	"Test 1 passed\n"
	.global __throw
.section	".text"
	.align 4
	.global test1__Fv
	.type	 test1__Fv,#function
	.proc	020
test1__Fv:
.LLFB1:
	!#PROLOGUE# 0
	save	%sp, -128, %sp
.LLCFI0:
	!#PROLOGUE# 1
	sethi	%hi(.LLC0), %o1
	or	%o1, %lo(.LLC0), %o0
	st	%o0, [%fp-20]
	ld	[%fp-20], %o0
	call	strdup, 0
	 nop
	st	%o0, [%fp-24]
	add	%fp, -32, %o1
	mov	%o1, %o0
	ld	[%fp-24], %o1
	call	__8MyStringPCc, 0
	 nop
.LLEHB3:
	ld	[%fp-24], %o0
	stb	%g0, [%o0]
	add	%fp, -32, %o1
	mov	%o1, %o0
	call	cStr__8MyString, 0
	 nop
	mov	%o0, %o1
	mov	%o1, %o0
	ld	[%fp-20], %o1
	call	strcmp, 0
	 nop
	cmp	%o0, 0
	be	.LL6
	nop
	sethi	%hi(.LLC1), %o1
	or	%o1, %lo(.LLC1), %o0
	sethi	%hi(.LLC2), %o2
	or	%o2, %lo(.LLC2), %o1
	mov	19, %o2
	sethi	%hi(.LLC3), %o4
	or	%o4, %lo(.LLC3), %o3
	call	__eprintf, 0
	 nop
	b	.LL6
	 nop
.LL5:
.LL6:
	add	%fp, -32, %o1
	mov	%o1, %o0
	call	cStr__8MyString, 0
	 nop
	mov	%o0, %o1
	sethi	%hi(.LLC4), %o2
	or	%o2, %lo(.LLC4), %o0
	call	printf, 0
	 nop
	sethi	%hi(.LLC5), %o1
	or	%o1, %lo(.LLC5), %o0
	call	printf, 0
	 nop
.LLEHE3:
	b	.LL7
	 nop
.LL4:
	call	__throw, 0
	 nop
.LL7:
	add	%fp, -32, %o1
	mov	%o1, %o0
	mov	2, %o1
	call	_._8MyString, 0
	 nop
	b	.LL8
	 nop
.LLEHB9:
.LL3:
	add	%fp, -32, %o1
	mov	%o1, %o0
	mov	2, %o1
	call	_._8MyString, 0
	 nop
	b	.LL4
	 nop
.LLEHE9:
	b	.LL9
	 nop
.LL10:
	call	__throw, 0
	 nop
.LL11:
.LL9:
	call	terminate__Fv, 0
	 nop
.LL8:
	b	.LL12
	 nop
	b	.LL2
	 nop
.LL12:
.LL2:
	ret
	restore
.LLFE1:
.LLfe1:
	.size	 test1__Fv,.LLfe1-test1__Fv
.section	".rodata"
	.align 8
.LLC6:
	.asciz	"!strcmp(ms2.cStr(),s1 )"
	.align 8
.LLC7:
	.asciz	"Test 2 passed\n"
.section	".text"
	.align 4
	.global test2__Fv
	.type	 test2__Fv,#function
	.proc	020
test2__Fv:
.LLFB2:
	!#PROLOGUE# 0
	save	%sp, -136, %sp
.LLCFI1:
	!#PROLOGUE# 1
	sethi	%hi(.LLC0), %o1
	or	%o1, %lo(.LLC0), %o0
	st	%o0, [%fp-20]
	ld	[%fp-20], %o0
	call	strdup, 0
	 nop
	st	%o0, [%fp-24]
	add	%fp, -32, %o1
	mov	%o1, %o0
	ld	[%fp-24], %o1
	call	__8MyStringPCc, 0
	 nop
.LLEHB14:
	add	%fp, -40, %o0
	add	%fp, -32, %o1
	call	__8MyStringR8MyString, 0
	 nop
.LLEHB16:
	ld	[%fp-24], %o0
	stb	%g0, [%o0]
	add	%fp, -40, %o1
	mov	%o1, %o0
	call	cStr__8MyString, 0
	 nop
	mov	%o0, %o1
	mov	%o1, %o0
	ld	[%fp-20], %o1
	call	strcmp, 0
	 nop
	cmp	%o0, 0
	be	.LL19
	nop
	sethi	%hi(.LLC1), %o1
	or	%o1, %lo(.LLC1), %o0
	sethi	%hi(.LLC2), %o2
	or	%o2, %lo(.LLC2), %o1
	mov	31, %o2
	sethi	%hi(.LLC6), %o4
	or	%o4, %lo(.LLC6), %o3
	call	__eprintf, 0
	 nop
	b	.LL19
	 nop
.LL18:
.LL19:
	add	%fp, -40, %o1
	mov	%o1, %o0
	call	cStr__8MyString, 0
	 nop
	mov	%o0, %o1
	sethi	%hi(.LLC4), %o2
	or	%o2, %lo(.LLC4), %o0
	call	printf, 0
	 nop
	sethi	%hi(.LLC7), %o1
	or	%o1, %lo(.LLC7), %o0
	call	printf, 0
	 nop
.LLEHE16:
	b	.LL20
	 nop
.LL17:
	call	__throw, 0
	 nop
.LL20:
	add	%fp, -40, %o1
	mov	%o1, %o0
	mov	2, %o1
	call	_._8MyString, 0
	 nop
.LLEHE14:
	b	.LL21
	 nop
.LL15:
	call	__throw, 0
	 nop
.LL21:
	add	%fp, -32, %o1
	mov	%o1, %o0
	mov	2, %o1
	call	_._8MyString, 0
	 nop
	b	.LL22
	 nop
.LLEHB23:
.LL16:
	add	%fp, -40, %o1
	mov	%o1, %o0
	mov	2, %o1
	call	_._8MyString, 0
	 nop
	b	.LL17
	 nop
.LL14:
	add	%fp, -32, %o1
	mov	%o1, %o0
	mov	2, %o1
	call	_._8MyString, 0
	 nop
	b	.LL15
	 nop
.LLEHE23:
	b	.LL23
	 nop
.LL24:
	call	__throw, 0
	 nop
.LL25:
.LL23:
	call	terminate__Fv, 0
	 nop
.LL22:
	b	.LL26
	 nop
	b	.LL13
	 nop
.LL26:
.LL13:
	ret
	restore
.LLFE2:
.LLfe2:
	.size	 test2__Fv,.LLfe2-test2__Fv
.section	".rodata"
	.align 8
.LLC8:
	.asciz	"ms2.length() == strlen(s1)"
	.align 8
.LLC9:
	.asciz	"len=%d\n"
	.align 8
.LLC10:
	.asciz	"Test 3 passed\n"
.section	".text"
	.align 4
	.global test3__Fv
	.type	 test3__Fv,#function
	.proc	020
test3__Fv:
.LLFB3:
	!#PROLOGUE# 0
	save	%sp, -136, %sp
.LLCFI2:
	!#PROLOGUE# 1
	sethi	%hi(.LLC0), %o1
	or	%o1, %lo(.LLC0), %o0
	st	%o0, [%fp-20]
	ld	[%fp-20], %o0
	call	strdup, 0
	 nop
	st	%o0, [%fp-24]
	add	%fp, -32, %o1
	mov	%o1, %o0
	ld	[%fp-24], %o1
	call	__8MyStringPCc, 0
	 nop
.LLEHB28:
	add	%fp, -40, %o0
	add	%fp, -32, %o1
	call	__8MyStringR8MyString, 0
	 nop
.LLEHB30:
	ld	[%fp-24], %o0
	stb	%g0, [%o0]
	add	%fp, -40, %o1
	mov	%o1, %o0
	call	length__8MyString, 0
	 nop
	mov	%o0, %l0
	ld	[%fp-20], %o0
	call	strlen, 0
	 nop
	cmp	%l0, %o0
	be	.LL33
	nop
	sethi	%hi(.LLC1), %o1
	or	%o1, %lo(.LLC1), %o0
	sethi	%hi(.LLC2), %o2
	or	%o2, %lo(.LLC2), %o1
	mov	43, %o2
	sethi	%hi(.LLC8), %o4
	or	%o4, %lo(.LLC8), %o3
	call	__eprintf, 0
	 nop
	b	.LL33
	 nop
.LL32:
.LL33:
	add	%fp, -40, %o1
	mov	%o1, %o0
	call	length__8MyString, 0
	 nop
	mov	%o0, %o1
	sethi	%hi(.LLC9), %o2
	or	%o2, %lo(.LLC9), %o0
	call	printf, 0
	 nop
	sethi	%hi(.LLC10), %o1
	or	%o1, %lo(.LLC10), %o0
	call	printf, 0
	 nop
.LLEHE30:
	b	.LL34
	 nop
.LL31:
	call	__throw, 0
	 nop
.LL34:
	add	%fp, -40, %o1
	mov	%o1, %o0
	mov	2, %o1
	call	_._8MyString, 0
	 nop
.LLEHE28:
	b	.LL35
	 nop
.LL29:
	call	__throw, 0
	 nop
.LL35:
	add	%fp, -32, %o1
	mov	%o1, %o0
	mov	2, %o1
	call	_._8MyString, 0
	 nop
	b	.LL36
	 nop
.LLEHB37:
.LL30:
	add	%fp, -40, %o1
	mov	%o1, %o0
	mov	2, %o1
	call	_._8MyString, 0
	 nop
	b	.LL31
	 nop
.LL28:
	add	%fp, -32, %o1
	mov	%o1, %o0
	mov	2, %o1
	call	_._8MyString, 0
	 nop
	b	.LL29
	 nop
.LLEHE37:
	b	.LL37
	 nop
.LL38:
	call	__throw, 0
	 nop
.LL39:
.LL37:
	call	terminate__Fv, 0
	 nop
.LL36:
	b	.LL40
	 nop
	b	.LL27
	 nop
.LL40:
.LL27:
	ret
	restore
.LLFE3:
.LLfe3:
	.size	 test3__Fv,.LLfe3-test3__Fv
.section	".rodata"
	.align 8
.LLC11:
	.asciz	"ms1.cStr()[0] == 0"
	.align 8
.LLC12:
	.asciz	"str=\"%s\"\n"
	.align 8
.LLC13:
	.asciz	"Test 4 passed\n"
.section	".text"
	.align 4
	.global test4__Fv
	.type	 test4__Fv,#function
	.proc	020
test4__Fv:
.LLFB4:
	!#PROLOGUE# 0
	save	%sp, -120, %sp
.LLCFI3:
	!#PROLOGUE# 1
	add	%fp, -24, %o1
	mov	%o1, %o0
	call	__8MyString, 0
	 nop
.LLEHB42:
	add	%fp, -24, %o1
	mov	%o1, %o0
	call	cStr__8MyString, 0
	 nop
	ldub	[%o0], %o1
	sll	%o1, 24, %o2
	sra	%o2, 24, %o0
	cmp	%o0, 0
	be	.LL45
	nop
	sethi	%hi(.LLC1), %o1
	or	%o1, %lo(.LLC1), %o0
	sethi	%hi(.LLC2), %o2
	or	%o2, %lo(.LLC2), %o1
	mov	51, %o2
	sethi	%hi(.LLC11), %o4
	or	%o4, %lo(.LLC11), %o3
	call	__eprintf, 0
	 nop
	b	.LL45
	 nop
.LL44:
.LL45:
	add	%fp, -24, %o1
	mov	%o1, %o0
	call	cStr__8MyString, 0
	 nop
	mov	%o0, %o1
	sethi	%hi(.LLC12), %o2
	or	%o2, %lo(.LLC12), %o0
	call	printf, 0
	 nop
	sethi	%hi(.LLC13), %o1
	or	%o1, %lo(.LLC13), %o0
	call	printf, 0
	 nop
.LLEHE42:
	b	.LL46
	 nop
.LL43:
	call	__throw, 0
	 nop
.LL46:
	add	%fp, -24, %o1
	mov	%o1, %o0
	mov	2, %o1
	call	_._8MyString, 0
	 nop
	b	.LL47
	 nop
.LLEHB48:
.LL42:
	add	%fp, -24, %o1
	mov	%o1, %o0
	mov	2, %o1
	call	_._8MyString, 0
	 nop
	b	.LL43
	 nop
.LLEHE48:
	b	.LL48
	 nop
.LL49:
	call	__throw, 0
	 nop
.LL50:
.LL48:
	call	terminate__Fv, 0
	 nop
.LL47:
	b	.LL51
	 nop
	b	.LL41
	 nop
.LL51:
.LL41:
	ret
	restore
.LLFE4:
.LLfe4:
	.size	 test4__Fv,.LLfe4-test4__Fv
.section	".rodata"
	.align 8
.LLC14:
	.asciz	"substr(2,3) of \"%s\"=\"%s\"\n"
	.align 8
.LLC15:
	.asciz	"Test 5 passed\n"
.section	".text"
	.align 4
	.global test5__Fv
	.type	 test5__Fv,#function
	.proc	020
test5__Fv:
.LLFB5:
	!#PROLOGUE# 0
	save	%sp, -144, %sp
.LLCFI4:
	!#PROLOGUE# 1
	sethi	%hi(.LLC0), %o1
	or	%o1, %lo(.LLC0), %o0
	st	%o0, [%fp-20]
	ld	[%fp-20], %o0
	call	strdup, 0
	 nop
	st	%o0, [%fp-24]
	add	%fp, -32, %o1
	mov	%o1, %o0
	ld	[%fp-24], %o1
	call	__8MyStringPCc, 0
	 nop
.LLEHB53:
	ld	[%fp-24], %o0
	stb	%g0, [%o0]
	add	%fp, -40, %o1
	mov	%o1, %o0
	call	__8MyString, 0
	 nop
.LLEHB55:
	add	%fp, -32, %o0
	add	%fp, -48, %o1
	st	%o1, [%sp+64]
	mov	2, %o1
	mov	3, %o2
	call	substring__8MyStringii, 0
	nop
	unimp	4
.LLEHB57:
	ld	[%fp-48], %o0
	st	%o0, [%fp-40]
.LLEHE57:
	b	.LL59
	 nop
.LL58:
	call	__throw, 0
	 nop
.LL59:
	add	%fp, -48, %o1
	mov	%o1, %o0
	mov	2, %o1
	call	_._8MyString, 0
	 nop
	add	%fp, -32, %o1
	mov	%o1, %o0
	call	cStr__8MyString, 0
	 nop
	mov	%o0, %l0
	add	%fp, -40, %o1
	mov	%o1, %o0
	call	cStr__8MyString, 0
	 nop
	mov	%o0, %o2
	sethi	%hi(.LLC14), %o1
	or	%o1, %lo(.LLC14), %o0
	mov	%l0, %o1
	call	printf, 0
	 nop
	sethi	%hi(.LLC15), %o1
	or	%o1, %lo(.LLC15), %o0
	call	printf, 0
	 nop
.LLEHE55:
	b	.LL60
	 nop
.LL56:
	call	__throw, 0
	 nop
.LL60:
	add	%fp, -40, %o1
	mov	%o1, %o0
	mov	2, %o1
	call	_._8MyString, 0
	 nop
.LLEHE53:
	b	.LL61
	 nop
.LL54:
	call	__throw, 0
	 nop
.LL61:
	add	%fp, -32, %o1
	mov	%o1, %o0
	mov	2, %o1
	call	_._8MyString, 0
	 nop
	b	.LL62
	 nop
.LLEHB63:
.LL57:
	add	%fp, -48, %o1
	mov	%o1, %o0
	mov	2, %o1
	call	_._8MyString, 0
	 nop
	b	.LL58
	 nop
.LL55:
	add	%fp, -40, %o1
	mov	%o1, %o0
	mov	2, %o1
	call	_._8MyString, 0
	 nop
	b	.LL56
	 nop
.LL53:
	add	%fp, -32, %o1
	mov	%o1, %o0
	mov	2, %o1
	call	_._8MyString, 0
	 nop
	b	.LL54
	 nop
.LLEHE63:
	b	.LL63
	 nop
.LL64:
	call	__throw, 0
	 nop
.LL65:
.LL63:
	call	terminate__Fv, 0
	 nop
.LL62:
	b	.LL66
	 nop
	b	.LL52
	 nop
.LL66:
.LL52:
	ret
	restore
.LLFE5:
.LLfe5:
	.size	 test5__Fv,.LLfe5-test5__Fv
.section	".rodata"
	.align 8
.LLC16:
	.asciz	"TestMyString test1|test2|test3|test4|test5\n"
.section	".text"
	.align 4
	.global usage__Fv
	.type	 usage__Fv,#function
	.proc	020
usage__Fv:
.LLFB6:
	!#PROLOGUE# 0
	save	%sp, -112, %sp
.LLCFI5:
	!#PROLOGUE# 1
	sethi	%hi(__iob+32), %o1
	or	%o1, %lo(__iob+32), %o0
	sethi	%hi(.LLC16), %o2
	or	%o2, %lo(.LLC16), %o1
	call	fprintf, 0
	 nop
	b	.LL68
	 nop
	b	.LL67
	 nop
.LL68:
.LL67:
	ret
	restore
.LLFE6:
.LLfe6:
	.size	 usage__Fv,.LLfe6-usage__Fv
.section	".rodata"
	.align 8
.LLC17:
	.asciz	"test1"
	.align 8
.LLC18:
	.asciz	"test2"
	.align 8
.LLC19:
	.asciz	"test3"
	.align 8
.LLC20:
	.asciz	"test4"
	.align 8
.LLC21:
	.asciz	"test5"
.section	".text"
	.align 4
	.global main
	.type	 main,#function
	.proc	04
main:
.LLFB7:
	!#PROLOGUE# 0
	save	%sp, -112, %sp
.LLCFI6:
	!#PROLOGUE# 1
	st	%i0, [%fp+68]
	st	%i1, [%fp+72]
	ld	[%fp+68], %o0
	cmp	%o0, 1
	bne	.LL70
	nop
	call	usage__Fv, 0
	 nop
	mov	1, %o0
	call	exit, 0
	 nop
.LL70:
	mov	4, %o0
	ld	[%fp+72], %o2
	add	%o0, %o2, %o1
	ld	[%o1], %o0
	sethi	%hi(.LLC17), %o2
	or	%o2, %lo(.LLC17), %o1
	call	strcmp, 0
	 nop
	cmp	%o0, 0
	bne	.LL71
	nop
	call	test1__Fv, 0
	 nop
	b	.LL72
	 nop
.LL71:
	mov	4, %o0
	ld	[%fp+72], %o2
	add	%o0, %o2, %o1
	ld	[%o1], %o0
	sethi	%hi(.LLC18), %o2
	or	%o2, %lo(.LLC18), %o1
	call	strcmp, 0
	 nop
	cmp	%o0, 0
	bne	.LL73
	nop
	call	test2__Fv, 0
	 nop
	b	.LL72
	 nop
.LL73:
	mov	4, %o0
	ld	[%fp+72], %o2
	add	%o0, %o2, %o1
	ld	[%o1], %o0
	sethi	%hi(.LLC19), %o2
	or	%o2, %lo(.LLC19), %o1
	call	strcmp, 0
	 nop
	cmp	%o0, 0
	bne	.LL75
	nop
	call	test3__Fv, 0
	 nop
	b	.LL72
	 nop
.LL75:
	mov	4, %o0
	ld	[%fp+72], %o2
	add	%o0, %o2, %o1
	ld	[%o1], %o0
	sethi	%hi(.LLC20), %o2
	or	%o2, %lo(.LLC20), %o1
	call	strcmp, 0
	 nop
	cmp	%o0, 0
	bne	.LL77
	nop
	call	test4__Fv, 0
	 nop
	b	.LL72
	 nop
.LL77:
	mov	4, %o0
	ld	[%fp+72], %o2
	add	%o0, %o2, %o1
	ld	[%o1], %o0
	sethi	%hi(.LLC21), %o2
	or	%o2, %lo(.LLC21), %o1
	call	strcmp, 0
	 nop
	cmp	%o0, 0
	bne	.LL79
	nop
	call	test5__Fv, 0
	 nop
	b	.LL72
	 nop
.LL79:
	call	usage__Fv, 0
	 nop
	mov	1, %o0
	call	exit, 0
	 nop
.LL80:
.LL78:
.LL76:
.LL74:
.LL72:
	mov	0, %o0
	call	exit, 0
	 nop
	mov	0, %i0
	b	.LL69
	 nop
.LL69:
	ret
	restore
.LLFE7:
.LLfe7:
	.size	 main,.LLfe7-main
.section	".gcc_except_table",#alloc,#write
	.align 4
__EXCEPTION_TABLE__:
	.uaword	.LLEHB3
	.uaword	.LLEHE3
	.uaword	.LL3

	.uaword	.LLEHB9
	.uaword	.LLEHE9
	.uaword	.LL9

	.uaword	.LLEHB14
	.uaword	.LLEHE14
	.uaword	.LL14

	.uaword	.LLEHB16
	.uaword	.LLEHE16
	.uaword	.LL16

	.uaword	.LLEHB23
	.uaword	.LLEHE23
	.uaword	.LL23

	.uaword	.LLEHB28
	.uaword	.LLEHE28
	.uaword	.LL28

	.uaword	.LLEHB30
	.uaword	.LLEHE30
	.uaword	.LL30

	.uaword	.LLEHB37
	.uaword	.LLEHE37
	.uaword	.LL37

	.uaword	.LLEHB42
	.uaword	.LLEHE42
	.uaword	.LL42

	.uaword	.LLEHB48
	.uaword	.LLEHE48
	.uaword	.LL48

	.uaword	.LLEHB53
	.uaword	.LLEHE53
	.uaword	.LL53

	.uaword	.LLEHB55
	.uaword	.LLEHE55
	.uaword	.LL55

	.uaword	.LLEHB57
	.uaword	.LLEHE57
	.uaword	.LL57

	.uaword	.LLEHB63
	.uaword	.LLEHE63
	.uaword	.LL63

.LLRTH1:
	.uaword	-1
	.uaword	-1


.section	".eh_frame",#alloc,#write
__FRAME_BEGIN__:
	.uaword	.LLECIE1-.LLSCIE1
.LLSCIE1:
	.uaword	0x0
	.byte	0x1
	.asciz	"eh"

	.uaword	__EXCEPTION_TABLE__
	.byte	0x1
	.byte	0x7c
	.byte	0x65
	.byte	0xc
	.byte	0xe
	.byte	0x0
	.byte	0x9
	.byte	0x65
	.byte	0xf
	.align 4
.LLECIE1:
	.uaword	.LLEFDE1-.LLSFDE1
.LLSFDE1:
	.uaword	.LLSFDE1-__FRAME_BEGIN__
	.uaword	.LLFB1
	.uaword	.LLFE1-.LLFB1
	.byte	0x4
	.uaword	.LLCFI0-.LLFB1
	.byte	0xd
	.byte	0x1e
	.byte	0x2d
	.byte	0x9
	.byte	0x65
	.byte	0x1f
	.align 4
.LLEFDE1:
	.uaword	.LLEFDE3-.LLSFDE3
.LLSFDE3:
	.uaword	.LLSFDE3-__FRAME_BEGIN__
	.uaword	.LLFB2
	.uaword	.LLFE2-.LLFB2
	.byte	0x4
	.uaword	.LLCFI1-.LLFB2
	.byte	0xd
	.byte	0x1e
	.byte	0x2d
	.byte	0x9
	.byte	0x65
	.byte	0x1f
	.align 4
.LLEFDE3:
	.uaword	.LLEFDE5-.LLSFDE5
.LLSFDE5:
	.uaword	.LLSFDE5-__FRAME_BEGIN__
	.uaword	.LLFB3
	.uaword	.LLFE3-.LLFB3
	.byte	0x4
	.uaword	.LLCFI2-.LLFB3
	.byte	0xd
	.byte	0x1e
	.byte	0x2d
	.byte	0x9
	.byte	0x65
	.byte	0x1f
	.align 4
.LLEFDE5:
	.uaword	.LLEFDE7-.LLSFDE7
.LLSFDE7:
	.uaword	.LLSFDE7-__FRAME_BEGIN__
	.uaword	.LLFB4
	.uaword	.LLFE4-.LLFB4
	.byte	0x4
	.uaword	.LLCFI3-.LLFB4
	.byte	0xd
	.byte	0x1e
	.byte	0x2d
	.byte	0x9
	.byte	0x65
	.byte	0x1f
	.align 4
.LLEFDE7:
	.uaword	.LLEFDE9-.LLSFDE9
.LLSFDE9:
	.uaword	.LLSFDE9-__FRAME_BEGIN__
	.uaword	.LLFB5
	.uaword	.LLFE5-.LLFB5
	.byte	0x4
	.uaword	.LLCFI4-.LLFB5
	.byte	0xd
	.byte	0x1e
	.byte	0x2d
	.byte	0x9
	.byte	0x65
	.byte	0x1f
	.align 4
.LLEFDE9:
	.uaword	.LLEFDE11-.LLSFDE11
.LLSFDE11:
	.uaword	.LLSFDE11-__FRAME_BEGIN__
	.uaword	.LLFB6
	.uaword	.LLFE6-.LLFB6
	.byte	0x4
	.uaword	.LLCFI5-.LLFB6
	.byte	0xd
	.byte	0x1e
	.byte	0x2d
	.byte	0x9
	.byte	0x65
	.byte	0x1f
	.align 4
.LLEFDE11:
	.uaword	.LLEFDE13-.LLSFDE13
.LLSFDE13:
	.uaword	.LLSFDE13-__FRAME_BEGIN__
	.uaword	.LLFB7
	.uaword	.LLFE7-.LLFB7
	.byte	0x4
	.uaword	.LLCFI6-.LLFB7
	.byte	0xd
	.byte	0x1e
	.byte	0x2d
	.byte	0x9
	.byte	0x65
	.byte	0x1f
	.align 4
.LLEFDE13:
	.ident	"GCC: (GNU) 2.95.2 19991024 (release)"
