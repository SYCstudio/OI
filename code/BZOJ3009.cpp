#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int inf=2147483647;

int n,m;

namespace cpp1
{
	const int maxN=110;
	const int maxM=10100;

	class HData
	{
	public:
		int u,v,key;
	};
	
	int Mp[maxN][maxN];
	int Color[maxN];
	priority_queue<HData> H[6];

	int GetId(int a,int b);
	void Do();
	bool operator < (HData A,HData B);
}

namespace cpp2
{
	const int maxN=101000;
	const int maxM=501000<<1;
	
	class SegmentData
	{
	public:
		int mov,val[9];
	};

	int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
	bool vis[maxN],del[maxM];
	SegmentData S[3][maxN];
	int dfn[3][maxN],lft[3][maxN],rht[3][maxN];

	void Bfs(int id);
	void Build(int now,int l,int r);
	void Modify(int now,int l,int r,int ql,int qr,int mov);
}

int main(){
	scanf("%d%d",&n,&m);
	if ((n<=100)&&(m<=10000)) cpp1::Do();

	return 0;
}

namespace cpp1
{
	int GetId(int a,int b){
		if (a>b) swap(a,b);
		if (a==0) return b;
		if (a==1) return b-a+3;
		return b-a+5;
	}
	
	void Do(){
		for (int i=1;i<=m;i++){
			int u,v,w;scanf("%d%d%d",&u,&v,&w);
			if ((Mp[u][v]==0)||(Mp[u][v]>w)) Mp[u][v]=Mp[v][u]=w;
		}
		for (int i=1;i<=n;i++)
			for (int j=i+1;j<=n;j++)
				if (Mp[i][j]) H[0].push((HData){i,j,Mp[i][j]});
		int Q;scanf("%d",&Q);char ipt[10];
		while (Q--){
			scanf("%s",ipt);
			if (ipt[0]=='M'){
				int u;scanf("%d",&u);Color[u]=ipt[4]-'A';
				for (int i=1;i<=n;i++) if (Mp[u][i]) H[GetId(Color[u],Color[i])].push((HData){u,i,Mp[u][i]});
			}
			if (ipt[0]=='A'){
				int a=ipt[3]-'A',b=ipt[4]-'A',id=GetId(a,b);
				if (a>b) swap(a,b);
				bool flag=0;
				while (!H[id].empty()){
					int u=H[id].top().u,v=H[id].top().v;
					if ( ((a==Color[u])&&(b==Color[v])) || ((a==Color[v])&&(b==Color[u])) ){
						printf("%d\n",H[id].top().key);flag=1;break;
					}
					H[id].pop();
				}
				if (flag==0) printf("No Found!\n");
			}
		}
		return;
	}

	bool operator < (HData A,HData B){
		return A.key>B.key;
	}
}
