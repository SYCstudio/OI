#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)

const int maxN=101000;
const int maxM=maxN<<1;
const int meminf=2139062143;
const int inf=2147483647;

class SegmentData
{
public:
	int mn,ls,rs;
};

int n,m;
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM];
int Size[maxN],Hs[maxN],Fa[maxN],Top[maxN],Dph[maxN];
int nodecnt=0,rt[maxN],dfncnt,dfn[maxN],fst[maxN],lst[maxN];
SegmentData S[maxN*50];

void Add_Edge(int u,int v);
void dfs1(int u,int fa);
void dfs2(int u,int top);
void Cover(int u,int v,int w);
void Modify(int &now,int l,int r,int ql,int qr,int key);
int Query(int now,int l,int r,int pos);

int main(){
	//freopen("in.in","r",stdin);freopen("out","w",stdout);
	mem(Head,-1);//mem(Mn,127);
	scanf("%d%d",&n,&m);
	for (int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
	}

	Dph[1]=1;dfs1(1,1);dfs2(1,1);

	//for (int i=1;i<=n;i++) cout<<dfn[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Top[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Hs[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<fst[i]<<" "<<lst[i]<<endl;

	while (m--){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		Cover(u,v,w);
	}

	for (int i=0;i<=edgecnt;i+=2){
		//cout<<V[i]<<" "<<V[i^1]<<endl;
		int mn=meminf;
		if (Dph[V[i]]>Dph[V[i^1]]) mn=Query(rt[Top[V[i]]],fst[Top[V[i]]],lst[Top[V[i]]],dfn[V[i]]);
		else mn=Query(rt[Top[V[i^1]]],fst[Top[V[i^1]]],lst[Top[V[i^1]]],dfn[V[i^1]]);
		if (mn==inf) printf("-1\n");
		else printf("%d\n",mn);
	}
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs1(int u,int fa){
	Size[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			Dph[V[i]]=Dph[u]+1;Fa[V[i]]=u;
			dfs1(V[i],u);Size[u]+=Size[V[i]];
			if (Size[V[i]]>Size[Hs[u]]) Hs[u]=V[i];
		}
	return;
}

void dfs2(int u,int top){
	Top[u]=top;dfn[u]=++dfncnt;
	if (fst[top]==0) fst[top]=dfncnt;lst[top]=dfncnt;
	if (Hs[u]==0) return;
	dfs2(Hs[u],top);
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=Fa[u])&&(V[i]!=Hs[u]))
			dfs2(V[i],V[i]);
	return;
}

void Modify(int &now,int l,int r,int ql,int qr,int key){
	if (now==0) now=++nodecnt,S[now].mn=inf;
	if ((l==ql)&&(r==qr)){
		S[now].mn=min(S[now].mn,key);return;
	}
	int mid=(l+r)>>1;
	if (qr<=mid) Modify(S[now].ls,l,mid,ql,qr,key);
	else if (ql>=mid+1) Modify(S[now].rs,mid+1,r,ql,qr,key);
	else{
		Modify(S[now].ls,l,mid,ql,mid,key);
		Modify(S[now].rs,mid+1,r,mid+1,qr,key);
	}
	return;
}

int Query(int now,int l,int r,int pos){
	if (now==0) return inf;
	if (l==r) return S[now].mn;
	int mid=(l+r)>>1;
	if (pos<=mid) return min(S[now].mn,Query(S[now].ls,l,mid,pos));
	else return min(S[now].mn,Query(S[now].rs,mid+1,r,pos));
}

void Cover(int u,int v,int w){
	//cout<<"Cover:"<<u<<" "<<v<<" "<<w<<endl;
	while (Top[u]!=Top[v]){
		//cout<<u<<" "<<v<<" "<<Top[u]<<" "<<Top[v]<<endl;
		if (Dph[Top[u]]<Dph[Top[v]]) swap(u,v);
		//cout<<u<<" "<<v<<" ["<<dfn[Top[u]]<<" "<<dfn[u]<<"] ["<<fst[Top[u]]<<" "<<lst[Top[u]]<<"]"<<endl;
		Modify(rt[Top[u]],fst[Top[u]],lst[Top[u]],dfn[Top[u]],dfn[u],w);
		u=Fa[Top[u]];
	}
	if (Dph[u]>Dph[v]) swap(u,v);
	if (u!=v){
		//cout<<u<<" "<<v<<" ["<<dfn[u]+1<<" "<<dfn[v]<<"] ["<<fst[Top[u]]<<" "<<lst[Top[u]]<<"]"<<endl;
		Modify(rt[Top[u]],fst[Top[u]],lst[Top[u]],dfn[u]+1,dfn[v],w);
	}
	return;
}
