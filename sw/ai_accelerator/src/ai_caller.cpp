#include "ai_caller.h"
#include "ai_accelerator.h"

/*
float req_prediction(const float *input_data, unsigned int input_size) {
	float pred;
	dma_completed = 0;
	*DMA_SRC_ADDR = (uint32_t)(&input_data[0]);
	*DMA_DST_ADDR = (uint32_t)(&pred);
	*DMA_LEN_ADDR = sizeof(input_size);
	*DMA_OP_ADDR = DMA_OP_MEMCPY;

	while (!dma_completed) {
		asm volatile("wfi");
	}
	return pred;
}
*/

float req_prediction(const float *input_data, unsigned int input_size) {
	return predict(input_data, input_size, 0);
}