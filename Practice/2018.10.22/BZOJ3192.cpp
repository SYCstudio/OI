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

int n1,n2;
int Seq[maxN],Id[maxN];
int BIT[maxN];

bool cmp(int a,int b);
void Add(int pos,int key);
int Sum(int pos);
int Query(int l,int r);

int main(){
	scanf("%d%d",&n1,&n2);
	for (int i=1;i<=n1+n2;i++) scanf("%d",&Seq[i]),Id[i]=i;
	reverse(&Seq[1],&Seq[n1+1]);
	sort(&Id[1],&Id[n1+n2+1],cmp);
	ll Ans=0;
	if (Id[1]<=n1) Ans=n1-Id[1];
	else Ans=Id[1]-n1-1;
	for (int i=1;i<=n1+n2;i++) if (i!=Id[1]) Add(i,1);
	int p=Id[1];
	for (int i=2;i<=n1+n2;i++){
		//cout<<Ans<<endl;
		if (p<Id[i]) Ans=Ans+Query(p,Id[i]-1);
		else Ans=Ans+Query(Id[i]+1,p);
		Add(Id[i],-1);p=Id[i];
	}
	printf("%lld\n",Ans);return 0;
}

bool cmp(int a,int b){
	return Seq[a]>Seq[b];
}

void Add(int pos,int key){
	while (pos<=n1+n2){
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

int Query(int l,int r){
	return Sum(r)-Sum(l-1);
}
