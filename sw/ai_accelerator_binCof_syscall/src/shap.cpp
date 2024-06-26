#include "shap.h"
#include <cstdint>
#include <iostream>
#include "ai_caller.h"

extern "C" int make_syscall(int arg1, int arg2, int syscall_number);

void replaceValues(std::vector<float>& array, const std::vector<bool>& mask, const std::vector<float>& newValues) {
	// Replace values in the array based on the mask
	for (std::size_t i = 0; i < array.size(); ++i) {
		if (!mask[i]) {
			array[i] = newValues[i];
		}
	}
}

uint32_t binomialCoeff(uint32_t n, uint32_t k) {
	// Calculate the binomial coefficient
/** if (k > n - k) {
		k = n - k;
	}
	uint32_t res = 1;
	for (uint32_t i = 0; i < k; ++i) {  // tested
		res *= (n - i);
		res /= (i + 1);
	}
	return res;
*/
	return make_syscall(n, k, 701);
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

std::vector<float> sampleFromData(const std::vector<std::vector<float>> data) {
	std::vector<float> res;
	for (size_t i=0; i < data[0].size(); ++i) {
		res.push_back(data[rand() % data.size()][i]);
	}
	return res;
}

float shapleyFrequency(uint32_t n, uint32_t s) {
	// Calculate the frequency of feature i in the shapley value calculation.
	// Equvalent to (n-s-1)! * s! / n!, but without overflow
	if (n-s <= 0) {
		return 0;
	}
	return 1.0f / (binomialCoeff(n, s) * (n-s));
}

std::vector<float> explainPrediction(std::vector<float> input_data, float (func)(const float*, unsigned int)) {
	std::vector<std::vector<float>> bgData = {std::vector<float>(input_data.size(), 0)};
	return explainPrediction(input_data, func, bgData);
}

std::vector<float> explainPrediction(std::vector<float> input_data, float (func)(const float*, unsigned int), std::vector<std::vector<float>> background_data) {
	uint32_t n = input_data.size();
	std::vector<float> shapley_values(n, 0);
	std::vector<bool> mask(n, false);

	for (uint32_t i = 0; i < n; ++i) {  // Shapley value for feature i
		uint64_t num_subsets = 1 << (n - 1);  // 2^(n-1) subsets of N\{i}
		for (uint32_t j = 0; j < num_subsets; ++j) {
			auto mask = getAsBoolVector(j, n - 1);
			mask.insert(mask.begin() + i, false);  // Add the feature back in
			// We need to know |S|, the size of the subset
			uint32_t subsetSize = 0;
			for (uint32_t k = 0; k < n; ++k) {
				if (mask[k]) {
					subsetSize++;
				}
			}
			std::vector<float> data_masked(input_data);
			auto sampled_background = sampleFromData(background_data);
			replaceValues(data_masked, mask, sampled_background);
			auto pred_without_i = func(&data_masked[0], data_masked.size());
			
			data_masked[i] = input_data[i];
			auto pred_with_i = func(&data_masked[0], data_masked.size());
			shapley_values[i] += shapleyFrequency(n, subsetSize) * (pred_with_i - pred_without_i);
		}
	}
	return shapley_values;
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
