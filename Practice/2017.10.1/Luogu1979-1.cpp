#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=32;
const int F1[5]={0,0,0,1,-1};
const int F2[5]={0,1,-1,0,0};
const int inf=2147483647;

int n,m;

class Queue_Data
{
public:
    int epx,epy,x,y;
    int step;
    int calc()
        {
            return ((epx*(maxN-1))+epy)*maxN*maxN+(x*(maxN-1))+y;
        }
};

int Map[maxN][maxN];
int Epx,Epy;
int Stx,Sty;
int Glx,Gly;
bool Hash[maxN*maxN*maxN*maxN];
Queue_Data Q[maxN*maxN*maxN*maxN];

int main()
{
    memset(Map,0,sizeof(Map));
    int qu;
    scanf("%d%d%d",&n,&m,&qu);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            scanf("%d",&Map[i][j]);
    while (qu--)
    {
        memset(Hash,0,sizeof(Hash));
        scanf("%d%d%d%d%d%d",&Epx,&Epy,&Stx,&Sty,&Glx,&Gly);
        Queue_Data init=(Queue_Data){Epx,Epy,Stx,Sty,0};
        int h=1,t=0;
        Q[1]=init;
        Hash[init.calc()]=1;
        bool get_ans=0;
        do
        {
            t++;
            if ((Q[t].x==Glx)&&(Q[t].y==Gly))
            {
                printf("%d\n",Q[t].step);
                get_ans=1;
                break;
            }
            Queue_Data v;
            for (int i=1;i<=4;i++)
            {
                v=Q[t];
                v.epx=Q[t].epx+F1[i];
                v.epy=Q[t].epy+F2[i];
                if (Map[v.epx][v.epy]==0)
                    continue;
                if ((v.epx==Q[t].x)&&(v.epy==Q[t].y))
                {
                    v.x=Q[t].epx;
                    v.y=Q[t].epy;
                }
                else
                {
                    v.x=Q[t].x;
                    v.y=Q[t].y;
                }
                int k=v.calc();
                if (Hash[k]==0)
                {
                    Hash[k]=1;
                    h++;
                    v.step=Q[t].step+1;
                    Q[h]=v;
                }
            }
        }
        while (t<h);
        if (get_ans==0)
            printf("-1\n");
    }
    return 0;
}
