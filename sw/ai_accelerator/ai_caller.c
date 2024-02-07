#include "ai_caller.h"

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
        predictions[i] = do_prediction(inputs[i], size);
    }

    for(int i = 0; i < size; i++){
        shapley_values[i] = .0;
    }
}


float do_prediction(float *input_data, unsigned int size){
    // TODO: Implement this function
}
