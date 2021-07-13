# ----------------------------------------------------------------------------------------
# Writes "Hello World" to the console using a C library. Runs on Linux or any other system
# that does not use underscores for symbols in its C library. To assemble and run:
#
#     gcc -o hello hello.s && ./hello
# ----------------------------------------------------------------------------------------
        .global main
        .text
main:                                  # This is called by C library's startup code
		push %rbp
		mov %rsp,%rbp
        lea	message(%rip), %rdi        # First integer (or pointer) parameter in %rdi
	mov     $10,%rsi                # second argument
        call    printf                 # printf(message)
		pop %rbp
        ret
                                       # Return to C library code
									
		.data
message:
        .asciz "A=%d\n"         # asciz puts a 0 byte at the end

