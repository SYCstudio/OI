#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=50010;
const int maxM=200100;
const int maxColor=1000100;
const int inf=2147483647;

class Data
{
public:
	int l,r,id;
	int Ans;
};

int n,m,Ans;
int Belong[maxN];
Data Q[maxM];
int Color[maxN],Sum[maxColor];

bool cmp1(Data A,Data B);
bool cmp2(Data A,Data B);
void Move(int pos,int opt);

int main()
{
	scanf("%d",&n);int size=sqrt(n);
	for (int i=1;i<=n;i++) scanf("%d",&Color[i]),Belong[i]=(i-1)/size+1;
	scanf("%d",&m);
	for (int i=1;i<=m;i++) scanf("%d%d",&Q[i].l,&Q[i].r),Q[i].id=i;
	sort(&Q[1],&Q[m+1],cmp1);
	int l=1,r=0;
	for (int i=1;i<=m;i++)
	{
		while (l<Q[i].l) Move(l,-1),l++;
		while (l>Q[i].l) Move(l-1,1),l--;
		while (r<Q[i].r) Move(r+1,1),r++;
		while (r>Q[i].r) Move(r,-1),r--;
		Q[i].Ans=Ans;
	}
	sort(&Q[1],&Q[m+1],cmp2);
	for (int i=1;i<=m;i++) printf("%d\n",Q[i].Ans);
	return 0;
}

bool cmp1(Data A,Data B)
{
	if (Belong[A.l]==Belong[B.l]) return A.r<B.r;
	return A.l<B.l;
}


bool cmp2(Data A,Data B)
{
	return A.id<B.id;
}

void Move(int pos,int opt)
{
	if (Sum[Color[pos]]) Ans--;
	Sum[Color[pos]]+=opt;
	if (Sum[Color[pos]]) Ans++;
	return;
}
