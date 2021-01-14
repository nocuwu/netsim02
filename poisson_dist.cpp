#include <iostream>
#include <random>

using namespace std;

int main(){
    mt19937 mt{ std::random_device{}() };
    poisson_distribution<int> dist(100);
    
    for(int i = 0; i < 100; i++){
        cout << dist(mt) << endl;
    }

    return 0;
}