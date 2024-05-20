#include "sorter.h"
#include <iostream>

int main()
{
    // measure_sorters("src/shortrandom.txt");
    measure_sorters("src/random.txt");
    // measure_sorters("src/shortsorted.txt");
    measure_sorters("src/sorted.txt");
}



#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <iostream>
using namespace std;
#include "sorter.h"
#include "timer.h"

constexpr int K = 11;

void Sorter::fill(int count, string file_name)
{
    // Clear the existing vector
    vec.clear();

    // Open the input file
    ifstream input(file_name);
    string word;
    int i = 0;
    while (i < count && input >> word)
    {
        vec.push_back(word);
        i++;
    }

    // Check if the desired count of words is not reached
    /*if (i < count)
    {
        // File does not have enough words
        error("fill", "File does not contain enough words.");
    }*/

    // Close the file
    input.close();
}

void Sorter::print(ostream & out)
{
    for (const string & word : vec)
        out << word << " ";
}

bool Sorter::verify_sorted()
{
    for (size_t i = 1; i < vec.size(); i++)
    {
        if (vec[i] < vec[i - 1])
            return false;
    }

    return true;
}

//////////////////////////

void InsertionSorter::insertionsort(vector<string>& vec, int low, int high)
{
    for (int i = low + 1; i <= high; i++)
    {
        string key = vec[i];
        int j = i - 1;

        while (j >= low && vec[j] > key)
        {
            vec[j + 1] = vec[j];
            j--;
        }

        vec[j + 1] = key;
    }
}

void InsertionSorter::sort() 
{
    insertionsort(vec, 0, vec.size() - 1);
}

/////////////////////////

string QuickSorter::select_pivot(vector<string>& vec, int low, int high)
{
    int mid = (low + high) / 2;
      if ( vec[mid] < vec[low] ) swap( vec[low], vec[mid] );
      if ( vec[high] < vec[low] ) swap( vec[low], vec[high] );
      if ( vec[mid] < vec[high] ) swap( vec[mid], vec[high] );
      return vec[high];


}

int QuickSorter::partition(vector<string>& vec, int low, int high)
{
    /*string pivot = select_pivot( vec, low, high );
    int below = low;
    int above = high - 1;
    for ( ; ; ) {
          while ( vec[below] < pivot ) { ++below; }
          while ( pivot < vec[above] ) { --above; }
          if ( below < above )    
              swap( vec[below++], vec[above--] );
          else break;
    } 
    swap( vec[below], vec[high] );  
    return below;*/

    string pivot = select_pivot(vec, low, high);

    for (int j = low; j < high; j++) {
        if (vec[j] <= pivot) {
            swap(vec[low], vec[j]);
            ++low;
        }
    }

    swap(vec[low], vec[high]);
    return low;


}

void QuickSorter::quicksort(vector<string>& vec, int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partition(vec, low, high);
        quicksort(vec, low, pivotIndex - 1);
        quicksort(vec, pivotIndex + 1, high);
    }
}

void QuickSorter::sort() 
{
    quicksort(vec, 0, vec.size() -1 );
}

////////////////////////

void HeapSorter::heapify(vector<string>& vec, int high, int root)
{
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left <= high && vec[left] > vec[largest])
        largest = left;

    if (right <= high && vec[right] > vec[largest])
        largest = right;

    if (largest != root)
    {
        swap(vec[root], vec[largest]);
        heapify(vec, high, largest);
    }
}

void HeapSorter::heapsort(vector<string>& vec, int low, int high)
{
    for (int i = (high - low) / 2 - 1; i >= low; i--)
    {
        heapify(vec, high, i);
    }

    for (int i = high; i > low; i--)
    {
        swap(vec[low], vec[i]);
        heapify(vec, i - 1, low);
    }
}

void HeapSorter::sort() 
{
    heapsort(vec, 0, vec.size() - 1);
}

///////////////////////

void introsort_util(vector<string>& arr, int low, int high, int depth_limit) 
{
    if (high - low < 11) 
    {
        InsertionSorter::insertionsort(arr, low, high);
        return;
    }
    if (depth_limit == 0) 
    {
        HeapSorter::heapsort(arr, low, high);
        return;
    }
    int p = QuickSorter::partition(arr, low, high);
    introsort_util(arr, low, p - 1, depth_limit - 1);
    introsort_util(arr, p + 1, high, depth_limit - 1);
}


void IntroSorter::introsort(vector<string>& vec, int low, int high)
{
    int depth_limit = 2 * log(high - low);
    introsort_util(vec, low, high, depth_limit);

}

void IntroSorter::sort() 
{
    introsort(vec, 0, vec.size() - 1);
}

///////////////////////

void STLSorter::sort() 
{
    std::sort(vec.begin(), vec.end());
}

//////////////////////

void StableSorter::sort() 
{
    std::stable_sort(vec.begin(), vec.end());
}

/////////////////////////

void ShellSorter::gapInsertionSort(vector<string> & avector, int start, int gap)
{
    int sz= avector.size();
    for (int i = start + gap; i < sz; i += gap) 
    { 
        string currentvalue = avector[i];
        int position = i;

        while(position>=gap && avector[position- gap]>currentvalue)
        {
            avector[position] = avector[position-gap];
            position-=gap;
        }

        avector[position] = currentvalue;
    }

}

void ShellSorter::shellSort(vector<string> & avector)
{
    int subvectorcount = avector.size()/2;
    while(subvectorcount>0)
    {
        for (int startposition = 0; startposition < subvectorcount; startposition++)
        {
            gapInsertionSort(avector, startposition, subvectorcount);
            subvectorcount = subvectorcount/2;
        }
    }
}

void ShellSorter::sort() 
{
    shellSort(vec);
}

///////////////////////////////

ostream & operator << (ostream & out, Sorter & L)
{
    L.print(out);
    return out;
}

void error(string word, string msg)
{
    cout << "ERROR: " << word << " " << msg << endl;
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

