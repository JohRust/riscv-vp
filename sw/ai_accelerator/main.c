#include "stdio.h"
#include "errno.h"
#include "string.h"
#include "unistd.h"

#include "ai_accelerator.h"
#include "ai_caller.h"

volatile int was_itr_triggered = 0;

int main(int argc, char **argv) {
	int n = printf("Running Linear Regression\n");

	float input_data[4] = {1.0, 2.0, 3.0, 4.0};
	float prediction = do_prediction(input_data, 4);
	
	printf("Prediction: %f\n", prediction);

	float shapley_values[4];
	explain_prediction(input_data, 4, shapley_values);

	return 0;
}
