#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <iostream>
using namespace std;
#include "sorter.h"
#include "timer.h"

constexpr int K = 11;

// SORTER -----

void Sorter::fill(int count, string file_name){
    vec.clear(); // this will clear the existing vector...
    ifstream input(file_name); // opens the input file
    string word;
    int i = 0;
    while (i < count && input >> word){
        vec.push_back(word);
        i++;
    }
    input.close();
}
void Sorter::print(ostream & out){
    for (const string & word : vec)
        out << word << " ";
}
bool Sorter::verify_sorted(){
    for (size_t i = 1; i < vec.size(); i++)
        if (vec[i] < vec[i-1]) return false;
    return true;
}

// INSERTIONSORTER -----

void InsertionSorter::insertionsort(vector<string> & vec, int low, int high){}
void InsertionSorter::sort(){}

// QUICKSORTER -----

string QuickSorter::select_pivot(vector<string> & vec, int low, int high){}
int QuickSorter::partition(vector<string> & vec, int low, int high){}
void QuickSorter::quicksort(vector<string> & vec, int low, int high){}
void QuickSorter::sort(){}

// HEAPSORTER -----

void HeapSorter::heapify(vector<string> & vec, int high, int root){}
void HeapSorter::heapsort(vector<string> & vec, int low, int hight){}
void HeapSorter::sort(){}

// INTROSORTER -----

void IntroSorter::introsort(vector<string> & vec, int low, int high){}
void IntroSorter::sort(){}

// STLSORTER -----

void STLSorter::sort(){}

// STABLESORTER -----

void StableSorter::sort(){}

// SHELLSORTER -----

void ShellSorter::gapInsertionSort(vector<string> & avector, int start, int gap){}
void ShellSorter::shellSort(vector<string> & avector){}
void ShellSorter::sort(){}

// OTHER FUNCTIONS -----

ostream & operator << (ostream & out, Sorter & L){}
void error(string word, string msg){}
void measure_partition(int k, string file_name, Sorter & L){}
void measure_partitions(string file_name, Sorter & L){}
void measure_sorters(string input_file){}






