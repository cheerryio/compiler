	.cpu arm7tdmi
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"test.cpp"
	.text
	.align	2
	.global	main
	.arch armv4t
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	.fnstart
.LFB0:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #44
	str	r0, [fp, #-40]
	ldr	r3, [fp, #-8]
	cmp	r3, #2
	bne	.L2
	ldr	r3, [fp, #-8]
	ldr	r2, [fp, #-12]
	mul	r2, r3, r2
	ldr	r3, [fp, #-8]
	ldr	r1, [fp, #-16]
	mul	r3, r1, r3
	add	r2, r2, r3
	ldr	r3, [fp, #-8]
	ldr	r1, [fp, #-16]
	mul	r3, r1, r3
	add	r2, r2, r3
	ldr	r3, [fp, #-8]
	ldr	r1, [fp, #-20]
	mul	r3, r1, r3
	add	r2, r2, r3
	ldr	r3, [fp, #-8]
	ldr	r1, [fp, #-24]
	mul	r3, r1, r3
	add	r2, r2, r3
	ldr	r3, [fp, #-8]
	ldr	r1, [fp, #-28]
	mul	r3, r1, r3
	add	r2, r2, r3
	ldr	r3, [fp, #-8]
	ldr	r1, [fp, #-32]
	mul	r3, r1, r3
	add	r2, r2, r3
	ldr	r3, [fp, #-12]
	ldr	r1, [fp, #-16]
	mul	r3, r1, r3
	add	r3, r2, r3
	str	r3, [fp, #-8]
	b	.L3
.L2:
	ldr	r3, [fp, #-8]
	lsr	r2, r3, #31
	add	r3, r2, r3
	asr	r3, r3, #1
	mov	r2, r3
	mov	r3, r2
	lsl	r3, r3, #1
	add	r3, r3, r2
	str	r3, [fp, #-8]
.L3:
	mov	r3, #0
	mov	r0, r3
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.cantunwind
	.fnend
	.size	main, .-main
	.ident	"GCC: (GNU Arm Embedded Toolchain 10-2020-q4-major) 10.2.1 20201103 (release)"
