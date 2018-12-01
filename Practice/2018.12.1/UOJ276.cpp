#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define Abt(x) (lower_bound(&Num[1],&Num[num+1],x)-Num)

const int maxN=50500;
const int maxM=maxN<<1;
const int inf=2147483647;
const ll INF=1e18;

int n;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
ll K,W[maxM];
int root,nowsize,Mx[maxN],Sz[maxN];
bool vis[maxN];
vector<int> DT[maxN];
vector<pair<ll,ll> > Vc;
ll num,Num[maxN*4],BIT[maxN*4];
int bittim,Tim[maxN*4];

void Add_Edge(int u,int v,ll w);
void dfs_root(int u,int fa);
void GDT(int u);
bool check(int u,ll lim);
void dfs_gdt(int u,int fa,int d,ll w);
void Modify(int pos,ll key);
ll GMax(int pos);

int main(){
	scanf("%d%lld",&n,&K);mem(Head,-1);ll mx=0;
	for (int i=1;i<n;i++){
		int u,v;ll w;scanf("%d%d%lld",&u,&v,&w);w-=K;mx=max(mx,abs(w));
		Add_Edge(u,v,w);Add_Edge(v,u,w);
	}
	//cerr<<"Input over"<<endl;
	Mx[0]=inf;root=0;nowsize=n;
	dfs_root(1,1);int glort=root;GDT(root);
	//cerr<<"GDT over"<<endl;
	ll l=0,r=mx+1,Ans=mx+1;
	do{
		ll mid=(l+r)>>1;mem(vis,0);
		//cerr<<"check:"<<mid<<endl;
		if (check(glort,mid)) Ans=mid,r=mid-1;
		else l=mid+1;
	}
	while (l<=r);
	Ans=max(0ll,Ans-1);
	printf("%lld\n",Ans);return 0;
}

void Add_Edge(int u,int v,ll w){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	return;
}

void dfs_root(int u,int fa){
	Sz[u]=1;Mx[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((vis[V[i]]==0)&&(V[i]!=fa)){
			dfs_root(V[i],u);Sz[u]+=Sz[V[i]];
			Mx[u]=max(Mx[u],Sz[V[i]]);
		}
	Mx[u]=max(Mx[u],nowsize-Sz[u]);
	if (Mx[u]<Mx[root]) root=u;return;
}

void GDT(int u){
	vis[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0){
			//if (Sz[V[i]]>Sz[u]) nowsize=Sz[V[i]]-Sz[u];
			nowsize=Sz[V[i]];
			root=0;dfs_root(V[i],V[i]);DT[u].push_back(root);GDT(root);
		}
	return;
}

bool check(int u,ll lim){
	//cout<<"check:"<<u<<" "<<lim<<endl;
	vis[u]=1;num=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0){
			Vc.clear();dfs_gdt(V[i],u,1,W[i]);
			//cout<<V[i]<<":"<<endl;
			//for (int j=0,sz=Vc.size();j<sz;j++) cout<<Vc[j].first<<" "<<Vc[j].second<<endl;
			for (int j=0,sz=Vc.size();j<sz;j++) Num[++num]=-(lim*Vc[j].first+Vc[j].second),Num[++num]=lim*Vc[j].first+Vc[j].second;
		}
	sort(&Num[1],&Num[num+1]);num=unique(&Num[1],&Num[num+1])-Num-1;
	++bittim;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0){
			Vc.clear();dfs_gdt(V[i],u,1,W[i]);
			for (int j=0,sz=Vc.size();j<sz;j++){
				int up=Abt(lim*Vc[j].first+Vc[j].second)-1;
				ll mx=GMax(up);
				if (mx>-(lim*Vc[j].first-Vc[j].second)) {/*cout<<"check1:["<<mx<<"] "<<Vc[j].first<<" "<<Vc[j].second<<endl;*/return 1;}
				if ((-lim*Vc[j].first<Vc[j].second)&&(lim*Vc[j].first>Vc[j].second)) {/*cout<<"check2:"<<Vc[j].first<<" "<<Vc[j].second<<endl;*/return 1;}
			}
			for (int j=0,sz=Vc.size();j<sz;j++){
				int pos=Abt(-(lim*Vc[j].first+Vc[j].second));
				Modify(pos,lim*Vc[j].first-Vc[j].second);
			}
		}
	for (int i=0,sz=DT[u].size();i<sz;i++)
		if (check(DT[u][i],lim)) return 1;
	return 0;
}

void dfs_gdt(int u,int fa,int d,ll w){
	Vc.push_back(make_pair(d,w));
	for (int i=Head[u];i!=-1;i=Next[i]) if ((vis[V[i]]==0)&&(V[i]!=fa)) dfs_gdt(V[i],u,d+1,w+W[i]);
	return;
}

void Modify(int pos,ll key){
	while (pos<=num){
		if (Tim[pos]!=bittim) BIT[pos]=key,Tim[pos]=bittim;
		else BIT[pos]=max(BIT[pos],key);
		pos+=(pos)&(-pos);
	}
	return;
}

ll GMax(int pos){
	ll ret=-INF;
	while (pos>0){
		if (Tim[pos]==bittim) ret=max(ret,BIT[pos]);
		pos-=(pos)&(-pos);
	}
	return ret;
}
