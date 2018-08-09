#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <hash_map>
#include <set>
using namespace std;
using namespace __gnu_cxx;

typedef struct listnode
{
    int value;
     struct listnode *pnext;
}ListNode;

typedef struct binarytree
{
    int value;
    struct binarytree *pleft;
    struct binarytree *pright;
}Btree;
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
    for(int i = 0; i < sum; i++)cout << "i:" << i << "num:" << dp[coinKinds][i] << endl;
    return dp[coinKinds][sum];
}

/*计算一个整数二进制中1的个数10111100*/
/*
    1.让整数右移和1&
    2.让1左移和整数&
    3，n-1 & n会使最右边的1变成0

判断一个数是不是2的整数次方，只有一个1
*/
int numof1(int n)
{
    int numcount = 0;
    while(n)
    {
        numcount++;
        n = (n - 1) & n;
    }

    return numcount;
}


/*打印n位数从1到最大*/
void printnumber(char *number, int length)
{
    int zerofrefix  = true;
    for(int i = 0; i < length; i++)
    {
        if (zerofrefix && number[i] != '0')
        {
            zerofrefix = false;
        }
        if (!zerofrefix)
        {
            printf("%c", number[i]);
        }
    }
    printf("\n");
}
void fullprintProc(char *number, int length, int index)
{
    if(index == length)
    {
        printnumber(number, length);
        return;
    }
    for(int i = 0; i < 10; i++)
    {
        number[index] = '0' + i;
        fullprintProc(number, length, index + 1);
    }
}
void fullprint(int n)
{
    char *number = new char[n + 1];
    number[n] = '\0';
    //for (int i =0; i < 10; i++)
    fullprintProc(number, n, 0);
    delete []number;
}

bool iseven(int a)
{
    return a & 0x1;
}
void recordOddEven(int *array, int length, bool (*func)(int))
{
    int left = 0;
    int right = length - 1;
    int temp;

    while(left < right)
    {
        while((left < right) && func(array[left]))left++;

        while((left < right) && func(array[right]) == 0)right--;
        if(left < right)
        {
            temp = array[right];
            array[right] = array[left];
            array[left] = temp;
        }
    }

    for(int i = 0; i < length; i++)cout << array[i] << "\t";
    cout << endl; 
}



/*链表翻转*/
#if 0
ListNode *reverseList(ListNode *phead)
{
    std::stack<ListNode> listStack;
    if(phead == NULL)
    {
        return NULL;
    }

    while()
    {
        s.push();
    }

    while(!s.empty())
    {
        s.top();
        s.pop();
    }
}
ListNode *reverseList(ListNode *phead)
{
    ListNode *pnext;
    ListNode *pnode;
    ListNode *pnew;
    ListNode *p_pre = NULL;
    if(NULL == phead)
    {
        return NULL;
    }

    pnode = phead;
    while(pnode)
    {
        pnext = pnode->pnext;
        if (pnext == NULL)
            pnew = pnode;         
        pnode->pnext= p_pre;

        p_pre = pnode;
        pnode = pnext;
    }

    return pnew;
}
#endif


/*判断一个树里是不是存在子树*/
/********/
bool existSubtreeProc(Btree *proot1, Btree *proot2)
{
    if(proot2 == NULL)
    {
        return true;
    }
    if (proot1 == NULL)
    {
        return false;
    }    
    if(proot1->value != proot2->value)
    {
        return false;
    }

    return existSubtreeProc(proot1->pleft, proot2->pleft) && existSubtreeProc(proot1->pright, proot2->pright);
}
bool existSubtree(Btree *proot1, Btree *proot2)
{
    bool exist = false;

    if ((NULL != proot1) && (NULL != proot2))
    {
        if(proot1->value == proot2->value)
        {
            exist = existSubtreeProc(proot1, proot2);
        }
        if(!exist)
        {
            exist = existSubtree(proot1->pleft, proot2);
        }
        if(!exist)
        {
            exist = existSubtree(proot1->pright, proot2);
        }
    }
        
    return exist;
}



/*实现带有min函数的栈结构*/
template <typename T>
class StackWithMin
{
public:
    void push(const T& data);
    void pop();
    const T& min();
private:
    std::stack<T> s_data;
    std::stack<T> s_min;
};

template <typename T> void StackWithMin<T>::push(const T& data)
{
    s_data.push(data);
    if(s_min.empty() || data < s_data.top())
    {
        s_min.push(data);
    }
    else
    {
        s_min.push(s_min.top());
    }
    
}
template <typename T> void StackWithMin<T>::pop()
{
    assert(!s_min.empty() && !s_data.empty());
    s_min.pop();
    s_data.pop();
}
template <typename T> const T& StackWithMin<T>::min()
{
    return s_min.top();
}

/*判断一个序列是不是入栈序列的出栈序列*/
bool IspopOrder(int *push, int *pop, int length)
{
    bool ret = false;
    int i = 0;
    int j = 0;
    std::stack<int> s_datatemp;
    if((push != NULL) && (NULL != pop) && (length > 0))
    {
        while(i <= length)
        {
            if(s_datatemp.empty() || s_datatemp.top() != pop[j])
            {
                if(i == length)
                {
                    break;
                }
                s_datatemp.push(push[i]);
                i++;
            }
            else if(s_datatemp.top() == pop[j])
            {
                s_datatemp.pop();
                j++;
            }
        }
        if(j == length)ret = true;
    }

    return ret;
}

