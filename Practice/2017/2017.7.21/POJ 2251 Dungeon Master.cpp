#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int maxN=35;
const int inf=2147483647;
const int F1[10]={0,1,-1,0,0,0,0};
const int F2[10]={0,0,0,1,-1,0,0};
const int F3[10]={0,0,0,0,0,1,-1};

class Position
{
public:
    int x,y,z;
    int step;
};

int a,b,c;
int Map[maxN][maxN][maxN];
queue<Position> Q;
bool vis[maxN][maxN][maxN];

int main()
{
    while (cin>>a>>b>>c)
    {
        if ((a==0)&&(b==0)&&(c==0))
            break;
        memset(Map,-1,sizeof(Map));
        memset(vis,0,sizeof(vis));
        while (!Q.empty())
            Q.pop();
        int x0,y0,z0,x1,y1,z1;
        char str[maxN];
        for (int i=1;i<=a;i++)
            for (int j=1;j<=b;j++)
            {
                cin>>str;
                for (int k=0;k<c;k++)
                {
                    if (str[k]!='#')
                        Map[i][j][k+1]=1;
                    if (str[k]=='S')
                    {
                        x0=i;
                        y0=j;
                        z0=k+1;
                    }
                    else
                    if (str[k]=='E')
                    {
                        x1=i;
                        y1=j;
                        z1=k+1;
                    }
                }
            }
        /*for (int i=1;i<=a;i++)
        {
            for (int j=1;j<=b;j++)
            {
                for (int k=1;k<=c;k++)
                    cout<<Map[i][j][k]<<' ';
                cout<<endl;
            }
            cout<<endl;
        }*/
        Q.push((Position){x0,y0,z0,0});
        vis[x0][y0][z0]=1;
        bool is_get=0;
        do
        {
            Position u=Q.front();
            Q.pop();
            //cout<<u.x<<' '<<u.y<<' '<<u.z<<' '<<u.step<<endl;
            if ((u.x==x1)&&(u.y==y1)&&(u.z==z1))
            {
                is_get=1;
                //out<<u.step<<endl;
                printf("Escaped in %d minute(s).\n",u.step);
                break;
            }
            for (int i=1;i<=6;i++)
                {
                    int x2=u.x+F1[i];
                    int y2=u.y+F2[i];
                    int z2=u.z+F3[i];
                    if ((Map[x2][y2][z2]!=-1)&&(vis[x2][y2][z2]==0))
                    {
                        //cout<<"("<<u.x<<","<<u.y<<','<<u.z<<")->("<<x2<<","<<y2<<","<<z2<<")"<<endl;
                        Q.push((Position){x2,y2,z2,u.step+1});
                        vis[x2][y2][z2]=1;
                    }
                }
        }
        while (!Q.empty());
        if (is_get==0)
            cout<<"Trapped!"<<endl;
    }
    return 0;
}
