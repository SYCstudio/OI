#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

class Trie
{
public:
	int ch[2],cnt;
};

const int maxN=1010;
const int maxM=303000;

int n,m,nodecnt;
int X[maxM],rt[maxM],rl[maxM],rr[maxM];
Trie T[maxM*40];

void Insert(int &x,int b,int key);
int Query(int b,int K,int l,int r);

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1; i<=n; i++) scanf("%d",&X[i]);
	for (int i=1; i<=m; i++) {
		int key;
		scanf("%d",&key);
		rt[i]=rt[i-1];
		Insert(rt[i],30,key);
	}
	int Q;
	scanf("%d",&Q);
	while (Q--) {
		int a,b,c,d,K;
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&K);
		K=(b-a+1)*(d-c+1)-K+1;
		for (int i=a; i<=b; i++) rl[i]=rt[c-1],rr[i]=rt[d];
		printf("%d\n",Query(30,K,a,b));
	}
	return 0;
}
void Insert(int &x,int b,int key)
{
	T[++nodecnt]=T[x];
	x=nodecnt;
	T[x].cnt++;
	if (b==-1) return;
	Insert(T[x].ch[(key>>b)&1],b-1,key);
	return;
}
int Query(int b,int K,int l,int r)
{
	if (b==-1) return 0;
	int sum=0;
	for (int i=l; i<=r; i++) {
		int d=(X[i]>>b)&1;
		sum+=T[T[rr[i]].ch[d]].cnt-T[T[rl[i]].ch[d]].cnt;
	}
	if (sum>=K) {
		for (int i=l; i<=r; i++) {
			int d=(X[i]>>b)&1;
			rr[i]=T[rr[i]].ch[d];
			rl[i]=T[rl[i]].ch[d];
		}
		return Query(b-1,K,l,r);
	} else {
		K-=sum;
		for (int i=l; i<=r; i++) {
			int d=(X[i]>>b)&1;
			rr[i]=T[rr[i]].ch[d^1];
			rl[i]=T[rl[i]].ch[d^1];
		}
		return Query(b-1,K,l,r)|(1<<b);
	}
}