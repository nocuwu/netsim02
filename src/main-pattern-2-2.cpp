#include <wchar.h>
#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip> //fixed << setprecision(10)
#include <functional>
#include <random>
#include <stdlib.h>

using namespace std;

#define rep(i, n) for (int(i) = 0; (i) < (n); (i)++)

typedef long long ll;
typedef vector<int> vi;

// サーバ1つ当たりのCPUコア数
//#define CPU_CORE 8
#define CPU_CORE 9999

// サーバ1つ当たりのメモリ(RAM)[GB]
//#define RAM 16
#define RAM 9999

// スループット（サーバ間）[Mbps]
//#define TP_LINK_SERVER 1000
#define TP_LINK_SERVER 99999

// サーバ台数
//#define NUM_SERVER 4
#define NUM_SERVER 4

#define SIZE_DATA 10.7

#define IN 4
#define OUT 5


/*
int bin2dec(int bin_1, int bin_0){
    return (bin_1 * bin_1) + bin_0;
}

int main()
{
    int n = 6;
    int W = 10;
    vector<int> a(n);

    for(int i = 0; i < n; i++){
        a[i] = 1;
    }

    int ans = 0;

    //組み合わせ数ループ
    for (int bit = 0; bit < (1 << n); ++bit)
    {
        int S = 0;
        for (int i = 0; i < n; i = i + 2)
        {
            int bin_0, bin_1;
            //整数bitを2進法表記したときの、下からi桁目が1か判定
            //cout << (bit & (1 << i));
            if (bit & (1 << i))
            {
                if (bit & (1 << i+1)){
                    cout << 3;
                }
                else{
                    cout << 1;
                }
                //cout << 1;
                //S += a[i];
            }
            else{
                if (bit & (1 << i+1)){
                    cout << 2;
                }
                else{
                    cout << 0;
                }
                //cout << 0;
            }
            
        }
        if (S == W)
        {
            ans++;
            cout << "(hit)";
        }
        cout << ":"<< bit << endl;
    }
}
*/

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

struct proc
{
  double d;
  double t;
} typedef proc;

//2進数をint型10進数に変換して返す
int bin2dec(int bin_1, int bin_0)
{
  return (bin_1 * 2) + bin_0;
}

//シャッフル
void shuffle(int ary[], int size)
{
  for (int i = 0; i < size; i++)
  {
    int j = rand() % size;
    int t = ary[i];
    ary[i] = ary[j];
    ary[j] = t;
  }
}

//映像取得
double camera()
{
  return 4.0;
  //return 1.0;
}

//FFmpeg（画像変換）
double ffmpeg_pic(double size_data)
{
  proc ffmpeg_pic;
  ffmpeg_pic.t = 5.5;
  ffmpeg_pic.d = size_data / 2.0;
  return 5.5;
}

//FFmpeg（エンコード）
double ffmpeg_encode(double size_data)
{
  double time;
  time = size_data / 48.4;
  return time;
  //return 1.0;
}

//FFmpeg（指定範囲切り出し）
double ffmpeg_cut(double size_data)
{
  double time;
  time = size_data / 43.7;
  return time;
  //return 1.0;
}

//FFmpeg（解像度変更）
double ffmpeg_reso(double size_data)
{
  double time;
  time = size_data / 74.3;
  return time;
  //return 1.0;
}

//FFmpeg（FPS変更）
double ffmpeg_fps(double size_data)
{
  double time;
  time = size_data / 44.8;
  return time;
  //return 1.0;
}

//イメージモザイキング
double mosiac(double size_data)
{
  double time;
  time = size_data / 1.8;
  return time;
}

//赤外線画像人物検出
double detect(double size_data)
{
  double time;
  time = size_data / 0.92;
  return time;
}

//YOLO v2
double yolo(double size_data)
{
  //==detect()
  double time;
  time = size_data / 0.92;
  return time;
  //return 1.0;
}

//MPEG-DASH
int dash(double size_data)
{
  return 0;
}

//処理時間を計算
double processing(int sf, double size_data)
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

//データサイズ変化を計算
double compression(int sf, double size_data_raw)
{
  if (sf == 0)
  {
    return size_data_raw;
  }
  //video -> pic
  else if (sf == 1)
  {
    return size_data_raw * 0.75;
  }
  //jikannshitei
  else if (sf == 2)
  {
    return size_data_raw * 0.51;
  }
  else if (sf == 3)
  {
    return size_data_raw;
  }
  else if (sf == 4)
  {
    return size_data_raw;
  }
  else if (sf == 5)
  {
    return size_data_raw;
  }
  else if (sf == 6)
  {
    return size_data_raw;
  }
  else if (sf == 7)
  {
    return size_data_raw;
  }
  else if (sf == 8)
  {
    return size_data_raw;
  }
  else if (sf == 9)
  {
    return size_data_raw;
  }

  return 0;
}

