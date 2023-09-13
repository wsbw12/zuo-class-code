#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <unordered_map>
#include <queue>
#include <cstdlib>
#include <unordered_set>
#include <set>

using namespace std;

// leetcode 547. 省份数量 https://leetcode.cn/problems/number-of-provinces
vector<int> father;

int find(int x)
{
    if(father[x]!=x)
    {
        father[x]=find(father[x]);
    }
    return father[x];
}
int findCircleNum(vector<vector<int>>& isConnected) {
    int n=isConnected.size();
    for(int i=0;i<n;i++)
    {
        father.push_back(i);
    }
    int res=n;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(isConnected[i][j]==0)
            {
                continue;
            }else{
                if(find(i)!=find(j))
                {
                    father[find(i)]=find(j);
                    res--;
                }
            }
        }
    }
    return res;
}