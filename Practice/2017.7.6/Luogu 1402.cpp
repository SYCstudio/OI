#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int maxN=200;
const int inf=2147483647;

int n,P,Q;//p是房间，Q是菜
vector<int> Room[maxN];//图
vector<int> Meal[maxN];
bool Modefy[maxN];//因为有两个二分图，第二个不匹配时要把第一个中修改的改回来
int Last[maxN];
bool vis[maxN];//注意这里为什么不能用vis代替Modefy，因为vis在两个Hungary函数中都用到了，而Modefy要保留第一个Hungary的值直到判断出第二个是否匹配，所以不能用vis代替
int Match_room[maxN];
int Match_meal[maxN];

bool Hungary_room(int u);//房间的匈牙利
bool Hungary_meal(int u);//菜的匈牙利

int main()
{
    cin>>n>>P>>Q;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=P;j++)
        {
            int k;
            scanf("%d",&k);
            if (k==1)
                Room[i].push_back(j);
        }

    for (int i=1;i<=n;i++)
        for (int j=1;j<=Q;j++)
        {
            int k;
            scanf("%d",&k);
            if (k==1)
                Meal[i].push_back(j);
        }
    int Ans=0;
    memset(Match_room,-1,sizeof(Match_room));
    memset(Match_meal,-1,sizeof(Match_meal));
    for (int i=1;i<=n;i++)
    {
        memset(vis,0,sizeof(vis));
        memset(Modefy,0,sizeof(Modefy));
        if (Hungary_room(i))
        {
            memset(vis,0,sizeof(vis));
            if (Hungary_meal(i))
            {
                Ans++;
            }
            else
            {
                for (int i=1;i<=P;i++)//若菜匹配失败，则要把房间的改回来
                    if (Modefy[i]==1)
                        Match_room[i]=Last[i];
            }
        }
    }
    cout<<Ans<<endl;
}

bool Hungary_room(int u)
{
    for (int i=0;i<Room[u].size();i++)
    {
        int v=Room[u][i];
        if (vis[v]==0)
        {
            vis[v]=1;
            if ((Match_room[v]==-1)||(Hungary_room(Match_room[v])))
            {
                Modefy[v]=1;//记录下被改变的值的信息
                Last[v]=Match_room[v];
                Match_room[v]=u;
                return 1;
            }
        }
    }
    return 0;
}

bool Hungary_meal(int u)
{
    for (int i=0;i<Meal[u].size();i++)
    {
        int v=Meal[u][i];
        if (vis[v]==0)
        {
            vis[v]=1;
            if ((Match_meal[v]==-1)||(Hungary_meal(Match_meal[v])))
            {
                Match_meal[v]=u;
                return 1;
            }
        }
    }
    return 0;
}