#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <chrono>

using namespace std;

// Function to generate a random matrix of size rows x cols
vector<vector<int>> generateRandomMatrix(int rows, int cols)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 9);

    vector<vector<int>> matrix(rows, vector<int>(cols));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = dis(gen); // Random values between 0 and 9
        }
    }
    return matrix;
}

// Sequential Matrix Multiplication
vector<vector<int>> sequentialMultiply(const vector<vector<int>> &A, const vector<vector<int>> &B)
{
    int rowsA = A.size();
    int colsA = A[0].size();
    int colsB = B[0].size();
    vector<vector<int>> result(rowsA, vector<int>(colsB, 0));

    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < colsB; j++)
        {
            for (int k = 0; k < colsA; k++)
            {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

// Multithreaded Matrix Multiplication
void multiplyWorker(const vector<vector<int>> &A, const vector<vector<int>> &B, vector<vector<int>> &result, int row)
{
    int colsB = B[0].size();
    int colsA = A[0].size();

    for (int j = 0; j < colsB; j++)
    {
        for (int k = 0; k < colsA; k++)
        {
            result[row][j] += A[row][k] * B[k][j];
        }
    }
}

vector<vector<int>> multithreadedMultiply(const vector<vector<int>> &A, const vector<vector<int>> &B)
{
    int rowsA = A.size();
    int colsB = B[0].size();
    vector<vector<int>> result(rowsA, vector<int>(colsB, 0));

    vector<thread> threads;

    for (int i = 0; i < rowsA; i++)
    {
        threads.push_back(thread(multiplyWorker, ref(A), ref(B), ref(result), i));
    }

    for (auto &t : threads)
    {
        t.join();
    }

    return result;
}

// Utility function to print a matrix
void printMatrix(const vector<vector<int>> &matrix)
{
    for (const auto &row : matrix)
    {
        for (int value : row)
        {
            cout << value << " ";
        }
        cout << endl;
    }
}

int main()
{
    int rowsA = 500, colsA = 500, rowsB = 500, colsB = 500;

    // Generate random matrices
    vector<vector<int>> A = generateRandomMatrix(rowsA, colsA);
    vector<vector<int>> B = generateRandomMatrix(rowsB, colsB);

    // Sequential Matrix Multiplication
    cout << "=== Sequential Matrix Multiplication ===" << endl;
    auto startSequential = chrono::high_resolution_clock::now();
    vector<vector<int>> sequentialResult = sequentialMultiply(A, B);
    auto endSequential = chrono::high_resolution_clock::now();
    cout << "Time Taken (Sequential): "
         << chrono::duration_cast<chrono::nanoseconds>(endSequential - startSequential).count()
         << " nanoseconds" << endl;

    // Multithreaded Matrix Multiplication
    cout << "\n=== Multithreaded Matrix Multiplication ===" << endl;
    auto startMultithreaded = chrono::high_resolution_clock::now();
    vector<vector<int>> multithreadedResult = multithreadedMultiply(A, B);
    auto endMultithreaded = chrono::high_resolution_clock::now();
    cout << "Time Taken (Multithreaded): "
         << chrono::duration_cast<chrono::nanoseconds>(endMultithreaded - startMultithreaded).count()
         << " nanoseconds" << endl;

    // Uncomment to verify the correctness of results
    // cout << "\nSequential Result:" << endl;
    // printMatrix(sequentialResult);
    // cout << "\nMultithreaded Result:" << endl;
    // printMatrix(multithreadedResult);

    return 0;
}
