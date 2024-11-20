#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

// Function to generate a random chromosome (tour)
std::vector<int> generate_chromosome(int n)
{
    std::vector<int> chromosome(n);
    for (int i = 0; i < n; i++)
    {
        chromosome[i] = i;
    }
    std::random_shuffle(chromosome.begin(), chromosome.end());
    return chromosome;
}

// Function to mutate the chromosome by swapping two cities
std::vector<int> mutate_chromosome(std::vector<int> &chromosome)
{
    // Randomly choose two indices to swap
    int index1 = rand() % chromosome.size();
    int index2 = rand() % chromosome.size();

    // Ensure index1 and index2 are different
    while (index1 == index2)
    {
        index2 = rand() % chromosome.size();
    }

    // Swap the cities
    std::swap(chromosome[index1], chromosome[index2]);
    return chromosome;
}

int main()
{
    srand(time(0)); // Initialize random seed

    int TSP_cities = 10; // Number of cities
    std::vector<int> chromosome = generate_chromosome(TSP_cities);

    // Print original chromosome
    std::cout << "Original chromosome: ";
    for (int city : chromosome)
    {
        std::cout << city << " ";
    }
    std::cout << std::endl;

    // Mutate the chromosome
    std::vector<int> mutated_chromosome = mutate_chromosome(chromosome);

    // Print mutated chromosome
    std::cout << "Mutated chromosome: ";
    for (int city : mutated_chromosome)
    {
        std::cout << city << " ";
    }
    std::cout << std::endl;

    return 0;
}
