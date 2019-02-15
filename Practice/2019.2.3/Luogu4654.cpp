#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010000;
const int maxM=maxN<<1;

int n,S,T;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],D[maxN];
int Fa[maxN],F[maxN],top,Seq[maxN],Cnt[maxN];

void Add_Edge(int u,int v);
void dfs(int u);
bool check(int limit);

int main(){
    scanf("%d%d%d",&n,&T,&S);mem(Head,-1);
    for (int i=1;i<n;i++){
	int u,v;scanf("%d%d",&u,&v);
	Add_Edge(u,v);Add_Edge(v,u);
    }

    dfs(T);

    int now=S;while (now) Seq[++top]=now,now=Fa[now];
    for (int i=top-1;i>=1;i--) Cnt[i]=Cnt[i+1]+D[Seq[i]]-2;
    ++Cnt[1];

    int l=0,r=n+n,mid,Ans=0;
    while (l<=r) check(mid=(l+r)>>1)?(Ans=mid,r=mid-1):l=mid+1;

    printf("%d\n",Ans);return 0;
}

void Add_Edge(int u,int v){
    Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;++D[u];
    return;
}
void dfs(int u){
    int mx=0,mxx=0;
    for (int i=Head[u];i!=-1;i=Next[i])
	if (V[i]!=Fa[u]){
	    Fa[V[i]]=u;dfs(V[i]);
	    if (F[V[i]]>=mx) mxx=mx,mx=F[V[i]];
	    else if (F[V[i]]>mxx) mxx=F[V[i]];
	}
    F[u]=mxx+D[u]-1;return;
}
bool check(int limit){
    int sum=0;
    for (int i=1;i<top;i++){
	int u=Seq[i],tot=0;
	for (int j=Head[u];j!=-1;j=Next[j])
	    if (V[j]!=Seq[i-1]&&V[j]!=Seq[i+1])
		tot+=(F[V[j]]+Cnt[i]>limit);
	limit-=tot;sum+=tot;
	if (limit<0||sum>i) return 0;
    }
    return 1;
}
