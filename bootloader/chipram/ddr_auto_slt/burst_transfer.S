@;++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
@;r0: SRC     r0 offset #4:DST     r0 offset #8:len
@;++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <config.h>
@AREA burst8_write_functions, CODE,READONLY

@CODE32
.globl BurstTransfer
.globl BurstTransfer_N

BurstTransfer_N:
    STMFD r13!,{r1-r9,r14}
    LDR   r4,[r0,#8]
    CMP   r4,#4
    BEQ   Burst4Transfer_N
    
    CMP   r4,#8
    BEQ   Burst8Transfer_N
    B     BurstErrSizeTransfer
    
Burst4Transfer_N:
    LDR r9,[r0]
   @ ;read data from the src addr
    LDMIA r9!,{r1,r2,r3,r4}
    
    MVN r1,r1
    MVN r2,r2
    MVN r3,r3
    MVN r4,r4
    
    LDR r9,[r0,#4]
    @;write data to the dst addr
    STMIA r9!,{r1,r2,r3,r4}
    
    BL BurstTransfer_ret
    
Burst8Transfer_N:
    LDR r9,[r0]
   @ ;read data from the src addr
    LDMIA r9!,{r1,r2,r3,r4,r5,r6,r7,r8}
    
    MVN r1,r1
    MVN r2,r2
    MVN r3,r3
    MVN r4,r4
    MVN r5,r5
    MVN r6,r6
    MVN r7,r7
    MVN r8,r8
    
    LDR r9,[r0,#4]
   @ ;write data to the dst addr
    STMIA r9!,{r1,r2,r3,r4,r5,r6,r7,r8}
    
    BL BurstTransfer_ret

BurstTransfer:
    STMFD r13!,{r1-r9,r14}
    LDR   r4,[r0,#8]
    CMP   r4,#4
    BEQ   Burst4Transfer
    
    CMP   r4,#8
    BEQ   Burst8Transfer
    B     BurstErrSizeTransfer
    
Burst4Transfer:
    LDR r9,[r0]
   @ ;read data from the src addr
    LDMIA r9!,{r1,r2,r3,r4}
    
    LDR r9,[r0,#4]
    @;write data to the dst addr
    STMIA r9!,{r1,r2,r3,r4}
    
    BL BurstTransfer_ret
    
Burst8Transfer:
    LDR r9,[r0]
   @ ;read data from the src addr
    LDMIA r9!,{r1,r2,r3,r4,r5,r6,r7,r8}
    
    LDR r9,[r0,#4]
   @ ;write data to the dst addr
    STMIA r9!,{r1,r2,r3,r4,r5,r6,r7,r8}
    
    BL BurstTransfer_ret

BurstTransfer_ret:
    MOV r0,#0
    LDMFD r13!,{r1-r9,pc}
    
    
BurstErrSizeTransfer:
    MVN r0,#0
    LDMFD r13!,{r1-r9,pc}
    