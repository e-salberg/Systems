; lab7_asm.asm, x86 code of lab_c.c

;export the symbol "main"
global main

;indicate that printf will be an extern that will have to be resolved at link time
extern printf
extern atoi

section .rodata
; note, must place the ascii value of \n (0xa) as a byte after our format string instead of making format string "%d\n"
format_string db "(%d, %d): %d", 0xa, 0

;the read-write data segment
section .data
;initialize the static variable var_s to 0
var_s dd 0x0

; the code (text) segment
section .text

; the 'main' function
main:
  ; outer_limit = [esp - 0x4]
  ; inner_limit = [ebp - 0x8]
  ;set up the main function's stack frame
  push ebp
  mov ebp, esp

  ; set aside space for the main's two local variables outer_limit, inner_limit
  sub esp, 0x8

  ; implement outer_limit = atoi(argv[1])
  ; set aside room for the one parameter on the stack for the first call to atoi
  sub esp, 0x4
  
  ; the array argv will be found in the location of the first argument placed on the stack for this function to consume
  mov ecx, [ebp+0xc]
 
  ; the 1st argument to the executable, a point to a character assumed to represent a legal integer, can be found 4 bytes offset from where eax points
  ; the 2nd argument to the executable, a pointer to a character assumed to reporesent a legal integer, can be found 8 bytes offset from where eax points
  ; move the 1st argument onto the stack in preparation for calling atoi
  mov eax, [ecx+0x4]
  mov [esp], eax
  call atoi

  ; restore the stack to its original state
  add esp, 0x4

  ; eax has our integer value of outer_limit that we can now store
  mov [ebp-0x4], eax

  ; implement inner_limit = atoi(argv[2]) just as above, but adjusted for the other offset
  sub esp, 0x4
  mov ecx, [ebp+0xc]
  mov eax, [ecx+0x8]
  mov [esp], eax
  call atoi
  add esp, 0x4
  mov [ebp-0x8], eax
  

  ; set up counter1 for outer for loop
  xor esi, esi
  ; outer for loop
  for_outer:

  ; compare counter1 to outer_limit 
  cmp esi, [ebp-0x4] 
  jge exit
  
  ; set up counter2 for innner for loop
  mov edi, 0x2
  for_inner:
  
  ; compare counter2 to inner_limit
  cmp edi,[ebp-0x8] 
  jle end_inner

  push edi
  push esi
  ; call complex_function
  call complex

  ; clean up the stack
  add esp, 0x8
	
  ; Print output
  ; move printf arguments on to the stack
  push eax
  push edi
  push esi
  
  ; move format string onto the stack
  mov eax, format_string  
  push eax

  ;call printf
  call printf

  ; reset the stack to its state before printf
  add esp, 0x10

  ; decrement counter2
  sub edi, 0x1

  ; jump to begining of inner loop
  jmp for_inner

  end_inner: 
  
  ; increment counter1
  add esi, 0x1

  ; jump to the start of the outer loop
  jmp for_outer

complex:
  push ebp
  mov ebp, esp

  ; variable list
  ; arg1 = [ebp+0x8]
  ; arg2 = [ebp+0xc]
  ; temp1 = [ebp-0x4]
  ; temp2 = [ebp-0x8]
  ; temp3 = [ebp-0xc]

  ; allocate space for variables temp1, temp2, and temp3
  sub esp, 0xc

  ; sets up temp1
  ; int temp1 = arg1 - 7
  mov ecx, [ebp+0x8]
  mov [ebp-0x4], ecx 
  sub DWORD [ebp-0x4], 0x7

  ; sets up temp2
  ; int temp2 = arg2
  mov ecx, [ebp+0xc]
  mov [ebp-0x8], ecx 

  ; sets up temp3 
  ; int temp3 = arg1 * arg2
  mov eax, [ebp+0x8]
  mul DWORD [ebp+0xc]
  mov [ebp-0xc], eax

  ; sets up retval
  ; int retval = temp1
  mov eax, [ebp-0x4]

  ; if temp2 < 0, adds 17 to retval else subtracts 13 from retval
  cmp DWORD [ebp-0x8], 0
  jge else
  add eax, 0x11
  jmp endif
  else:
  sub eax, 0xd
  endif:

  ; switch statement on arg1
  cmp DWORD [ebp+0x8], 0
  je case_0
  cmp DWORD [ebp+0x8], 1
  je case_1
  cmp DWORD [ebp+0x8], 2
  je case_2
  cmp DWORD [ebp+0x8], 3
  je case_3
  jmp dfault

  case_0:
  ; retval = retval + temp2 + some_static_int + 4
  add eax, [ebp-0x8]
  add eax, [var_s]
  add eax, 0x4
 
  case_1:
  ; retval = retval - temp2 + 5
  sub eax, [ebp-0x8]
  add eax, 0x5
  jmp break

  case_2:
  ; retval = retval - 13 - some_static_int
  sub eax, 0xd
  sub eax, [var_s]
  jmp break

  case_3:
  ; retval = retval + (temp3 * 7) - temp2
  push eax
  mov eax, 0x7
  mul DWORD [ebp-0xc]
  pop edx
  add eax, edx
  sub eax, [ebp-0x8]

  dfault:
  ; retval += 1;
  add eax, 0x1

  break:

  ; some_static_int = some_static_int - arg1 + retval
  mov ecx, [ebp+0x8]
  sub [var_s], ecx 
  add [var_s], eax

  leave
  ret

  exit:
  ; reset the stack to its orginal state
 ; add esp, 0x8

  ; set eax to 0 to return success to the caller of main()
  xor eax, eax

  ; resotre the stack frame for the caller
  leave

  ; and return 
  ret
















