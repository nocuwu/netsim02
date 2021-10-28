#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip> //fixed << setprecision(10)

using namespace std;

#define rep(i,n) for(int (i)=0;(i)<(n);(i)++)

typedef long long ll;
typedef vector<int> vi;
// サーバ1つ当たりのCPUコア（）
#define cpu_core 10
#define memory 100
// スループット（サーバ間）
#define tp 100

struct vnf(){
    int req_cpu = 2;
    int req_memory = 10;
}

int main(){
	
    
    return 0;
}

int gcd(int a, int b) {
  if (b == 0) 
    return a;  
  return gcd(b, a % b);
}
