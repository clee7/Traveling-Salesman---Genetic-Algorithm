#include "tsp-ga.hh"
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

//constructor
TSPGenome::TSPGenome(int numPoints) {
    for (int i = 0; i < numPoints; i++) {
        visitorder.push_back(i); // adding 0 to numPoints - 1 into vector
    }
    random_shuffle(visitorder.begin(), visitorder.end()); //shuffle
    distance = -1; //arbitrary starting distance
}

TSPGenome::TSPGenome(const vector<int> &order) {
    for (int i = 0; i < order.size(); i++) {
        visitorder.push_back(order[i]); // adding specfic order
    }
    distance = -1; //arbitrary starting distance
}


//accessor
vector<int> TSPGenome::getOrder() const{
    return visitorder;
}

void TSPGenome::computeCircuitLength(const vector<Point> &points) {
    double dist = 0;
    int j, k;

    // calculate circuit length base on the visit order
    for (int i = 0; i < points.size(); i++) {
        j = visitorder[i];
        k = visitorder[i + 1];
        if (i == points.size() - 1) {
            dist += points[j].distanceTo(points[visitorder[0]]);
        }
        else {
            dist += points[j].distanceTo(points[k]);
        }
    }

    distance = dist;
}

double TSPGenome::getCircuitLength() const{
    return distance;
}

//mutator 

void TSPGenome::mutate() {
    // swap two random values in the order vector
    int i, k;
    int n;
    i = rand() % visitorder.size(); // generate two random unique
    k = rand() % visitorder.size();
    while (i == k && visitorder.size() > 1) { // check if the unique
        k = rand() % visitorder.size();
    }
    n = visitorder[i]; //swap
    visitorder[i] = visitorder[k];
    visitorder[k] = n;
}