#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

class EDGE
{
public:
    int v,w;
};

const int maxN=30;
const int inf=2147483647;

int n;
vector<EDGE> E[maxN];//存二分图的边
int Match[maxN];//存右边匹配的左点编号
bool use_left[maxN];//判断是否访问，一是避免重复，二十判断是否在增广路上，以便后面加边
bool use_right[maxN];
int Wx[maxN];//两边的顶标
int Wy[maxN];

int read();
bool Hungary(int u);

int main()
{
    int P[maxN][maxN];
    int Q[maxN][maxN];
    mem(Match,-1);
    mem(Wy,0);
    cin>>n;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            P[i][j]=read();
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            Q[i][j]=read();
    for (int i=1;i<=n;i++)
    {
        int D=-inf;//初始化左边的顶标
        for (int j=1;j<=n;j++)
        {
            E[i].push_back((EDGE){j,P[i][j]*Q[j][i]});
            D=max(D,P[i][j]*Q[j][i]);//预处理出Wx
        }
        Wx[i]=D;
        Wy[i]=0;
    }

    for (int i=1;i<=n;i++)
    {
        do
        {
            mem(use_left,0);
            mem(use_right,0);
            if (Hungary(i))
                break;
            int D=inf;
            for (int j=1;j<=n;j++)
                if (use_left[j]==1)
                {
                    for (int k=0;k<E[j].size();k++)
                    {
                        int v=E[j][k].v;
                        int w=E[j][k].w;
                        if (use_right[v]==0)
                        {
                            D=min(D,Wx[j]+Wy[v]-w);
                        }
                    }
                }
            for (int j=1;j<=n;j++)
                if (use_left[j])
                    Wx[j]=Wx[j]-D;
            for (int j=1;j<=n;j++)
                if (use_right[j])
                    Wy[j]=Wy[j]+D;
        }
        while (1);
    }
    int Ans=0;
    for (int i=1;i<=n;i++)
        for (int j=0;j<E[Match[i]].size();j++)
        {
            if (E[Match[i]][j].v==i)
            {
                Ans+=E[Match[i]][j].w;
                break;
            }
        }
    cout<<Ans<<endl;
    return 0;
}

int read()//读入优化
{
    int x=0;
    int k=1;
    char ch=getchar();
    while (((ch>'9')||(ch<'0'))&&(ch!='-'))
        ch=getchar();
    if (ch=='-')
    {
        k=-1;
        ch=getchar();
    }
    while ((ch<='9')&&(ch>='0'))
    {
        x=x*10+ch-48;
        ch=getchar();
    }
    return x*k;
}

bool Hungary(int u)//匈牙利算法判断
{
    use_left[u]=1;
    for (int i=0;i<E[u].size();i++)
    {
        int v=E[u][i].v;
        if ((use_right[v]==0)&&(Wx[u]+Wy[v]==E[u][i].w))
        {
            use_right[v]=1;
            if ((Match[v]==-1) || (Hungary(Match[v])) )
                {
                    Match[v]=u;
                    return 1;
                }
        }
    }
    return 0;
}