int main()
{
  //------service function の設定
  //sfの種類数
  int types_sf = 10;
  //sf[0].first: vnf0の要求cpuコア数
  //sf[0].second: vnf0の要求メモリ[GB]
  vector<pair<int, int>> sf(types_sf);

  //sf[].first: cpu, sf[].second: ram
  //camera
  sf[0] = make_pair(2, 4);
  //ffmpeg(pic)
  sf[1] = make_pair(1, 2);
  //encode
  sf[2] = make_pair(2, 2);
  //cut
  sf[3] = make_pair(2, 2);
  //reso
  sf[4] = make_pair(2, 2);
  //fps
  sf[5] = make_pair(2, 2);
  sf[6] = make_pair(2, 2);
  sf[7] = make_pair(2, 2);
  //yolo
  sf[8] = make_pair(2, 2);
  sf[9] = make_pair(2, 2);

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
  //sc1の1番目のsfは1
  sc1.req_sf[1] = 1;
  sc1.req_sf[2] = 7;

  sc1.req_bw = 100'000'000;
  sc1.req_cpu_sc = sf[0].first + sf[1].first + sf[2].first + sf[4].first;
  sc1.req_ram_sc = sf[0].second + sf[1].second + sf[2].second + sf[4].second;

  //処理速度が順序に大きく依存するsc
  sc sc2;
  sc2.req_sf.resize(6);
  /*
  for (int i = 0; i < sc0.req_sf.size(); i++)
  {
    sc0.req_sf[i] = false;
  }
  */
  /*
  //camera
  sc2.req_sf[0] = 0;
  //cut
  sc2.req_sf[1] = 3;
  //reso
  sc2.req_sf[2] = 4;
  //fps
  sc2.req_sf[3] = 5;
  //encode
  sc2.req_sf[4] = 2;
  //yolo
  sc2.req_sf[5] = 8;
  */
  //要求scのsf数
  int num_of_sf = 6;

  //camera
  sc2.req_sf[0] = 0;

  int flow_right = 0;
  //ランダムな順序で要求
  if (flow_right == 0)
  {
    vector<int> list(num_of_sf - 1);
    mt19937_64 get_rand_mt;

    list[0] = 3;
    list[1] = 4;
    list[2] = 5;
    list[3] = 8;
    list[4] = 2;

    shuffle(list.begin(), list.end(), get_rand_mt);
    for (int i = 0; i < 5; i++)
    {
      sc2.req_sf[i + 1] = list[i];
    }
  }
  //処理データが最小になる順序で要求
  else if (flow_right == 1)
  {
    vector<pair<int, int>> queue(num_of_sf - 1);
    queue[0] = make_pair(compression(3, 10.0), 3);
    queue[1] = make_pair(compression(3, 10.0), 4);
    queue[2] = make_pair(compression(3, 10.0), 5);
    queue[3] = make_pair(compression(3, 10.0), 2);
    queue[4] = make_pair(compression(3, 10.0), 8);

    sort(queue.begin(), queue.end());

    for (int i = 0; i < 5; i++)
    {
      sc2.req_sf[i + 1] = queue[i].second;
    }

    /*
    //cut
    sc2.req_sf[1] = 3;
    //reso
    sc2.req_sf[2] = 4;
    //fps
    sc2.req_sf[3] = 5;
    //encode
    sc2.req_sf[4] = 2;
    //yolo
    sc2.req_sf[5] = 8;
    */
  }
  /*
  sc2.req_sf[0] = 0;
  sc2.req_sf[1] = 2;
  sc2.req_sf[2] = 3;
  sc2.req_sf[3] = 4;
  sc2.req_sf[4] = 5;
  sc2.req_sf[5] = 8;
  */
  /*
  for (int i = 0; i < 10; i++)
  {
    printf("%d,", list[i]);
  }
  */

  sc2.req_bw = 100'000'000;
  sc2.req_cpu_sc = sf[0].first + sf[1].first + sf[2].first + sf[4].first;
  sc2.req_ram_sc = sf[0].second + sf[1].second + sf[2].second + sf[4].second;

  //cout << sc1.req_cpu_sc << endl;

  //サーバ4つのトポロジー
  topology topology;
  topology.t_cpu = CPU_CORE * NUM_SERVER;
  topology.t_ram = RAM * NUM_SERVER;

  //各サーバ容量
  vector<pair<int, int>> server(NUM_SERVER);

  server[0] = make_pair(CPU_CORE, RAM);
  server[1] = make_pair(CPU_CORE, RAM);
  server[2] = make_pair(CPU_CORE, RAM);
  server[3] = make_pair(CPU_CORE, RAM);

  //各リンク要求
  //ノード（サーバ+IN+OUT）
  int num_of_node = 6;
  vector<vector<int>> link;
  link.assign(num_of_node, vector<int>(num_of_node, 0));

  link[IN][0] = TP_LINK_SERVER;
  link[IN][1] = TP_LINK_SERVER;
  link[IN][2] = TP_LINK_SERVER;
  link[IN][3] = TP_LINK_SERVER;
  link[0][1] = TP_LINK_SERVER;
  link[0][2] = TP_LINK_SERVER;
  link[0][3] = TP_LINK_SERVER;
  link[1][2] = TP_LINK_SERVER;
  link[1][3] = TP_LINK_SERVER;
  link[2][3] = TP_LINK_SERVER;
  link[0][OUT] = TP_LINK_SERVER;
  link[1][OUT] = TP_LINK_SERVER;
  link[2][OUT] = TP_LINK_SERVER;
  link[3][OUT] = TP_LINK_SERVER;

  //****************************************************************************************
  //n = sc数*12
  //n = 12 でsf6 x 2
  //n = 18 でsf6 x 3
  int n = 18;
  int W = 10;

  vector<int> a(n);

  for (int i = 0; i < n; i++)
  {
    a[i] = 1;
  }

  int ans = 0;

  //sc発生
  //発生させるscの数
  int num_of_sc = 2;
  vector<int> req_sc(num_of_sc);

  std::mt19937 mt{std::random_device{}()};
  std::uniform_int_distribution<int> dist(0, 1);

  //req_sc[i] = js
  //==i番目にscjが発生した
  /*
  req_sc[0] = 0;
  req_sc[1] = 0;
  req_sc[2] = 0;
  req_sc[3] = 0;
  */
  for (int i = 0; i < num_of_sc; i++)
  {
    //req_sc[i] = dist(mt);
    req_sc[i] = 2;
  }

  //best
  vector<pair<int, int>> best_pattern_accepted(NUM_SERVER);
  best_pattern_accepted[0] = make_pair(-1, -1);
  best_pattern_accepted[1] = make_pair(-1, -1);
  best_pattern_accepted[2] = make_pair(-1, -1);
  best_pattern_accepted[3] = make_pair(-1, -1);

  double best_bottleneck_server_time_passed = 9999;

  //***************組み合わせループ***********************************************************
  for (int bit = 0; bit < (1 << n); ++bit)
  {
    cout << bit << " ";
    int S = 0;
    int flag = 1;

    //各サーバ要求
    vector<pair<int, int>> req_server(NUM_SERVER);
    req_server[0] = make_pair(0, 0);
    req_server[1] = make_pair(0, 0);
    req_server[2] = make_pair(0, 0);
    req_server[3] = make_pair(0, 0);

    //サーバの処理時間
    /*
    vector<double> server_time_passed(4);
    for (int i = 0; i < 4; i++)
    {
      server_time_passed[i] = 0;
    }
    */
    vector<double> server_time_passed(2);
    for (int i = 0; i < 2; i++)
    {
      server_time_passed[i] = 0;
    }
    vector<double> server_time_passed_back(2);
    for (int i = 0; i < 2; i++)
    {
      server_time_passed[i] = 0;
    }

    //各リンク要求
    vector<vector<int>> req_link;
    req_link.assign(num_of_node, vector<int>(num_of_node, 0));

    double size_data = SIZE_DATA;

    //***********************scループ
    //for (int sc = 0; sc < n; sc = sc + 12)
    for (int sc = 0; sc < n; sc = sc + 6)
    {
      //double size_data = SIZE_DATA;
      //sfの配置先
      vector<int> deploy_sf(num_of_sf);

      //今見てるscの要求sfリスト
      vector<int> req_sf(types_sf);
      /*
      vector<double> server_time_passed_sc(4);
      for (int i = 0; i < 4; i++)
      {
        server_time_passed_sc[i] = 0;
      }
      */
      vector<double> server_time_passed_sc(2);
      for (int i = 0; i < 2; i++)
      {
        server_time_passed_sc[i] = 0;
      }
      vector<double> server_time_passed_sc_back(2);
      for (int i = 0; i < 2; i++)
      {
        server_time_passed_sc_back[i] = 0;
      }

      //サーバの待機時間
      //ex)2番目のsfを処理するサーバが1番目を待っている時間
      double time_standby_all = 0;

      double time_standby[3];
      time_standby[0] = 0.0;
      time_standby[1] = 0.0;
      time_standby[2] = 0.0;
      time_standby[3] = 0.0;

      /*
      //要求scが0だったら
      if (req_sc[sc / 6] == 0)
      {
        //sc0の要求sf番号の配列をコピー
        for (int j = 0; j < types_sf; j++)
        {
          req_sf[j] = sc0.req_sf[j];
        }
      }
      //要求scが1だったら
      else if (req_sc[sc / 6] == 1)
      {
        for (int j = 0; j < types_sf; j++)
        {
          req_sf[j] = sc1.req_sf[j];
        }
      }
      */

      //要求scが2(方式2　専用)
      //if (req_sc[sc / 12] == 2)
      if (req_sc[sc / 6] == 2)
      {
        for (int j = 0; j < 6; j++)
        {
          req_sf[j] = sc2.req_sf[j];
        }
      }
      else
      {
        //cout << (req_sc[sc / 6]) << endl;
      }

      int dec_old = -1;

      //*************************sfループ
      //for (int i = sc + 1; i < sc + 12 + 1; i += 2)
      for (int i = sc; i < sc + 6; i++)
      {

        int bin_0, bin_1;
        int dec;
        //整数bitを2進法表記したときの、下からi桁目が1か判定
        //cout << (bit & (1 << i));
        /*
        if (bit & (1 << i))
        {
          if (bit & (1 << i - 1))
          {
            dec = bin2dec(1, 1);
          }
          else
          {
            dec = bin2dec(1, 0);
          }
          //cout << 1;
          //S += a[i];
        }
        else
        {
          if (bit & (1 << i - 1))
          {
            dec = bin2dec(0, 1);
          }
          else
          {
            dec = bin2dec(0, 0);
          }
          //cout << 0;
        }
        */

        if (bit & (1 << i))
        {
          dec = 1;
        }
        else
        {
          dec = 0;
        }

        //今見てるsc内で何番目のsfか
        //ex) index_deploy_sf = 0 -> 0番目のsf
        int index_deploy_sf = (i % 6);
        //int index_deploy_sf = (i % 12) / 2;

        //そのsfが割り当てられたサーバ番号
        //ex) deploy_sf[index_deploy_sf] = 0 -> 0番目のsfの割当先がサーバ0
        deploy_sf[index_deploy_sf] = dec;

        //あるサーバに要求されるCPUコア数の総和
        //サーバ0のコア数 += 0番目のsfの要求コア
        req_server[deploy_sf[index_deploy_sf]].first += sf[req_sf[index_deploy_sf]].first;

        //あるサーバに要求されるCPUコア数の総和
        //サーバ0のメモリ += 0番目のsfの要求メモリ
        req_server[deploy_sf[index_deploy_sf]].second += sf[req_sf[index_deploy_sf]].second;

        /*
        //帯域
        if (index_deploy_sf == 2)
        {
          req_link[IN][deploy_sf[index_deploy_sf - 2]] += 250;
          req_link[deploy_sf[index_deploy_sf - 2]][deploy_sf[index_deploy_sf - 1]] += 250;
          req_link[deploy_sf[index_deploy_sf - 1]][deploy_sf[index_deploy_sf]] += 250;
          req_link[deploy_sf[index_deploy_sf]][OUT] += 250;
        }
        */

        //各scの待ち時間を加算
        //0~1番目の処理時間を2番目を処理するサーバに加える
        /*
        if (index_deploy_sf == 0)
        {
          time_standby_all += processing(req_sf[index_deploy_sf], size_data);
        }
        else if (index_deploy_sf == 1)
        {
          server_time_passed_sc[dec] += (time_standby_all - server_time_passed_sc[dec]);
          time_standby_all += processing(req_sf[index_deploy_sf], size_data);
        }
        else if (index_deploy_sf == 2)
        {
          server_time_passed_sc[dec] += (time_standby_all - server_time_passed_sc[dec]);
          time_standby_all += processing(req_sf[index_deploy_sf], size_data);
        }
        else if (index_deploy_sf == 3)
        {
          server_time_passed_sc[dec] += (time_standby_all - server_time_passed_sc[dec]);
          time_standby_all += processing(req_sf[index_deploy_sf], size_data);
        }
        else if (index_deploy_sf == 4)
        {
          server_time_passed_sc[dec] += (time_standby_all - server_time_passed_sc[dec]);
          time_standby_all += processing(req_sf[index_deploy_sf], size_data);
        }
        else if (index_deploy_sf == 5)
        {
          server_time_passed_sc[dec] += (time_standby_all - server_time_passed_sc[dec]);
        }
        */

        //算出された処理時間を割当先のサーバに足していく
        //server_time_passed_sc[dec] += max(server_time_passed_sc[0], server_time_passed_sc[1]);
        /*
        if (dec_old != dec)
        {
          server_time_passed_sc[dec] += max(server_time_passed_sc[0], server_time_passed_sc[1]);
        }
        dec_old = dec;
        server_time_passed_sc[dec] += processing(req_sf[index_deploy_sf], size_data);
        */
        if (dec == 0)
        {
          server_time_passed_sc[0] += server_time_passed_sc_back[0] + processing(req_sf[index_deploy_sf], size_data);
          server_time_passed_sc_back[1] += processing(req_sf[index_deploy_sf], size_data);
        }
        if (dec == 1)
        {
          server_time_passed_sc[1] += server_time_passed_sc_back[1] + processing(req_sf[index_deploy_sf], size_data);
          server_time_passed_sc_back[0] += processing(req_sf[index_deploy_sf], size_data);
        }

        if (req_sf[index_deploy_sf] == 2)
        {
          size_data *= 0.38;
          //size_data *= 1.0;
        }
        else if (req_sf[index_deploy_sf] == 3)
        {
          size_data *= 0.51;
          //size_data *= 1.0;
        }
        else if (req_sf[index_deploy_sf] == 4)
        {
          size_data *= 0.5;
          //size_data *= 1.0;
        }
        else if (req_sf[index_deploy_sf] == 5)
        {
          size_data *= 0.89;
          //size_data *= 1.0;
        }

        cout << deploy_sf[index_deploy_sf];
        /*
        if(i == 0){
          cout << "a";
        }
        */
      }
      cout << " ";

      //今回のscでサーバに割り当てられた処理時間を全体のに加算
      for (int ii = 0; ii < 2; ii++)
      {
        server_time_passed[ii] += server_time_passed_sc[ii];
        server_time_passed[ii] -= min(server_time_passed_back[ii], server_time_passed_sc_back[ii]);
        server_time_passed_back[ii] = fabs(server_time_passed_back[ii] - server_time_passed_sc_back[ii]);
      }
    }

    /*
    if (S == W)
    {
      ans++;
      cout << "(hit)";
    }
    */

    //要求CPUコア数を出力
    for (int j = 0; j < NUM_SERVER; j++)
    {
      cout << req_server[j].first << " ";
    }
    //要求メモリ容量を出力
    for (int j = 0; j < NUM_SERVER; j++)
    {
      cout << req_server[j].second << " ";
    }

    for (int i = 0; i < NUM_SERVER; i++)
    {
      if (req_server[i].first > server[i].first)
      {
        flag = 0;
      }
      if (req_server[i].second > server[i].second)
      {
        flag = 0;
      }
    }

    //必要帯域を出力
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

    if (req_link[IN][0] > link[IN][0])
    {
      flag = 0;
    }
    if (req_link[IN][1] > link[IN][1])
    {
      flag = 0;
    }
    if (req_link[IN][2] > link[IN][2])
    {
      flag = 0;
    }
    if (req_link[IN][3] > link[IN][3])
    {
      flag = 0;
    }
    if (req_link[0][1] > link[0][1])
    {
      flag = 0;
    }
    if (req_link[0][2] > link[0][2])
    {
      flag = 0;
    }
    if (req_link[0][3] > link[0][3])
    {
      flag = 0;
    }
    if (req_link[1][2] > link[1][2])
    {
      flag = 0;
    }
    if (req_link[1][3] > link[1][3])
    {
      flag = 0;
    }
    if (req_link[2][3] > link[2][3])
    {
      flag = 0;
    }
    if (req_link[0][OUT] > link[0][OUT])
    {
      flag = 0;
    }
    if (req_link[1][OUT] > link[1][OUT])
    {
      flag = 0;
    }
    if (req_link[2][OUT] > link[2][OUT])
    {
      flag = 0;
    }
    if (req_link[3][OUT] > link[3][OUT])
    {
      flag = 0;
    }

    double bottleneck_server_time_passed = -1.0;
    for (int k = 0; k < 2; k++)
    {
      //一番遅いサーバを見つける
      bottleneck_server_time_passed = max(bottleneck_server_time_passed, server_time_passed[k]);
      cout << server_time_passed[k] << " ";
    }
    cout << endl;

    //一番はやい組み合わせの合計処理時間
    if (flag == 1)
    {
      best_bottleneck_server_time_passed = min(best_bottleneck_server_time_passed, bottleneck_server_time_passed);
    }
  }

  cout << best_bottleneck_server_time_passed << endl;
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
