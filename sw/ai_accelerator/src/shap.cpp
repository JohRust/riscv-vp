#include "shap.h"
#include <cstdint>

#include "ai_caller.h"

std::vector<std::vector<float>> background_data;

void replaceValues(std::vector<float>& array, const std::vector<bool>& mask, const std::vector<float>& newValues) {
	// Replace values in the array based on the mask
	for (std::size_t i = 0; i < array.size(); ++i) {
		if (mask[i]) {
			array[i] = newValues[i];
		}
	}
}

uint32_t binomialCoeff(uint32_t n, uint32_t k) {
	// Calculate the binomial coefficient
	if (k > n - k) {
		k = n - k;
	}
	uint32_t res = 1;
	for (uint32_t i = 0; i < k; ++i) {  // tested
		res *= (n - i);
		res /= (i + 1);
	}
	return res;
}

uint64_t factorial(uint64_t n) {
	// Factorials larger than 20 cause overflow
	if (n > 20) return -1;

	uint64_t res = 1;
	for (uint32_t i = 1; i <= n; ++i) {
		res *= i;
	}
	return res;
}

float shapley_frequency(uint32_t n, uint32_t s) {
	// Calculate the frequency of feature i in the shapley value calculation.
	// Equvalent to (n-s-1)! * s! / n!, but without overflow
	if (n-s <= 0) {
		return 0;
	}
	return 1.0f / (binomialCoeff(n, s) * (n-s));
}

void explainPrediction(std::vector<float> input_data, std::vector<float>& shapley_values) {
	// Calculate the shapley value of every value in input_data
	uint32_t n = input_data.size();
	for (uint32_t i = 0; i < n; ++i) {
		shapley_values[i] = 0;
	}

	std::vector<bool> mask(n, false);
	for (uint32_t i = 0; i < n; ++i) {  // Shapley value for feature i
		mask[i] = true;
		uint64_t num_subsets = 1 << (n - 1);  // 2^(n-1) subsets of N\{i}
		for (uint32_t j = 0; j < num_subsets; ++j) {
			if (j == i) {
				continue;  // Exclude the feature itself
			}

			auto mask = getAsBoolVector(j, n - 1);
			mask.insert(mask.begin() + i, false);  // Add the feature back in
			// We need to know the size of the subset called |S|
			uint32_t numMasked = 0;
			for (uint32_t k = 0; k < n; ++k) {
				if (mask[k]) {
					numMasked++;
				}
			}
			std::vector<float> data_masked(input_data);
			replaceValues(data_masked, mask, input_data);

			input_data[i] = 1;
			float pred_with_i = req_prediction(&data_masked[0], data_masked.size());
			input_data[i] = 0;
			float pred_without_i = req_prediction(&input_data[0], input_data.size());

			shapley_values[i] += shapley_frequency(n, numMasked) * (pred_with_i - pred_without_i);
		}
	}
}

std::vector<bool> getAsBoolVector(uint32_t n, uint16_t length) {
	std::vector<bool> res(length, false);
	for (uint16_t i = 0; i < length; ++i) {
		if (n & (1 << i)) {
			res[i] = true;
		}
	}
	return res;
}