#pragma once

/**
 * @brief Calculates the shapley value of every value in input_data.
 * 
 * @param input_data The array of input data.
 * @param size The size of the input data array.
 * @param shapley_values The array where shapley values are written into.
 */
void explain_prediction(float *input_data, unsigned int size, float *shapley_values);

/**
 * @brief Requests a predictions for the input data using a linear regression model.
 * 
 * @param input_data The array of input data.
 * @param size The size of the input data array.
 * 
 * @return The predicted output value.
*/
float req_prediction(float *input_data, unsigned int size);
