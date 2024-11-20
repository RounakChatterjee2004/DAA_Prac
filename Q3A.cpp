#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

// Function to swap two elements in the array
void swap(vector<int> &arr, int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// Partition function for Quick Sort
int partition(vector<int> &arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(arr, i, j);
        }
    }
    swap(arr, i + 1, high);
    return i + 1;
}

// Quick Sort function
void quickSort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int partitionIndex = partition(arr, low, high);
        quickSort(arr, low, partitionIndex - 1);
        quickSort(arr, partitionIndex + 1, high);
    }
}

// Function to generate Best Case: Sorted Array
vector<int> generateBestCase(int n)
{
    vector<int> bestCase(n);
    for (int i = 0; i < n; i++)
    {
        bestCase[i] = i;
    }
    return bestCase;
}

// Function to generate Worst Case: Reversed Array
vector<int> generateWorstCase(int n)
{
    vector<int> worstCase(n);
    for (int i = 0; i < n; i++)
    {
        worstCase[i] = n - 1 - i;
    }
    return worstCase;
}

// Function to compare the time taken for Best and Worst case scenarios
void compareTime(int n)
{
    vector<int> bestCase = generateBestCase(n);
    vector<int> worstCase = generateWorstCase(n);

    // Calculating time for Best Case
    clock_t start = clock();
    quickSort(bestCase, 0, bestCase.size() - 1);
    clock_t end = clock();
    double bestCaseTime = double(end - start) / CLOCKS_PER_SEC;

    // Calculating time for Worst Case
    start = clock();
    quickSort(worstCase, 0, worstCase.size() - 1);
    end = clock();
    double worstCaseTime = double(end - start) / CLOCKS_PER_SEC;

    cout << "Best Case Time: " << bestCaseTime << " seconds\n";
    cout << "Worst Case Time: " << worstCaseTime << " seconds\n";
}

int main()
{
    int n = 10000; // You can adjust this value to test with different sizes
    compareTime(n);
    return 0;
}
