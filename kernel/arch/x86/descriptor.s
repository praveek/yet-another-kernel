.section .text
.global installGDT
.type installGDT, @function
installGDT:
    mov 4(%esp), %eax  // Get the pointer to the GDT, passed as a parameter.
    lgdt (%eax)
    mov $0x10, %ax 
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    jmp $0x08,$.flush
.flush:
    ret

.global installIDT
.type installIDT, @function
installIDT:
    mov 4(%esp), %eax  // Get the pointer to the IDT, passed as a parameter.
    lidt (%eax)
    ret

isrCommon:
  pusha               
  mov %ds, %ax        
  push %eax           

  mov $0x10, %ax      
  mov %ax, %ds
  mov %ax, %es
  mov %ax, %fs
  mov %ax, %gs
  
  call isrHandler

  pop %eax
  mov %ax, %ds
  mov %ax, %es
  mov %ax, %fs
  mov %ax, %gs
  
  popa
  add $8, %esp
  sti
  iret

.macro ISR_NOERRCODE num
.global isr\num
.type isr\num, @function
isr\num:
    cli
    push $0
    push $\num
    jmp isrCommon
.endm

.macro ISR_ERRCODE num
.global isr\num
.type isr\num, @function
isr\num:
    cli
    push $\num
    jmp isrCommon
.endm

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_ERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_ERRCODE 30
ISR_NOERRCODE 31
