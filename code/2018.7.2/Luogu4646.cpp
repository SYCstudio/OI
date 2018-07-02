#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000*4;
const int maxM=maxN<<1;
const int F1[]={1,0,-1,0};
const int F2[]={0,-1,0,1};
const int inf=2147483647;

class Pos
{
public:
	int x,y;
	int To[4],Id[4];
	int Idl[4],Idr[4];
};

int n,m;
int nodecnt=-1,Bg[maxN];
Pos P[maxN];
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM],Depth[maxN];
queue<int> Q;

void Add_Wall(int u,int v,int id);
void GetGraph(int id);
void Add_Edge(int u,int v);

int main()
{
	mem(Head,-1);
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d%d",&P[i].x,&P[i].y);
	scanf("%d",&m);
	for (int i=1;i<=m;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		Add_Wall(u,v,i);
	}

	/*
	for (int i=1;i<=n;i++)
		for (int j=0;j<4;j++)
			if (P[i].To[j]) cout<<i<<" -> "<<P[i].To[j]<<" ["<<j<<"]"<<endl;
	//*/
	
	for (int i=1;i<=n;i++) GetGraph(i);
	for (int i=1;i<=n;i++)
		for (int j=0;j<4;j++)
			if (P[i].To[j])
			{
				Add_Edge(P[i].Idl[j],P[i].Idr[j]);
				Add_Edge(P[i].Idr[j],P[i].Idl[j]);
			}

	/*
	for (int i=1;i<=n;i++)
		for (int j=0;j<4;j++)
			if (P[i].To[j])
				cout<<i<<":["<<j<<"] "<<P[i].Idl[j]<<" "<<P[i].Idr[j]<<endl;
	//*/

	mem(Depth,-1);
	for (int i=1;i<=nodecnt;i++) if (Bg[i]) Q.push(i),Depth[i]=1;
	
	while (!Q.empty())
	{
		int u=Q.front();Q.pop();//cout<<u<<" ";cout<<endl;
		for (int i=Head[u];i!=-1;i=Next[i])
			if (Depth[V[i]]==-1){
				Depth[V[i]]=Depth[u]^1;Q.push(V[i]);
			}
	}

	//for (int i=1;i<=nodecnt;i++) cout<<Depth[i]<<" ";cout<<endl;
	
	int Ans=0;
	for (int i=0;i<=edgecnt;i+=2) if (Depth[V[i]]==Depth[V[i^1]]) Ans++;

	printf("%d\n",Ans>>1);
	for (int i=1;i<=n;i++)
		for (int j=0;j<4;j++)
			if (P[i].To[j]>i)
				if (Depth[P[i].Idl[j]]==Depth[P[i].Idr[j]]) printf("%d\n",P[i].Id[j]);
	return 0;
}

void Add_Wall(int u,int v,int id)
{
	if (P[u].x==P[v].x){
		if (P[u].y<=P[v].y) P[u].To[3]=v,P[v].To[1]=u,P[u].Id[3]=P[v].Id[1]=id;
		else P[u].To[1]=v,P[v].To[3]=u,P[u].Id[1]=P[v].Id[3]=id;
	}
	else{
		if (P[u].x<=P[v].x) P[u].To[0]=v,P[v].To[2]=u,P[u].Id[0]=P[v].Id[2]=id;
		else P[u].To[2]=v,P[v].To[0]=u,P[u].Id[2]=P[v].Id[0]=id;
	}
	return;
}

void GetGraph(int id)
{
	//cout<<"GetGraph:"<<id<<endl;
	for (int f=0;f<4;f++)
		if ((P[id].To[f])&&(P[id].Idl[f]==0))
		{
			int nowf=f,cnt=0,u=id,v;
			bool flag=1;nodecnt++;
			while ((u!=id)||(flag==1))
			{
				v=P[u].To[nowf];flag=0;
				P[u].Idl[nowf]=P[v].Idr[(nowf+2)%4]=nodecnt;
				cnt--;nowf=(nowf-1+4)%4;u=v;
				while (P[u].To[nowf]==0){
					nowf=(nowf+1)%4;cnt++;
				}
			}
			if (cnt>0) Bg[nodecnt]=1;
		}
	return;
}

void Add_Edge(int u,int v){
	//cout<<"Add:"<<u<<" "<<v<<endl;
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}
