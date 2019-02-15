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

const int maxN=501000;
const int inf=2147483647;

class SplayData
{
public:
	int fa,ch[2],opt,key;
	int sum0,sum1;
};

int n,m,L,root,Stone[maxN];
vector<int> To[maxN];
SplayData S[maxN];
int dfncnt,dfn[maxN],lst[maxN],Qn[maxN];
map<int,int> Id;

void dfs(int u,int fa,int opt);
void Update(int x);
void Rotate(int x);
void Splay(int x,int goal);
int Prev(int x);
void Outp(int u);

int main(){
	//freopen("1.in","r",stdin);freopen("out.out","w",stdout);
	scanf("%d%d",&n,&L);
	for (int i=1;i<=n;i++) scanf("%d",&Stone[i]),Id[i]=i,Stone[i]%=(L+1);
	for (int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		To[u].push_back(v);To[v].push_back(u);
	}

	dfs(1,1,1);

	root=1;
	for (int i=2;i<=dfncnt;i++) S[i].fa=i-1;
	for (int i=1;i<dfncnt;i++) S[i].ch[1]=i+1;

	//Outp(1);
	
	Splay(dfncnt,0);

	//cout<<"root:"<<root<<endl;
	//Outp(root);

	int lastans=0;
	scanf("%d",&m);
	while (m--){
		int opt;scanf("%d",&opt);
		if (opt==1){
			int u;scanf("%d",&u);u^=lastans;u=Id[u];
			Splay(dfn[u],0);Splay(lst[u],dfn[u]);
			int key=(S[dfn[u]].opt==1)?(S[S[lst[u]].ch[0]].sum0):(S[S[lst[u]].ch[0]].sum1);
			//cout<<u<<" "<<key<<endl;
			if (key==0) printf("GTY\n");
			else printf("MeiZ\n"),lastans++;
		}
		if (opt==2){
			int u,key;scanf("%d%d",&u,&key);u^=lastans;key^=lastans;u=Id[u];key%=(L+1);
			Splay(dfn[u],0);S[dfn[u]].key=key;Update(dfn[u]);
		}
		if (opt==3){
			int u,v,key;scanf("%d%d%d",&u,&v,&key);u^=lastans;v^=lastans;key^=lastans;u=Id[u];key%=(L+1);
			Id[v]=++n;v=n;
			dfn[v]=++dfncnt;lst[v]=++dfncnt;
			int prev=Prev(lst[u]);
			//cout<<"prev:"<<u<<" "<<lst[u]<<" "<<prev<<endl;
			Splay(prev,0);Splay(lst[u],prev);
			//cout<<"root:"<<root<<endl;
			//Outp(root);

			S[dfn[v]].opt=S[dfn[u]].opt^1;S[dfn[v]].key=key;
			S[dfn[v]].fa=lst[u];S[lst[u]].ch[0]=dfn[v];
			S[dfn[v]].ch[1]=lst[v];S[lst[v]].fa=dfn[v];
			Splay(lst[v],0);
		}
		//cout<<flush;
		//lastans=0;/////////////////////////////////////////////////
		//cout<<"root:"<<root<<endl;
		//Outp(root);
	}

	return 0;
}

void dfs(int u,int fa,int opt){
	Qn[dfn[u]=++dfncnt]=u;S[dfncnt].opt=opt;S[dfncnt].key=Stone[u];
	for (int i=0,sz=To[u].size();i<sz;i++)
		if (To[u][i]!=fa) dfs(To[u][i],u,opt^1);
	Qn[lst[u]=++dfncnt]=-u;return;
}

void Update(int x){
	S[x].sum0=S[S[x].ch[0]].sum0^S[S[x].ch[1]].sum0;
	S[x].sum1=S[S[x].ch[0]].sum1^S[S[x].ch[1]].sum1;
	if (S[x].opt==0) S[x].sum0^=S[x].key;
	else S[x].sum1^=S[x].key;
	return;
}

void Rotate(int x){
	int y=S[x].fa,z=S[y].fa;
	int sx=(x==S[y].ch[1]),sy=(y==S[z].ch[1]);
	S[x].fa=z;if (z) S[z].ch[sy]=x;
	S[y].ch[sx]=S[x].ch[sx^1];if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
	S[x].ch[sx^1]=y;S[y].fa=x;
	Update(y);return;
}

void Splay(int x,int goal){
	while (S[x].fa!=goal){
		int y=S[x].fa,z=S[y].fa;
		if (z!=goal)
			((x==S[y].ch[0])^(y==S[z].ch[0]))?(Rotate(x)):(Rotate(y));
		Rotate(x);
	}
	Update(x);
	if (goal==0) root=x;
	return;
}

int Prev(int x){
	Splay(x,0);
	x=S[x].ch[0];
	while (S[x].ch[1]) x=S[x].ch[1];
	return x;
}

void Outp(int u){
	if (u==root) cout<<"id ls rs fa key opt s0 s1"<<endl;
	if (S[u].ch[0]) Outp(S[u].ch[0]);
	printf("%2d%3d%3d%3d%4d%4d%3d%4d\n",u,S[u].ch[0],S[u].ch[1],S[u].fa,S[u].key,S[u].opt,S[u].sum0,S[u].sum1);
	//cout<<" "<<u<<"  "<<S[u].ch[0]<<"  "<<S[u].ch[1]<<" "<<S[u].fa<<" "<<S[u].key<<" "<<S[u].opt<<" "<<S[u].sum0<<" "<<S[u].opt<<endl;
	if (S[u].ch[1]) Outp(S[u].ch[1]);
	if (u==root) cout<<endl;
	return;
}

/*
2 1000
0 0
1 2
1
1 1

5 1000
3 4 2 5 1
1 2
1 4
1 5
2 3

18
1 1
1 2
1 3
1 4
1 5
3 1 6 6
1 1
3 4 7 2
1 1
1 4
3 5 8 3
1 5
1 1
3 7 9 1
1 1
1 4
1 7
1 9
//*/
