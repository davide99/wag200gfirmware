	.file	1 "offset.c"
	.version	"01.01"
gcc2_compiled.:
__gnu_compiled_c:
 #APP
	.macro	__sti
	.set	push
	.set	reorder
	.set	noat
	mfc0	$1,$12
	ori	$1,0x1f
	xori	$1,0x1e
	mtc0	$1,$12
	.set	pop
	.endm
	.macro	__cli
	.set	push
	.set	reorder
	.set	noat
	mfc0	$1,$12
	ori	$1,1
	xori	$1,1
	.set	noreorder
	mtc0	$1,$12
	nop
	nop
	nop
	.set	pop
	.endm
	.macro	__save_flags flags
	.set	push
	.set	reorder
	mfc0	\flags, $12
	.set	pop
	.endm
	.macro	__save_and_cli result
	.set	push
	.set	reorder
	.set	noat
	mfc0	\result, $12
	ori	$1, \result, 1
	xori	$1, 1
	.set	noreorder
	mtc0	$1, $12
	sll	$0, $0, 1			# nop
	sll	$0, $0, 1			# nop
	sll	$0, $0, 1			# nop
	.set	pop
	.endm
	.macro	__restore_flags flags
	.set	noreorder
	.set	noat
	mfc0	$1, $12
	andi	\flags, 1
	ori	$1, 1
	xori	$1, 1
	or	\flags, $1
	mtc0	\flags, $12
	nop
	nop
	nop
	.set	at
	.set	reorder
	.endm
	.rdata
	.align	2
$LC0:
	.ascii	"kernel BUG at %s:%d!\n\000"
	.align	2
$LC1:
	.ascii	"/home/chi/Linksys/projekt/code/kernel/src/include/linux/"
	.ascii	"sched.h\000"
	
@@@/* DO NOT TOUCH, AUTOGENERATED BY OFFSET.C */
	
@@@
	
@@@#ifndef _MIPS_OFFSET_H
	
@@@#define _MIPS_OFFSET_H
	
@@@
 #NO_APP
	.text
	.align	2
	.globl	output_ptreg_defines
	.ent	output_ptreg_defines
output_ptreg_defines:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	
@@@/* MIPS pt_regs offsets. */
	
@@@#define PT_R0     24
	
@@@#define PT_R1     28
	
@@@#define PT_R2     32
	
@@@#define PT_R3     36
	
@@@#define PT_R4     40
	
@@@#define PT_R5     44
	
@@@#define PT_R6     48
	
@@@#define PT_R7     52
	
@@@#define PT_R8     56
	
@@@#define PT_R9     60
	
@@@#define PT_R10    64
	
@@@#define PT_R11    68
	
@@@#define PT_R12    72
	
@@@#define PT_R13    76
	
@@@#define PT_R14    80
	
@@@#define PT_R15    84
	
@@@#define PT_R16    88
	
@@@#define PT_R17    92
	
@@@#define PT_R18    96
	
@@@#define PT_R19    100
	
@@@#define PT_R20    104
	
@@@#define PT_R21    108
	
@@@#define PT_R22    112
	
@@@#define PT_R23    116
	
@@@#define PT_R24    120
	
@@@#define PT_R25    124
	
@@@#define PT_R26    128
	
@@@#define PT_R27    132
	
@@@#define PT_R28    136
	
@@@#define PT_R29    140
	
@@@#define PT_R30    144
	
@@@#define PT_R31    148
	
@@@#define PT_LO     152
	
@@@#define PT_HI     156
	
@@@#define PT_EPC    160
	
@@@#define PT_BVADDR 164
	
@@@#define PT_STATUS 168
	
@@@#define PT_CAUSE  172
	
@@@#define PT_SIZE   176
	
@@@
 #NO_APP
	j	$31
	.end	output_ptreg_defines
	.align	2
	.globl	output_task_defines
	.ent	output_task_defines
output_task_defines:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	
@@@/* MIPS task_struct offsets. */
	
@@@#define TASK_STATE         0
	
@@@#define TASK_FLAGS         100
	
@@@#define TASK_SIGPENDING    8
	
@@@#define TASK_NEED_RESCHED  20
	
@@@#define TASK_PTRACE        24
	
@@@#define TASK_COUNTER       32
	
@@@#define TASK_NICE          36
	
@@@#define TASK_MM            44
	
@@@#define TASK_PID           128
	
@@@#define TASK_STRUCT_SIZE   1072
	
@@@
 #NO_APP
	j	$31
	.end	output_task_defines
	.align	2
	.globl	output_thread_defines
	.ent	output_thread_defines
output_thread_defines:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	
@@@/* MIPS specific thread_struct offsets. */
	
@@@#define THREAD_REG16   632
	
@@@#define THREAD_REG17   636
	
@@@#define THREAD_REG18   640
	
@@@#define THREAD_REG19   644
	
@@@#define THREAD_REG20   648
	
@@@#define THREAD_REG21   652
	
@@@#define THREAD_REG22   656
	
@@@#define THREAD_REG23   660
	
@@@#define THREAD_REG29   664
	
@@@#define THREAD_REG30   668
	
@@@#define THREAD_REG31   672
	
@@@#define THREAD_STATUS  676
	
@@@#define THREAD_FPU     680
	
@@@#define THREAD_BVADDR  944
	
@@@#define THREAD_BUADDR  948
	
@@@#define THREAD_ECODE   952
	
@@@#define THREAD_TRAPNO  956
	
@@@#define THREAD_MFLAGS  960
	
@@@#define THREAD_CURDS   964
	
@@@#define THREAD_TRAMP   968
	
@@@#define THREAD_OLDCTX  972
	
@@@
 #NO_APP
	j	$31
	.end	output_thread_defines
	.align	2
	.globl	output_mm_defines
	.ent	output_mm_defines
output_mm_defines:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	
@@@/* Linux mm_struct offsets. */
	
@@@#define MM_USERS      16
	
@@@#define MM_PGD        12
	
@@@#define MM_CONTEXT    128
	
@@@
 #NO_APP
	j	$31
	.end	output_mm_defines
	.align	2
	.globl	output_sc_defines
	.ent	output_sc_defines
output_sc_defines:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	
@@@/* Linux sigcontext offsets. */
	
@@@#define SC_REGS       16
	
@@@#define SC_FPREGS     272
	
@@@#define SC_MDHI       552
	
@@@#define SC_MDLO       560
	
@@@#define SC_PC         8
	
@@@#define SC_STATUS     4
	
@@@#define SC_OWNEDFP    528
	
@@@#define SC_FPC_CSR    532
	
@@@#define SC_FPC_EIR    536
	
@@@#define SC_CAUSE      568
	
@@@#define SC_BADVADDR   572
	
@@@
 #NO_APP
	j	$31
	.end	output_sc_defines
 #APP
	
@@@#endif /* !(_MIPS_OFFSET_H) */