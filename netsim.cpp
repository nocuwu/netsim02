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

uint64_t get_rand() {
    // 乱数生成器（引数にシードを指定可能）
    static mt19937_64 mt64(rand());

    // [0, (2^64)-1] の一様分布整数を生成
    return mt64();
}

double exp_distribution(double average){ //指数分布
    srand(time(NULL));
    double rand_rate = ((rand()*get_rand())%100+1)/100.0;
    
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
    int NUM_OF_CALLS = 10000; //発生呼数: 10000

	ll LINK_CAPACITY= 100000000; //リンク容量: 100Mbps
    int CAPS_PER_CALL = 64000; //呼ひとつあたり: 64Kbps
    int NUM_OF_LINES = floor(LINK_CAPACITY / CAPS_PER_CALL); //回線数: 1562本
    
    double service_rate = 1.0;
    int through_puts = 0;

    for(int lambda = 0; lambda <= 100; lambda++){ //到着率λ(0~100)
        vi line(1562, 0);
        int loss = 0;
        for(int i = 0; i < 10000; i++){ //発生呼数回ループ
            int flag = 0;
            for(int j = 0; j < 1562; j++){ //回線数ループ
                if(flag == 0 && line[j] == 0){
                    line[j] = 180;
                    flag = 1;
                }
                line[j] = max(0, line[j]-lambda);
            }
            if(flag == 0){
                loss++;
            }
        }
        cout << lambda << " " << loss << endl;
    }

    /*
    for(int i = 0; i < NUM_OF_CALLS; i++){ //発生呼数回ループ
        for(int  lambda = 0; lambda <= 100; lambda++){ //到着率λ(0~100)
            for(int k = 0; k < 1562; k++){
                if(k == 1561 && 0 < line[k]){
                    loss++;
                }
                if(line[k] == 0){
                    line[k] = 180;
                }
                if(0 < line[k]){
                    line[k] -= lambda;
                }
                if(line[k] < 0){
                    line[k] = 0;
                }
            }
        }
    }
    */

    /*
    for(int i = 0; i <= 100; i++){
        double lambda = poisson(i)/100.0;
        int remains = NUM_OF_CALLS;
        int call = 0;
        //vi line(NUM_OF_LINES, 0);
        int line[1562];
        for(int k = 0; k < 1562; k++){
            line[k] = 0;
        }
        int time = 0;

        while(0 < remains){
            sort(line, line+1562);
            //sort(line.begin(), line.end());

            call += floor(NUM_OF_CALLS*lambda);
            
            for(int j = 0; j < NUM_OF_LINES; j++){
                if(0 < call){
                    line[j] += exp_distribution(180);
                    //line[j] += 180;
                    call--;
                    remains--;
                }
                else
                    break;
            }
            time += 100;
            remains--;
        }
        sort(line, line+1562);
        std::reverse(line, line+1562);
        //sort(line.begin(), line.end());
        //reverse(line.begin(), line.end());
        double ans = 64000.0/(time + line[0]);
        std::cout << lambda << " " << ans << endl;
    }
    */
    return 0;
}