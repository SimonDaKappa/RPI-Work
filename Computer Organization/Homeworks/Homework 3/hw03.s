################################################################################
# Homework 3: NxM MIPSplication
# CSCI-2500 Spring 2023
# Prof. Slota 
################################################################################
## Data segment
################################################################################
.data
  newline:  .asciiz "\n"
  tab:      .asciiz "\t"

################################################################################
## Text segment
################################################################################
.text
  .align 2          # instructions must be on word boundaries
  .globl main       # main is a global label
  .globl mm_read    # read in NxM matrix
  .globl mm_alloc   # allocate space for NxM matrix
  .globl mm_print   # print out formatted NxM matrix
  .globl mm_mult    # multiple two non-square matrices

################################################################################
# Main segment
################################################################################
main:
  # save return address on the stack
  sub $sp, $sp, 4   
  sw  $ra, 0($sp)

  # Read in a matrix 1 of some NxM size
  # Return in $v0 - N
  # Return in $v1 - M
  # Return in 0($sp) - base address of matrix
  sub $sp, $sp, 4   # make space on stack for return value
  jal mm_read

  # save matrix 1 values
  move  $s0, $v0
  move  $s1, $v1
  lw    $s2, 0($sp)
  add   $sp, $sp, 4   # restore stack

  # Setup arguments and print out matrix 1
  move  $a0, $s0
  move  $a1, $s1
  move  $a2, $s2
  jal mm_print

  # Read in matrix 2 of some NxM size
  sub $sp, $sp, 4   # make space on stack for return value
  jal mm_read

  # save matrix 2 values
  move  $s3, $v0
  move  $s4, $v1
  lw    $s5, 0($sp)
  add   $sp, $sp, 4   # restore stack

  # Setup arguments and print out matrix 2
  move  $a0, $s3
  move  $a1, $s4
  move  $a2, $s5
  jal mm_print

  # Setup arguments and call mm_mult
  # Note: 5 arguments, so we need to use stack
  # Note: num cols matrix 1 == num rows matrix 2
  move  $a0, $s0    # num rows matrix1
  move  $a1, $s1    # num cols matrix1
  move  $a2, $s2    # address of matrix 1
  move  $a3, $s4    # num cols matrix2
  sub   $sp, $sp, 4   
  sw    $s5, 0($sp) # address of matrix 2
  jal mm_mult
  add   $sp, $sp, 4

  # print the result
  move $a0, $s0 
  move $a1, $s4
  move $a2, $v0
  jal mm_print

  # restore $ra, free stack space, and return
  lw  $ra, 0($sp)
  add $sp, $sp, 4
  jr  $ra

