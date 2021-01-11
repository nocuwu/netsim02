#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>
#include <iomanip> //fixed << setprecision(10)

using namespace std;

typedef long long ll;
typedef vector<int> vi;

double expd(double ave){
    random_device seed_gen;
    default_random_engine engine(seed_gen());

    exponential_distribution<> dist(1.0);

    return ave*dist(engine);
}


int main(){
    //指数分布
    random_device seed_gen;
    default_random_engine engine(seed_gen());
    exponential_distribution<> dist(1.0);

    int NUM_OF_CALLS = 10000; //発生呼数: 10000

	ll LINK_CAPACITY= 100000000; //リンク容量: 100Mbps
    int CAPS_PER_CALL = 64000; //呼ひとつあたり: 64Kbps
    int NUM_OF_LINES = floor(LINK_CAPACITY / CAPS_PER_CALL); //回線数: 1562本
    
    double service_rate = 1.0;
    int through_puts = 0;

    for(int lambda = 1; lambda <= 100; lambda++){ //到着率λ(1~100)
        vi line(NUM_OF_LINES, 0);
        int loss = 0;
        int cnt = 0;
        while(cnt < NUM_OF_CALLS){ //発生呼数ループ
            int j = -1;
            for(int i = 0; i < min(lambda, NUM_OF_CALLS - cnt); i++){
                while(1){
                    j++;
                    if(NUM_OF_LINES <= j){
                        loss++;
                        break;
                    }
                    if(line[j] == 0){
                        line[j] = floor(180*dist(engine));
                        break;
                    }
                }
            }
            for(int i = 0; i < NUM_OF_LINES; i++){ //1秒経過
                line[i] = max(0, line[i]-1);
            }
            cnt += lambda; //λ呼すすめる
        }
        cout << lambda << ", " << loss << endl;
    }

    return 0;
}