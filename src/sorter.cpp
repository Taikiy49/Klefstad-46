#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cmath>
#include <iostream>
using namespace std;
#include "sorter.h"
#include "timer.h"

constexpr int K = 11;

// SORTER -----
// a sorter organizes elements in a specific order, like numerical or alphabetical

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
// a insertion sorter iterates through a list of elements,
// inserting each element into its proper place within a sorted sublist.
// it repeatedly selects the next element and inserts it into the correct position
// it gradually builds a sorted sequence


void InsertionSorter::insertionsort(vector<string> & vec, int low, int high){
    for (int i = low + 1; i <= high; i++){
        string key = vec[i];
        int j = i - 1;
        while (j >= low && vec[j] > key){
            vec[j+1] = vec[j];
            j--;
        }
        vec[j+1] = key;
    }
}
void InsertionSorter::sort(){
    insertionsort(vec, 0, vec.size() - 1);
}

// QUICKSORTER -----
// sorts elements by recursively partitioning the array into small segments
// based on a chosen pivot element
// it arranges the elements so that elements less than the pivot are on one side
// and all greater elements are on the other, repeating this process until the entire array is sorted

string QuickSorter::select_pivot(vector<string> & vec, int low, int high){
    int mid = (low + high) / 2; // binary search!
    if (vec[mid] < vec[low]) swap(vec[low], vec[mid]);
    if (vec[high] < vec[low]) swap(vec[low], vec[high]);
    if (vec[mid] < vec[high]) swap(vec[mid], vec[high]);
    return vec[high];
}
int QuickSorter::partition(vector<string> & vec, int low, int high){
    string pivot = select_pivot(vec, low, high);
    for (int j = low; j < high; j++){
        if (vec[j] <= pivot){
            swap(vec[low], vec[j]);
            ++low;
        }
    }
    swap(vec[low], vec[high]);
    return low;
}
void QuickSorter::quicksort(vector<string> & vec, int low, int high){
    if (low < high){
        int pivotIndex = partition(vec, low, high);
        quicksort(vec, low, pivotIndex - 1);
        quicksort(vec, pivotIndex + 1, high);                  
    }
}
void QuickSorter::sort(){
    quicksort(vec, 0, vec.size() - 1);
}

// HEAPSORTER -----
// an algorithm that organizes eleemnts in a list into a binary heap structure
// allowing for effecient sorting...
// it repeatedly extracts the max (or min) element from the heap and
// rebuilds the heap until all elements are sorted!

void HeapSorter::heapify(vector<string> & vec, int high, int root){
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left <= high && vec[left] > vec[largest]) largest = left;
    if (right <= high && vec[right] > vec[largest]) largest = right;
    if (largest != root){
        swap(vec[root], vec[largest]);
        heapify(vec, high, largest);
    }
}
void HeapSorter::heapsort(vector<string> & vec, int low, int high){
    for (int i = (high - low) / 2 - 1; i >= low; i--) heapify(vec, high, i);
    for (int i = high; i > low; i--){
        swap(vec[low], vec[i]);
        heapify(vec, i - 1, low);
    }
}
void HeapSorter::sort(){
    heapsort(vec, 0, vec.size() - 1);
}

// INTROSORTER -----
// algorithm that begins with quicksort and switches to heapsort when
// the recursion depth exceeds a certain level, to ensure worst-case O(N log N) performance
// it combines the fast average performance of quicksort with the worst-case efficiency of heapsort

// i think another helper function that i could use for introsort here would be nice!
void introsort_util(vector<string> & arr, int low, int high, int depth_limit){
    if (high - low < 1){
        InsertionSorter::insertionsort(arr, low, high);
        return;
    }
    if (depth_limit == 0){
        HeapSorter::heapsort(arr, low, high);
        return;
    }
    int p = QuickSorter::partition(arr, low, high);
    introsort_util(arr, low, p - 1, depth_limit - 1);
    introsort_util(arr, p + 1, high, depth_limit - 1);
}
void IntroSorter::introsort(vector<string> & vec, int low, int high){
    int depth_limit = 2 * log(high - low);
    introsort_util(vec, low, high, depth_limit);
}
void IntroSorter::sort(){
    introsort(vec, 0, vec.size() - 1);
}

// STLSORTER -----
// starts with quicksort for fast average performance and switches to heapsort if the recursion depth becomes too deep
// this ensures worst-case O(N log N), and finishes with insertion sort for small partitions to optimize performance
void STLSorter::sort(){
    std::sort(vec.begin(), vec.end());
}

// STABLESORTER -----
// if two elements are equal, their order in the original list is preserved in the sorted list
// maintains the relative order of equal elements in the sorted output
void StableSorter::sort(){
    std::stable_sort(vec.begin(), vec.end());
}

// SHELLSORTER -----
// an in-place comparison-based sorting that generalizes insertion sort by allowing the exchange of items that are far apart.
// it starts by sorting elements that are a certain gap distance apart and gradually reduces the gap
// until it performs a final pass with a gap of 1, resulting in a sorted array

void ShellSorter::gapInsertionSort(vector<string> & avector, int start, int gap){
    int sz = avector.size();
    for (int i = start + gap; i < sz; i += gap){
        string currentValue = avector[i];
        int position = i; 
        while (position>=gap && avector[position-gap] > currentValue){
            avector[position] = avector[position-gap];
            position -= gap;
        }
        avector[position] = currentValue;
    }
}
void ShellSorter::shellSort(vector<string> & avector){
    int subvectorcount = avector.size() / 2;
    while (subvectorcount > 0){
        for (int startpos = 0; startpos < subvectorcount; startpos++){
            gapInsertionSort(avector, startpos, subvectorcount);
            subvectorcount = subvectorcount / 2;
        }
    }
}
void ShellSorter::sort(){
    shellSort(vec);
}

// OTHER FUNCTIONS -----

ostream & operator << (ostream & out, Sorter & L){
    L.print(out);
    return out;
}
void error(string word, string msg){
    cout << "ERROR: " <<  word << " " <<  msg << endl;
}
void measure_partition(int k, string file_name, Sorter & L)
{
    Timer t;
    double eTime;
    int limit = k*NWORDS/10;
    
    std::cout<<"\tK = "<<k<<endl;
    L.fill(limit, file_name);
    t.start();
    L.sort();
    t.elapsedUserTime(eTime);
    std::cout<<"\t\tI = "<<eTime<<endl;
    
}
void measure_partitions(string file_name, Sorter & L)
{
    std::cout<<L.name<<endl;
    for(int K=1; K<=10;++K)
    {
        measure_partition(K, file_name, L);
        if(!L.verify_sorted())
            error(L.name, "is not sorted");
    }
}
void measure_sorters(string input_file)
{
    InsertionSorter IS;
    measure_partitions(input_file, IS);
    QuickSorter QS;
    measure_partitions(input_file, QS);
    HeapSorter HS;
    measure_partitions(input_file, HS);
    IntroSorter NS;
    measure_partitions(input_file, NS);
    STLSorter SS;
    measure_partitions(input_file, SS);
    StableSorter TS;
    measure_partitions(input_file, TS);
    ShellSorter LS;
    measure_partitions(input_file, LS);







