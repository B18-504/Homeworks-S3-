#include "functions.hpp"

namespace rnd {
    double randDouble(double n1, double n2) {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(n1, n2);
        return dist(mt);
    }
    
    int randInt(int n1, int n2) {
        return round(randDouble(n1, n2));
    }
}
