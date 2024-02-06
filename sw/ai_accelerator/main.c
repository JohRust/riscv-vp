#include "stdio.h"
#include "errno.h"
#include "string.h"
#include "unistd.h"


int main(int argc, char **argv) {
	int n = printf("ABCDEFX %s\n", "Done");

	float input_data[4] = {1.0, 2.0, 3.0, 4.0};
	printf("Prediction: %f\n", predict(input_data, 4, 0));

	return 0;
}
