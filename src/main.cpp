#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip> //fixed << setprecision(10)
#include <functional>

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

struct sc
{
  int req_bw;
  int req_cpu_sc;
  int req_ram_sc;
};

int main()
{
  //vnfの種類数
  int num_of_vnf = 4;
  //vnf[0].first: vnf0の要求cpuコア数
  //vnf[0].second: vnf0の要求メモリ[GB]
  vector<pair<int, int>> vnf(num_of_vnf);
  vnf[0] = make_pair(2, 2);
  vnf[1] = make_pair(2, 2);
  vnf[2] = make_pair(2, 2);
  vnf[3] = make_pair(2, 2);
  vnf[4] = make_pair(2, 2);

  //データサイズが変化するsc
  sc sc0;
  sc0.req_bw = 100000000;
  sc0.req_cpu_sc = vnf[0].first + vnf[1].first + vnf[2].first + vnf[3].first;
  sc0.req_ram_sc = vnf[0].second + vnf[1].second + vnf[2].second + vnf[3].second;
  //データサイズが変化しないsc
  sc sc1;
  sc1.req_bw = 100000000;
  sc1.req_cpu_sc = vnf[0].first + vnf[1].first + vnf[2].first + vnf[4].first;
  sc1.req_ram_sc = vnf[0].second + vnf[1].second + vnf[2].second + vnf[4].second;

  cout << sc1.req_cpu_sc << endl;

  return 0;
}

int gcd(int a, int b)
{
  if (b == 0)
    return a;
  return gcd(b, a % b);
}
