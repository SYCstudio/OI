#include<bits/stdc++.h>
using namespace std;

const int maxN=1010000;

class SegmentData{
public:
    int lz,mx;
};

int n,K,seq[maxN],st[maxN];
vector<int> T[maxN];
int dfncnt,dfn[maxN],rht[maxN];
SegmentData S[maxN<<2];

void dfs(int u);
void PushDown(int x);
void Modify(int x,int l,int r,int ql,int qr,int key);
int Query(int x,int l,int r,int ql,int qr);
int main(){
    scanf("%d%d",&n,&K);for (int i=1;i<=n;i++) scanf("%d",&seq[i]);
    for (int i=n,top=0;i>=1;i--){
	while (top&&seq[st[top]]<=seq[i]) --top;
	T[st[top]].push_back(i);st[++top]=i;
	//cout<<i<<":";
	//for (int j=1;j<=top;j++) cout<<seq[st[j]]<<" ";cout<<endl;
    }//cout<<endl;
    dfs(0);
    //for (int i=1;i<=n;i++) cout<<dfn[i]<<" "<<rht[i]<<endl;
    for (int i=1;i<K;i++) Modify(1,1,n,dfn[i],rht[i],1);
    for (int i=1;i+K-1<=n;i++){
	Modify(1,1,n,dfn[i+K-1],rht[i+K-1],1);
	printf("%d ",Query(1,1,n,1,n));
	Modify(1,1,n,dfn[i],rht[i],-1);
    }
    return 0;
}
void dfs(int u){
    if (u) dfn[u]=++dfncnt;
    for (int i=0;i<T[u].size();i++) dfs(T[u][i]);
    rht[u]=dfncnt;return;
}
#define ls (x<<1)
#define rs (ls|1)
void PushDown(int x){
    if (S[x].lz){
	S[ls].mx+=S[x].lz;S[ls].lz+=S[x].lz;
	S[rs].mx+=S[x].lz;S[rs].lz+=S[x].lz;
	S[x].lz=0;return;
    }
}
void Modify(int x,int l,int r,int ql,int qr,int key){
    if (l==ql&&r==qr){
	S[x].lz+=key;S[x].mx+=key;return;
    }
    int mid=(l+r)>>1;PushDown(x);
    if (qr<=mid) Modify(ls,l,mid,ql,qr,key);
    else if (ql>=mid+1) Modify(rs,mid+1,r,ql,qr,key);
    else Modify(ls,l,mid,ql,mid,key),Modify(rs,mid+1,r,mid+1,qr,key);
    S[x].mx=max(S[ls].mx,S[rs].mx);return;
}
int Query(int x,int l,int r,int ql,int qr){
    if (l==ql&&r==qr) return S[x].mx;
    int mid=(l+r)>>1;PushDown(x);
    if (qr<=mid) return Query(ls,l,mid,ql,qr);
    else if (ql>=mid+1) return Query(rs,mid+1,r,ql,qr);
    else return max(Query(ls,l,mid,ql,mid),Query(rs,mid+1,r,mid+1,qr));
}
