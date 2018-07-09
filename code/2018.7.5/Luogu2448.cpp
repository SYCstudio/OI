#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define find(x) (lower_bound(&Num[1],&Num[numcnt+1],x)-Num)
#define lowbit(x) ((x)&(-x))

const int maxN=101000;
const int inf=2147483647;

class Option
{
public:
	int x,y;
};

int K;
int numcnt=0,Num[maxN],A[maxN],BIT[maxN];
Option O[maxN];

void Add(int pos,int key);
int Sum(int pos);
int Query(int l,int r);

int main()
{
	scanf("%d",&K);
	for (int i=1;i<=K;i++)
	{
		scanf("%d%d",&O[i].x,&O[i].y);
		Num[++numcnt]=O[i].x;Num[++numcnt]=O[i].y;
	}

	sort(&Num[1],&Num[numcnt+1]);numcnt=unique(&Num[1],&Num[numcnt+1])-Num-1;

	for (int i=1;i<=K;i++) O[i].x=find(O[i].x),O[i].y=find(O[i].y);

	for (int i=1;i<=numcnt;i++) A[i]=i;
	for (int i=1;i<=K;i++) swap(A[O[i].x],A[O[i].y]);

	ll Ans=0;
	for (int i=1;i<=numcnt;i++)
	{
		Ans+=1ll*Query(A[i]+1,numcnt);
		Add(A[i],1);
	}

	for (int i=1;i<=numcnt;i++)
		if (i!=A[i])
		{
			Ans=Ans+abs(Num[i]-Num[A[i]]);
			Ans=Ans-abs(i-A[i]);
		}
	printf("%lld\n",Ans);
	return 0;
}

void Add(int pos,int key){
	while (pos<=numcnt){
		BIT[pos]+=key;pos+=lowbit(pos);
	}
	return;
}

int Sum(int pos){
	int ret=0;
	while (pos){
		ret+=BIT[pos];pos-=lowbit(pos);
	}
	return ret;
}

int Query(int l,int r){
	return Sum(r)-Sum(l-1);
}
