#include<bits/stdc++.h>
using namespace std;

#define pb push_back
const int maxN=101000;
const int maxM=maxN*10;
const int inf=2000000000;

class Edge{
public:
	int v,flow;
};

int n,m;
int Mx[maxN],My[maxN];
map<string,int> Mp;
int S=1,T=2,nodecnt=2;
char In[100][100];
int revcnt=0,Idx[maxN],Idy[maxN];
int ecnt=-1,Hd[maxN],Nt[maxM];
Edge E[maxM];
int Qu[maxN],Dep[maxN],cur[maxN];

void Add_Edge(int u,int v,int flow);
bool bfs();
int dfs(int u,int flow);
int main(){
	//freopen("out","w",stdout);
	int Case;scanf("%d",&Case);
	while (Case--){
		ecnt=-1;S=1;T=2;nodecnt=2;
		memset(Hd,-1,sizeof(Hd));
		Mp.clear();revcnt=0;
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++) scanf("%d",&Mx[i]),Idx[i]=++nodecnt;
		for (int i=1;i<=m;i++) scanf("%d",&My[i]),Idy[i]=++nodecnt;
		for (int i=1;i<=n;i++) scanf("%s",In[i]+1);
		Mp[""]=-1;
		for (int i=1;i<=n;i++){
			string s="",revs="";
			int SWAP=-1;vector<int> L,R;
			for (int j=1;j<=m+1;j++)
				if (j==m+1||In[i][j]=='_'){
					if (s=="") continue;
					if (s==revs){
						if (Mp.count(s)==0) ++revcnt,Mp[s]=-1;
					}
					else{
						//cout<<s<<" "<<revs<<endl;
						if (s>revs) swap(s,revs),SWAP=1;
						else SWAP=0;
						if (Mp.count(s)==0&&Mp.count(revs)==0){
							Mp[s]=++nodecnt;Mp[revs]=++nodecnt;
							Add_Edge(Mp[s],Mp[revs],2);
						}
						L.pb(Mp[s]);R.pb(Mp[revs]);
					}
					s=revs="";
				}
				else s=s+In[i][j],revs=In[i][j]+revs;
			//for (int j=0;j<L.size();j++) cerr<<L[j]<<" ";cerr<<endl;
			//for (int j=0;j<R.size();j++) cerr<<R[j]<<" ";cerr<<endl;
			if (SWAP==-1) continue;
			if (Mx[i]==0){
				for (int j=0;j<R.size();j++) Add_Edge(R[j],Idx[i],inf);
				for (int j=0;j<L.size();j++) Add_Edge(Idx[i],L[j],inf);
			}
			else if ((Mx[i]==1&&SWAP==0)||(Mx[i]==-1&&SWAP==1)){
				Add_Edge(S,Idx[i],inf);for (int j=0;j<L.size();j++) Add_Edge(Idx[i],L[j],inf);
			}
			else{
				Add_Edge(Idx[i],T,inf);for (int j=0;j<R.size();j++) Add_Edge(R[j],Idx[i],inf);
			}
		}
		for (int j=1;j<=m;j++){
			string s="",revs="";
			int SWAP=-1;vector<int> L,R;
			for (int i=1;i<=n+1;i++)
				if (i==n+1||In[i][j]=='_'){
					if (s=="") continue;
					if (s==revs){
						if (Mp.count(s)==0) ++revcnt,Mp[s]=-1;
					}
					else{
						//cout<<s<<" "<<revs<<endl;
						if (s>revs) swap(s,revs),SWAP=1;
						else SWAP=0;
						if (Mp.count(s)==0&&Mp.count(revs)==0){
							Mp[s]=++nodecnt;Mp[revs]=++nodecnt;
							Add_Edge(Mp[s],Mp[revs],2);
						}
						L.pb(Mp[s]);R.pb(Mp[revs]);
					}
					s=revs="";
				}
				else s=s+In[i][j],revs=In[i][j]+revs;
			if (SWAP==-1) continue;
			if (My[j]==0){
				for (int i=0;i<R.size();i++) Add_Edge(R[i],Idy[j],inf);
				for (int i=0;i<L.size();i++) Add_Edge(Idy[j],L[i],inf);
			}
			else if ((My[j]==1&&SWAP==0)||(My[j]==-1&&SWAP==1)){
				Add_Edge(S,Idy[j],inf);for (int i=0;i<L.size();i++) Add_Edge(Idy[j],L[i],inf);
			}
			else{
				Add_Edge(Idy[j],T,inf);for (int i=0;i<R.size();i++) Add_Edge(R[i],Idy[j],inf);
			}
		}
		
		int Ans=0;
		while (bfs()){
			memcpy(cur,Hd,sizeof(cur));
			while (int di=dfs(S,inf)) Ans+=di;
		}
		printf("%d\n",Ans+revcnt);
	}
	return 0;
}
void Add_Edge(int u,int v,int flow){
	//cerr<<"Add:"<<u<<" "<<v<<endl;
	Nt[++ecnt]=Hd[u];Hd[u]=ecnt;E[ecnt]=((Edge){v,flow});
	Nt[++ecnt]=Hd[v];Hd[v]=ecnt;E[ecnt]=((Edge){u,0});
	return;
}
bool bfs(){
	memset(Dep,-1,sizeof(Dep));int ql=1,qr=1;Dep[Qu[1]=S]=1;
	while (ql<=qr)
		for (int u=Qu[ql++],i=Hd[u];i!=-1;i=Nt[i])
			if (E[i].flow&&Dep[E[i].v]==-1) Dep[Qu[++qr]=E[i].v]=Dep[u]+1;
	return Dep[T]!=-1;
}
int dfs(int u,int flow){
	if (u==T) return flow;
	for (int &i=cur[u];i!=-1;i=Nt[i])
		if (E[i].flow&&Dep[E[i].v]==Dep[u]+1){
			int di=dfs(E[i].v,min(flow,E[i].flow));
			if (di){
				E[i].flow-=di;E[i^1].flow+=di;return di;
			}
		}
	return 0;
}
