#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lowbit(x) ((x)&(-x))

const int maxN=101000;
const int inf=2147483647;

int n,Seq[maxN];
int numcnt,Num[maxN];
int BIT[maxN],F[maxN];

int GetMax(int pos);
void Modify(int pos,int key);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&Seq[i]),Num[i]=Seq[i]=-Seq[i];
	numcnt=n;
	sort(&Num[1],&Num[n+1]);numcnt=unique(&Num[1],&Num[n+1])-Num-1;

	int Mx=0;
	for (int i=n;i>=1;i--){
		int p=lower_bound(&Num[1],&Num[numcnt+1],Seq[i])-Num;//cout<<"p:"<<p<<endl;
		F[i]=GetMax(p-1)+1;
		Modify(p,F[i]);
		Mx=max(Mx,F[i]);
	}

	//for (int i=1;i<=n;i++) cout<<F[i]<<" ";cout<<endl;

	for (int i=1;i<=n;i++) Seq[i]=-Seq[i];

	int Q;scanf("%d",&Q);
	while (Q--){
		int k;scanf("%d",&k);
		if (k>Mx) printf("Impossible\n");
		else{
			for (int i=1,j=1,mn=-inf;(j<=k)&&(i<=n);i++)
				if ((F[i]+j-1>=k)&&(Seq[i]>mn)){
					printf("%d ",Seq[i]);mn=max(mn,Seq[i]);j++;
				}
			printf("\n");
		}
	}
	
	return 0;
}

int GetMax(int pos){
	int ret=0;
	while (pos){
		ret=max(ret,BIT[pos]);pos-=lowbit(pos);
	}
	return ret;
}

void Modify(int pos,int key){
	while (pos<=numcnt){
		BIT[pos]=max(BIT[pos],key);pos+=lowbit(pos);
	}
	return;
}
