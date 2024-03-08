#pragma once


/**
 * @brief Requests a predictions for the input data using a linear regression model.
 *
 * @param input_data The array of input data.
 * @param input_size The size of the input data array.
 *
 * @return The predicted output value.
 */
float req_prediction(const float *input_data, unsigned int input_size);
