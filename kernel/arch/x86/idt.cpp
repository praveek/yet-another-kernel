#include "idt.h"
#include <stddef.h>
#include <stdint.h>

// 0 - Division by zero exception
// 1 - Debug exception
// 2 - Non maskable interrupt
// 3 - Breakpoint exception
// 4 - 'Into detected overflow'
// 5 - Out of bounds exception
// 6 - Invalid opcode exception
// 7 - No coprocessor exception
// 8 - Double fault (pushes an error code)
// 9 - Coprocessor segment overrun
// 10 - Bad TSS (pushes an error code)
// 11 - Segment not present (pushes an error code)
// 12 - Stack fault (pushes an error code)
// 13 - General protection fault (pushes an error code)
// 14 - Page fault (pushes an error code)
// 15 - Unknown interrupt exception
// 16 - Coprocessor fault
// 17 - Alignment check exception
// 18 - Machine check exception
// 19-31 - Reserved

namespace {

struct registers {
    uint32_t ds;                                     // Data segment selector
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
    uint32_t int_no, err_code;                       // Interrupt number and error code (if applicable)
    uint32_t eip, cs, eflags, useresp, ss;           // Pushed by the processor automatically.
};

struct IDTDescriptor {
    uint16_t baseLow;
    uint16_t segmentSelector;
    uint8_t reserved;
    uint8_t flags;
    uint16_t baseHigh;
} __attribute__((packed));

struct IDTPtr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

IDTDescriptor createDescriptor(uint32_t base, uint16_t selector, uint8_t flags) {
    IDTDescriptor ret;
    ret.baseLow = (base & 0xFFFF);
    ret.baseHigh = (base >> 16) & 0xFFFF;
    ret.segmentSelector = selector;
    ret.flags = flags;
    ret.reserved = 0;
    return ret;
}

IDTDescriptor idtDesc[256];
IDTPtr idtPtr;
} // namespace

void *memset(void *ptr, int value, size_t num) {
    uint8_t *start = static_cast<uint8_t *>(ptr);
    for (size_t i = 0; i < num; ++i) {
        *(start++) = (uint8_t)value;
    }
    return ptr;
}

extern "C" void isr0();
extern "C" void isr1();
extern "C" void isr2();
extern "C" void isr3();
extern "C" void isr4();
extern "C" void isr5();
extern "C" void isr6();
extern "C" void isr7();
extern "C" void isr8();
extern "C" void isr9();
extern "C" void isr10();
extern "C" void isr11();
extern "C" void isr12();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();

extern "C" void installIDT(IDTPtr *);

void setupIDT() {
    memset(idtDesc, 0, sizeof(idtDesc));
    idtDesc[0] = createDescriptor((uint32_t)&isr0, 0x08, 0x8E);
    idtDesc[1] = createDescriptor((uint32_t)&isr1, 0x08, 0x8E);
    idtDesc[2] = createDescriptor((uint32_t)&isr2, 0x08, 0x8E);
    idtDesc[3] = createDescriptor((uint32_t)&isr3, 0x08, 0x8E);
    idtDesc[4] = createDescriptor((uint32_t)&isr4, 0x08, 0x8E);
    idtDesc[5] = createDescriptor((uint32_t)&isr5, 0x08, 0x8E);
    idtDesc[6] = createDescriptor((uint32_t)&isr6, 0x08, 0x8E);
    idtDesc[7] = createDescriptor((uint32_t)&isr7, 0x08, 0x8E);
    idtDesc[8] = createDescriptor((uint32_t)&isr8, 0x08, 0x8E);
    idtDesc[9] = createDescriptor((uint32_t)&isr9, 0x08, 0x8E);
    idtDesc[10] = createDescriptor((uint32_t)&isr10, 0x08, 0x8E);
    idtDesc[11] = createDescriptor((uint32_t)&isr11, 0x08, 0x8E);
    idtDesc[12] = createDescriptor((uint32_t)&isr12, 0x08, 0x8E);
    idtDesc[13] = createDescriptor((uint32_t)&isr13, 0x08, 0x8E);
    idtDesc[14] = createDescriptor((uint32_t)&isr14, 0x08, 0x8E);
    idtDesc[15] = createDescriptor((uint32_t)&isr15, 0x08, 0x8E);
    idtDesc[16] = createDescriptor((uint32_t)&isr16, 0x08, 0x8E);
    idtDesc[17] = createDescriptor((uint32_t)&isr17, 0x08, 0x8E);
    idtDesc[18] = createDescriptor((uint32_t)&isr18, 0x08, 0x8E);
    idtDesc[19] = createDescriptor((uint32_t)&isr19, 0x08, 0x8E);
    idtDesc[20] = createDescriptor((uint32_t)&isr20, 0x08, 0x8E);
    idtDesc[21] = createDescriptor((uint32_t)&isr21, 0x08, 0x8E);
    idtDesc[22] = createDescriptor((uint32_t)&isr22, 0x08, 0x8E);
    idtDesc[23] = createDescriptor((uint32_t)&isr23, 0x08, 0x8E);
    idtDesc[24] = createDescriptor((uint32_t)&isr24, 0x08, 0x8E);
    idtDesc[25] = createDescriptor((uint32_t)&isr25, 0x08, 0x8E);
    idtDesc[26] = createDescriptor((uint32_t)&isr26, 0x08, 0x8E);
    idtDesc[27] = createDescriptor((uint32_t)&isr27, 0x08, 0x8E);
    idtDesc[28] = createDescriptor((uint32_t)&isr28, 0x08, 0x8E);
    idtDesc[29] = createDescriptor((uint32_t)&isr29, 0x08, 0x8E);
    idtDesc[30] = createDescriptor((uint32_t)&isr30, 0x08, 0x8E);
    idtDesc[31] = createDescriptor((uint32_t)&isr31, 0x08, 0x8E);

    idtPtr.limit = sizeof(idtDesc) - 1;
    idtPtr.base = (uintptr_t)idtDesc;

    installIDT(&idtPtr);
}

extern "C" void isrHandler(registers reg) {}