#include "arch.h"
#include <stddef.h>
#include <stdint.h>


#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernelMain(void) {
  archInit();
  for(;;);
}
