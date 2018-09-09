#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=12;
const int maxM=500100;
const int inf=2147483647;

int n,m,Q;
int W[maxN];
char Input[maxN+5];
ll Cnt[(1<<maxN)+5],Id[(1<<maxN)+5],Di[(1<<maxN)+5];
ll F[(1<<maxN)+2][(1<<maxN)+2],Sum[(1<<maxN)+2];

bool cmp(int a,int b);

int main(){
	scanf("%d%d%d",&n,&m,&Q);
	for (int i=0;i<n;i++) scanf("%d",&W[i]);
	for (int i=1;i<=m;i++){
		scanf("%s",Input);
		int key=0;for (int j=0;j<n;j++) key=key|((Input[j]-'0')<<j);
		Cnt[key]++;
	}

	for (int S=0;S<(1<<n);S++) for (int i=0;i<n;i++) if ((S&(1<<i))) Sum[S]+=W[i];

	//for (int i=0;i<(1<<n);i++) cout<<Sum[i]<<" ";cout<<endl;
	
	for (int S=0;S<(1<<n);S++) Id[S]=S;

	sort(&Id[0],&Id[(1<<n)],cmp);
	for (int S=0;S<(1<<n);S++) Di[Id[S]]=S;

	for (int i=0;i<(1<<n);i++) for (int j=0;j<(1<<n);j++) F[i][Di[((1<<n)-1)^i^j]]=Cnt[j];
	for (int i=0;i<(1<<n);i++) for (int j=1;j<(1<<n);j++) F[i][j]+=F[i][j-1];

	sort(&Sum[0],&Sum[(1<<n)]);

	//for (int i=0;i<(1<<n);i++) cout<<Sum[i]<<" ";cout<<endl;

	while (Q--){
		scanf("%s",Input);
		int key=0;for (int i=0;i<n;i++) key=key|((Input[i]-'0')<<i);
		int k;scanf("%d",&k);
		if (k<Sum[0]){
			printf("0\n");continue;
		}
		int L=0,R=(1<<n)-1,p=0;
		while (L<=R){
			int mid=(L+R)>>1;
			if (Sum[mid]<=k) p=mid,L=mid+1;
			else R=mid-1;
		}

		printf("%lld\n",F[key][p]);
	}

	return 0;
}

bool cmp(int a,int b){
	return Sum[a]<Sum[b];
}
