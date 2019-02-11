#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int gi(){
	int x=0,w=1;char ch=getchar();
	while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
	if(ch=='-')w=0,ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return w?x:-x;
}
#define pi pair<int,int>
#define mk make_pair
const int N=2e5+5;
int n,to[N],nxt[N],head[N],q[N],hd,tl,fa[N],sz[N],w[N],vis[N],ans;
pi findroot(int x,int op){
	q[hd=tl=1]=x;
	while(hd<=tl)
		for(int u=q[hd++],e=head[u];e;e=nxt[e])
			if(to[e]!=fa[u]&&(!vis[to[e]]||op))
				fa[q[++tl]=to[e]]=u;
	int rt=0,val=n;
	for(int i=tl;i;--i){
		int u=q[i],v=0;sz[u]=1;
		for(int e=head[u];e;e=nxt[e])
			if(to[e]!=fa[u]&&(!vis[to[e]]||op))
				sz[u]+=sz[to[e]],v=max(v,sz[to[e]]);
		v=max(v,tl-sz[u]);if(v<val)val=v,rt=u;
	}
	return mk(rt,val+n-tl);
}
int main(){
	n=gi();
	for(int i=1,j=0;i<n;++i){
		int u=gi(),v=gi();
		to[++j]=v;nxt[j]=head[u];head[u]=j;
		to[++j]=u;nxt[j]=head[v];head[v]=j;
	}
	int x=n;
	while(!vis[x]){
		fa[x]=0;x=findroot(x,0).first;vis[x]=1;
		pi res=mk(n,0);
		for(int e=head[x];e;e=nxt[e])
			fa[to[e]]=x,res=min(res,mk(findroot(to[e],1).second,to[e]));
		ans=max(ans,res.first);x=res.second;
	}
	printf("%d\n",ans);return 0;
}