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

#define IN 4
#define OUT 5

//トポロジの残余リソース
struct topology
{
  int t_cpu;
  int t_ram;
};

//サービス（ファンクション）チェイン
struct sc
{
  vector<int> req_sf;
  //sc要求帯域
  int req_bw;
  //sc要求cpuコア数
  int req_cpu_sc;
  //sc要求メモリ[GB]
  int req_ram_sc;
};

//2進数をint型10進数に変換して返す
int bin2dec(int bin_1, int bin_0)
{
  return (bin_1 * 2) + bin_0;
}

//映像取得
int camera()
{
  return 0;
}

//FFmpeg（画像変換）
int ffmpeg_pic(int size_data)
{
  return 0;
}

//FFmpeg（エンコード）
int ffmpeg_encode(int size_data)
{
  return 0;
}

//FFmpeg（指定範囲切り出し）
int ffmpeg_cut(int size_data)
{
  return 0;
}

//FFmpeg（解像度変更）
int ffmpeg_reso(int size_data)
{
  return 0;
}

//FFmpeg（FPS変更）
int ffmpeg_fps(int size_data)
{
  return 0;
}

//イメージモザイキング
int mosiac(int size_data)
{
  int time;
  time = size_data / 2;
  return time;
}

//赤外線画像人物検出
int detect(int size_data)
{
  int time;
  time = size_data;
  return time;
}

//YOLO v2
int yolo(int size_data)
{
  return 0;
}

//MPEG-DASH
int dash(int size_data)
{
  return 0;
}

//処理時間を計算
int processing(int sf, int size_data)
{
  if (sf == 0)
  {
    return camera();
  }
  else if (sf == 1)
  {
    return ffmpeg_pic(size_data);
  }
  else if (sf == 2)
  {
    return ffmpeg_encode(size_data);
  }
  else if (sf == 3)
  {
    return ffmpeg_cut(size_data);
  }
  else if (sf == 4)
  {
    return ffmpeg_reso(size_data);
  }
  else if (sf == 5)
  {
    return ffmpeg_fps(size_data);
  }
  else if (sf == 6)
  {
    return mosiac(size_data);
  }
  else if (sf == 7)
  {
    return detect(size_data);
  }
  else if (sf == 8)
  {
    return yolo(size_data);
  }
  else if (sf == 9)
  {
    return dash(size_data);
  }

  return 0;
}

