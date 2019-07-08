#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<iostream>
using namespace std;

const int maxN=202000;

int n,m,Seq[maxN],Lft[maxN],Rht[maxN],Del[maxN];
priority_queue<pair<int,int> > H;

int main()
{
	scanf("%d%d",&n,&m);
	if (m>n/2) {
		printf("Error!\n");
		return 0;
	}
	for (int i=1; i<=n; i++) scanf("%d",&Seq[i]),H.push(make_pair(Seq[i],i));
	for (int i=1; i<=n; i++) Lft[i]=i-1,Rht[i]=i+1;
	Rht[n]=1;
	Lft[1]=n;
	int Ans=0;
	while (m--) {
		while (Del[H.top().second]) H.pop();
		int p=H.top().second;
		H.pop();
		//cout<<p<<" "<<Seq[p]<<endl;
		Ans+=Seq[p];
		Seq[p]=Seq[Lft[p]]+Seq[Rht[p]]-Seq[p];
		Del[Lft[p]]=Del[Rht[p]]=1;
		Lft[p]=Lft[Lft[p]];
		Rht[p]=Rht[Rht[p]];
		Rht[Lft[p]]=p;
		Lft[Rht[p]]=p;
		H.push(make_pair(Seq[p],p));
	}
	printf("%d\n",Ans);
	return 0;
}