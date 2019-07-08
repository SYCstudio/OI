#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;

#define ls (x<<1)
#define rs (ls|1)
const int maxN=505000;

int n,Q,Key[maxN];
int Mx[maxN<<2],Cnt[maxN<<2],Pos[maxN];
set<int> Lf[maxN];

void Build(int x,int l,int r);
void Update(int x);
void Modify(int p);

int main()
{
	scanf("%d%d",&n,&Q);
	for (int i=1; i<=n; i++) scanf("%d",&Key[i]),Lf[Key[i]].insert(i);
	Build(1,1,n);
	while (Q--) {
		int pos,key;
		scanf("%d%d",&pos,&key);
		Lf[Key[pos]].erase(pos);
		Modify(Key[pos]);
		Key[pos]=key;
		Lf[key].insert(pos);
		Modify(key);
		printf("%d\n",Mx[1]);
	}
	return 0;
}

void Build(int x,int l,int r)
{
	if (l==r) {
		Pos[l]=x;
		Cnt[x]=Lf[l].size();
		if (Lf[l].empty()) Mx[x]=-Cnt[x];
		else Mx[x]=*(Lf[l].rbegin())-Cnt[x];
		return;
	}
	int mid=(l+r)>>1;
	Build(ls,l,mid);
	Build(rs,mid+1,r);
	Update(x);
	return;
}
void Update(int x)
{
	Cnt[x]=Cnt[ls]+Cnt[rs];
	Mx[x]=max(Mx[ls],Mx[rs]-Cnt[ls]);
	return;
}
void Modify(int p)
{
	int x=Pos[p];
	Cnt[x]=Lf[p].size();
	if (Lf[p].empty()) Mx[x]=-Cnt[x];
	else Mx[x]=*(Lf[p].rbegin())-Cnt[x];
	x>>=1;
	while (x) {
		Update(x);
		x>>=1;
	}
	return;
}