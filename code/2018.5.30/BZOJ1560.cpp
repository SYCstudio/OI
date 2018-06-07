#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll int
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=201000;
const int maxM=1010;
const int inf=1047483647;
const ll INF=inf;

class Loc
{
public:
	ll x,y,val;
};

int n,m;
Loc P[maxN];
ll F[maxN],Pos[maxM];

bool cmp(Loc A,Loc B);
ll Dis(int id1,int id2);

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d%d%d",&P[i].x,&P[i].y,&P[i].val);
	//P[++n]=((Loc){1,1,0});
	//P[++n]=((Loc){m,m,0});

	sort(&P[1],&P[n+1],cmp);

	//for (int i=1;i<=n;i++) cout<<"("<<P[i].x<<","<<P[i].y<<") "<<P[i].val<<endl;
	
	Pos[1]=1;F[1]=P[1].val;

	for (int i=2;i<=n;i++)
	{
		ll p=-INF;
		for (int j=1;j<=P[i].y;j++)
			if (Pos[j])
				p=max(p,F[Pos[j]]-Dis(i,Pos[j]));
		F[i]=p+P[i].val;Pos[P[i].y]=i;
	}
	printf("%d\n",F[n]);
	return 0;
}

bool cmp(Loc A,Loc B){
	if (A.x!=B.x) return A.x<B.x;
	return A.y<B.y;
}

ll Dis(int id1,int id2){
	return (P[id1].x-P[id2].x)*(P[id1].x-P[id2].x)+(P[id1].y-P[id2].y)*(P[id1].y-P[id2].y);
}
