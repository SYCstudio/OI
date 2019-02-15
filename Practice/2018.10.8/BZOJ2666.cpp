#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10100;
const int maxM=101000;
const int inf=2147483647;

class Data
{
public:
	ld mid,pre,nxt;
};

int n,m;
int X[maxM],P[maxM],Lst[maxN];
Data D[maxM*10];

bool cmp(Data A,Data B);

int main(){
	scanf("%d%d",&n,&m);
	ld s=0,s2=0;
	int dcnt=0;
	for (int i=1;i<=m;i++){
		scanf("%d%d",&X[i],&P[i]);
		if (Lst[P[i]]!=0) D[++dcnt]=((Data){1.0*(X[i]+X[Lst[P[i]]])/2,X[Lst[P[i]]],X[i]});
		else s=s+X[i],s2=s2+(ld)1.0*X[i]*X[i];
		Lst[P[i]]=i;
	}
	sort(&D[1],&D[dcnt+1],cmp);
	ld ans=0,anskey=s2;
	for (int i=1;i<=dcnt;i++){
		s-=D[i].pre;s+=D[i].nxt;
		s2-=D[i].pre*D[i].pre;s2+=D[i].nxt*D[i].nxt;
		ld p=s/n;
		if (s2-2*p*s+p*p*n<anskey) anskey=s2-2*p*s+p*p*n,ans=p;
	}
	printf("%.4LF\n",ans);return 0;
}

bool cmp(Data A,Data B){
	return A.mid<B.mid;
}
