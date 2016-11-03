#include "tsp-ga.hh"
#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <ctime>
#include <cstdlib>


using namespace std;


bool isShorterPath(const TSPGenome &g1, const TSPGenome &g2) {
    // comapre whiwh one is shorter
    return (g1.getCircuitLength() < g2.getCircuitLength());
}

TSPGenome crosslink(const TSPGenome &g1, const TSPGenome &g2) {
    // combine two genes into a new crosslink gene
    vector<int> order;
    set<int> s;
    vector<int> gene1 = g1.getOrder();
    vector<int> gene2 = g2.getOrder();

    int i = rand() % gene1.size(); //deciding where to cut gene 1
    
    for (int k = 0; k < i; k++) { //obtaining gene 1 from 0 to the cut
        order.push_back(gene1[k]);
        s.insert(gene1[k]);
    }
    for (int j = 0; j < gene2.size(); j++) { // adding points from gene 2
        if (s.count(gene2[j]) == 0) {        // that are not already added
            order.push_back(gene2[j]);
            s.insert(gene2[j]);
        }
    }
    return TSPGenome(order);
}

TSPGenome findShortPath(const vector<Point> &points, int populationSize,
                        int numGenerations, int keepPopulation, 
                        int numMutations) {
    int g1, g2, mut;
    vector<TSPGenome> population;

    // initializing first generation 
    for (int i = 0; i < populationSize; i++) {
            population.push_back(TSPGenome(points.size()));
        }

    // evaluating and generating new generations    
    for (int gen = 0; gen < numGenerations; gen++) {
        // calculate circuit length
        for (int k = 0; k < populationSize; k++) {
            population[k].computeCircuitLength(points);
        }
        // sort using path length
        sort(population.begin(), population.end(), isShorterPath);

        if(gen % 10 == 0) {
            // show progress (every ten generations)
            cout << "Generation" << gen << ": shortest path is "
                 << population[0].getCircuitLength() << endl;
        }

        // generating new genes using the 'fittest' genes
        for (int j = keepPopulation; j < populationSize; j++) {
            g1 = rand() % keepPopulation;
            g2 = rand() % keepPopulation;
            while (keepPopulation > 1 && g1 == g2) { // check if unique
                g2 = rand() % keepPopulation;

            }
            population[j] = crosslink(population[g1], population[g2]);
        }

        for (int i = 0; i < numMutations; i++){ // random mutation
            mut = 1 + rand() % (populationSize - 1);
            population[mut].mutate();
        }
    }

    return population[0];
}



void usage(const char *progname) {
    cout << "usage: " << progname << "population generations keep mutate" << 
    endl;
    cout << "population is a positive integer specifying the population size."
    << endl;
    cout << "generations is a positive integer specifying how many"
    << "generations to run the GA for." << endl;
    cout << "keep is a floating-point value in the range 0-1 that specifies" 
    << "the percentage of the population that should be preserved from" <<
    "generation to generation. For example, 0.3 would specify that the top 30"
    << "percent of the population should be preserved to the next generation."
    << endl;
    cout << "mutate is a nonnegative floating-point value that specifies how" 
    << "many mutations to apply to each member of the population, on average."
    << "For example, a value of 1.5 specifies that each member will have"
    << "about 1.5 mutations applied. The total number of mutations to apply"
    << "to the population is simply mutate &mult; population at the end of"
    << "each generation." << endl;
}


int main(int argc,char **argv) {
    if (argc != 5) { //check if correct number of arguments
        usage(argv[0]);
        return 1;
    }
    int population = (int) atoi(argv[1]); // check if argument in range
    int generations = (int) atoi(argv[2]);
    float keep = (float) atof(argv[3]);
    float mutate = (float) atof(argv[4]);
    if (population < 1 || generations < 1 || keep < 0 || keep > 1 ||
        mutate < 0) {
        usage(argv[0]);
        return 1;
    }


    int npoints = 0;
    int x, y, z;
    double distance = 0;
    vector<Point> points;
    vector<int> order;
    
    srand(time(nullptr));

    cout << "How many points? "; // getting points from the user
    cin >> npoints;
    for (int i = 0; i < npoints; i++) {
        cout << "Point " << i << ": ";
        cin >> x >> y >> z;
        Point p(x, y, z);
        points.push_back(p);
    }

    // find short path
    TSPGenome spath = findShortPath(points, population, generations, 
        (int)(keep * population), (int)(mutate * population));
    distance = spath.getCircuitLength(); // get the distance
    order = spath.getOrder(); // get the order

    cout << "Shortest distance: " << distance << endl;
    cout << "Best order: [";
    for (int i = 0; i < npoints; i++) {
        if (i == npoints - 1) {
            cout << order[i] << ']' << endl;
        }
        else {
            cout << order[i] << ' ';
        }
    }
    return 0;
}
