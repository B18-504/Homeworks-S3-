#include "functions.hpp"

double randDouble(double n1, double n2) {
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> dist(n1, n2);
    return dist(mt);
}

int randInt(int n1, int n2) {
    return round(randDouble(n1, n2));
}
