#include<bits/stdc++.h>
using namespace std;

const int maxN=505000;

class SplayData{
public:
	int fa,ch[2],key,lz,c[4];
};

int n,Fa[maxN*4],Key[maxN];
vector<int> T[maxN];
SplayData S[maxN];

void dfs_init(int u);
bool Isroot(int x);
void Update(int x);
void Plus(int x,int key);
void PushDown(int x);
void Rotate(int x);
void Splay(int x);
void Access(int x);
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		int a,b,c;scanf("%d%d%d",&a,&b,&c);
		T[i].pb(a);T[i].pb(b);T[i].pb(c);
		Fa[a]=Fa[b]=Fa[c]=i;
	}
	for (int i=1;i<=n+n+1;i++) scanf("%d",&Key[n+i]);
	dfs_init(1);

	int Q;scanf("%d",&Q);
	while (Q--){
		int id,key;scanf("%d%d",&id,&key);
		if (Key[id]!=key){
			key=key-Key[id];
			int fa=Fa[id];
			Access(fa);Splay(fa);
			if (key==1){
				if (S[fa].c[1]){
					
				}
			}
		}
	}
}
void dfs_init(int u){
	for (int i=0;i<T[u].size();i++){
		int v=T[u][i];
		if (v<=n) dfs_init(v),S[u].key+=(S[v].key>=2),S[v].fa=u;
		else S[u].key+=Key[v];
	}
	Update(u);
	return;
}
bool Isroot(int x){
	int fa=S[x].fa;if (S[fa].ch[0]==x||S[fa].ch[1]==x) return 0;
	return 1;
}
void Update(int x){
	for (int i=0;i<4;i++){
		S[x].c[i]=0;
		if (S[x].ch[0]) S[x].c[i]+=S[S[x].ch[0]].c[i];
		if (S[x].ch[1]) S[x].c[i]+=S[S[x].ch[1]].c[i];
	}
	++S[x].c[S[x].key];
	return;
}
void Plus(int x,int key){
	S[x].key+=key;S[x].lz+=key;
	if (key<0){
		for (int i=key;i<4;i++) S[x].c[i-key]=S[x].i;
		for (int i=4-key;i<4;i++) S[x].c[i]=0;
	}
	if (key>0){
		for (int i=3;i>=key;i--) S[x].c[i]=S[x].c[i-key];
		for (int i=0;i<key;i++) S[x].c[i]=0;
	}
	return;
}
void PushDown(int x){
	if (S[x].lz){
		if (S[x].ch[0]) Plus(S[x].ch[0],S[x].lz);
		if (S[x].ch[1]) Plus(S[x].ch[1],S[x].lz);
		S[x].lz=0;
	}
	return;
}
void Rotate(int x){
	int y=S[x].fa,z=S[y].fa,sx=(x==S[y].ch[1]),sy=(y==S[z].ch[1]);
	S[x].fa=z;if (!Isroot(y)) S[z].ch[sy]=x;
	S[y].ch[sx]=S[x].ch[sx^1];if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
	S[y].fa=x;S[x].ch[sx^1]=y;
	Update(y);return;
}
void Splay(int x){
	static int St[maxN];int top=1,now=x;St[1]=now;
	while (Isroot(now)) St[++top]=now=S[now].fa;
	while (top) PushDown(St[top--]);
	while (!Isroot(x)){
		int y=S[x].fa,z=S[y].fa;
		if (!Isroot(y)) ((x==S[y].ch[0])^(y==S[z].ch[0]))?Rotate(x):Rotate(y);
		Rotate(x);
	}
	Update(x);return;
}
void Access(int x){
	int lstx=0;
	while (x){
		Splay(x);S[x].ch[1]=lstx;Update(x);
		lstx=x;x=S[x].fa;
	}
	return;
}
