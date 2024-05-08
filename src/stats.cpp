#include <string>
#include <vector>
#include <map>
#include <cmath>
#include "stats.h"


double compute_mean(const std::vector <int>&v)
{
    double sum=0;
    for(auto &n:v)
        sum+=n;
    return sum/v.size();
}

double compute_stddev(const std::vector <int>&v)
{
    double sum_squares=0;
    double mean = compute_mean(v);
    double len = v.size();
    for(auto n:v)
    {
        double diff = n-mean;
        sum_squares+=diff *diff;

    }
    return sqrt(sum_squares/len);

}


Stats::Stats(string name, const vector<int> & chain_lengths)
    :name(name),chain_lengths(chain_lengths)
{
    for (int num : chain_lengths) 
    {
        entries += num;
    }

    // Compute other statistics
    chains = chain_lengths.size();
    load_factor = static_cast<double>(entries) / chains;
    min = *min_element(chain_lengths.begin(), chain_lengths.end());
    max = *max_element(chain_lengths.begin(), chain_lengths.end());
   
    mean = compute_mean(chain_lengths);
    stddev = compute_stddev(chain_lengths);

    // Compute histogram
    for (int length : chain_lengths) {
        histogram[length]++;
    }
}