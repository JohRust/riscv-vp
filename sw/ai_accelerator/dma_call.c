#include "dma_call.h"

void dma_irq_handler() {
	dma_completed = 1;
}
