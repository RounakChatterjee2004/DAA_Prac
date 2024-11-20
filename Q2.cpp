#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

// Merge Sort
void merge(vector<int> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> leftArr(n1), rightArr(n2);

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (leftArr[i] <= rightArr[j])
        {
            arr[k] = leftArr[i];
            i++;
        }
        else
        {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Quick Sort Partition
int partition(vector<int> &arr, int low, int high)
{
    int pivot = arr[high]; // pivot element is at high index
    int i = low - 1;       // index of smaller element

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        { // if current element is smaller than pivot
            i++;
            swap(arr[i], arr[j]); // swap arr[i] and arr[j]
        }
    }
    swap(arr[i + 1], arr[high]); // swap the pivot element with the element at index i + 1
    return i + 1;                // return the partitioning index
}

// Randomized Quick Sort Partition
int randomizedPartition(vector<int> &arr, int low, int high)
{
    int randomIndex = low + rand() % (high - low + 1); // randomly select a pivot
    swap(arr[randomIndex], arr[high]);                 // swap the random pivot with the last element
    return partition(arr, low, high);                  // call the regular partition
}

void randomizedQuickSort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = randomizedPartition(arr, low, high); // get partition index

        randomizedQuickSort(arr, low, pi - 1);  // recursively sort the left subarray
        randomizedQuickSort(arr, pi + 1, high); // recursively sort the right subarray
    }
}

// Function to print the array
void printArray(const vector<int> &arr)
{
    for (int num : arr)
    {
        cout << num << " ";
    }
    cout << endl;
}

int main()
{
    srand(time(0)); // Seed for randomization
    vector<int> arr = {10, 80, 30, 90, 40, 50, 70};

    cout << "Original Array: ";
    printArray(arr);

    // Randomized Quick Sort
    auto start = chrono::high_resolution_clock::now();
    randomizedQuickSort(arr, 0, arr.size() - 1); // Call Randomized Quick Sort
    auto end = chrono::high_resolution_clock::now();
    cout << "Sorted Array (Quick Sort): ";
    printArray(arr);
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Time taken for Randomized Quick Sort: " << duration.count() << " ms" << endl;

    // Reset array for Merge Sort
    arr = {10, 80, 30, 90, 40, 50, 70};

    // Merge Sort
    start = chrono::high_resolution_clock::now();
    mergeSort(arr, 0, arr.size() - 1); // Call Merge Sort
    end = chrono::high_resolution_clock::now();
    cout << "Sorted Array (Merge Sort): ";
    printArray(arr);
    duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Time taken for Merge Sort: " << duration.count() << " ms" << endl;

    return 0;
}
