#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define mp make_pair
#define ft first
#define sd second
#define pb push_back

const int maxN=110;
const int maxM=1010;
const int maxL=32;

int n,W;
int F[maxL][maxM];
vector<pair<int,int> > Gd[maxL];
int Sum[maxL];

int main(){
    while (scanf("%d%d",&n,&W)!=EOF){
	if (n==-1&&W==-1) break;
	mem(F,0);mem(Sum,0);
	for (int i=0;i<maxL;i++) Gd[i].clear();

	int mxl=0;
	for (int i=1;i<=n;i++){
	    int a,b,cnt=0;scanf("%d%d",&a,&b);
	    while (!(a&1)) ++cnt,a>>=1;
	    //cout<<a<<" "<<cnt<<" "<<b<<endl;
	    mxl=max(mxl,cnt);
	    Gd[cnt].pb(mp(a,b));Sum[cnt]+=a;
	}

	for (int i=0;i<=mxl;i++)
	    for (int j=0,sz=Gd[i].size();j<sz;j++)
		for (int k=Sum[i];k>=Gd[i][j].ft;k--) F[i][k]=max(F[i][k],F[i][k-Gd[i][j].ft]+Gd[i][j].sd);

	while ((1<<(mxl+1))<=W) ++mxl;
	for (int i=1;i<=mxl;i++){
	    Sum[i]=Sum[i]+((Sum[i-1]+1)>>1);
	    for (int j=Sum[i];j>=0;j--)
		for (int k=0;k<=j;k++) F[i][j]=max(F[i][j],F[i][j-k]+F[i-1][min(k*2+((W>>(i-1))&1),Sum[i-1])]);
	}

	printf("%d\n",F[mxl][1]);
	//printf("%d\n",Ans);
    }
    return 0;
}
