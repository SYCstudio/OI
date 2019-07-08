#include<bits/stdc++.h>
using namespace std;

#define pb push_back
const int maxN=202000;

class SplayData
{
public:
	int ch[2],fa,size,rev,key;
};

int n,Q,Fa[maxN],nodecnt;
vector<int> T[maxN];
priority_queue<int,vector<int>,greater<int> > Heap;
int B[maxN+maxN];
SplayData S[maxN];

void dfs_init(int u,int fa);
bool Isroot(int x);
void Update(int x);
void PushDown(int x);
void Reverse(int x);
void Rotate(int x);
void Splay(int x);
void Access(int x);
int Query(int u);
void Plus(int p,int k);
int Sum(int p);
int main()
{
	scanf("%d%d",&n,&Q);
	for (int i=1; i<=n; i++) S[i].key=i,S[i].size=1;
	for (int i=1; i<n; i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		T[u].pb(v);
		T[v].pb(u);
	}
	dfs_init(n,0);

	nodecnt=n;
	for (int qi=1; qi<=Q; qi++) {
		char ipt[10];
		scanf("%s",ipt);
		if (ipt[0]=='u') {
			int u;
			scanf("%d",&u);
			++nodecnt;
			Access(u);
			Splay(u);
			Reverse(u);
			S[u].key=nodecnt;
		}
		if (ipt[0]=='w') {
			int u;
			scanf("%d",&u);
			printf("%d\n",Query(u));
		}
		if (ipt[0]=='c') {
			int u,v,m1,m2;
			scanf("%d%d",&u,&v);
			//cerr<<Query(u)<<" "<<Query(v)<<endl;
			printf("%d\n",Query(u)<Query(v)?u:v);
		}
		//for (int i=1;i<=n+Q;i++) cerr<<Sum(i)-Sum(i-1)<<" ";cerr<<endl;
		//for (int i=1;i<=n;i++) cerr<<S[i].key<<" ";cerr<<endl;
	}
	return 0;
}
void dfs_init(int u,int fa)
{
	S[u].fa=fa;
	S[u].key=u;
	for (int i=0; i<T[u].size(); i++) {
		int v=T[u][i];
		if (v==fa) continue;
		dfs_init(v,u);
		if (S[v].key>S[u].key) {
			S[u].key=S[v].key;
			S[u].ch[1]=v;
			S[u].size=S[v].size+1;
		}
	}
	Plus(S[u].key,1);
	return;
}
bool Isroot(int x)
{
	int fa=S[x].fa;
	if (S[fa].ch[0]==x||S[fa].ch[1]==x) return 0;
	return 1;
}
void Update(int x)
{
	S[x].size=1;
	if (S[x].ch[0]) S[x].size+=S[S[x].ch[0]].size;
	if (S[x].ch[1]) S[x].size+=S[S[x].ch[1]].size;
	return;
}
void Reverse(int x)
{
	S[x].rev^=1;
	swap(S[x].ch[0],S[x].ch[1]);
	return;
}
void PushDown(int x)
{
	if (S[x].rev) {
		if (S[x].ch[0]) Reverse(S[x].ch[0]);
		if (S[x].ch[1]) Reverse(S[x].ch[1]);
		S[x].rev=0;
	}
	if (S[x].ch[0]) S[S[x].ch[0]].key=S[x].key;
	if (S[x].ch[1]) S[S[x].ch[1]].key=S[x].key;
	return;
}
void Rotate(int x)
{
	int y=S[x].fa,z=S[y].fa,sx=(x==S[y].ch[1]),sy=(y==S[z].ch[1]);
	S[x].fa=z;
	if (Isroot(y)==0) S[z].ch[sy]=x;
	S[y].ch[sx]=S[x].ch[sx^1];
	if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
	S[x].ch[sx^1]=y;
	S[y].fa=x;
	Update(y);
	return;
}
void Splay(int x)
{
	static int ST[maxN];
	int now=x,top=1;
	ST[1]=x;
	while (!Isroot(now)) ST[++top]=now=S[now].fa;
	while (top) PushDown(ST[top--]);
	while (!Isroot(x)) {
		int y=S[x].fa,z=S[y].fa;
		if (!Isroot(y)) ((x==S[y].ch[0])^(y==S[z].ch[0]))?Rotate(x):Rotate(y);
		Rotate(x);
	}
	Update(x);
	return;
}
void Access(int x)
{
	int lstx=0;
	while (x) {
		Splay(x);
		S[x].ch[1]=0;
		Update(x);
		Plus(S[x].key,-S[x].size);
		S[x].ch[1]=lstx;
		Update(x);
		lstx=x;
		x=S[x].fa;
	}
	Splay(lstx);
	Plus(nodecnt,S[lstx].size);
	return;
}
int Query(int x)
{
	Splay(x);
	return Sum(S[x].key)-S[S[x].ch[0]].size;
}
void Plus(int p,int k)
{
	//cout<<"Plus:"<<p<<" "<<k<<endl;
	while (p<=n+Q) {
		B[p]+=k;
		p+=(p)&(-p);
	}
	return;
}
int Sum(int p)
{
	int ret=0;
	while (p) {
		ret+=B[p];
		p-=(p)&(-p);
	}
	return ret;
}
