#include<bits/stdc++.h>
using namespace std;

#define NUM "6"
const int maxN=1010;

int n,K,W0;
vector<int> E[maxN],G[maxN];
int Ku[maxN],Kv[maxN];
int Ans=1e8;

int random(int l,int r);
int Calc();
int Bfs(int S);
void Outp();
int main(){
    freopen("road"NUM".in","r",stdin);
    srand(time(0));
    scanf("%d%d%d",&n,&K,&W0);
    for (int i=1;i<n;i++){
	int u,v;scanf("%d%d",&u,&v);
	E[u].push_back(v);E[v].push_back(u);
    }
    int start=random(1,n);
    for (int i=1;i<=K;i++) Ku[i]=start,Kv[i]=random(1,n);
    int S=Calc();
    if (S<Ans){
	Ans=S;Outp();
    }
    while (1){
	int id=random(1,K),u=Ku[id],v=Kv[id];
	Kv[id]=random(1,n);
	    
	int s=Calc();//printf("%d %d\n",Ans,s);
	if (s<Ans){
	    Ans=s;Outp();
	}
	else Ku[id]=u,Kv[id]=v;
    }
    return 0;
}
int random(int l,int r){
    double dou=1.0*rand()/RAND_MAX;
    return min(r,(int)(dou*(r-l+1)+l));
}
int Calc(){
    for (int i=1;i<=n;i++) G[i].clear();
    for (int i=1;i<=K;i++) G[Ku[i]].push_back(Kv[i]),G[Kv[i]].push_back(Ku[i]);
    int sum=0;
    for (int i=1;i<=n;i++) sum+=Bfs(i);
    return sum/2;
}
int Bfs(int S){
    static int D[maxN];static queue<int> Qu;
    memset(D,-1,sizeof(D));D[S]=0;Qu.push(S);int sum=0;
    while (!Qu.empty()){
	int u=Qu.front();Qu.pop();sum+=D[u];
	for (int i=0,sz=E[u].size();i<sz;i++) if (D[E[u][i]]==-1) D[E[u][i]]=D[u]+1,Qu.push(E[u][i]);
	for (int i=0,sz=G[u].size();i<sz;i++) if (D[G[u][i]]==-1) D[G[u][i]]=D[u]+1,Qu.push(G[u][i]);
    }
    return sum;
}
void Outp(){
    printf("%d\n",Ans);
    FILE *fout=fopen("road"NUM".out","w");
    for (int i=1;i<=K;i++) fprintf(fout,"%d %d\n",Ku[i],Kv[i]);
    fclose(fout);return;
}
