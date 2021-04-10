@;++++++++++++++++++++++++++++++++++++++++++++++++++++++++
@; r0: data      r1: src addr      r2: len         (we should at least test 1k here and must be interger multi of 1k)
@;++++++++++++++++++++++++++++++++++++++++++++++++++++++++

@AREA burst8_write_functions, CODE,READONLY

@ENTRY

@CODE32
.globl burst8_write_all
.globl burst8_move
.globl burst8_write_while1
.global burst8_write_one_burst
burst8_write_all:
    STMFD r13!,{r3-r10,r14}
    ADD r2,r1,r2

@;set data
    MOV r3,r0
    MVN r4,r0
    MOV r5,r0
    MVN r6,r0
    MOV r7,r0
    MVN r8,r0
    MOV r9,r0
    MVN r10,r0
    B WR_LOOP

@;r0=data0,r1=data1,r2=data2,r3=data3,r4=data4,r5=data5,r6=data6,r7=data7
burst8_write_while1:
    LDR   r4, [r13]
    LDR   r5, [r13,#0x4]
    LDR   r6, [r13,#0x8]
    LDR   r7, [r13,#0xc]
write_while1_loop:
    MOV r8, #0x80000000
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    STMIA r8!,{r0,r1,r2,r3,r4,r5,r6,r7}
    B write_while1_loop

@;r0=data0,r1=data1,r2=data2,r3=data3,r4=data4,r5=data5,r6=data6,r7=data7
@;r0=src	r0+#4=dst r0+#8=len
burst8_write_one_burst:
    STMFD r13!,{r1-r9,r14}
    LDR r9,[r0]
   @ ;read data from the src addr
    LDMIA r9!,{r1,r2,r3,r4,r5,r6,r7,r8}

    LDR r9,[r0,#4]
   @ ;write data to the dst addr
    STMIA r9!,{r1,r2,r3,r4,r5,r6,r7,r8}
    LDMFD r13!,{r1-r9,pc}


WR_LOOP:
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}
    STMIA r1!,{r3,r4,r5,r6,r7,r8,r9,r10}

    CMP r1,r2
    BNE WR_LOOP

    LDMFD r13!,{r3-r10,pc}

   @ENDP

   @EXPORT burst8_write_all


burst8_move:
@;r0=src	r0+#4=dst r0+#8=len
    STMFD r13!,{r1-r10,r14}
    LDR r9,[r0,#4]
    LDR r10,[r0,#8]
    LDR r0,[r0]
    ADD r10,r9,r10

MOVE_LOOP:
    LDMIA r0!,{r1,r2,r3,r4,r5,r6,r7,r8}
    STMIA r9!,{r1,r2,r3,r4,r5,r6,r7,r8}

    CMP r9,r10
    BLE MOVE_LOOP

    LDMFD r13!,{r1-r10,pc}

   @ENDP

   @EXPORT burst8_move

@END
