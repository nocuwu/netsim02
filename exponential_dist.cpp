#include <iostream>
#include <random>

using namespace std;

int main(){
    int ave = 180;
    random_device seed_gen;
    default_random_engine engine(seed_gen());
    
    exponential_distribution<> dist(1.0);

    for (int i = 0; i < 100; i++){
        cout << floor(ave * dist(engine)) << endl;
    }
    return 0;
}