################################################################################
# mm_read: Read in a NxM matrix from standard input
# Note: You will be calling mm_alloc from this function, so you'll need to save 
#       $ra on the stack. Also, you'll be returning 3 values back to main, one
#       value (the matrix base address), will need to be saved on the stack.
#       Matrix format is:
#         First line:  N = num rows
#         Second line: M = num cols
#         Subsequent lines contain one value each, filling each row in turn
#         (same format as hw01, except N,M on separate lines)  
# Input:
#   None
# Return:
#   v0 = N
#   v1 = M
#   0($sp) = base address of matrix
################################################################################
mm_read:
  # save return address and any saved registers on the stack, if necessary
  sub $sp, $sp, 4
  sw  $ra, 0($sp)
  # get N
  li $v0, 5
  syscall
  move $t8, $v0
  # get M
  li $v0, 5
  syscall
  move $t9, $v0 
  # Setup up arguments and call mm_alloc - v0 is returned as base address
  move $a0, $t8         #a0 = s0 = N
  move $a1, $t9         #a1 = s1 = M
  jal mm_alloc
  # do nested loops to read in values
  move $ra, $v1         # it easiest to return the previous $ra from stack now
  move $t0, $v0         #Base Address Dont Modify
  move $t1, $zero       #t0 = row counter
  move $t2, $zero       #t1 = col counter
                        #s0 = N
                        #s1 = M
  # outer loop - N times
  read_loop:
    # inner loop - M times 
    read_loop2:
      # Read in value and store in matrix[t1][t2]
      # Note: Mat[i][j] = start + (i * M + j) * 4
      li $v0, 5
      syscall
      mul $t3, $t1, $t9 #mat[i][j] address = t1 * M  
      add $t3, $t3, $t2 #mat[i][j] address = (t1 * M) + t2
      sll $t3, $t3, 2   #mat[i][j] address = (t1 * M + t2) * 4
      # Since stack instead of heap try sub instead of add
      sub $t3, $t0, $t3 #mat[i][j] address = start - (t1 * M + t2) * 4
      # store value in matrix
      sw $v0, 0($t3)
      # increment col counter
      addi $t2, $t2, 1
      # check if we are done with inner loop
      bne $t2, $t9, read_loop2
      # end inner loop
    # increment row counter and reset column counter
    addi $t1, $t1, 1
    move $t2, $zero
    # check if we are done with outer loop
    bne $t1, $t8, read_loop
    # end outer loop
  # reset row/col counter
  move $t1, $zero
  move $t2, $zero
  # setup up return values
  move $v0, $t8         # N
  move $v1, $t9         # M
  # Note: third return value goes on the stack *after* restoration below
  la $t1, 0($t0)       # base address of matrix
  sw $t1, 0($sp)  
  # restore stack, ra, and any saved registers, if necessary
  # return to main
  jr  $ra

################################################################################
# mm_alloc: Allocate an NxM matrix
# Note: You can just allocate a single array of length N*M.
# Input:
#   a0 = N
#   a1 = M
# Return:
#   v0 = base address of allocated space
################################################################################
mm_alloc:
  # save return address and any saved registers on the stack, if necessary
  # Allocate sufficient space (on stack???)
  lw $v1, 0($sp)     #previous $ra (for Jal mm_read)
  # Calculate Space Needed on Stack
  mul $t0, $a0, $a1
  sll $t0, $t0, 2     # (N * M) * 4
  # Set v0 as current stack pointer address
  la $v0, 0($sp)      #v0 = base address
  sub $sp, $sp, $t0
  # set return value
  
  # restore stack, ra, and any saved registers, if necessary
  move $t0, $zero
  # return to main
  jr  $ra

################################################################################
# mm_print: Output the formatted contents of NxM matrix
# Note: Within a row, separate each value by tab
#       End each row with a newline
# Input:
#   a0 = N
#   a1 = M
#   a2 = base pointer
# Return:
#   None
################################################################################
mm_print:
  # save return address and any saved registers on the stack, if necessary

  # do nested loops to print out values
  move $t0, $a2         #Base Address Dont Modify
  move $t6, $a0         #t6 = s0/s3 = N
  move $t7, $a1         #t7 = s1/s4 = M
  move $t1, $zero       #t0 = row counter
  move $t2, $zero       #t1 = col counter
  # outer loop - N times
  print_loop:
    # inner loop - M times 
    print_loop2:
      # Read in value and store in matrix[t1][t2]
      # Note: Mat[i][j] = start + (i * M + j) * 4
      mul $t3, $t1, $t7 #mat[i][j] address = t1 * M  
      add $t3, $t3, $t2 #mat[i][j] address = (t1 * M) + t2
      sll $t3, $t3, 2   #mat[i][j] address = (t1 * M + t2) * 4
      # Since stack instead of heap try sub instead of add
      sub $t3, $t0, $t3 #mat[i][j] address = start - (t1 * M + t2) * 4
      # print value in matrix
      lw $a0, 0($t3)
      li $v0, 1
      syscall
      li $v0, 4
      la $a0, tab
      syscall
      # increment col counter
      addi $t2, $t2, 1
      # check if we are done with inner loop
      bne $t2, $t7, print_loop2
      # end inner loop
  li $v0, 4
  la $a0, newline
  syscall
  # increment row counter and reset column counter
  addi $t1, $t1, 1
  move $t2, $zero
  # check if we are done with outer loop
  bne $t1, $t6, print_loop
    # end outer loop
  # reset row/col counter
  move $t1, $zero
  move $t2, $zero
  # restore stack, ra, and any saved registers, if necessary

  # return to main
  jr  $ra

