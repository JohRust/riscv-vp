#include <vector>
#include "stdio.h"
#include "unistd.h"
#include "shap.h"
#include "ai_caller.h"
extern "C" {
	#include "irq.h"
}

int main(int argc, char **argv) {
	init_dma();
	std::vector<float> input_data = {1.0, 2.0, 3.0, 4.0};
	std::vector<std::vector<float>> background_data = {
		{0.0, 0.5, 1.0, 1.5}, {1.0, 1.5, 2.0, 2.5}, {2.0, 2.5, 3.0, 3.5}};
	std::vector<float> shapley_values = explainPrediction(input_data, reqPredictionFPGA, background_data);
	printf("Shapley values:\n");
	for (auto value : shapley_values) {
		printf("%f ", value);
	}
	puts("\n");
	return 0;
}
