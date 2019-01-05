#include "../../arch.h"
#include "gdt.h"
#include "idt.h"

void archInit() {
  setupGDT();
  setupIDT();
}

