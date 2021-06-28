# -----------------------------------------------------------------------------
# A 64-bit function that returns the addition of two number.  
# The function has signature:
#
#   int add(int x, int y)
#
# Note that the parameters have already been passed in rdi and rsi.  We
# just have to return the value in rax.
# -----------------------------------------------------------------------------

        .globl  add
        
        .text
add:
		push %rbp
		mov %rsi,%rax
		add %rdi,%rax
		pop %rbp
        ret
		