
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
using namespace std;

/*动态规划算法，解决最少硬币*/
int find_dest(int money, int *coin, int n)

{
    int * minCoin = new int[money + 1];
    minCoin[0] = 0;
    
    for (int i = 1; i <= money; i++)
    {
        int maxCoin = i;

        for (int j = 0; j < n; j++)

        {
            if (i >= coin[j] && j == 0)

            {
                maxCoin = 1 + minCoin[i - coin[j]];
            }
            else if((i >= coin[j] && j != 0))
            {     
               if (minCoin[i - coin[j]] + 1 < maxCoin )
               {
                   maxCoin = minCoin[i - coin[j]] + 1;//F[I] = MIN{F[I-VALUE[J]]+1}
               }
            }
            else if(i < coin[j])
            {
                break;
            }
        }

        minCoin[i] = maxCoin;

    }

    for(int i = 0; i <= money; i++)
    {
        cout << "i:" << i << "num:" << minCoin[i] << endl;
    }
    delete[] minCoin;
    return 0;
}

/*给定数字和硬币种类，计算组合出硬币的方法之和*/
int coinCombinations(int coins[], int coinKinds, int sum)
{
    vector<vector<int> > dp(coinKinds + 1, vector<int>(sum+1,0));

    for (int i = 0; i <= coinKinds; ++i)    //递推初始条件
    {
        dp[i][0] = 1;
    }
    for (int i = 1; i <= coinKinds; ++i)
    {
        for (int j = 1; j <= sum; ++j)
        {
            dp[i][j] = 0;
            //j / coins[i-1]表示能取的该硬币的最大数量。
            for (int k = 0; k <= j / coins[i-1]; ++k)   //i-1是因为coins是从0开始算起的。
            {
                dp[i][j] += dp[i-1][j - k * coins[i-1]];
            }
        }
    }
    for(int i = 0; i < 20; i++)cout << "i:" << i << "num:" << dp[coinKinds][i] << endl;
    return dp[coinKinds][sum];
}

int main()

{
    int money = 100;
    int coin[3] = { 1, 2, 5 };
    //find_dest(money, coin, 3);
    coinCombinations(coin, 3, 20);
    return 0;
}