int main()
{
  //------service function の設定
  //vnfの種類数
  int num_of_sf = 5;
  //sf[0].first: vnf0の要求cpuコア数
  //sf[0].second: vnf0の要求メモリ[GB]
  vector<pair<int, int>> sf(num_of_sf);
  sf[0] = make_pair(2, 2);
  sf[1] = make_pair(2, 2);
  sf[2] = make_pair(2, 2);
  sf[3] = make_pair(2, 2);
  sf[4] = make_pair(2, 2);

  //------service (function) chain の設定
  //データサイズが変化するsc
  sc sc0;
  //要求sf数を4、全て未割当(false)に設定
  sc0.req_sf.resize(3);
  /*
  for (int i = 0; i < sc0.req_sf.size(); i++)
  {
    sc0.req_sf[i] = false;
  }
  */
  //sc0の0番目のsfは0
  //==camera()
  sc0.req_sf[0] = 0;
  //sc0の1番目のsfは1
  //==ffmpeg()
  sc0.req_sf[1] = 1;
  //sc0の1番目のsfは6
  //==mosaic()
  sc0.req_sf[2] = 6;

  sc0.req_bw = 100'000'000;
  sc0.req_cpu_sc = sf[0].first + sf[1].first + sf[2].first + sf[3].first;
  sc0.req_ram_sc = sf[0].second + sf[1].second + sf[2].second + sf[3].second;

  //データサイズが変化しないsc
  sc sc1;
  sc1.req_sf.resize(3);
  /*
  for (int i = 0; i < sc0.req_sf.size(); i++)
  {
    sc0.req_sf[i] = false;
  }
  */
  //sc1の0番目のsfは0
  sc1.req_sf[0] = 0;
  //sc1の1番目のsfは0
  sc1.req_sf[1] = 0;
  sc1.req_sf[2] = 0;

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

  //****************************************************************************************

  int n = 12;
  int W = 10;
  vector<int> a(n);

  for (int i = 0; i < n; i++)
  {
    a[i] = 1;
  }

  int ans = 0;

  //sc発生
  int num_of_sc = 4;
  vector<int> req_sc(num_of_sc);
  //req_sc[i] = j
  //==i番目にscjが発生した
  req_sc[0] = 0;
  req_sc[1] = 0;
  req_sc[2] = 0;
  req_sc[3] = 0;

  //***************組み合わせループ
  for (int bit = 0; bit < (1 << n); ++bit)
  {
    cout << bit << " ";
    int S = 0;

    //各サーバ要求
    vector<pair<int, int>> req_server(NUM_SERVER);
    req_server[0] = make_pair(0, 0);
    req_server[1] = make_pair(0, 0);
    req_server[2] = make_pair(0, 0);
    req_server[3] = make_pair(0, 0);

    //サーバの処理時間
    vector<int> server_time_passed(4);
    for (int i = 0; i < 4; i++)
    {
      server_time_passed[i] = 0;
    }

    //各リンク要求
    int num_of_node = 6;
    vector<vector<int>> req_link;
    req_link.assign(num_of_node, vector<int>(num_of_node, 0));

    //***********************scループ
    for (int sc = 0; sc < n; sc = sc + 6)
    {
      //sfの配置先
      vector<int> deploy_sf(num_of_sf);
      //今見てるscの要求sfリスト
      vector<int> req_sf(num_of_sf);

      //要求scが0だったら
      if (req_sc[sc / 6] == 0)
      {
        //sc0の要求sf番号の配列をコピー
        for (int j = 0; j < num_of_sf; j++)
        {
          req_sf[j] = sc0.req_sf[j];
        }
      }
      //要求scが1だったら
      else if (req_sc[sc / 6] == 1)
      {
        for (int j = 0; j < num_of_sf; j++)
        {
          req_sf[j] = sc1.req_sf[j];
        }
      }
      //*************************sfループ
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

        //今見てるsc内で何番目のsfか
        int index_deploy_sf = (i % 6) / 2;
        //そのsfが割り当てられたサーバ番号
        deploy_sf[index_deploy_sf] = dec;
        //あるサーバに要求されるCPUコア数の総和
        req_server[deploy_sf[index_deploy_sf]].first += sf[req_sf[index_deploy_sf]].first;
        //あるサーバに要求されるCPUコア数の総和
        req_server[deploy_sf[index_deploy_sf]].second += sf[req_sf[index_deploy_sf]].second;

        if (index_deploy_sf == 2)
        {
          req_link[IN][deploy_sf[index_deploy_sf - 2]] += 100;
          req_link[deploy_sf[index_deploy_sf - 2]][deploy_sf[index_deploy_sf - 1]] += 100;
          req_link[deploy_sf[index_deploy_sf - 1]][deploy_sf[index_deploy_sf]] += 100;
          req_link[deploy_sf[index_deploy_sf]][OUT] += 100;
        }

        //算出された処理時間を割当先のサーバに足していく
        server_time_passed[dec] += processing(req_sf[index_deploy_sf], 5);

        cout << deploy_sf[index_deploy_sf];
      }
      cout << " ";
    }
    if (S == W)
    {
      ans++;
      cout << "(hit)";
    }

    for (int j = 0; j < NUM_SERVER; j++)
    {
      cout << req_server[j].first << " ";
    }
    for (int j = 0; j < NUM_SERVER; j++)
    {
      cout << req_server[j].second << " ";
    }

    cout << req_link[IN][0] << " ";
    cout << req_link[IN][1] << " ";
    cout << req_link[IN][2] << " ";
    cout << req_link[IN][3] << " ";
    cout << req_link[0][1] << " ";
    cout << req_link[0][2] << " ";
    cout << req_link[0][3] << " ";
    cout << req_link[1][2] << " ";
    cout << req_link[1][3] << " ";
    cout << req_link[2][3] << " ";
    cout << req_link[0][OUT] << " ";
    cout << req_link[1][OUT] << " ";
    cout << req_link[2][OUT] << " ";
    cout << req_link[3][OUT] << " ";

    for (int k = 0; k < 4; k++)
    {
      cout << server_time_passed[k] << " ";
    }
    cout << endl;
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
