#include "stdio.h"
#include "errno.h"
#include "string.h"
#include "unistd.h"


int main(int argc, char **argv) {
	int n = printf("Running Linear Regression\n");

	float input_data[4] = {1.0, 2.0, 3.0, 4.0};
	float prediction = predict(input_data, 4, 0);
	printf("Prediction: %f\n", prediction);

	return 0;
}
