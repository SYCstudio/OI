#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<iostream>
#include<cassert>
using namespace std;

#define mp make_pair
#define ft first
#define sd second
#define pb push_back
typedef long long ll;
const int maxN=202000;
const int Alpha=26;
const int Bit=20;

int L,na,nb,m,Al[maxN],Ar[maxN],Bl[maxN],Br[maxN];
char str[maxN];
int Ida[maxN],Idb[maxN],Idsi[maxN<<1],Idso[maxN<<1];
vector<pair<int,int> > Ra[maxN<<1],Rb[maxN<<1];

namespace SAM{
    class SAM{
    public:
	int son[Alpha],len,fail;
	void clear(){
	    memset(son,0,sizeof(son));len=fail=0;
	}
    };
    int scnt=0,lst,Pos[maxN<<1],Fa[Bit][maxN<<1];
    vector<int> Vt[maxN<<1];
    SAM S[maxN<<1];
    void Init();
    void Extend(int c);
    void dfs_build(int x);
}
namespace TPS{
    int tcnt=0,Key[maxN*6],Dg[maxN*6];
    ll F[maxN*6];
    vector<int> T[maxN*6];
    void Add_Edge(int u,int v);
    void Work();
}
using TPS::tcnt;
using TPS::Add_Edge;
using SAM::scnt;
using SAM::Fa;

int main(){
    int Case;scanf("%d",&Case);
    scnt=SAM::lst=1;
    while (Case--){
	scanf("%s",str+1);L=strlen(str+1);
	SAM::Init();
	scanf("%d",&na);for (int i=1;i<=na;i++) scanf("%d%d",&Al[i],&Ar[i]);
	scanf("%d",&nb);for (int i=1;i<=nb;i++) scanf("%d%d",&Bl[i],&Br[i]);

	for (int i=1;i<=na;i++) Ida[i]=++tcnt,TPS::Key[Ida[i]]=Ar[i]-Al[i]+1;
	for (int i=1;i<=nb;i++) Idb[i]=++tcnt;
	for (int i=1;i<=scnt;i++) Idsi[i]=++tcnt,Idso[i]=++tcnt;

	scanf("%d",&m);
	for (int i=1;i<=m;i++){
	    int x,y;scanf("%d%d",&x,&y);Add_Edge(Ida[x],Idb[y]);
	}
	for (int i=1;i<=na;i++){
	    int now=SAM::Pos[Al[i]],len=Ar[i]-Al[i]+1;
	    for (int j=Bit-1;j>=0;j--) if (Fa[j][now]&&SAM::S[Fa[j][now]].len>=len) now=Fa[j][now];
	    Ra[now].pb(mp(len,Ida[i]));
	}
	for (int i=1;i<=nb;i++){
	    int now=SAM::Pos[Bl[i]],len=Br[i]-Bl[i]+1;
	    for (int j=Bit-1;j>=0;j--) if (Fa[j][now]&&SAM::S[Fa[j][now]].len>=len) now=Fa[j][now];
	    Rb[now].pb(mp(len,Idb[i]));
	}
	SAM::dfs_build(1);
	TPS::Work();

	for (int i=1;i<=scnt;i++){
	    Ra[i].clear();Rb[i].clear();SAM::S[i].clear();
	    SAM::Vt[i].clear();SAM::Pos[i]=0;
	    for (int j=0;j<Bit;j++) Fa[j][i]=0;
	}
	scnt=SAM::lst=1;
	for (int i=1;i<=tcnt;i++){
	    TPS::Key[i]=TPS::Dg[i]=TPS::F[i]=0;TPS::T[i].clear();
	}
	tcnt=0;
    }
    return 0;
}
namespace SAM{
    void Init(){
	for (int i=L;i>=1;i--) Extend(str[i]-'a'),Pos[i]=lst;
	/*
	for (int i=1;i<=scnt;i++) cout<<S[i].fail<<" ";cout<<endl;
	for (int i=1;i<=scnt;i++)
	    for (int j=0;j<Alpha;j++)
		if (S[i].son[j]) cout<<i<<" "<<S[i].son[j]<<" "<<(char)(j+'a')<<endl;
	//*/
	for (int i=2;i<=scnt;i++) Vt[S[i].fail].pb(i),Fa[0][i]=S[i].fail;
	for (int i=1;i<Bit;i++) for (int j=1;j<=scnt;j++) Fa[i][j]=Fa[i-1][Fa[i-1][j]];
	return;
    }
    void Extend(int c){
	int np=++scnt,p=lst;lst=np;S[np].len=S[p].len+1;
	while (p&&S[p].son[c]==0) S[p].son[c]=np,p=S[p].fail;
	if (!p) S[np].fail=1;
	else{
	    int q=S[p].son[c];
	    if (S[q].len==S[p].len+1) S[np].fail=q;
	    else{
		int nq=++scnt;S[nq]=S[q];S[nq].len=S[p].len+1;S[q].fail=S[np].fail=nq;
		while (p&&S[p].son[c]==q) S[p].son[c]=nq,p=S[p].fail;
	    }
	}
	return;
    }
    void dfs_build(int x){
	Add_Edge(Idsi[x],Idso[x]);
	if (Ra[x].size()+Rb[x].size()){
	    int sz=Rb[x].size()-1;
	    sort(Rb[x].begin(),Rb[x].end());sort(Ra[x].begin(),Ra[x].end());
	    if (Rb[x].size()){
		Add_Edge(Idsi[x],Rb[x][0].sd);Add_Edge(Rb[x][sz].sd,Idso[x]);
	    }
	    int j=0,sa=Ra[x].size()-1;
	    while (j<=sa&& (Rb[x].size()==0||Ra[x][j].ft<Rb[x][0].ft) )
		Add_Edge(Idsi[x],Ra[x][j].sd),++j;
	    for (int i=0;i<=sz;i++){
		if (i+1<=sz) Add_Edge(Rb[x][i].sd,Rb[x][i+1].sd);
		while (j<=sa&&(i==sz||Ra[x][j].ft<Rb[x][i+1].ft))
		    Add_Edge(Rb[x][i].sd,Ra[x][j].sd),++j;
	    }
	}
	for (int i=0,sz=Vt[x].size();i<sz;i++) Add_Edge(Idso[x],Idsi[Vt[x][i]]),dfs_build(Vt[x][i]);
	return;
    }
}
namespace TPS{
    void Add_Edge(int u,int v){
	T[u].pb(v);return;
    }
    void Work(){
	for (int i=1;i<=tcnt;i++) for (int j=0,sz=T[i].size();j<sz;j++) ++Dg[T[i][j]];
	queue<int> Qu;
	for (int i=1;i<=tcnt;i++) if (Dg[i]==0) F[i]=Key[i],Qu.push(i);
	int tot=0;ll Ans=0;
	while (!Qu.empty()){
	    ++tot;int u=Qu.front();Qu.pop();Ans=max(Ans,F[u]);
	    for (int i=0,sz=T[u].size();i<sz;i++){
		F[T[u][i]]=max(F[T[u][i]],F[u]+Key[T[u][i]]);
		assert(Dg[T[u][i]]>=0);
		if ((--Dg[T[u][i]])==0) Qu.push(T[u][i]);
	    }
	}
	if (tot!=tcnt) puts("-1");else printf("%lld\n",Ans);
	return;
    }
}
