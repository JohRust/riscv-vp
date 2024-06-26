#pragma once


/**
 * @brief Requests a predictions for the input data using a linear regression model.
 *
 * @param input_data The array of input data.
 * @param input_size The size of the input data array.
 *
 * @return The predicted output value.
 */
float reqPrediction(const float *input_data, unsigned int input_size);

/**
 * @brief Requests a predictions for the input data using a linear regression model implemented in a dummy FPGA.
 *
 * @param input_data The array of input data.
 * @param input_size The size of the input data array.
 *
 * @return The predicted output value.
 */
float reqPredictionFPGA(const float *input_data, unsigned int input_size);

/** Simulates a prediction function like the example from Wikipedia for testing purposes:
 * https://de.wikipedia.org/wiki/Shapley-Wert#Beispiel
 */
float reqPrediction_dummy(const float *input_data, unsigned int input_size);

/**
 * @brief Initializes the DMA controller.
 */
void init_dma();