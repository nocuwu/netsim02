   
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
#define CPU_CORE 12
// サーバ1つ当たりのメモリ(RAM)[GB]
#define RAM 24
// スループット（source-サーバ間/サーバ-terminal間）[bps]
#define tp_io_server 1'000'000'000
// スループット（サーバ間）[bps]
#define tp_server_server 100'000'000

//トポロジの残余リソース
struct topology
{
  int t_cpu;
  int t_ram;
};

//サービス（ファンクション）チェイン
struct sc
{
  vector<bool> req_sf;
  //sc要求帯域
  int req_bw;
  //sc要求cpuコア数
  int req_cpu_sc;
  //sc要求メモリ[GB]
  int req_ram_sc;
};

int main()
{
  //------service function の設定
  //vnfの種類数
  int num_of_vnf = 4;
  //vnf[0].first: vnf0の要求cpuコア数
  //vnf[0].second: vnf0の要求メモリ[GB]
  vector<pair<int, int>> sf(num_of_vnf);
  sf[0] = make_pair(2, 2);
  sf[1] = make_pair(2, 2);
  sf[2] = make_pair(2, 2);
  sf[3] = make_pair(2, 2);
  sf[4] = make_pair(2, 2);

  //------service (function) chain の設定
  //データサイズが変化するsc
  sc sc0;
  //要求sf数を4、全て未割当(false)に設定
  sc0.req_sf.resize(4);
  for (int i = 0; i < sc0.req_sf.size(); i++)
  {
    sc0.req_sf[i] = false;
  }
  sc0.req_bw = 100'000'000;
  sc0.req_cpu_sc = sf[0].first + sf[1].first + sf[2].first + sf[3].first;
  sc0.req_ram_sc = sf[0].second + sf[1].second + sf[2].second + sf[3].second;

  //データサイズが変化しないsc
  sc sc1;
  sc0.req_sf.resize(4);
  for (int i = 0; i < sc0.req_sf.size(); i++)
  {
    sc0.req_sf[i] = false;
  }
  sc1.req_bw = 100'000'000;
  sc1.req_cpu_sc = sf[0].first + sf[1].first + sf[2].first + sf[4].first;
  sc1.req_ram_sc = sf[0].second + sf[1].second + sf[2].second + sf[4].second;

  //cout << sc1.req_cpu_sc << endl;

  //サーバ4つのトポロジー
  topology topology;
  topology.t_cpu = CPU_CORE * 4;
  topology.t_ram = RAM * 4;
  while (1)
  {
    //sc0が発生した
    int req_sc;
    req_sc = 0;
    int req_cpu_sc;
    int req_ram_sc;

    //割り当て関数内の変数にコピー
    if (req_sc == 0)
    {
      vector<bool> req_sf = sc0.req_sf;
      req_cpu_sc = sc0.req_cpu_sc;
      req_ram_sc = sc0.req_ram_sc;
    }
    else if (req_sc == 1)
    {
      vector<bool> req_sf = sc1.req_sf;
      req_cpu_sc = sc1.req_cpu_sc;
      req_ram_sc = sc1.req_ram_sc;
    }

    

    //トポロジの残余リソースが発生したscの要求リソースに満たない場合棄却
    if (topology.t_cpu <= req_cpu_sc || topology.t_ram <= req_ram_sc)
    {
      cout << "break: " << topology.t_cpu << " " << req_cpu_sc << " " << topology.t_ram << " " << req_ram_sc << endl;
      break;
    }
    else
    {
      cout << topology.t_cpu << " " << req_cpu_sc << " " << topology.t_ram << " " << req_ram_sc << endl;
      topology.t_cpu -= 10;
      topology.t_ram -= 10;
    }
  }

  return 0;
}
