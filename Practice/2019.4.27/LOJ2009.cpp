#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

typedef long long ll;
#define ls(x) ((x)<<1)
#define rs(x) (ls(x)|1)
const int maxN=202000;
const int maxB=20;
const ll INF=1e18;

int n;
ll A[maxN],B[maxN],Len[maxN];
ll F[maxN][maxB],G[maxN][maxB];

int main(){
    scanf("%d",&n);for (int i=1;i<=n;i++) scanf("%lld",&A[i]);
    for (int i=2;i<=n;i++) scanf("%lld",&B[i]),Len[i]=Len[i>>1]+B[i];

    for (int i=n;i>=1;i--)
	for (int j=0;;j++){
	    if (ls(i)>n){
		F[i][j]=(Len[i]-Len[i>>j])*A[i>>j];
		G[i][j]=(Len[i]-Len[i>>(j+1)]+B[(i>>j)^1])*A[(i>>j)^1];
	    }
	    else if (rs(i)>n){
		F[i][j]=A[ls(i)]*B[ls(i)]+F[ls(i)][j+1];
		G[i][j]=A[ls(i)]*B[ls(i)]+G[ls(i)][j+1];
	    }
	    else{
		F[i][j]=A[ls(i)]*B[ls(i)]+G[ls(i)][0]+F[rs(i)][j+1];
		F[i][j]=min(F[i][j],A[rs(i)]*B[rs(i)]+G[rs(i)][0]+F[ls(i)][j+1]);
		G[i][j]=A[ls(i)]*B[ls(i)]+G[ls(i)][0]+G[rs(i)][j+1];
		G[i][j]=min(G[i][j],A[rs(i)]*B[rs(i)]+G[rs(i)][0]+G[ls(i)][j+1]);
	    }
	    if ((i>>j)==0) break;
	}
    /*
    for (int i=n;i>=1;i--){
	cout<<i<<endl;
	for (int j=0;;j++){
	    cout<<F[i][j]<<" ";if ((i>>j)==0) break;
	}cout<<endl;
	for (int j=0;;j++){
	    cout<<G[i][j]<<" ";if ((i>>j)==0) break;
	}cout<<endl;
    }
    //*/
    ll Ans=1e18;
    for (int i=1;i<=n;i++){
	ll sum=F[i][1];
	for (int now=i>>1,lst=i;now;lst=now,now>>=1)
	    if ((lst^1)>n) sum=sum+A[now>>1]*B[now];
	    else sum=sum+A[lst^1]*B[lst^1]+F[lst^1][2];
	//cout<<i<<":"<<sum<<endl;
	Ans=min(Ans,sum);
    }
    printf("%lld\n",Ans);return 0;
}
