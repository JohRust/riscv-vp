#include "ai_caller.h"
#include "ai_accelerator.h"

void explain_prediction(float *input_data, unsigned int size, float *shapley_values){
    int NUM_INPUTS = 12;
    float inputs[NUM_INPUTS][size];

    // Create NUM_INPUTS copies of the input data
    for(int i = 0; i < NUM_INPUTS; i++){
        for(int j = 0; j < size; j++){
            inputs[i][j] = input_data[j];
        }
    }

    // Do predictions for each input
    float predictions[NUM_INPUTS];
    for(int i = 0; i < NUM_INPUTS; i++){
        predictions[i] = req_prediction(inputs[i], size);
    }

    for(int i = 0; i < size; i++){
        shapley_values[i] = .0;
    }
}


float req_prediction(const float *input_data, unsigned int input_size){
    float pred;
    dma_completed = 0;
	*DMA_SRC_ADDR = (uint32_t)(&input_data[0]);
	*DMA_DST_ADDR = (uint32_t)(&pred);
	*DMA_LEN_ADDR = sizeof(input_size);
	*DMA_OP_ADDR  = DMA_OP_MEMCPY;

    while (!dma_completed) {
        asm volatile ("wfi");
    }
    return pred;
}
