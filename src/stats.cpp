
#include<iostream>
#include<vector>
#include "stats.h"
#include <cmath>
#include<algorithm> 

// Helper function to calculate the mean of a vector of integers
double compute_mean(const std::vector<int> &v) {
    double sum = 0;
    for (auto &n: v) {
        sum += n;
    }
    return sum / v.size();
}

// Helper function to calculate the standard deviation of a vector of integers
double compute_stddev(const std::vector<int> &v) {
    double mean = compute_mean(v);
    double sum_squares = 0;
    double len = v.size();
    for (auto n : v) {
        double diff = n - mean;
        sum_squares += diff * diff;
    }
    return std::sqrt(sum_squares / len);
}

// Helper function to find the minimum value in a vector of integers
int find_min(const std::vector<int> &v) {
    double min = v[0];
    for (auto n : v) {
        if (n < min) {
            min = n;
        }
    }
    return min;
}

// Helper function to find the maximum value in a vector of integers
int find_max(const std::vector<int> &v) {
    double max = v[0];
    for (int n : v) {
        if (n > max) {
            max = n;
        }
    }
    return max;
}

Stats::Stats(string name, const vector<int> &chain_lengths) {
    this->name = name;
    this->entries = chain_lengths.size();
    this->chains = count_if(chain_lengths.begin(), chain_lengths.end(), [](int n){ return n > 0; });
    this->load_factor = (double)entries / chains;
    this->min = find_min(chain_lengths);
    this->max = find_max(chain_lengths);
    this->span = max - min;
    this->mean = compute_mean(chain_lengths);
    this->stddev = compute_stddev(chain_lengths);

    // Generate the histogram
    for (int i = min; i <= max; i++) {
        histogram[i] = count(chain_lengths.begin(), chain_lengths.end(), i);
    }
}
