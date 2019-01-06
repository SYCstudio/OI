#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=210;
const int maxL=101000;
const ll INF=1e17;

int n,m;
ll Dt[maxN],Tr[maxN][maxN],Bp[maxN][maxN];
char Input[maxN][maxL];
int Next[maxN][maxL];

void GetNext(int id);
int GetLen(int pre,int suf);
void Mul1();
void Mul2();

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%s",Input[i]+1),GetNext(i);
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) Tr[i][j]=strlen(Input[j]+1)-GetLen(i,j);
	for (int i=1;i<=n;i++) Dt[i]=strlen(Input[i]+1);
	/*
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++)
			cout<<Tr[i][j]<<" ";
		cout<<endl;
	}
	//*/
	m--;
	while (m){
		if (m&1) Mul1();
		Mul2();m>>=1;
	}
	ll Ans=INF;
	for (int i=1;i<=n;i++) Ans=min(Ans,Dt[i]);
	printf("%lld\n",Ans);return 0;
}

void GetNext(int id){
	int len=strlen(Input[id]+1);
	Next[id][1]=Next[id][0]=0;
	for (int i=2,j=0;i<=len;i++){
		while ((j)&&(Input[id][j+1]!=Input[id][i])) j=Next[id][j];
		if (Input[id][j+1]==Input[id][i]) ++j;
		Next[id][i]=j;
	}
	return;
}
int GetLen(int pre,int suf){
	int len=strlen(Input[pre]+1),j=0;
	for (int i=1;i<=len;i++){
		while ((j)&&(Input[pre][i]!=Input[suf][j+1])) j=Next[suf][j];
		if (Input[pre][i]==Input[suf][j+1]) ++j;
	}
	if (j==strlen(Input[suf]+1)) j=Next[suf][j];
	return j;
}
void Mul1(){
	for (int i=1;i<=n;i++) Bp[0][i]=Dt[i],Dt[i]=INF;
	for (int j=1;j<=n;j++)
		for (int k=1;k<=n;k++)
			Dt[j]=min(Dt[j],Bp[0][k]+Tr[k][j]);
	return;
}
void Mul2(){
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) Bp[i][j]=Tr[i][j],Tr[i][j]=INF;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			for (int k=1;k<=n;k++)
				Tr[i][j]=min(Tr[i][j],Bp[i][k]+Bp[k][j]);
	return;
}
