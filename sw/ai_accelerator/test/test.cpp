#include <iostream>
#include <stdint.h>
#include <gtest/gtest.h>
#include "../src/shap.h"
#include "../src/ai_caller.h"

TEST(getAsBoolVector, getAsBoolVectorTest) {
    EXPECT_EQ(getAsBoolVector(5, 5), std::vector<bool>({true, false, true, false, false}));
    EXPECT_EQ(getAsBoolVector(6, 5), std::vector<bool>({false, true, true, false, false}));
    EXPECT_EQ(getAsBoolVector(7, 5), std::vector<bool>({true , true, true, false, false}));
}

TEST(replaceValues, replaceValuesTest) {
    std::vector<float> array = {1, 2, 3, 4, 5};
    std::vector<bool> mask = {true, false, true, false, true};
    std::vector<float> newValues = {10, 20, 30, 40, 50};
    replaceValues(array, mask, newValues);
    EXPECT_EQ(array[0], 1);
    EXPECT_EQ(array[1], 20);
    EXPECT_EQ(array[2], 3);
    EXPECT_EQ(array[3], 40);
    EXPECT_EQ(array[4], 5);
}

// Test the binomial coefficient function
TEST(binomialCoeff, bonimialCoeffTest) {
    EXPECT_EQ(binomialCoeff(5, 2), 10);
    EXPECT_EQ(binomialCoeff(10, 3), 120);
    EXPECT_EQ(binomialCoeff(1000, 999), 1000);
    EXPECT_EQ(binomialCoeff(6, 4), 15);
    EXPECT_EQ(binomialCoeff(6, 2), 15);
    EXPECT_EQ(binomialCoeff(8, 0), 1);
    EXPECT_EQ(binomialCoeff(0, 0), 1);
}

TEST(factorial, factorialTest) {
    EXPECT_EQ(factorial(5), 120);
    EXPECT_EQ(factorial(10), 3628800);
    EXPECT_EQ(factorial(6), 720);
    EXPECT_EQ(factorial(8), 40320);
    EXPECT_EQ(factorial(0), 1);
    EXPECT_EQ(factorial(20), 2432902008176640000);
    EXPECT_EQ(factorial(21), -1); // Avoid overflow
    EXPECT_EQ(factorial(-1), -1); // Negative values are invalid input
}

TEST(shapleyFrequency, shapleyFrequencyTest) {
    EXPECT_FLOAT_EQ(shapleyFrequency(3, 0), 0.333333343);
    EXPECT_FLOAT_EQ(shapleyFrequency(3, 1), 0.1666667);
    EXPECT_FLOAT_EQ(shapleyFrequency(3, 2), 0.333333343);
    EXPECT_FLOAT_EQ(shapleyFrequency(3, 3), 0.0); // Special case to avoid undefined behavior 
}

TEST(reqPrediction, reqPredictionTest) {
    float input_data[4] = {0, 0, 0, 0};
    reqPrediction(input_data, 4);
    EXPECT_FLOAT_EQ(reqPrediction(input_data, 4), 0.0);
    float input_data2[4] = {1, 2, 3, 4};
    EXPECT_FLOAT_EQ(reqPrediction(input_data2, 4), 56.0);
    float input_data3[4] = {0, 0, 0, 1};
    EXPECT_FLOAT_EQ(reqPrediction(input_data3, 4), 7.8);
}

TEST(explainPrediction, explainPredictionTest) {
    std::vector<float> input_data = {1.0, 1.0, 1.0};
    std::vector<std::vector<float>> background_data = {{0.0, 0.0, 0.0}};
    std::vector<float> shapley_values = explainPrediction(input_data, reqPrediction_dummy, background_data);
    EXPECT_FLOAT_EQ(reqPrediction_dummy(input_data.data(), input_data.size()), 36.0);
    EXPECT_EQ(shapley_values.size(), 3);
    EXPECT_FLOAT_EQ(shapley_values[0], 17.0);
    EXPECT_FLOAT_EQ(shapley_values[1], 8.0); // This is the case from Wikipedia
    EXPECT_FLOAT_EQ(shapley_values[2], 11.0);
    EXPECT_EQ(input_data, std::vector<float>({1.0, 1.0, 1.0})); // Ensure input data is unchanged
}

TEST(explainPrediction, paretoEfficiencyTest) {
    std::vector<float> input_data = {1.0, 1.0, 1.0};
    std::vector<std::vector<float>> background_data = {{0.0, 0.0, 0.0}};
    std::vector<float> shapley_values = explainPrediction(input_data, reqPrediction_dummy, background_data);
    int shapley_sum = 0;
    for (auto value : shapley_values) {
        shapley_sum += value;
        EXPECT_GE(value, 0);
    }
    EXPECT_EQ(shapley_sum, 36);
}

TEST(sampleFromData, sampleFromDataTest) {
    std::vector<std::vector<float>> data = {{1.0, 12.0, 23.0, 34.0}, {4.0, 15.0, 26.0, 37.0}, {7.0, 18.0, 29.0, 39.0}};
    std::vector<float> sample = sampleFromData(data);
    EXPECT_EQ(sample.size(), 4);
    EXPECT_GE(sample[0], 1.0);
    EXPECT_LE(sample[0], 7.0);
    EXPECT_GE(sample[1], 12.0);
    EXPECT_LE(sample[1], 18.0);
    EXPECT_GE(sample[2], 23.0);
    EXPECT_LE(sample[2], 29.0);
    EXPECT_GE(sample[3], 34.0);
    EXPECT_LE(sample[3], 39.0);

    data = {{0.0, 0.0, 0.0}};
    sample = sampleFromData(data);
    EXPECT_EQ(sample.size(), 3);
    for (auto value : sample) {
        EXPECT_EQ(value, 0.0);
    }
}

/* Test the Shapley value calculation of a linear regression model.
The coefficients become larger as the index increases,
so the Shapley value should be larger for the later indices.
*/
TEST(explainPrediction, explainPredictionTest2) {
    std::vector<float> input_data = {1.0, 2.0, 3.0, 4.0};
    std::vector<std::vector<float>> background_data = {{0.0, 0.5, 1.0, 1.5}, {1.0, 1.5, 2.0, 2.5}, {2.0, 2.5, 3.0, 3.5}};
    std::vector<float> shapley_values = explainPrediction(input_data, reqPrediction, background_data);
    EXPECT_EQ(shapley_values.size(), input_data.size());
    EXPECT_GE(shapley_values[3], shapley_values[2]);
    EXPECT_GE(shapley_values[2], shapley_values[1]);
    EXPECT_GE(shapley_values[1], shapley_values[0]);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
