#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define NAME "disaster"

const int maxN=101000;
const int maxBit=21;
const int maxM=maxN<<1;
const int inf=10000000;

int n;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],Fa[maxN],Anc[maxN];
int scnt,Seq[maxN],D[maxN];
int tim,Tim[maxN],Q[maxN];
bool inl[maxN];
int ST1[maxBit][maxN],ST2[maxBit][maxN],Log[maxN];

void Add_Edge(int u,int v);
int Bfs(int S,int fa);
int dfs(int u,int fa,int d,int anc);
int Query1(int l,int r);
int Query2(int l,int r);

int main(){
	mem(Head,-1);
	for (int i=1;i<maxN;i++) Log[i]=log2(i);
	scanf("%d",&n);
	for (int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
	}

	int n1=Bfs(1,1);
	int n2=Bfs(n1,n1);

	//cout<<"n1,n2:"<<n1<<" "<<n2<<endl;

	int now=n2;Seq[++scnt]=now;inl[n1]=inl[n2]=1;
	while (now!=n1) inl[now=Seq[++scnt]=Fa[now]]=1;
	reverse(&Seq[1],&Seq[scnt+1]);

	//for (int i=0;i<maxBit;i++) for (int j=0;j<maxN;j++) ST1[i][j]=ST2[i][j]=-inf;
	
	for (int i=1;i<=scnt;i++){
		int u=Seq[i],mx=0;Anc[u]=i;D[u]=0;
		for (int j=Head[u];j!=-1;j=Next[j])
			if (inl[V[j]]==0) mx=max(mx,dfs(V[j],u,1,i));
		//cout<<i<<" "<<u<<":"<<mx<<" ["<<mx-i<<","<<mx+i<<"]"<<endl;
		ST1[0][i]=mx-i;ST2[0][i]=mx+i;
	}

	//cout<<"Inl:";for (int i=1;i<=n;i++) cout<<inl[i]<<" ";cout<<endl;
	//cout<<"Seq:";for (int i=1;i<=scnt;i++) cout<<Seq[i]<<" ";cout<<endl;
	//cout<<"Anc:";for (int i=1;i<=n;i++) cout<<Anc[i]<<" ";cout<<endl;
	//cout<<"D:";for (int i=1;i<=n;i++) cout<<D[i]<<" ";cout<<endl;

	for (int i=1;i<maxBit;i++)
		for (int j=1;j+(1<<i)<=scnt;j++){
			ST1[i][j]=max(ST1[i-1][j],ST1[i-1][j+(1<<(i-1))]);
			ST2[i][j]=max(ST2[i-1][j],ST2[i-1][j+(1<<(i-1))]);
		}

	int m,x,y;scanf("%d",&m);
	while (m--){
		int u,v,mx=0;scanf("%d%d",&u,&v);
		int uu=Anc[u],vv=Anc[v];
		if (uu>vv) swap(uu,vv),swap(u,v);

		//cout<<u<<" "<<v<<endl;
		//cout<<uu<<" "<<vv<<endl;
		
		int w=uu+vv-D[u]+D[v];//cout<<"w:"<<w<<endl;
		if (uu==vv) mx=max(uu-1,scnt-vv)+min(D[u],D[v]);
		else if (w<=uu*2) mx=max(vv-1,scnt-vv)+D[v];
		else if (w>=vv*2) mx=max(uu-1,scnt-uu)+D[u];
		else{
			//cout<<"w:"<<w<<" "<<uu-1<<" "<<Query2(uu+1,w/2)-uu<<" "<<scnt-vv<<" "<<Query1(w/2+1,vv-1)<<" "<<vv<<endl;
			mx=max(max(uu-1,Query2(uu+1,w/2)-uu)+D[u],max(scnt-vv,Query1(w/2+1,vv-1)+vv)+D[v]);
		}
		printf("%d\n",mx);
	}
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

int Bfs(int S,int fa){
	//cout<<"Bfs:"<<S<<" "<<fa<<endl;
	D[S]=1;tim++;int h=1,t=0;Tim[S]=tim;
	Q[1]=S;int rt=S;Fa[S]=fa;Anc[S]=fa;
	do for (int u=Q[++t],i=Head[u];i!=-1;i=Next[i])
		   if ((Tim[V[i]]!=tim)&&(V[i]!=fa)){
			   D[Q[++h]=V[i]]=D[Fa[V[i]]=u]+1;Tim[V[i]]=tim;
			   if (D[V[i]]>D[rt]) rt=V[i];
		   }
	while (t!=h);
	return rt;
}

int dfs(int u,int fa,int d,int anc){
	D[u]=d;Anc[u]=anc;int ret=d;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa) ret=max(ret,dfs(V[i],u,d+1,anc));
	return ret;
}

int Query1(int l,int r){
	if (l>r) return -inf;
	int lg=Log[r-l+1];
	return max(ST1[lg][l],ST1[lg][r-(1<<lg)+1]);
}

int Query2(int l,int r){
	if (l>r) return -inf;
	int lg=Log[r-l+1];
	return max(ST2[lg][l],ST2[lg][r-(1<<lg)+1]);
}
