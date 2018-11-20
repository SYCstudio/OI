#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int inf=2147483647;

int n;
int Pos[maxN],Input[maxN];
int BIT[maxN];
int S[maxN<<2];

void Plus(int pos,int key);
int Sum(int pos);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&Input[i]),++Input[i];
	for (int i=n;i>=1;i--){
		Pos[i]=Input[i]+Sum(Input[i]);
		Plus(Input[i],1);
	}
	for (int i=1;i<=n;i++) cout<<Pos[i]<<" ";cout<<endl;
}

void Plus(int pos,int key){
	while (pos<=n){
		BIT[pos]+=key;pos+=(pos)&(-pos);
	}
	return;
}

int Sum(int pos){
	int ret=0;
	while (pos){
		ret+=BIT[pos];pos-=(pos)&(-pos);
	}
	return ret;
}
