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
    int N, W;
    //cin >> N >> W;
    N = 5;
    W = 10;
    vector<int> A(N);
    /*
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    */
    A[0] = 1;
    A[1] = 2;
    A[2] = 3;
    A[3] = 6;
    A[4] = 8;

    int ans = 0;

    for (int bit = 0; bit < (1 << N); ++bit)
    {
        int S = 0;
        for (int i = 0; i < N; ++i)
        {
            //整数bitを2進法表記したときの、下からi桁目が1か判定
            if (bit & (1 << i))
            {
                cout << A[i];
                S += A[i];
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
