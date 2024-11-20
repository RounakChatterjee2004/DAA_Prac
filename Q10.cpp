#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

// Helper function to check if a value is in the array
bool contains(const vector<int> &arr, int value)
{
    for (int city : arr)
    {
        if (city == value)
        {
            return true;
        }
    }
    return false;
}

// Fitness function for evaluating a solution (TSP: sum of distances)
int fitness(const vector<int> &chromosome)
{
    int totalDistance = 0;
    for (int i = 0; i < chromosome.size() - 1; i++)
    {
        totalDistance += abs(chromosome[i] - chromosome[i + 1]); // Dummy distance calculation
    }
    totalDistance += abs(chromosome[chromosome.size() - 1] - chromosome[0]); // Closing the loop
    return totalDistance;
}

// Crossover function between two parent chromosomes
vector<int> crossover(const vector<int> &parent1, const vector<int> &parent2)
{
    int size = parent1.size();
    vector<int> child(size, -1);

    // Randomly select 2 points for crossover
    int start = rand() % size;
    int end = rand() % size;
    if (start > end)
        swap(start, end);

    // Copy a portion of parent1 to the child
    for (int i = start; i <= end; i++)
    {
        child[i] = parent1[i];
    }

    // Fill the remaining positions from parent2
    int currentIndex = 0;
    for (int i = 0; i < size; i++)
    {
        if (child[i] == -1)
        {
            while (contains(child, parent2[currentIndex]))
            {
                currentIndex++;
            }
            child[i] = parent2[currentIndex++];
        }
    }
    return child;
}

// Tournament selection to pick two parents
vector<int> tournamentSelection(const vector<vector<int>> &population, int tournamentSize)
{
    int populationSize = population.size();
    vector<vector<int>> tournament;

    // Randomly select a subset of individuals (tournament)
    for (int i = 0; i < tournamentSize; i++)
    {
        tournament.push_back(population[rand() % populationSize]);
    }

    // Evaluate fitness of each individual in the tournament
    vector<int> bestIndividual = tournament[0];
    int bestFitness = fitness(bestIndividual);

    for (int i = 1; i < tournament.size(); i++)
    {
        vector<int> individual = tournament[i];
        int currentFitness = fitness(individual);
        if (currentFitness < bestFitness)
        {
            bestIndividual = individual;
            bestFitness = currentFitness;
        }
    }

    return bestIndividual;
}

int main()
{
    srand(time(0)); // Initialize random seed

    // Initialize population with some sample chromosomes (city permutations)
    vector<vector<int>> population = {
        {0, 1, 2, 3, 4},
        {4, 3, 2, 1, 0},
        {1, 2, 3, 4, 0},
        {2, 0, 1, 4, 3}};

    int tournamentSize = 2;

    // Tournament selection to pick two parents
    vector<int> parent1 = tournamentSelection(population, tournamentSize);
    vector<int> parent2 = tournamentSelection(population, tournamentSize);

    cout << "Parent 1: ";
    for (int city : parent1)
        cout << city << " ";
    cout << endl;

    cout << "Parent 2: ";
    for (int city : parent2)
        cout << city << " ";
    cout << endl;

    // Perform crossover between the two parents
    vector<int> child = crossover(parent1, parent2);
    cout << "Child after Crossover: ";
    for (int city : child)
        cout << city << " ";
    cout << endl;

    // Example test for fitness function (calculating the total distance)
    cout << "Fitness of Parent 1: " << fitness(parent1) << endl;
    cout << "Fitness of Parent 2: " << fitness(parent2) << endl;
    cout << "Fitness of Child: " << fitness(child) << endl;

    return 0;
}
