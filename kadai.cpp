#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip> //fixed << setprecision(10)

using namespace std;

typedef long long ll;
typedef vector<int> vi;

double exp_distribution(double average){ //指数分布
    srand(time(NULL));
    double rand_rate = (rand()%100+1)/100.0;
    
    return average * -log(1.0 - rand_rate);
}

int poisson(int n){ //ポアソン分布
    int k = 0;
    double l=exp(-n);
    double m = 1;
    do{
        k++;
        m*=rand()/double(RAND_MAX);
    }while(m>=l);
    int po=k-1;

    return po;
}

int main(){
    int NUM_OF_CALLS = 1000; //発生呼数: 1000

	ll link_capacity = 100000000; //リンク容量: 100Mbps
    int per_call = 64000; //呼ひとつあたり: 64Kbps
    
    double service_rate = 1.0;
    int through_puts = 0;
    
    for(int i = 0; i <= 100; i++){
        double lambda = poisson(i);
    }
    
    //cout << poisson(50) << endl;
    
    return 0;
}