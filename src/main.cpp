#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip> //fixed << setprecision(10)

using namespace std;

#define rep(i, n) for (int(i) = 0; (i) < (n); (i)++)

typedef long long ll;
typedef vector<int> vi;

// サーバ1つ当たりのCPUコア数
#define cpu_core 12
// サーバ1つ当たりのメモリ(RAM)[GB]
#define ram 24
// スループット（source-サーバ間/サーバ-terminal間）[bps]
#define tp_inout_server 1000000000
// スループット（サーバ間）[bps]
#define tp_server_server 100000000

int a = 1;
int b = 1;

struct sc
{
  int req_bw;
  int req_cpu_sc;
  int req_ram_sc;
};

struct vnf
{
  int req_cpu;
  int req_ram;
};

int main()
{
  //データサイズが変化するsc
  sc variable;
  variable.req_bw = 100000000;
  //データサイズが変化しないsc
  sc no_compression;
  no_compression.req_bw = 100000000;　

  return 0;
}

int gcd(int a, int b)
{
  if (b == 0)
    return a;
  return gcd(b, a % b);
}
