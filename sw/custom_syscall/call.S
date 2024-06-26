.globl _start
.globl make_syscall
.equ SYSCALL_ADDR, 0x02010000

.macro SYS_EXIT, exit_code
li   a7, 93
li   a0, \exit_code
li   t0, SYSCALL_ADDR
csrr a6, mhartid
sw   a6, 0(t0)
.endm

#Make syscall with two parameters
make_syscall:
    mv a7, a2
    li t0, SYSCALL_ADDR
    csrr a6, mhartid
    sw a6, 0(t0)
    ret

# Macro to make a syscall with two parameters
.macro SYSCALL, syscall_number, arg1, arg2
li a7, \syscall_number
li a0, \arg1
li a1, \arg2
li t0, SYSCALL_ADDR
csrr a6, mhartid
sw a6, 0(t0)
.endm

# program entry-point
_start:

jal main

#SYSCALL 701, 5, 3
# Exit with previous syscall return value
#li   a7, 93
#li   t0, SYSCALL_ADDR
#csrr a6, mhartid
#sw   a6, 0(t0)

SYS_EXIT 0