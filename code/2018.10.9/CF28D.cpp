#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define NAME "european"

const int maxN=201000;
const int maxM=201000;
const int inf=2147483647;

int n;
int W[maxN],P[maxN],L[maxN],R[maxN],F[maxN],Path[maxN];
int num,Num[maxN+maxN];
int scnt,Seq[maxN];
map<int,pair<int,int> > Mp[maxN+maxN];

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d%d%d%d",&W[i],&P[i],&L[i],&R[i]);
	
	for (int i=1;i<=n;i++) Num[++num]=L[i],Num[++num]=L[i]+P[i];
	sort(&Num[1],&Num[num+1]);num=unique(&Num[1],&Num[num+1])-Num-1;

	mem(F,-127);
	for (int i=1;i<=n;i++) if (L[i]==0) F[i]=0,Path[i]=0;

	for (int i=1;i<=n;i++){
		//cerr<<i<<endl;
		int k=lower_bound(&Num[1],&Num[num],L[i])-Num;
		if (Mp[k].find(R[i]+P[i])!=Mp[k].end()){
			F[i]=Mp[k][R[i]+P[i]].first;Path[i]=Mp[k][R[i]+P[i]].second;
		}
		if (F[i]==F[0]) continue;
		F[i]=F[i]+W[i];
		k=lower_bound(&Num[1],&Num[num],L[i]+P[i])-Num;
		if (F[i]>Mp[k][R[i]].first) Mp[k][R[i]]=make_pair(F[i],i);
	}

	int anspos=0;
	for (int i=1;i<=n;i++) if ((R[i]==0)&&(F[i]>F[anspos])) anspos=i;
	if (anspos==0){
		printf("0\n");return 0;
	}
	//printf("%d\n",F[anspos]);
	while (anspos) Seq[++scnt]=anspos,anspos=Path[anspos];
	printf("%d\n",scnt);
	for (int i=scnt;i>=1;i--) printf("%d ",Seq[i]);printf("\n");
	return 0;
}
