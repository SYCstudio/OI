#include"library.h"
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

const int maxN=1010;
int N,Sm[maxN];
vector<int> Ans,T[maxN];

int GET(int mid,int x);
void dfs_outp(int u,int fa);
void Solve(int n){
    N=n;
    if (N==1){
	Ans.push_back(1);Answer(Ans);return;
    }
    for (int i=0;i<N;i++) Sm[i]=GET(i,i);
    //for (int i=0;i<N;i++) cout<<Sm[i]<<" ";cout<<endl;

    for (int i=0;i<N;i++){
	int l=0,r=i-1,pl=-1;
	while (l<=r){
	    int mid=(l+r)>>1;
	    if (GET(mid,i)<=Sm[mid]) pl=mid,r=mid-1;
	    else l=mid+1;
	}
	if (pl==-1) continue;
	//cout<<"pl:"<<i<<" "<<pl<<endl;
	T[i].push_back(pl);T[pl].push_back(i);
	l=pl+1;r=i-1;int pr=-1;
	while (l<=r){
	    int mid=(l+r)>>1;
	    if (GET(mid,i)<Sm[mid]) pr=mid,r=mid-1;
	    else l=mid+1;
	}
	if (pr==-1) continue;
	//cout<<"pr:"<<i<<" "<<pr<<endl;
	T[i].push_back(pr);T[pr].push_back(i);
    }
    for (int i=0;i<N;i++)
	if (T[i].size()==1){
	    dfs_outp(i,i);break;
	}
    Answer(Ans);return;
}
int GET(int mid,int x){
    vector<int> Q;Q.resize(N);
    for (int i=0;i<N;i++) if (i<=mid) Q[i]=1;else Q[i]=0;
    Q[x]=1;return Query(Q);
}
void dfs_outp(int u,int fa){
    Ans.push_back(u+1);
    for (int i=0;i<T[u].size();i++) if (T[u][i]!=fa) dfs_outp(T[u][i],u);
    return;
}
