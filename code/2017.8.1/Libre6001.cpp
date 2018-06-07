#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=1000;
const int maxM=maxN*maxN*4;
const int inf=147483647;

class Edge
{
public:
    int v,flow;
};

int n,m;
int cnt=-1;
int Head[maxN];
int Next[maxM];
Edge E[maxM];
int depth[maxN];
int cur[maxN];
int Q[maxM];
bool chose[maxN];
char str[maxM];

void Add_Edge(int u,int v,int flow);
bool bfs();
int dfs(int u,int flow);

int main()
{
    int sum=0;
    memset(Head,-1,sizeof(Head));
    scanf("%d%d",&m,&n);
    char ch=getchar();
    while (ch!='\n')
        ch=getchar();
    //int mcnt=1;
	for(int i=1;i<=m;++i)
	{
		int v;
		scanf("%d",&v);
        Add_Edge(0,i,v);
        sum+=v;
        memset(str,0,sizeof(str));
        cin.getline(str,maxM);
        int j=0;
        while(sscanf(str+j,"%d",&v)==1)
        {
			if(!v)
				j++;
			else
				Add_Edge(i,v+m,inf);
			while(v)
				v/=10,j++;
			j++;
		   }
       }
	/*
    for (int i=1;i<=m;i++)
    {
        int v;
        scanf("%d",&v);
        sum+=v;
        Add_Edge(0,i,v);
        ch=getchar();
        do
        {
            while (((ch>'9')||(ch<'0'))&&(ch!='\n'))
                ch=getchar();
            if (ch=='\n')
                break;
            v=0;
            while ((ch>='0')&&(ch<='9'))
            {
                v=v*10+ch-48;
                ch=getchar();
            }
            ///mcnt++;
            Add_Edge(i,v+m,inf);
        }
        while (1);
		}*/
    for (int i=1;i<=n;i++)
    {
        int v;
        scanf("%d",&v);
        Add_Edge(i+m,n+m+1,v);
    }
    /*for (int i=0;i<=n+m+1;i++)
    {
        for (int j=Head[i];j!=-1;j=Next[j])
            cout<<i<<"->"<<E[j].v<<' '<<E[j].flow<<endl;
        cout<<endl;
        }*/
    //cout<<"mcnt:"<<mcnt<<endl;
    int Flow=0;
    while (bfs())
    {
        for (int i=0;i<=n+m+1;i++)
            cur[i]=Head[i];
        while (int di=dfs(0,inf))
            Flow+=di;
    }
    memset(chose,0,sizeof(chose));
    for (int i=1;i<=m;i++)
        if (depth[i]!=-1)
        {
            printf("%d ",i);
            for (int j=Head[i];j!=-1;j=Next[j])
                chose[E[j].v-m]=1;
        }
    cout<<endl;
    for (int i=1;i<=n;i++)
        if (chose[i]==1)
            printf("%d ",i);
    cout<<endl;
    cout<<sum-Flow<<endl;
    return 0;
}

void Add_Edge(int u,int v,int flow)
{
    cnt++;
    Next[cnt]=Head[u];
    Head[u]=cnt;
    E[cnt].v=v;
    E[cnt].flow=flow;

    cnt++;
    Next[cnt]=Head[v];
    Head[v]=cnt;
    E[cnt].v=u;
    E[cnt].flow=0;
    return;
}

bool bfs()
{
    memset(depth,-1,sizeof(depth));
    int h=1,t=0;
    Q[1]=0;
    depth[0]=1;
    do
    {
        t++;
        int u=Q[t];
        for (int i=Head[u];i!=-1;i=Next[i])
        {
            int v=E[i].v;
            if ((E[i].flow>0)&&(depth[v]==-1))
            {
                depth[v]=depth[u]+1;
                h++;
                Q[h]=v;
            }
        }
    }
    while (h!=t);
    if (depth[n+m+1]==-1)
        return 0;
    return 1;
}

int dfs(int u,int flow)
{
    if (u==n+m+1)
        return flow;
    for (int &i=cur[u];i!=-1;i=Next[i])
    {
        int v=E[i].v;
        if ((E[i].flow>0)&&(depth[v]==depth[u]+1))
        {
            int di=dfs(v,min(flow,E[i].flow));
            if (di>0)
            {
                E[i].flow-=di;
                E[i^1].flow+=di;
                return di;
            }
        }
    }
    return 0;
}
