#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG register
#define IL inline

const int maxN=1010000;
const int maxM=maxN<<1;
const int inf=2147483647;

int n,g,K;
int Seq[maxN];
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],Dg[maxN];
int L[maxN],R[maxN];

IL int Input();
IL void Add_Edge(RG int u,RG int v);
void dfs(RG int u,RG int fa);
IL void Mark(RG int u,RG int l,RG int r);

int main(){
	//freopen("1.in","r",stdin);
	RG  int i,s,t,u,v,op,ed,l,r,mid;
	mem(Head,-1);
	n=Input();g=Input();K=Input();//scanf("%d%d%d",&n,&g,&K);
	for (i=1;i<=g;++i) Seq[i]=Input();//scanf("%d",&Seq[i]);
	sort(&Seq[1],&Seq[g+1]);
	for (i=1;i<n;++i){
		u=Input();v=Input();//scanf("%d%d",&u,&v);
		if (i==1) s=u,t=v;++Dg[u];++Dg[v];
		Add_Edge(u,v);Add_Edge(v,u);
	}
	Mark(s,K,K);
	Mark(t,K,K);
	dfs(s,t);dfs(t,s);

	//for (int i=1;i<=n;i++) cout<<Dg[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<"i:"<<i<<" ["<<L[i]<<","<<R[i]<<"]"<<endl;
	//for (int i=1;i<=g;i++) cout<<Seq[i]<<" ";cout<<endl;
	ll Ans=0;
	for (i=1;i<=n;++i)
		if (Dg[i]==1){
			if ((L[i]==-1)||(Seq[g]<L[i])||((R[i]!=-1)&&(Seq[1]>R[i]))) continue;
			op=ed=0;
			l=1;r=g;
			if (L[i]<=Seq[1]) op=1;
			else do{
				mid=(l+r)>>1;
				if (Seq[mid]>=L[i]) op=mid,r=mid-1;
				else l=mid+1;
			}
			while (l<=r);
			l=1;r=g;
			if (R[i]>=Seq[g]) ed=g;
			else if (R[i]==-1) ed=g;
			else do{
				mid=(l+r)>>1;
				if (Seq[mid]<=R[i]) ed=mid,l=mid+1;
				else r=mid-1;
			}
			while (l<=r);

			//cout<<i<<" "<<op<<" "<<ed<<endl;

			Ans=Ans+(ed-op+1);
		}
	printf("%lld\n",1ll*Ans*K);return 0;
}

IL int Input(){
	RG int x=0;RG char ch=getchar();
	while ((ch>'9')||(ch<'0')) ch=getchar();
	while ((ch>='0')&&(ch<='9')) x=x*10+ch-48,ch=getchar();
	return x;
}

IL void Add_Edge(RG int u,RG int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs(RG int u,RG int fa){
	for (RG int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			Mark(V[i],L[u],R[u]);dfs(V[i],u);
		}
	return;
}

IL void Mark(RG int u,RG int l,RG int r){
	if (Dg[u]==1) L[u]=l,R[u]=r;
	else{
		RG int d=Dg[u]-1;
		if (l==-1) {L[u]=R[u]=-1;return;}
		else if (1ll*l*d>Seq[g]) {L[u]=R[u]=-1;return;}
		else L[u]=1ll*l*d;
		
		if (r==-1) R[u]=-1;
		else if (1ll*r*d+d-1>Seq[g]) R[u]=-1;
		else R[u]=1ll*r*d+d-1;
	}
	return;
}

