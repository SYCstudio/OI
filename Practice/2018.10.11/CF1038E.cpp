#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define NAME "there"
#define RG register
#define IL inline

const int inf=2147483647;

namespace cpp1
{
	const int maxN=110;
	const int maxM=50;

	class Data
	{
	public:
		int a,b,w;
	};

	int n,Ans=0;
	Data D[maxN];
	int Ws[3][5][5],s[5];
	int edgecnt=-1,Head[maxN],Next[maxM],V[maxM],W[maxM];
	bool vise[maxM],visn[maxN];
	queue<int> Q;

	void Do();
	void Add_Edge(RG int u,RG int v,RG int w);
	void dfs(RG int u,RG int sum);
	bool cmp(Data A,Data B);
}

int main(){
	cpp1::Do();
	return 0;
}

namespace cpp1
{
	void Do(){
		RG  int i,j,k,a,b;
		mem(Head,-1);
		scanf("%d",&n);
		for (i=1;i<=n;++i) scanf("%d%d%d",&D[i].a,&D[i].w,&D[i].b);
		sort(&D[1],&D[n+1],cmp);

		for (i=n;i>=1;--i){
			if (D[i].a>D[i].b) swap(D[i].a,D[i].b);
			a=D[i].a;b=D[i].b;
			if (a==b) s[a]+=D[i].w;
			else if (Ws[2][a][b]==0) Ws[2][a][b]=D[i].w;
			else if (Ws[1][a][b]==0) Ws[1][a][b]=D[i].w;
			else if (Ws[0][a][b]==0) Ws[0][a][b]=D[i].w;
			else{
				Ws[2][a][b]+=Ws[1][a][b]+Ws[0][a][b];
				Ws[1][a][b]=Ws[0][a][b]=0;
				Ws[1][a][b]=D[i].w;
			}
		}

		//for (int i=0;i<=2;i++) for (int j=1;j<=4;j++) for (int k=1;k<=4;k++) cout<<"("<<i<<" "<<j<<" "<<k<<")"<<Ws[i][j][k]<<endl;

		for (i=0;i<=2;++i)
			for (j=1;j<=4;++j)
				for (k=1;k<=4;++k)
					if (Ws[i][j][k]) Add_Edge(j,k,Ws[i][j][k]);
		dfs(1,0);dfs(2,0);dfs(3,0);dfs(4,0);
		printf("%d\n",Ans);return;
	}
	
	void Add_Edge(RG int u,RG int v,RG int w){
		Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
		Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;W[edgecnt]=w;
		return;
	}
	
	void dfs(RG int u,RG int sum){
		bool flag=0;
		if (visn[u]==0){
			sum+=s[u];visn[u]=1;flag=1;
		}
		Ans=max(Ans,sum);
		for (int i=Head[u];i!=-1;i=Next[i])
			if (vise[i]==0){
				vise[i]=vise[i^1]=1;
				dfs(V[i],sum+W[i]);
				vise[i]=vise[i^1]=0;
			}
		if (flag) visn[u]=0;return;
	}
	
	bool cmp(Data A,Data B){
		return A.w<B.w;
	}
}
