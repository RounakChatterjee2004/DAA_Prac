#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

// Function to generate random array
vector<int> generateRandomArray(int size)
{
    vector<int> array(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 1000);

    for (int i = 0; i < size; ++i)
    {
        array[i] = dist(gen);
    }
    return array;
}

// Quicksort implementation
void quicksort(vector<int> &array, int low, int high);
int partition(vector<int> &array, int low, int high);
void swap(int &a, int &b);

// Mergesort implementation
void mergesort(vector<int> &array, int low, int high);
void merge(vector<int> &array, int low, int mid, int high);

int main()
{
    // Generate random data
    vector<int> data = generateRandomArray(500);

    // PART A: Quicksort
    vector<int> quickSortData = data; // Copy data
    auto start_time = chrono::high_resolution_clock::now();
    quicksort(quickSortData, 0, quickSortData.size() - 1);
    auto end_time = chrono::high_resolution_clock::now();
    auto quickSort_time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
    cout << "The time required for quick sort is " << quickSort_time << " ns" << endl;

    // PART B: Mergesort
    vector<int> mergeSortData = data; // Copy data
    start_time = chrono::high_resolution_clock::now();
    mergesort(mergeSortData, 0, mergeSortData.size() - 1);
    end_time = chrono::high_resolution_clock::now();
    auto mergeSort_time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
    cout << "The time required for merge sort is " << mergeSort_time << " ns" << endl;

    return 0;
}

void quicksort(vector<int> &array, int low, int high)
{
    if (low < high)
    {
        int partition_index = partition(array, low, high);
        quicksort(array, low, partition_index - 1);
        quicksort(array, partition_index + 1, high);
    }
}

int partition(vector<int> &array, int low, int high)
{
    int pivot = array[high];
    int i = low - 1;
    for (int j = low; j < high; ++j)
    {
        if (array[j] <= pivot)
        {
            ++i;
            swap(array[i], array[j]);
        }
    }
    swap(array[i + 1], array[high]);
    return i + 1;
}

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void mergesort(vector<int> &array, int low, int high)
{
    if (low < high)
    {
        int mid = low + (high - low) / 2;
        mergesort(array, low, mid);
        mergesort(array, mid + 1, high);
        merge(array, low, mid, high);
    }
}

void merge(vector<int> &array, int low, int mid, int high)
{
    vector<int> left(array.begin() + low, array.begin() + mid + 1);
    vector<int> right(array.begin() + mid + 1, array.begin() + high + 1);

    int i = 0, j = 0, k = low;
    while (i < left.size() && j < right.size())
    {
        if (left[i] <= right[j])
        {
            array[k++] = left[i++];
        }
        else
        {
            array[k++] = right[j++];
        }
    }

    while (i < left.size())
    {
        array[k++] = left[i++];
    }

    while (j < right.size())
    {
        array[k++] = right[j++];
    }
}
