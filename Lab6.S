    .section .note.GNU-stack, ""
    .text
    .global strlen_mine
    .global strlen_utf8


strlen_mine:
# counter 
mov $0, %rax
    
loop_strlen:
# compare current byte with zero to find end
cmpb $0, (%rdi)
je done_strlen
# If je fell through add to len counter and move to next byte
inc %rax
add $1, %rdi
# Keep looping
jmp loop_strlen

done_strlen:
ret

strlen_utf8:
# counter
mov $0, %rax

loop_utf8:
# same as before and check for null termination
cmpb $0, (%rdi)
je done_utf8

# check for continuation byte
# load into 8-bit register to do and
movb (%rdi), %dl 
andb $0b11000000, %dl
cmpb $0b10000000, %dl
# skip if 
je skip

inc %rax

skip:
# even when skipped move along the string
add $1, %rdi
jmp loop_utf8

done_utf8:
ret

