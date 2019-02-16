#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100010;
const int maxK=21;
const int inf=2147483647;

int n,K;
int Num[maxN];
ll F[maxK][maxN];
ll Cnt[maxN];
int ML,MR;
ll sum;

ll Query(int ql,int qr);
void Divide(int now,int l,int r,int L,int R);

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>K;
	//for (int i=1;i<=n;i++) for (int j=1;j<=K;j++) F[i][j]=inf;
	mem(F,63);
	for (int i=1;i<=n;i++) cin>>Num[i];
	ML=1;MR=0;mem(Cnt,0);
	for (int i=1;i<=n;i++) F[1][i]=Query(1,i);
	for (int i=2;i<=K;i++) Divide(i,1,n,1,n);
	cout<<F[K][n]<<endl;
	return 0;
}

ll Query(int ql,int qr)
{
	while (ML>ql) sum+=Cnt[Num[--ML]]++;
	while (MR<qr) sum+=Cnt[Num[++MR]]++;
	while (ML<ql) sum-=--Cnt[Num[ML++]];
	while (MR>qr) sum-=--Cnt[Num[MR--]];
	return sum;
}

void Divide(int now,int l,int r,int L,int R)
{
	if (l>r) return;
	int mid=(l+r)>>1;
	int pos=-1;
	for (int i=L;i<=min(R,mid);i++)
	{
		ll nowsum=Query(i,mid);
		if (nowsum+F[now-1][i-1]<=F[now][mid])
		{
			F[now][mid]=nowsum+F[now-1][i-1];
			pos=i;
		}
	}
	if (l!=r)
	{
		Divide(now,l,mid,L,pos);
		Divide(now,mid+1,r,pos,R);
	}
	return;
}
