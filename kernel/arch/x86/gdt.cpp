#include "gdt.h"
#include <stdint.h>

namespace
{

struct GDTDescriptor
{
  uint16_t limitLow;
  uint16_t baseLow;
  uint8_t baseMiddle;
  uint8_t access;
  uint8_t granularity;
  uint8_t baseHigh;
}__attribute__((packed));

struct GDTPtr {
  uint16_t limit;
  uint32_t base;
}__attribute__((packed));

GDTDescriptor createDescriptor(uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
  GDTDescriptor ret;
  ret.baseLow = (base & 0xFFFF);
  ret.baseMiddle = (base >> 16) & 0xFF;
  ret.baseHigh = (base >> 24) & 0xFF;
  ret.limitLow = (limit & 0xFFFF);
  ret.granularity = (limit >> 16) & 0x0F;
  ret.granularity |= granularity & 0xF0;
  ret.access = access;
  return ret;
}

GDTDescriptor gdtDesc[5];
GDTPtr gdtPtr;
}

extern "C" void installGDT(GDTPtr*);

void setupGDT() {
  gdtDesc[0] = createDescriptor(0,0,0,0);                   // Null segment
  gdtDesc[1] = createDescriptor(0, 0xFFFFFFFF, 0x9A, 0xCF); // Kernel Code segment
  gdtDesc[2] = createDescriptor(0, 0xFFFFFFFF, 0x92, 0xCF); // Kernel Data segment
  gdtDesc[3] = createDescriptor(0, 0xFFFFFFFF, 0xFA, 0xCF); // User Code segment
  gdtDesc[4] = createDescriptor(0, 0xFFFFFFFF, 0xF2, 0xCF); // User Data segment

  gdtPtr.limit = sizeof(gdtDesc) - 1;
  gdtPtr.base = (uintptr_t) gdtDesc;

  installGDT(&gdtPtr);
}
