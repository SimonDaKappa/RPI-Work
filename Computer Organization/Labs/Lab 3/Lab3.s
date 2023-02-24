################################################################################
# Lab 3: Assembling some arrays
# CSCI-2500 Spring 2023
################################################################################
## Data segment
################################################################################
.data 
  newline:      .asciiz "\n"

################################################################################
## Text segment
################################################################################
.text
  .align 2          # instructions must be on word boundaries
  .globl main       # main is a global label
  .globl read_arr   # allocate and read in an array of some length
  .globl print_arr  # print out the values that were read in

################################################################################
# Main segment
# Note: You don't need to modify anything here (and you shouldn't)
################################################################################
main:
  # Save return address on the stack
  sub $sp, $sp, 4   
  sw  $ra, 0($sp)

  # Read in an array of some length
  # Return in $v0 - the length of the array
  # Return in $v1 - the pointer to the array
  jal read_arr

  # Move our return values to the argument registers
  move $a0, $v0 # length of array
  move $a1, $v1 # pointer to array

  # Call our function to print out the array
  jal print_arr

  # Restore $ra, free stack space, and return
  lw  $ra, 0($sp)
  add $sp, $sp, 4
  jr  $ra

################################################################################
# Read in our array
# Construct a loop to read in 'length' values into the array in our data segment
#
# Input:
#   None
# Return:
#   v0 = length of allocated array
#   v1 = base memory address of the array
################################################################################
read_arr: 
  # Read in the length of the array
  li $v0, 5
  syscall
  move $t0, $v0   # Set array length 
  # Allocate sufficient space
  li $v0, 9 
  sll $a0, $t0, 2
  syscall
  move $t1, $v0   # Set array pointer
  li $t2, 0       # Set counter value
  # Do primary loop
read_loop:
  # Read in next value from the array and store it
  sll $t4, $t2, 2   # get the offset from our base address using our counter
                    # offset = 4*i, where i is our counter and int is 4 bytes
  add $t4, $t4, $t1 # Add to our offset the array pointer and offset //
                    # get the address of the current index we're writing to
                    # address of index i = (base address) + 4*i
  li $v0, 5
  syscall
  sw $v0, 0($t4)   # Store next into address of offset

  # branch back to array if counter != length ($t2 != $t0)
  addi $t2, $t2, 1    # increment counter
  bne $t2, $t0, read_loop
  # Done with loop
  li $t2, 0 # reset counter
  # Set the return values
  move $v0, $t0
  move $v1, $t1
  # Go back to main
  jr $ra

################################################################################
# Print out the array
# Construct a loop to print out the 'length' values that were read in
#
# Input:
#   a0 = length of array
#   a1 = base address of array
# Return:
#   None
################################################################################
print_arr:
  # Initialize any registers
  move $t0, $a0 # Array length in t0
  move $t1, $a1 # Array pointer in t1
  li $t2, 0     # Index Offset = 0
  # Do primary loop
print_loop:
  # Output the integer from the array

  # Read in next value from the array and store it
  sll $t4, $t2, 2   # get the offset from our base address using our counter
                    # offset = 4*i, where i is our counter and int is 4 bytes
  add $t4, $t4, $t1 # Add to our offset the array pointer and offset //
                    # get the address of the current index we're writing to
                    # address of index i = (base address) + 4*i
                       # Store arr + offset in $t3
  li $v0, 1            # Print int
  lw $a0, 0($t4)       # Store $t3 into print argument
  syscall
  # Output a new line
  li $v0, 4
  la $a0, newline
  syscall
  # increment counter
  addi $t2, $t2, 1   
  # Done with loop
  bne $t2, $t0, print_loop
  # Go back to main
  jr $ra
