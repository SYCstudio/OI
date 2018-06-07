#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int maxN=200;
const int inf=2147483647;

int n,m;
vector<int> E[maxN];
int Match[maxN];
bool vis[maxN];//标记第i个皇家飞行员是否已经在我们dfs的路径上（其实就是增广路）

bool Hungary(int u);//匈牙利算法

int main()
{
    cin>>m>>n;
    int u,v;
    while (cin>>u>>v)
    {
        if ((u==-1)&&(v==-1))
            break;
        E[u].push_back(v-m);//注意题目中给出的皇家飞行员编号与我们程序中的不一致，要转换一下
    }
    int Ans=0;
    memset(Match,-1,sizeof(Match));//匹配数组先置为-1，方便判断是否匹配
    for (int i=1;i<=m;i++)
    {
        memset(vis,0,sizeof(vis));//vis记得清空
        if (Hungary(i))//每次跑一边匈牙利算法，看能否匹配
            Ans++;
    }
    if (Ans==0)
    {
        cout<<"No Solution!"<<endl;
        return 0;
    }
    cout<<Ans<<endl;
    for (int i=1;i<=n;i++)
    {
        //cout<<Match[i]<<' '<<i+m<<endl;
        if (Match[i]!=-1)
        {
            cout<<Match[i]<<' '<<i+m<<endl;//输出编号，注意又要转换一下
        }
    }
    return 0;
}

bool Hungary(int u)
{
    for (int i=0;i<E[u].size();i++)
    {
        int v=E[u][i];
        if (vis[v]==0)
        {
            vis[v]=1;
            if ((Match[v]==-1)||(Hungary(Match[v])))//巧妙之处
            {
                Match[v]=u;
                return 1;
            }
        }
    }
    return 0;
}