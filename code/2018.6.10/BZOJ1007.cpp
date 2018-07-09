#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=50100;
const ld eps=1e-8;
const int inf=2147483647;

class Line
{
public:
	ld k,b;
	int id;
};

int n;
Line L[maxN],S[maxN];
bool ans[maxN];

bool cmp(Line A,Line B);
ld GetX(Line A,Line B);

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%LF%LF",&L[i].k,&L[i].b);
		L[i].id=i;
	}
	sort(&L[1],&L[n+1],cmp);

	int top=0;
	for (int i=1;i<=n;i++)
	{
		if ((i>=2)&&(L[i].k==L[i-1].k)) continue;
		while ((top>=2)&&(GetX(S[top-1],L[i])-eps<=GetX(S[top-1],S[top]))) top--;
		S[++top]=L[i];
	}
	for (int i=1;i<=top;i++) ans[S[i].id]=1;
	for (int i=1;i<=n;i++) if (ans[i]) printf("%d ",i);
	return 0;
}

bool cmp(Line A,Line B){
	if (A.k!=B.k) return A.k<B.k;
	else return A.b>B.b;
}

ld GetX(Line A,Line B){
	//cout<<"y="<<A.k<<"x+"<<A.b<<" y="<<B.k<<"x+"<<B.b<<endl;
	return (B.b-A.b)/(A.k-B.k);
}
