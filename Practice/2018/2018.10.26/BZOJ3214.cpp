#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define find(x) (lower_bound(&Num[1],&Num[num+1],x)-Num)

const int maxN=3010000;
const int inf=100000000;

char Input[maxN];
int Sq[maxN],A[maxN],B[maxN],C[maxN];
int F[maxN],G[maxN];
int num,Num[maxN];
int Head[maxN],Next[maxN];

void GetIn(int *P,int &L);

int main(){
	//freopen("in","r",stdin);
	int l1,l2,l3,l4;
	GetIn(Sq,l1);GetIn(A,l2);GetIn(B,l3);GetIn(C,l4);
	for (int i=1;i<=l1;i++) Num[++num]=Sq[i];
	for (int i=1;i<=l2;i++) Num[++num]=A[i];
	for (int i=1;i<=l3;i++) Num[++num]=B[i];
	for (int i=1;i<=l4;i++) Num[++num]=C[i];
	sort(&Num[1],&Num[num+1]);num=unique(&Num[1],&Num[num+1])-Num-1;
	for (int i=1;i<=l1;i++) Sq[i]=find(Sq[i]);
	for (int i=1;i<=l2;i++) A[i]=find(A[i]);
	for (int i=1;i<=l3;i++) B[i]=find(B[i]);
	for (int i=1;i<=l4;i++) C[i]=find(C[i]);

	//cout<<l1<<" "<<l2<<" "<<l3<<" "<<l4<<endl;
	/*
	for (int i=1;i<=l1;i++) cout<<Sq[i]<<" ";cout<<endl;
	for (int i=1;i<=l2;i++) cout<<A[i]<<" ";cout<<endl;
	for (int i=1;i<=l3;i++) cout<<B[i]<<" ";cout<<endl;
	for (int i=1;i<=l4;i++) cout<<C[i]<<" ";cout<<endl;
	//*/

	int pl=1,pr=l1,cnt=2;
	for (int i=1;i<=l2;i++)	while ((pl<=l1)&&(Sq[pl]!=A[i])) ++pl,++cnt;
	for (int i=l4;i>=1;i--) while ((pr>=1)&&(Sq[pr]!=C[i])) --pr,++cnt;
	cnt=cnt-l2-l4;

	//cout<<pl<<" "<<pr<<" "<<cnt<<endl;

	for (int i=1;i<=l3;i++){
		Next[i]=Head[B[i]];Head[B[i]]=i;
		G[i]=inf;
	}

	int Ans=inf;
	for (int i=pl+1;i<pr;i++){
		for (int j=Head[Sq[i]];j;j=Next[j]){
			if (j==1) F[j]=i,G[j]=0;
			else G[j]=G[j-1]+(i-F[j-1]-1),F[j]=i;
			Ans=min(Ans,G[l3]);
		}
		//cout<<i<<endl;
		//for (int j=1;j<=l3;j++) cout<<F[j]<<" ";cout<<endl;
		//for (int j=1;j<=l3;j++) cout<<G[j]<<" ";cout<<endl;
	}
	printf("%d\n",Ans+cnt);return 0;
}

void GetIn(int *P,int &L){
	char ch=getchar();int key=0;L=0;
	while (ch!='\n'){
		if ((ch>='a')&&(ch<='z')) key=key*27+ch-'a'+1;
		else P[++L]=key,key=0;
		ch=getchar();
	}
	if (key) P[++L]=key;return;
}
