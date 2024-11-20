#include <iostream>
#include <vector>
#include <ctime>

// Function to merge two halves of the array
void merge(std::vector<int> &array, int low, int mid, int high)
{
    int leftArraySize = mid - low + 1;
    int rightArraySize = high - mid;

    std::vector<int> left(leftArraySize);
    std::vector<int> right(rightArraySize);

    for (int i = 0; i < leftArraySize; i++)
    {
        left[i] = array[low + i];
    }

    for (int i = 0; i < rightArraySize; i++)
    {
        right[i] = array[mid + 1 + i];
    }

    int i = 0, j = 0, k = low;
    while (i < leftArraySize && j < rightArraySize)
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

    while (i < leftArraySize)
    {
        array[k++] = left[i++];
    }

    while (j < rightArraySize)
    {
        array[k++] = right[j++];
    }
}

// Function to perform merge sort
void mergesort(std::vector<int> &array, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergesort(array, low, mid);
        mergesort(array, mid + 1, high);
        merge(array, low, mid, high);
    }
}

// Function to generate the best-case scenario (sorted array)
std::vector<int> generateBestCase(int n)
{
    std::vector<int> best_case(n);
    for (int i = 0; i < n; i++)
    {
        best_case[i] = i + 1; // Sorted array: [1, 2, 3, ..., n]
    }
    return best_case;
}

// Function to generate the worst-case scenario (reverse-sorted array)
std::vector<int> generateWorstCase(int n)
{
    std::vector<int> worst_case(n);
    for (int i = 0; i < n; i++)
    {
        worst_case[i] = n - i; // Reverse sorted array: [n, n-1, ..., 1]
    }
    return worst_case;
}

// Function to generate a random case (random array)
std::vector<int> generateRandomCase(int n)
{
    std::vector<int> random_case(n);
    for (int i = 0; i < n; i++)
    {
        random_case[i] = rand() % 1000; // Random numbers between 0 and 999
    }
    return random_case;
}

// Function to print the array
void printArray(const std::vector<int> &array)
{
    for (int num : array)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main()
{
    srand(time(0)); // Seed for random number generation

    // Test with 100 elements
    int n = 100;

    // Generate best-case scenario
    std::vector<int> best_case = generateBestCase(n);
    std::cout << "Best Case (Sorted Array) Before Merge Sort: ";
    printArray(best_case);

    // Perform merge sort on best-case scenario
    std::vector<int> best_case_copy = best_case; // Copy to maintain original
    clock_t start = clock();
    mergesort(best_case_copy, 0, n - 1);
    clock_t end = clock();
    std::cout << "Best Case After Merge Sort: ";
    printArray(best_case_copy);
    std::cout << "Time taken for Best Case: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;

    // Generate worst-case scenario
    std::vector<int> worst_case = generateWorstCase(n);
    std::cout << "\nWorst Case (Reverse-Sorted Array) Before Merge Sort: ";
    printArray(worst_case);

    // Perform merge sort on worst-case scenario
    std::vector<int> worst_case_copy = worst_case; // Copy to maintain original
    start = clock();
    mergesort(worst_case_copy, 0, n - 1);
    end = clock();
    std::cout << "Worst Case After Merge Sort: ";
    printArray(worst_case_copy);
    std::cout << "Time taken for Worst Case: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;

    // Generate random-case scenario
    std::vector<int> random_case = generateRandomCase(n);
    std::cout << "\nRandom Case Before Merge Sort: ";
    printArray(random_case);

    // Perform merge sort on random-case scenario
    std::vector<int> random_case_copy = random_case; // Copy to maintain original
    start = clock();
    mergesort(random_case_copy, 0, n - 1);
    end = clock();
    std::cout << "Random Case After Merge Sort: ";
    printArray(random_case_copy);
    std::cout << "Time taken for Random Case: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;

    return 0;
}