/*按层打印二叉树*/
void printBtreeBylayer(Btree *proot)
{
    std::queue<Btree> treeTemp;
    if (NULL == proot)
    {
        return;
    }
    treeTemp.push(*proot);
    while(!treeTemp.empty())
    {
        cout << treeTemp.front().value << endl;
        if(NULL != treeTemp.front().pleft)
            treeTemp.push(*treeTemp.front().pleft);
        if(NULL != treeTemp.front().pright)
            treeTemp.push(*treeTemp.front().pright);
        treeTemp.pop();
    }
}


/*判断一个序列是不是某个二叉搜索树的后续遍历结果*/
bool is_BST_after_traver(int *ptraverArry, int length)
{
    bool ret = false;
    if (NULL == ptraverArry || length <= 0)return false;

    int rootvalue = ptraverArry[length - 1];
    int i = length - 1;
    int index;
    while( i >= 0)
    {
        if(ptraverArry[i] < rootvalue)
        {
            break;
            index = i;
        }
        i--;
    }
    while(i >= 0)
    {
        if (ptraverArry[i] >= rootvalue)return false;
    }

    if(index > 0 )
        ret = is_BST_after_traver(ptraverArry + index + 1, length - 2 - index);
    if(index < length - 2)
        ret = ret && is_BST_after_traver(ptraverArry + index + 1, length - 2 - index);

    return ret;
}


/*dayin BiTree zhong he wei mou yi zhi de lu jing */
void printsumroadProc(Btree *proot, int sum, int &cursum, std::vector<int> &mpath)
{
    cursum += proot->value;
    mpath.push_back(proot->value);

    bool isleaf = ((proot->pleft == NULL) && (NULL == proot->pright));
    if (isleaf && cursum == sum)
    {
        for(std::vector<int>::iterator it = mpath.begin(); it != mpath.end(); it++)
            cout << *it ;
        cout << endl;
    }
    if(NULL != proot->pleft)
        printsumroadProc(proot->pleft, sum, cursum, mpath);
    if(NULL != proot->pright)
        printsumroadProc(proot->pright, sum, cursum, mpath);

    cursum -= proot->value;
    mpath.pop_back();
}

void printsumroad(Btree *proot, int sum)
{
    if (NULL == proot) return;
    std::vector<int> path;
    int cursum = 0;

    printsumroadProc(proot, sum, cursum, path);
}

/**/
void maptest()
{
    std::map<int, string> map_test;
    std::map<int, string>::iterator it;

    map_test.insert(pair<int, string>(1, "1asdsad"));
    map_test.insert(pair<int, string>(2, "2asewdsad"));
    map_test.insert(pair<int, string>(3, "3fdkjadsad"));

    for(it = map_test.begin(); it != map_test.end(); it++)
    {
        cout << "key:" << it->first << "value:" << it->second << endl;
    }
}

int findmostone(int *numbers, int length)
{
    hash_map<int, int> m_number;
    hash_map<int, int>::iterator it;
    for(int i = 0; i < length; i++)
    {
        it = m_number.find(numbers[i]);
        if (it != m_number.end())
        {
            it->second ++;
            if (it->second > length/2)
                return it->first; 
        }
        else
        {
            m_number.insert(pair<int, int>(numbers[i], 1));
        }
    }
    return 0;
}
#if 0
int partition(int number[], int left, int right)
{
    int privot = number[left];
    int i = left;
    int j = right;
    while (true)
    {
        while (i < j && number[j--] >= x);
        if (i >= j) break;
        while (i < j && number[++i] < x);
        if (i >= j) break; 
        swap(&number[i], &number[j]);
    }
    swap(&number[j], &number[right]);
    return j;
}
#endif
void getleastn(int *input, int n, int *output, int k)
{
     if(NULL == input || NULL == output || n < 0 || k < 0  || k < n)return;
     
}

void mutltisetTest()
{
    std::multiset<int> ms_test;
}


void calmaxsu(int *number, int length)
{
    int *temp = new int[length];
    int *sum = new int[length];
    temp[0] = 0;
    int j = 0;
    for(int i = 0; i < length; i++)
    {
        if(temp[i] <= 0)
        {
            j = 0;
            temp[j] = number[i];
        }
        else
        {
            j++;
            temp[j] = number[i];
        }
    }
    for(int i =0; i <= j; i++)
        cout<< "ans:" << temp[j] << endl;
    delete[] temp;
    return;
}


int main()
{
    int money = 100;
    int coin[3] = { 1, 2, 5 };
    int oddeven[] = {7,12,3,1,3,1,2,432,2,5,3};
    #if 0
    find_dest(money, coin, 3);
    coinCombinations(coin, 3, 100);
    cout << "numof1:-20:" << numof1(-20) << endl;  
    fullprint(2);
    recordOddEven(oddeven, sizeof(oddeven)/sizeof(int), iseven);
    StackWithMin<int> a;
    a.push(3);
    a.push(4);
    cout << "min:" << a.min() << endl;
    a.pop();
    cout << "min:" << a.min() << endl;

    int push[] = {1,2,3,4,5};
    int pop[] = {4,5,3,2,1};
    int pop2[] = {4,3,5,1,2};
    printf("<%s>\n", IspopOrder(push, pop, 5)? "true":"false");
    printf("<%s>\n", IspopOrder(push, pop2, 5)? "true":"false");

    maptest();

    int numbers[] = {1,2,3,2,2,2,5,4,2};
    cout<< "is:" << findmostone(numbers, sizeof(numbers)/sizeof(int)) << endl;
    #endif
    int number[] = {1,-2,3,10,-4,7,2,-5};
    calmaxsu(number, 8);
    return 0;
}

