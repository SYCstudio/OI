#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
#include<assert.h>
using namespace std;

const int maxN=100100*2;
const int maxKey=50000;
const int Alpha=26;
const int Mod=998244353;

class SegmentData{
public:
    int ls,rs,sum,nx,cov;
    SegmentData(){
	cov=-1;return;
    }
};

int n,Pos[maxN];
vector<pair<int,int> > T[maxN];
int rt[maxN][Alpha],mxlen[maxN][Alpha],FIST,Ans[maxN],nodecnt;
SegmentData S[maxN*40];

int Calc(int l,int r);
void dfs(int u,int d,int len);
void Cover(int x,int l,int r,int strt);
void PushDown(int x,int l,int r);
void Update(int x);
void Modify(int &x,int l,int r,int limit,int id,int strt);
int Query(int x,int l,int r,int limit,int &nxt);

int main(){
    scanf("%d",&n);int now=1,ncnt=1;Pos[0]=now;
    for (int i=1;i<=n;i++){
	int opt;scanf("%d",&opt);
	if (opt==1){
	    int x;char c;scanf("%d %c",&x,&c);
	    T[now].push_back(make_pair(++ncnt,(c-'a')*maxKey+x));
	    now=ncnt;
	}
	else{
	    int x;scanf("%d",&x);now=Pos[x];
	}
	Pos[i]=now;
    }
    dfs(1,0,0);for (int i=1;i<=n;i++) printf("%d\n",Ans[Pos[i]]);
    return 0;
}
int Calc(int l,int r){
    if (l>r) return 0;
    return (1ll*(l+r)*(r-l+1)/2ll)%Mod;
}

void dfs(int u,int d,int len){
    //cout<<"dfs at:"<<u<<" "<<d<<" "<<len<<endl;
    for (int i=0,sz=T[u].size();i<sz;i++){
	int v=T[u][i].first,c=T[u][i].second/maxKey,l=T[u][i].second%maxKey,nxt=0;
	Ans[v]=Ans[u];
	if (d==0) FIST=T[u][i].second,Ans[v]=(Ans[v]+Calc(1,l-1))%Mod,nxt=0;
	else{
	    Ans[v]=(Ans[v]+Query(rt[d][c],1,maxKey,l,nxt))%Mod;
	    if (nxt==0&&l>mxlen[d][c]&&FIST/maxKey==c) Ans[v]=(Ans[v]+1ll*(FIST%maxKey)*(l-mxlen[d][c])%Mod)%Mod;
	    if (nxt==0&&FIST/maxKey==c&&FIST%maxKey<=l) nxt=1;
	}
	//cerr<<c<<" "<<l<<endl;
	//cout<<u<<" "<<d<<" "<<len<<" "<<nxt<<" ("<<(char)(c+'a')<<" "<<l<<")"<<" "<<Ans[v]<<endl;
	int prert=rt[d][c],prelen=mxlen[d][c];mxlen[d][c]=max(mxlen[d][c],l);
	memcpy(rt[d+1],rt[nxt],sizeof(rt[nxt]));memcpy(mxlen[d+1],mxlen[nxt],sizeof(mxlen[nxt]));
	Modify(rt[d][c],1,maxKey,l,d+1,len+1);
	dfs(v,d+1,(len+l)%Mod);
	rt[d][c]=prert;mxlen[d][c]=prelen;
    }
    return;
}//*/
void Cover(int x,int l,int r,int strt){
    S[x].sum=Calc(strt,strt+r-l);S[x].cov=strt;return;
}
void PushDown(int x,int l,int r){
    if (S[x].cov!=-1){
	int mid=(l+r)>>1;
	S[++nodecnt]=S[S[x].ls];S[x].ls=nodecnt;
	S[++nodecnt]=S[S[x].rs];S[x].rs=nodecnt;
	Cover(S[x].ls,l,mid,S[x].cov);
	Cover(S[x].rs,mid+1,r,S[x].cov+mid-l+1);
	S[x].cov=-1;
    }
    return;
}
void Update(int x){
    S[x].sum=(S[S[x].ls].sum+S[S[x].rs].sum)%Mod;
    return;
}
void Modify(int &x,int l,int r,int limit,int id,int strt){
    S[++nodecnt]=S[x];x=nodecnt;
    if (l==r){
	S[x].sum=strt;S[x].nx=id;return;
    }
    int mid=(l+r)>>1;PushDown(x,l,r);
    if (limit<=mid) Modify(S[x].ls,l,mid,limit,id,strt);
    else S[++nodecnt]=S[S[x].ls],S[x].ls=nodecnt,Cover(S[x].ls,l,mid,strt),Modify(S[x].rs,mid+1,r,limit,id,strt+mid-l+1);
    Update(x);return;
}
int Query(int x,int l,int r,int limit,int &nxt){
    //cerr<<"Q:"<<x<<" "<<l<<" "<<r<<endl;
    if (l==r){
	nxt=S[x].nx;return S[x].sum;
    }
    int mid=(l+r)>>1;PushDown(x,l,r);
    if (limit<=mid) return Query(S[x].ls,l,mid,limit,nxt);
    else return (S[S[x].ls].sum+Query(S[x].rs,mid+1,r,limit,nxt))%Mod;
}
