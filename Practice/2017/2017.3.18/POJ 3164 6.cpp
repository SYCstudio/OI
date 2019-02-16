#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
using namespace std;

class Edge
{
public:
    int u,v;
    double w;
};

class point
{
public:
    int x,y;
};

const int maxM=20000;
const int maxN=15000;
const int inf=2000000000;

int N,M;
int Pre[maxN];//前驱
int Id[maxN];//缩点后每个点的编号
double In[maxN];//当前每个点选定的最小边
int vis[maxN];//当前点在哪个环中，或不在任意一个环中
Edge E[maxM];
point Point[maxN];

inline double Dist(int a,int b);
inline void init();
double Directed_MST(int root,int NV,int NE);

int main()
{
    int i,j,k;
    int T;
    int a,b;
    double Ans;

    while (scanf("%d%d",&N,&M)!=EOF)
    {
        init();
        Ans=Directed_MST(1,N,M);
        //cout<<"The ans is"<<Ans<<endl;
        if (Ans==-1)
            cout<<"poor snoopy"<<endl;
        else
            printf("%.2f\n",Ans);
    }
    return 0;
}

inline double Dist(int a,int b)
{
    return sqrt(double( (Point[a].x-Point[b].x)*(Point[a].x-Point[b].x) + (Point[a].y-Point[b].y)*(Point[a].y-Point[b].y) ) );
}

inline void init()
{
    int i,j,k;
    int a,b;
    for (i=1;i<=N;i++)
        scanf("%d%d",&Point[i].x,&Point[i].y);
        //cin>>Point[i].x>>Point[i].y;
    for (i=1;i<=M;i++)
    {
        //cin>>E[i].u>>E[i].v;
        scanf("%d%d",&E[i].u,&E[i].v);
        if (E[i].u!=E[i].v)
        {
            E[i].w=Dist(E[i].u,E[i].v);
        }
        else
        {
            E[i].w=inf;
        }
        //cout<<E[i].w<<endl;
    }
    return;
}

double Directed_MST(int root,int NV,int NE)//根节点为root，NV为点数，NE为边数
{
    double ret=0;//累加边权
    int cntnode;//缩点后的节点编号
    while (1)
    {
        //A.选出每个点的最小入边
        for (int i=1;i<=NV;i++)//为了防止后面循环变量出错，全部内部定义
            In[i]=inf;
        for (int i=1;i<=NE;i++)
        {
            int u=E[i].u;
            int v=E[i].v;
            if ((u!=v)&&(E[i].w<In[v]))
            {
                Pre[v]=u;
                In[v]=E[i].w;
            }
        }
        /*for (int i=1;i<=NV;i++)
        {
            cout<<i<<" "<<In[i]<<" "<<Pre[i]<<endl;
        }*/
        for (int i=1;i<=NV;i++)//若缩点时某个点已经孤立，则不存在最小树形图
        {
            if (i==root)
                continue;
            if (In[i]==inf)
                return -1;
        }
        //cout<<"BJ"<<endl;
        //B.标记环
        memset(Id,-1,sizeof(Id));
        memset(vis,-1,sizeof(vis));
        In[root]=0;//因为先前处理时略过了根节点，所以要使根节点入度为0
        cntnode=1;
        for (int i=1;i<=NV;i++)
        {
            ret+=In[i];
            //cout<<i<<"-"<<In[i]<<endl;
            int v=i;
            while ((vis[v]!=i)&&(Id[v]==-1)&&(v!=root))
            {
                vis[v]=i;
                v=Pre[v];
            }
            if ((v!=root)&&(Id[v]==-1))
            {
                for (int x=Pre[v];x!=v;x=Pre[x])
                {
                    Id[x]=cntnode;
                }
                Id[v]=cntnode++;
            }
        }
        //cout<<"cnt"<<cntnode<<endl;
        if(cntnode==1)//当前图中已无环，表示算法结束
            break;
        //C.缩点，重新分配编号，以便后续处理
        for (int i=1;i<=NV;i++)//给不是环中的点分配编号
            if (Id[i]==-1)
            {
                Id[i]=cntnode++;
            }
        for (int i=1;i<=NE;i++)
        {
            int v=E[i].v;//先用一个临时变量存下原来的v值，确定缩点后权值是否要变
            E[i].u=Id[E[i].u];
            E[i].v=Id[E[i].v];
            if(E[i].u!=E[i].v)
                E[i].w=E[i].w-In[v];
        }
        NV=cntnode;
        root=Id[root];
        //cout<<"cnt"<<cntnode<<endl;
    }
    return ret;
}
