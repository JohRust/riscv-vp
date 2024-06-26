#include "ai_caller.h"
#include "ai_accelerator.h"
extern "C" {
	#include "irq.h"
}

static volatile uint32_t * const DMA_SRC_ADDR  = (uint32_t * const)0x70000000;
static volatile uint32_t * const DMA_DST_ADDR  = (uint32_t * const)0x70000004;
static volatile uint32_t * const DMA_LEN_ADDR  = (uint32_t * const)0x70000008;
static volatile uint32_t * const DMA_OP_ADDR   = (uint32_t * const)0x7000000C;
static volatile uint32_t * const DMA_STAT_ADDR = (uint32_t * const)0x70000010;

static const uint32_t DMA_OP_NOP = 0;
static const uint32_t DMA_OP_MEMCPY = 1;

volatile bool prediction_done = false;

float reqPredictionFPGA(const float *input_data, unsigned int input_size) {
	float pred = predict(input_data, input_size, 0);
	// Imagine that the prediction is done on a parallel hardware accelerator
	prediction_done = false;
	float pred_in_memory;
	*DMA_SRC_ADDR = (uint32_t)(&pred);
	*DMA_DST_ADDR = (uint32_t)(&pred_in_memory);
	*DMA_LEN_ADDR = sizeof(pred);
	*DMA_OP_ADDR  = DMA_OP_MEMCPY;

	while (!prediction_done) {
		asm volatile("wfi");
	}
	return pred_in_memory;
}

void dma_irq_handler() {
	prediction_done = true;
}

void init_dma() {
	register_interrupt_handler(4, dma_irq_handler);
}

float reqPrediction(const float *input_data, unsigned int input_size) {
	return predict(input_data, input_size, 0);
}

float reqPrediction_dummy(const float *input_data, unsigned int input_size) {
	// {}
	if (input_data[0] == 0 && input_data[1] == 0 && input_data[2] == 0) {
		return 0.0;
	}
	// {b}
	if (input_data[0] == 0 && input_data[1] == 1 && input_data[2] == 0) {
		return 6.0;
	}
	// {a}
	if (input_data[0] == 1 && input_data[1] == 0 && input_data[2] == 0) {
		return 12.0;
	}
	// {a, b}
	if (input_data[0] == 1 && input_data[1] == 1 && input_data[2] == 0) {
		return 24.0;
	}
	// {c}
	if (input_data[0] == 0 && input_data[1] == 0 && input_data[2] == 1) {
		return 9.0;
	}
	// {b, c}
	if (input_data[0] == 0 && input_data[1] == 1 && input_data[2] == 1) {
		return 15.0;
	}
	// {a, c}
	if (input_data[0] == 1 && input_data[1] == 0 && input_data[2] == 1) {
		return 27.0;
	}
	// {a, b, c}
	if (input_data[0] == 1 && input_data[1] == 1 && input_data[2] == 1) {
		return 36.0;
	}
	return 0.0;
}
