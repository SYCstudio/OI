#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<map>//涉及字符串处理
#include<queue>//Dij堆优化
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define ll long long
#define ld long double

const int maxN=10010;
const int maxM=20010*2;
const int maxK=12;//最多经过的红绿灯的数量
const int maxGas=53;//加油站的数量
const int inf=2147483647;

class Mystring
{
public:
    char ch[25];
};

bool operator < (Mystring A,Mystring B)//map需要支持大小比较
{
    return strcmp(A.ch,B.ch)>0;//这里是大于而不是大于等于
}

class Node_Data
{
public:
    int id;
    double cost;
};

class Graph
{
public:
    int cnt,Head[maxN],Next[maxM],V[maxM],RedLight[maxM];
    ld W[maxM];
    Graph()
	{
	    cnt=0;
	    mem(Head,-1);
	    return;
	}
    void Add_Edge(int u,int v,ld w,int rd)
	{
	    cnt++;Next[cnt]=Head[u];Head[u]=cnt;V[cnt]=v;W[cnt]=w;RedLight[cnt]=rd;
	    return;
	}
};

class Queue_Data
{
public:
    int u,cnt;ld dist;
};

bool operator < (Queue_Data A,Queue_Data B)
{
    return A.dist>B.dist;
}

int n,m,K,Limit,Cost;
int S,T;//出发点，目的地
int gascnt=0,GasId[maxGas];//加油站的数量和位置
map<Mystring,int> NodeId;//点的名字对应的编号
Graph G1,G2;
Node_Data Node[maxN];
ld Dist[maxK][maxN];
bool vis[maxK][maxN];
priority_queue<Queue_Data> Queue;

void Dij(int start);

int main()
{
    scanf("%d%d%d%d%d",&n,&m,&K,&Limit,&Cost);
    Mystring name;
    for (int i=1;i<=n;i++)//处理点
    {
	int a,b;
	scanf("%s%d%d",name.ch,&a,&b);
	NodeId[name]=i;//cout<<name.ch<<endl;
	if ((name.ch[0]=='s')&&(name.ch[1]=='t')&&(name.ch[2]=='a')&&(name.ch[3]=='r')&&(name.ch[4]=='t')) S=i;
	if ((name.ch[0]=='e')&&(name.ch[1]=='n')&&(name.ch[2]=='d')) T=i;
	int l=strlen(name.ch);
	if (a==0) Node[i].cost=0;//注意这里先把加油站的用时也看作0
	else Node[i].cost=1.0*(ld)a/((ld)(a+b))*(ld)a/2.0;//平均用时
	for (int j=0;j<l-2;j++) if ((name.ch[j]=='g')&&(name.ch[j+1]=='a')&&(name.ch[j+2]=='s'))//标记加油站
				{
				    //cout<<i<<" is a gas!"<<endl;
				    gascnt++;GasId[gascnt]=i;
				    break;
				}
    }
    for (int i=1;i<=m;i++)//处理边
    {
	int u,v,w;
	scanf("%s",name.ch);u=NodeId[name];//cout<<name.ch<<endl;
	scanf("%s",name.ch);v=NodeId[name];//cout<<name.ch<<endl;
	scanf("%s",name.ch);scanf("%d",&w);//cout<<name.ch<<endl;
	//cout<<u<<" "<<v<<" "<<w<<endl;
	G1.Add_Edge(u,v,w,0);G1.Add_Edge(v,u,w,0);
    }
    /*
    for (int i=1;i<=n;i++)
    {
	for (int j=G1.Head[i];j!=-1;j=G1.Next[j])
	    printf("%d->%d %.3LF\n",i,G1.V[j],G1.W[j]);
	cout<<endl;
    }
    //*/
    //for (int i=1;i<=n;i++) cout<<Node[i].cost<<" ";
    //cout<<endl;

    //第一遍最短路，从源汇点和每一个加油站出发，找出能到达哪些加油站
    GasId[++gascnt]=S;GasId[++gascnt]=T;//把源汇点加入
    //cout<<"S:"<<S<<" T:"<<T<<endl;
    for (int i=1;i<=gascnt;i++)
    {
	Dij(GasId[i]);
	for (int j=1;j<=gascnt;j++)//建立新图
	    for (int k=0;k<=K;k++) if ((j!=i)&&(Dist[k][GasId[j]]!=-1)&&(Dist[k][GasId[j]]<=Limit)) G2.Add_Edge(GasId[i],GasId[j],Dist[k][GasId[j]],k);
    }
    /*
    for (int i=1;i<=n;i++)
    {
	for (int j=G2.Head[i];j!=-1;j=G2.Next[j])
	    printf("%d->%d %.3LF %d\n",i,G2.V[j],G2.W[j],G2.RedLight[j]);
    }
    //*/
    //最后在新的图上跑最短路径
    mem(vis,0);for (int i=0;i<=K;i++) for (int j=1;j<=n;j++) Dist[i][j]=-1;
    Dist[0][S]=0;
    Queue.push((Queue_Data){S,0,0});
    do
    {
	Queue_Data u=Queue.top();Queue.pop();
	if (vis[u.cnt][u.u]) continue;
	vis[u.cnt][u.u]=1;
	for (int i=G2.Head[u.u];i!=-1;i=G2.Next[i])
	{
	    int v=G2.V[i];
	    if (u.cnt+G2.RedLight[i]>K) continue;
	    int thisCost=0;
	    if ((u.u!=T)&&(u.u!=S)) thisCost=Cost;
	    if ((vis[u.cnt+G2.RedLight[i]][v]==0)&&((Dist[u.cnt+G2.RedLight[i]][v]==-1)||(Dist[u.cnt+G2.RedLight[i]][v]>Dist[u.cnt][u.u]+G2.W[i]+thisCost)))
	    {
		Dist[u.cnt+G2.RedLight[i]][v]=Dist[u.cnt][u.u]+G2.W[i]+thisCost;
		Queue.push((Queue_Data){v,u.cnt+G2.RedLight[i],Dist[u.cnt+G2.RedLight[i]][v]});
	    }
	}
    }
    while (!Queue.empty());
    ld Ans=inf;
    //cout<<S<<" "<<T<<endl;
    for (int i=0;i<=K;i++) if (Dist[i][T]!=-1) Ans=min(Ans,Dist[i][T]);
    printf("%.3Lf\n",Ans);
    return 0;
}

