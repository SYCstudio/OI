#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

class Edge
{
public:
    int v,dist;
};

class Position
{
public:
    int x,y;
};

const int maxmap=200;
const int maxN=200;
const int inf=2147483647;

int n,m;
int G[maxN][maxN];
int Match_man[maxN];
int Match_house[maxN];
int Wx[maxN];
int Wy[maxN];
vector<Position> House;
vector<Position> Man;
bool use_man[maxN];
bool use_house[maxN];

bool Hungary(int u);

int main()
{
    while (cin>>n>>m)
    {
        if ((n==0)&&(m==0))
            break;
        House.clear();
        Man.clear();
        char str[maxN];
        for (int i=1;i<=n;i++)
        {
            cin>>str;
            for (int j=0;j<m;j++)
                if (str[j]=='H')
                {
                    House.push_back((Position){i,j+1});
                }
                else
                if (str[j]=='m')
                {
                    Man.push_back((Position){i,j+1});
                }
        }
        //cout<<Man.size()<<endl;
        //cout<<"A"<<endl;
        for (int i=0;i<=Man.size();i++)
            for (int j=0;j<=House.size();j++)
                G[i][j]=-1;
        //cout<<"B"<<endl;
        memset(Match_house,-1,sizeof(Match_house));
        memset(Match_man,-1,sizeof(Match_man));
        memset(Wy,0,sizeof(Wy));
        for (int i=0;i<Man.size();i++)
        {
            //cout<<i<<endl;
            Wx[i+1]=inf;
            for (int j=0;j<House.size();j++)
            {
                int d=abs(Man[i].x-House[j].x)+abs(Man[i].y-House[j].y);
                G[i+1][j+1]=d;
                Wx[i+1]=min(Wx[i+1],d);//注意这里要的是最小值
            }
        }
        //cout<<"C"<<endl;
        for (int i=1;i<=Man.size();i++)
        {
            do
            {
                memset(use_man,0,sizeof(use_man));
                memset(use_house,0,sizeof(use_house));
                if (Hungary(i))
                    break;
                int D=inf;
                for (int j=1;j<=Man.size();j++)
                    if (use_man[j]==1)
                        for (int k=1;k<=House.size();k++)
                            if ((G[j][k]!=-1)&&(use_house[k]==0))
                            {
                                D=min(D,G[j][k]-Wx[j]-Wy[k]);;//这里因为Wx,Wy的意义变成了最小值，所以G[j][k]比Wx[j]+Wy[k]要大，所以这里的D就成了当前能放入的权值最小的边（在原KM算法中是最大的）
                            }
                //cout<<"D "<<D<<endl;
                for (int j=1;j<=Man.size();j++)
                    if (use_man[j]==1)
                        Wx[j]=Wx[j]+D;//注意这里Wx变成了-D，而Wy成了+D
                for (int j=1;j<=House.size();j++)
                    if (use_house[j]==1)
                        Wy[j]=Wy[j]-D;
            }
            while (1);
        }
        int Ans=0;
        for (int i=1;i<=House.size();i++)
            Ans+=G[Match_house[i]][i];
        cout<<Ans<<endl;
    }
    return 0;
}

bool Hungary(int u)
{
    use_man[u]=1;
    for (int i=1;i<=House.size();i++)
        if ((G[u][i]!=-1)&&(Wx[u]+Wy[i]==G[u][i])&&(use_house[i]==0))
        {
            use_house[i]=1;
            if ((Match_house[i]==-1)||(Hungary(Match_house[i])))
            {
                Match_house[i]=u;
                Match_man[u]=i;
                return 1;
            }
        }
    return 0;
}