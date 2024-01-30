#include "stdio.h"
#include "errno.h"
#include "string.h"
#include "unistd.h"

float PARAMS[4] = {1.2, 3.4, 5.6, 7.8};
float predict(float *input_data, unsigned int size, unsigned int delay);

int main(int argc, char **argv) {
	int n = printf("ABCDEFX %s\n", "Done");

	float input_data[4] = {1.0, 2.0, 3.0, 4.0};
	printf("Prediction: %f\n", predict(input_data, 4, 0));

	return 0;
}

/**
 * @brief Waits for a specified number of operations.
 *
 * This function waits for a specified number of operations by executing a series of "nop" instructions.
 * The number of operations to wait for is determined by the parameter nOps.
 *
 * @param nOps The number of operations to wait for.
 */
void wait(uint32_t nOps) {
	for(uint32_t i = 0; i < nOps; i++) {
		asm("nop"); // TODO correlate nOps to clocks/time waited
	}
}

/**
 * Predicts the output based on the input data using a linear regression model.
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
float predict(float *input_data, unsigned int size, unsigned int delay)
{
	wait(delay);
	float sum = 0.0;
	for (int i = 0; i < size; i++)
	{
		sum += PARAMS[i] * input_data[i];
	}
	return sum;
}
