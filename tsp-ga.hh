// one possible solution to the travel salesman problem
#include "Point.hh"
#include <vector>

using namespace std;

class TSPGenome {

private:
    vector<int> visitorder; // representing the order of the solution
    double distance; // representing the total distance of the solution

public:
    // costructor
    TSPGenome(int numPoints); // takes the number of points and generate
                              // random order to visit
    TSPGenome(const vector<int> &order); // initialize from specified order


    // accessor method
    vector<int> getOrder() const; //returns the genome's current order
    
    void computeCircuitLength(const vector<Point> &points); 
                                    //compute circuit length
    double getCircuitLength() const; //returns the cicuit length

    // mutator method
    void mutate(); //swap two random values in the order vector

};
