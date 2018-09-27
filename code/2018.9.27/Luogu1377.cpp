#include<iostream>
#include<cstdio>
#include<cstring>
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

class Tree
{
public:
	int key,o,ls,rs;
};

int n,St[maxN];
Data D[maxN];
Tree T[maxN];

bool cmp(Data A,Data B);
void outp(int u);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&D[i].key),D[i].pos=i;
	sort(&D[1],&D[n+1],cmp);

	int top=1;T[1].key=D[1].pos;T[1].o=D[1].key;St[1]=1;
	for (int i=2;i<=n;i++){
		T[i].key=D[i].pos;T[i].o=D[i].key;
		int lst=0;
		while ((top>0)&&(D[i].pos<T[St[top]].key)) lst=St[top--];
		if (top) T[St[top]].rs=i;
		if (lst) T[i].ls=lst;
		St[++top]=i;
	}
	outp(St[1]);printf("\n");
	return 0;
}

bool cmp(Data A,Data B){
	return A.key<B.key;
}

void outp(int u){
	printf("%d ",T[u].o);
	if (T[u].ls) outp(T[u].ls);
	if (T[u].rs) outp(T[u].rs);
}
