#include "shap.h"
#include "ai_caller.h"
#include <cstdint>


void replaceValues(std::vector<float>& array, const std::vector<bool>& mask, const std::vector<float>& newValues) {
    // Replace values in the array based on the mask
    for (size_t i = 0; i < array.size(); ++i) {
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
    for (uint32_t i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

// TODO: Extract requests and make 
void explainPrediction(const std::vector<float>& input_data, std::vector<float>& shapley_values) {
    // Calculate the shapley value of every value in input_data
    uint32_t n = input_data.size();
    for (uint32_t i = 0; i < n; ++i) {
        shapley_values[i] = 0;
    }
    for (uint32_t i = 0; i < n; ++i) {
        std::vector<bool> mask(n, false);
        mask[i] = true;
        for (uint32_t j = 0; j < n; ++j) {
            if (j != i) {
                mask[j] = true;
                uint32_t numMasked = 0;
                for (uint32_t k = 0; k < n; ++k) {
                    if (mask[k]) {
                        numMasked++;
                    }
                }
                std::vector<float> data_masked(input_data);
                replaceValues(data_masked, mask, input_data);
                float marginalContribution = (req_prediction(&input_data[0], input_data.size()) - req_prediction(&data_masked[0], data_masked.size())) / binomialCoeff(n - 1, numMasked);
                shapley_values[i] += marginalContribution;
                mask[j] = false;
            }
        }
    }
}
