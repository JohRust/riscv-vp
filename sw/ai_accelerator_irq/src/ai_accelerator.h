#pragma once

#include "errno.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "unistd.h"

// Some random coefficients for the linear regression model
static float COEFFS[4] = {1.2, 3.4, 5.6, 7.8};
// Where the prediction requests are put
static volatile char *const ACCLERATOR_INPUT_ADDR = (char *const)0x50000000;

/**
 * @brief Waits for a specified number of operations.
 *
 * This function waits for a specified number of operations by executing a series of "nop" instructions.
 * The number of operations to wait for is determined by the parameter nOps.
 *
 * @param nOps The number of operations to wait for.
 */
void wait_nops(uint32_t nOps);

/**
 * @brief Predicts the output based on the input data using a linear regression model.
 *
 * This function takes an array of input data, the size of the array, and a delay
 * value as parameters. It calculates the sum of the product of each element in
 * the input data array with the corresponding element in the PARAMS array. The
 * calculation is delayed by the specified delay value using the wait function.
 *
 * @param input_data The array of input data.
 * @param size The size of the input data array.
 * @param delay The delay value in number of operations.
 * @return The predicted output value.
 */
float predict(const float *input_data, unsigned int size, unsigned int delay);