################################################################################
# mm_mult: Perform the actual NxM matrix multiplication
# Input:
#   a0 = N for matrix 1
#   a1 = M for matrix 1 <-> N for matrix 2
#   a2 = base address for matrix 1
#   a3 = M for matrix 2
#   0($sp) = base address for matrix 2
# Return:
#   v0 = base address for result matrix
################################################################################
mm_mult:
  # save return address and any saved registers on the stack, if necessary
  sub $sp, $sp, 4
  sw $ra, 0($sp)
  # set up and call mm_alloc for result matrix
  move $a0, $s0
  move $a1, $s4
  jal mm_alloc
  move $ra, $v1       # restore $ra from mm_alloc (NOTICE THIS PLS)
  # three nested loops for matrix-matrix multiplication
  move $t0, $v0       # new matrix base address
  move $t1, $zero     # mat1 row counter (0 to N) r
  move $t2, $zero     # mat2 col counter (0 To P) c
  move $t3, $zero     # mat1 col/mat2 row counter (0 to M) i
  move $t4, $zero     # [i][j] sum 
  move $t5, $zero     # mat1[i][k] address
  move $t6, $zero     # mat2[k][j] address
  move $t7, $zero     # mat3 address
  mult_loopN: # r
  
    mult_loopP: # c
      move $t4, $zero # Reset sum
      mult_loopM: # i
        # Calculate mat1[r][i] address
        mul $t5, $t1, $s1 #mat1[r][i] address = r * M
        add $t5, $t5, $t3 #mat1[r][i] address = (r * M) + i
        sll $t5, $t5, 2   #mat1[r][i] address = (r * M + i) * 4
        sub $t5, $s2, $t5 #mat1[r][i] address = start + (r * M + i) * 4
        lw $t5, 0($t5)    #value at mat[r][i]
        # Calculate mat2[i][c] address
        mul $t6, $t3, $s4 #mat2[i][c] address = i * P
        add $t6, $t6, $t2 #mat2[i][c] address = (i * P) + c
        sll $t6, $t6, 2   #mat2[i][c] address = (i * P + c) * 4
        sub $t6, $s5, $t6,  #mat2[i][c] address = start + (i * P + c) * 4
        lw $t6, 0($t6)    #value at mat[i][c]
        # Multiply mat1[r][i] * mat2[i][c]
        mul $t8, $t5, $t6
        # Add to sum
        add $t4, $t4, $t8
        # increment mixed counter
        addi $t3, $t3, 1
        bne $t3, $s1, mult_loopM
      # end mult_loopM

    # Set Mat3[r][c] = sum
    # Calculate mat3[r][c] address
    mul $t7, $t1, $s4 #mat3[r][c] address = r * P
    add $t7, $t7, $t2 #mat3[r][c] address = (r * P) + c
    sll $t7, $t7, 2   #mat3[r][c] address = (r * P + c) * 4
    sub $t7, $t0, $t7 #mat3[r][c] address = start + (r * P + c) * 4
    # Store sum in mat3[r][c]
    sw $t4, 0($t7)
    #increment col counter and reset mixed counter
    addi $t2, $t2, 1
    move $t3, $zero
    bne $t2, $s4, mult_loopP  
    #end mult_loopP

  # increment row counter and reset column counter
  addi $t1, $t1, 1
  move $t2, $zero  
  bne $t1, $s0, mult_loopN 
  # set return value
  move $v0, $t0
  # restore stack, ra, and any saved registers, if necessary
  la $sp, 0($s2)
  addi $sp, $sp, 4
  # return to main
  jr  $ra
