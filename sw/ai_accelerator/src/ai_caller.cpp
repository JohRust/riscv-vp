#include "ai_caller.h"
#include "ai_accelerator.h"

/*
float reqPrediction(const float *input_data, unsigned int input_size) {
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

float reqPrediction(const float *input_data, unsigned int input_size) {
	return predict(input_data, input_size, 0);
}

float reqPrediction_dummy(const float *input_data, unsigned int input_size) {
	// {}
	if (input_data[0] == 0 && input_data[1] == 0 && input_data[2] == 0) {
		return 1.0;
	}
	if (input_data[0] == 0 && input_data[1] == 1 && input_data[2] == 0) {
		return 1.0 + 6.0;
	}
	// {a}
	if (input_data[0] == 1 && input_data[1] == 0 && input_data[2] == 0) {
		return 2.0;
	}
	if (input_data[0] == 1 && input_data[1] == 1 && input_data[2] == 0) {
		return 2.0 + 12.0;
	}
	// {c}
	if (input_data[0] == 0 && input_data[1] == 0 && input_data[2] == 1) {
		return 3.0;
	}
	if (input_data[0] == 0 && input_data[1] == 1 && input_data[2] == 1) {
		return 3.0 + 6.0;
	}
	// {a, c}
	if (input_data[0] == 1 && input_data[1] == 0 && input_data[2] == 1) {
		return 4.0;
	}
	if (input_data[0] == 1 && input_data[1] == 1 && input_data[2] == 1) {
		return 4.0 + 9.0;
	}
	return 0.0;	
}
