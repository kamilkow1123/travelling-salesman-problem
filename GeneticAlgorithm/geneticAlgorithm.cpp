#include "../TabuSearch/tabuSearch.cpp"
using namespace std;

random_device rd;
mt19937 rng(rd());

vector<int> randomChromosome(int numberOfVertices){
    vector<int> randomChromosome(numberOfVertices - 1);
    iota(randomChromosome.begin(), randomChromosome.end(), 1);
    shuffle(randomChromosome.begin(), randomChromosome.end(), rng);
    return randomChromosome;
}

vector<int> chooseParentsIndexes(vector<int> chromosomeGrades){
    int populationSize = chromosomeGrades.size();
    vector<int> parentsIndexes(populationSize);

    int sumOfGrades = 0;
    for (int i = 0; i < populationSize; i++){
        sumOfGrades += chromosomeGrades[i];
        chromosomeGrades[i] = sumOfGrades;
    }

    std::uniform_int_distribution<std::mt19937::result_type> randomFromSumOfGrades(1, sumOfGrades - 1);

    for (int i = 0; i < populationSize; i++){
        int drawn = randomFromSumOfGrades(rng);
        for (int j = 0; j < populationSize; j++){
            if(drawn < chromosomeGrades[j]){
                parentsIndexes[i] = j;
                break;
            }
        }
    }

    return parentsIndexes;
}

vector<vector<int>> reproducePopulation(vector<vector<int>> population, vector<int> parentsIndexes){
    vector<vector<int>> newPopulation;
    for (int i = 0; i < population.size(); i++)
        newPopulation.push_back(population[parentsIndexes[i]]);

    return newPopulation;
}

int findInVector(vector<int> vector, int number){
    for (int i = 0; i < vector.size(); i++)
        if(vector[i] == number)
            return i;

    return -1;
}

vector<int> gradeChromosomes(GraphAM *graph, vector<vector<int>> population, int populationSize, int bestChromosomeCost){
    vector<int> grades;

    for (int i = 0; i < populationSize; i++){
        int chromosomeCost = costOfPermutation(graph, population[i]);
        grades.push_back(bestChromosomeCost - chromosomeCost);
    }

    //normalize grades, find the lowest (the worst), make all positive
    int theWorstGrade = 0;
    for (int i = 0; i < populationSize; i++)
        if(grades[i] < theWorstGrade)
            theWorstGrade = grades[i];

    theWorstGrade = (-1 * theWorstGrade) + 1;
    for (int i = 0; i < populationSize; i++)
        grades[i] += theWorstGrade;

    return grades;
}

vector<vector<int>> performCrossover(vector<vector<int>> population, std::uniform_real_distribution<double> probability, float crossoverProb){
    for (int i = 0; i < population.size() / 2; i++){
        if (probability(rng) > crossoverProb) continue;

        int firstPopulationIndex = i * 2;
        int secondPopulationIndex = i * 2 + 1;
        vector<int> tempChromosomeA = population[firstPopulationIndex];
        vector<int> tempChromosomeB = population[secondPopulationIndex];

        std::uniform_int_distribution<std::mt19937::result_type> randomFromChromosome(0, tempChromosomeA.size());
        int crossingPoint = randomFromChromosome(rng);

        for (int j = 0; j < crossingPoint; j++){
            int position = findInVector(population[firstPopulationIndex], tempChromosomeB[j]);
            population[firstPopulationIndex][position] = population[firstPopulationIndex][j];
            population[firstPopulationIndex][j] = tempChromosomeB[j];

            position = findInVector(population[secondPopulationIndex], tempChromosomeA[j]);
            population[secondPopulationIndex][position] = population[secondPopulationIndex][j];
            population[secondPopulationIndex][j] = tempChromosomeA[j];
        }
    }

    return population;
}

vector<vector<int>> performMutations(vector<vector<int>>population, std::uniform_real_distribution<double> probability, float mutationProb){
    for(int i = 0; i < population.size(); i++){
        if(probability(rng) > mutationProb) continue;

        vector<int> tempChromosome = population[i];
        std::uniform_int_distribution<std::mt19937::result_type> randomFromChromosome(0, tempChromosome.size() - 1);
        int firstIndex, secondIndex;
        do{
            firstIndex = randomFromChromosome(rng);
            secondIndex = randomFromChromosome(rng);
        } while (firstIndex == secondIndex);

        tempChromosome = permutationSwap(tempChromosome, firstIndex, secondIndex);
        population[i] = tempChromosome;
    }
    return population;
}

pair<vector<int>, int> solveGeneticAlgorithm(GraphAM *graph, int populationSize, int numOfGenerations, float crossoverProb, float mutationProb ){
    int numberOfVertices = graph->getNumOfVertexes();
    vector<int> bestChromosome = initialPermutation(graph);
    int bestChromosomeCost = costOfPermutation(graph, bestChromosome);
    int prevBestCost = INT_MAX;
    int bestInPopulationIndex = 0;

    int potentialBestCost;
    vector<int> potentialBestChromosome;

    vector<vector<int>> population;
    population.push_back(bestChromosome);
    for (int i = 0; i < populationSize - 1; i++)
        population.push_back(randomChromosome(numberOfVertices));

    vector<vector<int>> newPopulation;
    vector<int> chromosomesGrades = gradeChromosomes(graph, population, populationSize, bestChromosomeCost);

    std::uniform_real_distribution<double> probability(0.0, 1.0);

    int bestGrade = -1 * INT_MAX;

    for (int i = 0; i < numOfGenerations; i++){

        if(prevBestCost != bestChromosomeCost) printNewAnswer(i, bestChromosomeCost, graph->getOptimalValue());

        vector<int> selectedParentsIndexes = chooseParentsIndexes(chromosomesGrades);
        newPopulation = reproducePopulation(population, selectedParentsIndexes);

        newPopulation = performCrossover(newPopulation, probability, crossoverProb);
        newPopulation = performMutations(newPopulation, probability, mutationProb);
        chromosomesGrades = gradeChromosomes(graph, newPopulation, populationSize, bestChromosomeCost);

        population = newPopulation;

        for (int j = 0; j < populationSize; j++){
            if (chromosomesGrades[j] > bestGrade){
                bestGrade = chromosomesGrades[j];
                bestInPopulationIndex = j;
            }
        }

        prevBestCost = bestChromosomeCost;

        potentialBestChromosome = population[bestInPopulationIndex];
        potentialBestCost = costOfPermutation(graph, potentialBestChromosome);
        if ( potentialBestCost < bestChromosomeCost){
            bestChromosome = potentialBestChromosome;
            bestChromosomeCost = potentialBestCost;
        }
    }

    bestChromosome.insert(bestChromosome.begin(), 0);
    bestChromosome.push_back(0);
    return make_pair(bestChromosome, bestChromosomeCost);
}