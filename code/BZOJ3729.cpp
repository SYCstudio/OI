#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=500000;
const int inf=2147483647;

class SplayData
{
public:
	int fa,ch[2],sum0,sum1,vsum0,vsum1,key;
};

int n,L,m,Fa[maxN];
SplayData S[maxN];
vector<int> T[maxN];
map<int,int> Id;

void dfs(int u,int fa);
bool Isroot(int x);
void Update(int x);
void Rotate(int x);
void Splay(int x);
void Access(int x);

int main(){
	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&L);
	for (int i=1;i<=n;i++) scanf("%d",&S[i].key),S[i].key%=(L+1),Id[i]=i;
	for (int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		T[u].push_back(v);T[v].push_back(u);
	}

	dfs(1,1);

	/*
	for (int i=1;i<=n;i++) cout<<S[i].sum0<<" "<<S[i].sum1<<endl;
	for (int i=1;i<=n;i++){
		Access(i);
		cout<<"Access:"<<i<<endl;
		for (int j=1;j<=n;j++) cout<<(S[j].sum0^S[S[j].ch[0]].sum1)<<" "<<(S[j].sum1^S[S[j].ch[0]].sum0)<<endl;
	}
	//*/


	scanf("%d",&m);int lastans=0;
	while (m--){
		int opt;scanf("%d",&opt);
		if (opt==1){
			int u;scanf("%d",&u);cout<<u<<endl;u^=lastans;u=Id[u];
			Access(u);Splay(u);
			//cout<<u<<" "<<S[u].sum0<<" "<<S[u].sum1<<endl;
			if ((S[u].sum0)==0) printf("GTY\n");
			else printf("MeiZ\n"),lastans++;
		}
		if (opt==2){
			int x,y;scanf("%d%d",&x,&y);x^=lastans;y^=lastans;
			x=Id[x];y%=(L+1);
			Access(x);Splay(x);
			S[x].key=y;Update(x);
		}
		if (opt==3){
			int u,v,x;scanf("%d%d%d",&u,&v,&x);
			u^=lastans;v^=lastans;x^=lastans;
			u=Id[u];Id[v]=++n;v=Id[v];x%=(L+1);
			S[u].vsum0^=x;Update(u);S[v].fa=u;S[v].key=S[v].sum1=x;Update(v);
			Access(v);Fa[v]=u;
		}

		//lastans=0;///////////////////////////////////////
	}

	return 0;
}

void dfs(int u,int fa){
	Fa[u]=fa;
	for (int i=0,sz=T[u].size();i<sz;i++)
		if (T[u][i]!=fa){
			S[T[u][i]].fa=u;
			dfs(T[u][i],u);
			S[u].vsum0^=S[T[u][i]].sum0;
			S[u].vsum1^=S[T[u][i]].sum1;
		}
	Update(u);
	return;
}

bool Isroot(int x){
	int fa=S[x].fa;
	if ((S[fa].ch[0]==x)||(S[fa].ch[1]==x)) return 0;
	return 1;
}

void Update(int x){
	S[x].sum0=S[S[x].ch[0]].sum1^S[S[x].ch[1]].sum1^S[x].vsum1;
	S[x].sum1=S[S[x].ch[0]].sum0^S[S[x].ch[1]].sum0^S[x].key^S[x].vsum0;
	return;
}

void Rotate(int x){
	int y=S[x].fa,z=S[y].fa;
	int sx=(x==S[y].ch[1]),sy=(y==S[z].ch[1]);
	S[x].fa=z;if (Isroot(y)==0) S[z].ch[sy]=x;
	S[y].ch[sx]=S[x].ch[sx^1];if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
	S[x].ch[sx^1]=y;S[y].fa=x;
	Update(y);return;
}

void Splay(int x){
	while (Isroot(x)==0){
		int y=S[x].fa,z=S[y].fa;
		if (Isroot(y)==0)
			((x==S[y].ch[0])^(y==S[z].ch[0]))?(Rotate(x)):(Rotate(y));
		Rotate(x);
	}
	Update(x);return;
}
void Access(int x){
	int lastx=0;
	while (x){
		Splay(x);
		S[x].vsum0^=S[S[x].ch[1]].sum0;//S[x].sum0^=S[S[x].ch[1]].sum1;
		S[x].vsum1^=S[S[x].ch[1]].sum1;//S[x].sum1^=S[S[x].ch[1]].sum0;
		
		S[x].ch[1]=lastx;

		S[x].vsum0^=S[S[x].ch[1]].sum0;//S[x].sum0^=S[S[x].ch[1]].sum1;
		S[x].vsum1^=S[S[x].ch[1]].sum1;//S[x].sum1^=S[S[x].ch[1]].sum0;
		
		Update(x);lastx=x;x=S[x].fa;
	}
	return;
}

/*
2 1000
0 0
1 2
1
1 1

5 1000
1 3 2 5 3
1 2
2 3
2 4
4 5
5
1 1
1 2
1 3
1 4
1 5
//*/
