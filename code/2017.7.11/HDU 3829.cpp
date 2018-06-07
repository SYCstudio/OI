#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int maxN=200;
const int maxP=1001;
const int inf=2147483647;

class Child
{
public:
    int like,dislike;
};

int n,m,P;
Child C[maxP];
vector<int> E[maxP];
int Match[maxP];
bool vis[maxP];

bool Hungary(int u);

int main()
{
    while (cin>>n>>m>>P)
    {
        memset(Match,-1,sizeof(Match));
        for (int i=1;i<=P;i++)
            E[i].clear();
        for (int i=1;i<=P;i++)//这里把猫和狗的编号处理了一下，猫的编号为1~n，狗的编号为n+1~n+m
        {
            char ch;
            cin>>ch;
            int k=(ch=='C') ? 0 : 1;
            int x;
            cin>>x;
            C[i].like=x+n*k;
            cin>>ch;
            k=(ch=='C') ? 0 : 1;
            cin>>x;
            C[i].dislike=x+n*k;
        }
        
        for (int i=1;i<=P;i++)//看看哪几对小朋友会冲突，建图
            for (int j=i+1;j<=P;j++)
                if ((C[i].like==C[j].dislike)||(C[i].dislike==C[j].like))
                {
                    E[i].push_back(j);
                    E[j].push_back(i);
                }
        
        int Ans=0;
        for (int i=1;i<=P;i++)//匈牙利算法
        {
            memset(vis,0,sizeof(vis));
            if (Hungary(i))
                Ans++;
        }
        cout<<P-Ans/2<<endl;
    }
}

bool Hungary(int u)//匈牙利算法
{
    for (int i=0;i<E[u].size();i++)
    {
        int v=E[u][i];
        if (vis[v]==0)
        {
            vis[v]=1;
            if ((Match[v]==-1)||(Hungary(Match[v])))
            {
                Match[v]=u;
                return 1;
            }
        }
    }
    return 0;
}