void Dij(int start)
{
    mem(vis,0);for (int i=0;i<=K;i++) for (int j=1;j<=n;j++) Dist[i][j]=-1;
    Dist[0][start]=0;
    while (!Queue.empty()) Queue.pop();
    Queue.push((Queue_Data){start,0,0});
    //cout<<"Dijkstra:"<<start<<endl;
    do
    {
	Queue_Data u=Queue.top();Queue.pop();
	if (vis[u.cnt][u.u]) continue;
	vis[u.cnt][u.u]=1;
	if (Dist[u.cnt][u.u]>Limit) continue;
	int islight=(bool)(Node[u.u].cost!=0);//标记是否是红绿灯
	if ((u.cnt==K)&&(islight)) continue;
	for (int i=G1.Head[u.u];i!=-1;i=G1.Next[i])
	{
	    int v=G1.V[i];
	    if ((vis[u.cnt+islight][v]==0)&&((Dist[u.cnt+islight][v]==-1)||(Dist[u.cnt+islight][v]>Dist[u.cnt][u.u]+G1.W[i]+Node[u.u].cost)))
	    {
		//cout<<"Update! "<<u.u<<","<<u.cnt<<"["<<Dist[u.cnt][u.u]<<"] -> "<<v<<" ["<<Dist[u.cnt][u.u]+G1.W[i]+Node[u.u].cost<<"]"<<endl;
		Dist[u.cnt+islight][v]=Dist[u.cnt][u.u]+G1.W[i]+Node[u.u].cost;
		Queue.push((Queue_Data){v,u.cnt+islight,Dist[u.cnt+islight][v]});
	    }
	}
    }
    while (!Queue.empty());
    /*
    cout<<"Start:"<<start<<endl;
    for (int i=0;i<=K;i++) printf("%6d",i);cout<<endl;
    for (int i=1;i<=n;i++)
    {
	for (int j=0;j<=K;j++) printf("%6.2LF",Dist[j][i]);
	cout<<endl;
    }
    //*/
    return;
}
