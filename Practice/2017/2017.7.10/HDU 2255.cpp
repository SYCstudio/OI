#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

class Edge
{
public:
    int v,w;
};

const int maxN=301;
const int inf=2147483647;

int n;
int G[maxN][maxN];
int Wx[maxN];
int Wy[maxN];
int Match[maxN];
bool visx[maxN];
bool visy[maxN];

int read();
bool Hungary(int u);//匈牙利算法

int main()
{
    while (cin>>n)
    {
        for (int i=1;i<=n;i++)//注意初始化
        {
            Wx[i]=-inf;
            Wy[i]=0;
        }
        memset(Match,-1,sizeof(Match));
        for (int i=1;i<=n;i++)
            for (int j=1;j<=n;j++)
            {
                int x=read();
                G[i][j]=x;
                Wx[i]=max(Wx[i],x);//顺带把Wx初始化
            }
        for (int i=1;i<=n;i++)
        {
            while (1)
            {
                memset(visx,0,sizeof(visx));
                memset(visy,0,sizeof(visy));
                if (Hungary(i))//如果匹配成功则退出，匹配下一个
                    break;
                int D=inf;//若不成功则增加一条当前权值最大的增广路
                for (int i=1;i<=n;i++)
                    if (visx[i]==1)
                        for (int j=1;j<=n;j++)
                            if (visy[j]==0)
                                D=min(D,Wx[i]+Wy[j]-G[i][j]);
                for (int i=1;i<=n;i++)
                    if (visx[i]==1)
                        Wx[i]-=D;
                for (int i=1;i<=n;i++)
                    if (visy[i]==1)
                        Wy[i]+=D;
            }
        }
        int Ans=0;
        for (int i=1;i<=n;i++)
            Ans+=G[Match[i]][i];
        cout<<Ans<<endl;
    }
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
    while ((ch>='0')&&(ch<='9'))
    {
        x=x*10+ch-48;
        ch=getchar();
    }
    return x*k;
}

bool Hungary(int u)
{
    visx[u]=1;
    for (int i=1;i<=n;i++)
        if ((visy[i]==0)&&(Wx[u]+Wy[i]==G[u][i]))
        {
            visy[i]=1;
            if ((Match[i]==-1)||(Hungary(Match[i])))
            {
                Match[i]=u;
                return 1;
            }
        }
    return 0;
}