#include <wchar.h>
#include <bits/stdc++.h>
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
// スループット（サーバ間）[bps]
#define tp_io_server 1'000'000'000
// サーバ台数
#define NUM_SERVER 4

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

int bin2dec(int bin_1, int bin_0)
{
    return (bin_1 * bin_1) + bin_0;
}

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
  topology.t_cpu = CPU_CORE * NUM_SERVER;
  topology.t_ram = RAM * NUM_SERVER;

  //各サーバ容量
  vector<tuple<int, int, int>> server(NUM_SERVER);

  server[0] = make_tuple(CPU_CORE, RAM, 0);
  server[1] = make_tuple(CPU_CORE, RAM, 0);
  server[2] = make_tuple(CPU_CORE, RAM, 0);
  server[3] = make_tuple(CPU_CORE, RAM, 0);

  //各サーバ割当状況
  vector<pair<int, int>> req_server(NUM_SERVER);
  req_server[0] = make_pair(0, 0);
  req_server[1] = make_pair(0, 0);
  req_server[2] = make_pair(0, 0);
  req_server[3] = make_pair(0, 0);

  //****************************************************************************************

  int n = 12;
  int W = 10;
  vector<int> a(n);

  for (int i = 0; i < n; i++)
  {
    a[i] = 1;
  }

  int ans = 0;

  //組み合わせ数ループ
  for (int bit = 0; bit < (1 << n); ++bit)
  {
    int S = 0;
    for (int sc = 0; sc < n; sc = sc + 6)
    {
      vector<int> deploy_sf(3);
      for (int i = sc * 6; i < (sc * 6) + 6; i = i + 2)
      {
        int bin_0, bin_1;
        int dec;
        //整数bitを2進法表記したときの、下からi桁目が1か判定
        //cout << (bit & (1 << i));
        if (bit & (1 << i))
        {
          if (bit & (1 << i + 1))
          {
            dec = bin2dec(1, 1);
          }
          else
          {
            dec = bin2dec(0, 1);
          }
          //cout << 1;
          //S += a[i];
        }
        else
        {
          if (bit & (1 << i + 1))
          {
            dec = bin2dec(1, 0);
          }
          else
          {
            dec = bin2dec(0, 0);
          }
          //cout << 0;
        }

        //iビット目の
        int index_deploy_sf = (i % 6) /2;
        deploy_sf[index_deploy_sf] = dec;
        cout << deploy_sf[index_deploy_sf];
      }
      cout << " ";
    }
    if (S == W)
    {
      ans++;
      cout << "(hit)";
    }
    cout << ":" << bit << endl;
  }
  //これダメなの？？
  /*
  for(int i = 0; i < NUM_SERVER; i++){
    server[i] = make_tuple((CPU_CORE, RAM, 0);
  }
  */

  /*
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
    

    // sf配置を全通り試す
    for (int m = 0; m < 25; m++)
    {
      // 1つめのsf配置
      for (int fst = 0; fst < NUM_SERVER; fst++)
      {
        // 2つめのsf配置
        for (int scd = 0; scd < NUM_SERVER; scd++)
        {
          // 3つめのsf配置
          for (int trd = 0; trd < NUM_SERVER; trd++)
          {
            // 4つめのsf配置
            for (int fth = 0; fth < NUM_SERVER; fth++)
            {
              //CPUコア
              req_server[fst].first += 4;
              req_server[scd].first += 4;
              req_server[trd].first += 4;
              req_server[fth].first += 4;
              //メモリ
              req_server[fst].second += 4;
              req_server[scd].second += 4;
              req_server[trd].second += 4;
              req_server[fth].second += 4;
            }
          }
        }
      }
    }
  }
  */
  return 0;
}
