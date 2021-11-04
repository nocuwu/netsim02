#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip> //fixed << setprecision(10)
#include <functional>

using namespace std;

int main()
{
    int n = 5;
    int W = 10;
    vector<int> a(n);

    for(int i = 0; i < n; i++){
        a[i] = 1;
    }

    int ans = 0;

    for (int bit = 0; bit < (1 << n); ++bit)
    {
        int S = 0;
        for (int i = 0; i < n; ++i)
        {
            //整数bitを2進法表記したときの、下からi桁目が1か判定
            if (bit & (1 << i))
            {
                cout << a[i];
                //S += a[i];
            }
        }
        if (S == W)
        {
            ans++;
            cout << "(hit)";
        }
        cout << ":"<< bit << endl;
    }

    cout  << ans << endl;
}
