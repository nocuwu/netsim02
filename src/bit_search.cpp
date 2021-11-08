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
