#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=201000;
const int inf=2147483647;

class Data
{
public:
	int key,pos;
};

int n;
Data D[maxN];
int L[maxN],R[maxN];

bool cmp(Data A,Data B);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&D[i].key),D[i].pos=i;
	sort(&D[1],&D[n+1],cmp);
	int m=0;
	for (int i=1,j;i<=n;i=j+1){
		j=i;
		while ((j<n)&&(D[j+1].key==D[i].key)) j++;
		++m;L[m]=D[i].pos;R[m]=D[j].pos;
	}
	int Ans=1;
	for (int i=1,opt=1,h=inf;i<=m;i++)
		if (opt==1){
			if (h>R[i]) h=L[i];
			else opt^=1,h=R[i];
		}
		else{
			if (h<L[i]) h=R[i];
			else opt^=1,Ans++,h=L[i];
		}
	printf("%d\n",Ans);return 0;
}

bool cmp(Data A,Data B){
	if (A.key!=B.key) return A.key<B.key;
	return A.pos<B.pos;
}
/*
6
3 6 0 9 6 3
//*/
