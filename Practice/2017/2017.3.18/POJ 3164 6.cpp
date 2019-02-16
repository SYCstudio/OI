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
int Pre[maxN];//ǰ��
int Id[maxN];//�����ÿ����ı��
double In[maxN];//��ǰÿ����ѡ������С��
int vis[maxN];//��ǰ�����ĸ����У���������һ������
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

double Directed_MST(int root,int NV,int NE)//���ڵ�Ϊroot��NVΪ������NEΪ����
{
    double ret=0;//�ۼӱ�Ȩ
    int cntnode;//�����Ľڵ���
    while (1)
    {
        //A.ѡ��ÿ�������С���
        for (int i=1;i<=NV;i++)//Ϊ�˷�ֹ����ѭ����������ȫ���ڲ�����
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
        for (int i=1;i<=NV;i++)//������ʱĳ�����Ѿ��������򲻴�����С����ͼ
        {
            if (i==root)
                continue;
            if (In[i]==inf)
                return -1;
        }
        //cout<<"BJ"<<endl;
        //B.��ǻ�
        memset(Id,-1,sizeof(Id));
        memset(vis,-1,sizeof(vis));
        In[root]=0;//��Ϊ��ǰ����ʱ�Թ��˸��ڵ㣬����Ҫʹ���ڵ����Ϊ0
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
        if(cntnode==1)//��ǰͼ�����޻�����ʾ�㷨����
            break;
        //C.���㣬���·����ţ��Ա��������
        for (int i=1;i<=NV;i++)//�����ǻ��еĵ������
            if (Id[i]==-1)
            {
                Id[i]=cntnode++;
            }
        for (int i=1;i<=NE;i++)
        {
            int v=E[i].v;//����һ����ʱ��������ԭ����vֵ��ȷ�������Ȩֵ�Ƿ�Ҫ��
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
