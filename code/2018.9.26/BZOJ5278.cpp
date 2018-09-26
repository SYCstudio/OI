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

class Data
{
public:
	int key,pos;
};

int n;
Data D[maxN];
int BIT[maxN];

bool cmp(Data A,Data B);
void Add(int pos);
int Query(int pos);

int main(){
	scanf("%d",&n);for (int i=1;i<=n;i++) scanf("%d",&D[i].key),D[i].pos=i;
	sort(&D[1],&D[n+1],cmp);
	int Ans=1;
	for (int i=1;i<=n;i++){
		Add(D[i].pos);Ans=max(Ans,i-Query(i));
	}
	printf("%d\n",Ans);return 0;
}

bool cmp(Data A,Data B){
	if (A.key!=B.key) return A.key<B.key;
	return A.pos<B.pos;
}

void Add(int pos){
	while (pos<=n){
		BIT[pos]++;pos+=(pos)&(-pos);
	}
	return;
}

int Query(int pos){
	int ret=0;
	while (pos){
		ret+=BIT[pos];pos-=(pos)&(-pos);
	}
	return ret;
}
