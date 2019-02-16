#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<string>
#include<set>
using namespace std;

const int maxN=2001;
const int maxM=1001;
const int inf=2147483647;

int n,m;
int MaxCnt;
vector<int> E[maxN];
int Match[maxN][maxN];
int Num[maxN];
bool vis[maxN];

bool check(int mid);
bool Hungary(int u);

int main()
{
    while (cin>>n>>m)
    {
        if ((n==0)&&(m==0))
            break;
        for (int i=1;i<=n;i++)//init
            E[i].clear();

        string str;
        int x;
        for (int i=1;i<=n;i++)
        {
            cin>>str;
            char ch=getchar();
            while (ch!='\n')//读入，一定要注意啊
            {
                cin>>x;
                E[i].push_back(x+1);
                ch=getchar();
            }
        }
        /*for (int i=1;i<=n;i++)
        {
            for (int j=0;j<E[i].size();j++)
                cout<<E[i][j]<<' ';
            cout<<endl;
        }
        cout<<endl;*/
        int l=0,r=n;
        int Ans=0;
        do//二分答案
        {
            //cout<<l<<' '<<r<<endl;
            int mid=(l+r)/2;
            if (check(mid))
            {
                r=mid;
                Ans=mid;
            }
            else
            {
                l=mid+1;
            }
        }
        while (l<r);
        cout<<l<<endl;//最后输出
    }
    return 0;
}

bool check(int mid)
{
    MaxCnt=mid;
    memset(Num,0,sizeof(Num));
    memset(Match,-1,sizeof(Match));
    for (int i=1;i<=n;i++)
    {
        memset(vis,0,sizeof(vis));
        if (!Hungary(i))//因为必须所有人都匹配，所以若有一个人不能则匹配失败
            return 0;
    }
    return 1;
}

bool Hungary(int u)
{
    for (int i=0;i<E[u].size();i++)
    {
        int v=E[u][i];
        if (vis[v]==0)
        {
            vis[v]=1;
            if (Num[v]<MaxCnt)//首先判断能否直接加入
            {
                Num[v]++;
                Match[v][Num[v]]=u;
                return 1;
            }
            for (int j=1;j<=Num[v];j++)//否则依次将v之前匹配的人进行“让”操作，看能否让出来给u
            {
                if (Hungary(Match[v][j]))
                {
                    Match[v][j]=u;
                    return 1;
                }
            }
        }
    }
    return 0;
}