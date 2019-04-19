#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

typedef long long ll;
const int maxN=404000;
const int Mod=998244353;

class SplayData{
public:
    int ch[2],fa;ll pls;
};

int n,m,Ans,Mx[maxN];
vector<int> It[maxN];
SplayData S[maxN];
ll Sum[maxN],Ras[maxN],Val[maxN];

void dfs_init(int u,int fa);
void Plus(int x,ll key);
void PushDown(int x);
bool Isroot(int x);
void Rotate(int x);
void Splay(int x);
void Access(int x,ll key);
int main(){
    scanf("%d%d",&n,&m);for (int i=1;i<=n;i++) scanf("%lld",&Val[i]);
    for (int i=1;i<n;i++){
	int u,v;scanf("%d%d",&u,&v);
	It[u].push_back(v);It[v].push_back(u);
    }

    dfs_init(1,1);printf("%d\n",Ans);
    while (m--){
	int u,key;scanf("%d%d",&u,&key);
	Access(u,key);
	printf("%d\n",Ans);
    }
    return 0;
}
void dfs_init(int u,int fa){
    Sum[u]=Val[u];Mx[u]=0;
    for (int i=0,sz=It[u].size();i<sz;i++){
	int v=It[u][i];if (v==fa) continue;
	S[v].fa=u;dfs_init(v,u);Sum[u]+=Sum[v];
	if (Sum[v]>Sum[Mx[u]]) Mx[u]=v;
    }
    if (Sum[u]<=Sum[Mx[u]]+Sum[Mx[u]]) S[u].ch[1]=Mx[u];
    Ras[u]=min(Sum[u]-1,2ll*(Sum[u]-max(Sum[Mx[u]],Val[u])));
    Ans=(Ans+Ras[u]%Mod)%Mod;
    return;
}
void Plus(int x,ll key){
    Sum[x]+=key;S[x].pls+=key;return;
}
void PushDown(int x){
    if (S[x].pls){
	if (S[x].ch[0]) Plus(S[x].ch[0],S[x].pls);
	if (S[x].ch[1]) Plus(S[x].ch[1],S[x].pls);
	S[x].pls=0;
    }
    return;
}
bool Isroot(int x){
    int fa=S[x].fa;
    if (S[fa].ch[0]==x||S[fa].ch[1]==x) return 0;
    return 1;
}
void Rotate(int x){
    int y=S[x].fa,z=S[y].fa,sx=(x==S[y].ch[1]),sy=(y==S[z].ch[1]);
    S[x].fa=z;if (!Isroot(y)) S[z].ch[sy]=x;
    S[y].ch[sx]=S[x].ch[sx^1];if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
    S[x].ch[sx^1]=y;S[y].fa=x;return;
}
void Splay(int x){
    static int now,St[maxN],top;
    St[top=1]=now=x;while (!Isroot(now)) St[++top]=now=S[now].fa;
    while (top) PushDown(St[top--]);
    while (!Isroot(x)){
	int y=S[x].fa,z=S[y].fa;
	if (!Isroot(y)) ((x==S[y].ch[0])^(y==S[z].ch[0]))?Rotate(x):Rotate(y);
	Rotate(x);
    }
    return;
}
void Access(int x,ll key){
    int lstx=S[x].ch[1];Val[x]+=key;
    while (x){
	Splay(x);Sum[x]+=key;if (S[x].ch[0]) Plus(S[x].ch[0],key);
	if (lstx){
	    Ans=(Ans-Ras[x]%Mod+Mod)%Mod;
	    if (Sum[x]<=Sum[lstx]+Sum[lstx]){
		Mx[x]=lstx;S[x].ch[1]=lstx;
	    }
	    Ras[x]=min(Sum[x]-1,2ll*(Sum[x]-max(Sum[Mx[x]],Val[x])));
	    Ans=(Ans+Ras[x]%Mod)%Mod;
	}
	if (Sum[x]>Sum[Mx[x]]+Sum[Mx[x]]) S[x].ch[1]=0;
	
	while (S[x].ch[0]) PushDown(x),x=S[x].ch[0];Splay(x);
	lstx=x;x=S[x].fa;
    }
    return;
}
