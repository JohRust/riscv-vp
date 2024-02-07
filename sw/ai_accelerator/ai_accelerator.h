#include "stdio.h"
#include "errno.h"
#include "string.h"
#include "unistd.h"

float COEFFS[4] = {1.2, 3.4, 5.6, 7.8};
float predict(float *input_data, unsigned int size, unsigned int delay);
