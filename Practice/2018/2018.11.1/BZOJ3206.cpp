#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxM=303000<<1;
const int maxK=22;
const int inf=2147483647;
const ll INF=1e18;

int n,m,K;
ll People[maxN],Ppl[maxN];
pair<ll,pair<int,int> > E[maxM];
pair<int,int> EK[maxK],Mch[maxN];
int mchcnt=0,UFS[maxN],Id[maxN],idcnt;
ll Mp[maxK][maxK];
int edgecnt,Head[maxK],Next[maxM];
pair<int,ll> To[maxM];
ll FaW[maxK];
int Fa[maxK],Dph[maxK];
int chscnt,chs[maxM];
ll sum=0;

int Find(int x);
void Add_Edge(int u,int v,ll w);
void Min(int u,int v,ll w);
void dfs_fa(int u,int fa);
ll dfs_calc(int u,int fa);

int main(){
	//freopen("10.in","r",stdin);
	scanf("%d%d%d",&n,&m,&K);
	for (int i=1;i<=m;i++) scanf("%d%d%lld",&E[i].second.first,&E[i].second.second,&E[i].first);
	for (int i=0;i<K;i++) scanf("%d%d",&EK[i].first,&EK[i].second);
	for (int i=1;i<=n;i++) scanf("%lld",&People[i]);
	for (int i=1;i<=n;i++) UFS[i]=i;
	for (int i=0;i<K;i++) UFS[Find(EK[i].first)]=Find(EK[i].second);
	sort(&E[1],&E[m+1]);
	for (int i=1;i<=m;i++){
		int u=E[i].second.first,v=E[i].second.second;
		if (Find(u)!=Find(v)){
			UFS[Find(u)]=Find(v);
			Mch[++mchcnt]=E[i].second;
		}
	}

	for (int i=1;i<=n;i++) UFS[i]=i;
	for (int i=1;i<=mchcnt;i++) UFS[Find(Mch[i].first)]=Find(Mch[i].second);

	//for (int i=1;i<=n;i++) cout<<Find(i)<<" ";cout<<endl;

	for (int i=1;i<=n;i++) if (Id[Find(i)]==0) Id[Find(i)]=++idcnt;
	for (int i=1;i<=n;i++) Ppl[Id[Find(i)]]+=People[i];
	for (int i=0;i<K;i++) EK[i].first=Id[Find(EK[i].first)],EK[i].second=Id[Find(EK[i].second)];
	for (int i=1;i<=idcnt;i++) for (int j=1;j<=idcnt;j++) Mp[i][j]=(i==j)?0:INF;
	for (int i=1;i<=m;i++){
		int u=Id[Find(E[i].second.first)],v=Id[Find(E[i].second.second)];
		Mp[u][v]=Mp[v][u]=min(Mp[u][v],E[i].first);
	}
	m=0;
	for (int i=1;i<=idcnt;i++) for (int j=i+1;j<=idcnt;j++) if (Mp[i][j]!=INF) E[++m]=make_pair(Mp[i][j],make_pair(i,j));
	sort(&E[1],&E[m+1]);
	int mm=0;
	for (int i=1;i<=idcnt;i++) UFS[i]=i;
	for (int i=1;i<=m;i++)
		if (Find(E[i].second.first)!=Find(E[i].second.second)){
			E[++mm]=E[i];
			UFS[Find(E[i].second.first)]=Find(E[i].second.second);
		}
	m=mm;

	/*
	cout<<idcnt<<endl;
	for (int i=1;i<=idcnt;i++) cout<<Ppl[i]<<" ";cout<<endl;
	for (int i=0;i<K;i++) cout<<"("<<EK[i].first<<","<<EK[i].second<<") ";cout<<endl;
	//*/

	ll Ans=0;
	for (int S=0;S<(1<<K);S++){
		for (int i=1;i<=idcnt;i++) UFS[i]=i;
		bool flag=1;edgecnt=-1;mem(Head,-1);
		for (int i=0;i<K;i++)
			if (S&(1<<i)){
				if (Find(EK[i].first)==Find(EK[i].second)){
					flag=0;break;
				}
				Add_Edge(EK[i].first,EK[i].second,inf),UFS[Find(EK[i].first)]=Find(EK[i].second);
			}
		if (flag==0) continue;
		++chscnt;
		for (int i=1;i<=m;i++)
			if (Find(E[i].second.first)!=Find(E[i].second.second)){
				Add_Edge(E[i].second.first,E[i].second.second,0);chs[i]=chscnt;
				UFS[Find(E[i].second.first)]=Find(E[i].second.second);
			}

		/*
		cout<<"S:"<<S<<endl;
		for (int i=1;i<=idcnt;i++)
			for (int j=Head[i];j!=-1;j=Next[j])
				cout<<i<<" -> "<<To[j].first<<" "<<To[j].second<<endl;
		//*/
		
		Dph[1]=1;dfs_fa(1,1);
		for (int i=1;i<=m;i++)
			if (chs[i]!=chscnt) Min(E[i].second.first,E[i].second.second,E[i].first);
		sum=0;dfs_calc(1,1);
		//cout<<S<<" "<<sum<<endl;
		Ans=max(Ans,sum);
	}
	printf("%lld\n",Ans);return 0;
}

int Find(int x){
	return UFS[x]==x?(UFS[x]):(UFS[x]=Find(UFS[x]));
}

void Add_Edge(int u,int v,ll w){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;To[edgecnt]=make_pair(v,w);
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;To[edgecnt]=make_pair(u,w);
}

void Min(int u,int v,ll w){
	if (Dph[u]<Dph[v]) swap(u,v);
	while (Dph[u]>Dph[v]) FaW[u]=min(FaW[u],w),u=Fa[u];
	while (u!=v) FaW[u]=min(FaW[u],w),FaW[v]=min(FaW[v],w),u=Fa[u],v=Fa[v];
	return;
}

void dfs_fa(int u,int fa){
	for (int i=Head[u];i!=-1;i=Next[i])
		if (To[i].first!=fa){
			Fa[To[i].first]=u;FaW[To[i].first]=To[i].second;Dph[To[i].first]=Dph[u]+1;
			dfs_fa(To[i].first,u);
		}
	return;
}

ll dfs_calc(int u,int fa){
	ll tot=Ppl[u];
	for (int i=Head[u];i!=-1;i=Next[i])
		if (To[i].first!=fa) tot+=dfs_calc(To[i].first,u);
	sum=sum+tot*FaW[u];
	return tot;
}

