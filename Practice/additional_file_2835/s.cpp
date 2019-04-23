#include<bits/stdc++.h>
using namespace std;

#define Case "6"
#define ft first
#define sd second
#define mp make_pair
const int maxN=1300;

int n,K,W0;
vector<int> E[maxN],Nw[maxN];
int Ans,Ku[maxN],Kv[maxN];
int Dt[maxN];

int random(int l,int r);
int Dst(int S);
int Sum();
void Outp();
pair<int,int> GetH();
int main(){
    freopen("road"Case".in","r",stdin);
    srand(time(0));
    scanf("%d%d%d",&n,&K,&W0);
    for (int i=1;i<n;i++){
	int u,v;scanf("%d%d",&u,&v);
	E[u].push_back(v);E[v].push_back(u);
    }
    for (int i=1;i<=K;i++) Ku[i]=random(1,n),Kv[i]=random(1,n);
    for (int i=1;i<=K;i++){
	pair<int,int> p=GetH();
	Ku[i]=p.ft;Kv[i]=p.sd;
    }
    Ans=Sum();Outp();
    while (1){
	int opt=random(1,100),id=random(1,K),u=Ku[id],v=Kv[id];
	Ku[id]=random(1,n);Kv[id]=random(1,n);
	int s=Sum();//printf("%d--%d\n",Ans,s);
	if (s<Ans){
	    Outp();Ans=s;
	}
	else Ku[id]=u,Kv[id]=v;
    }
    return 0;
}
int random(int l,int r){
    double dou=1.0*rand()/RAND_MAX;
    return min(r,(int)(dou*(r-l+1))+l);
}
int Dst(int S){
    static queue<int> Qu;
    memset(Dt,-1,sizeof(Dt));while (!Qu.empty()) Qu.pop();
    Dt[S]=0;Qu.push(S);int ret=0;
    while (!Qu.empty()){
	int u=Qu.front();Qu.pop();ret+=Dt[u];
	for (int i=0,sz=E[u].size();i<sz;i++)
	    if (Dt[E[u][i]]==-1){
		Dt[E[u][i]]=Dt[u]+1;Qu.push(E[u][i]);
	    }
	for (int i=0,sz=Nw[u].size();i<sz;i++)
	    if (Dt[Nw[u][i]]==-1){
		Dt[Nw[u][i]]=Dt[u]+1;Qu.push(Nw[u][i]);
	    }
    }
    return ret;
}
int Sum(){
    for (int i=1;i<=n;i++) Nw[i].clear();
    for (int i=1;i<=K;i++) Nw[Ku[i]].push_back(Kv[i]),Nw[Kv[i]].push_back(Ku[i]);
    int sum=0;for (int i=1;i<=n;i++) sum=sum+Dst(i);return sum;
}
pair<int,int> GetH(){
    int a=1,b=1,d=0;
    for (int i=1;i<=n;i++){
	Dst(i);
	for (int j=1;j<=n;j++) if (Dt[j]>d) d=Dt[j],a=i,b=j;
    }
    return make_pair(a,b);
}
void Outp(){
    FILE *fout;
    fout=fopen("road"Case".out","w");
    for (int i=1;i<=K;i++) fprintf(fout,"%d %d\n",Ku[i],Kv[i]);
    fclose(fout);
    printf("%d\n",Ans);
    return;
}
