#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)

const int maxN=101000;
const int inf=2147483647;

class Range
{
public:
	int l,r,key;
};

int n;
map<pair<int,int>,int> Mp;
Range R[maxN];
int Mx[maxN<<2];

bool cmp(Range A,Range B);
void Modify(int now,int l,int r,int pos,int key);
int Query(int now,int l,int r,int ql,int qr);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		int a,b;scanf("%d%d",&a,&b);
		if (a+b>=n) continue;
		//cout<<"("<<b+1<<" "<<n-a<<")"<<endl;
		Mp[make_pair(b+1,n-a)]++;
	}
	int rcnt=0;
	for (map<pair<int,int>,int>::iterator it=Mp.begin();it!=Mp.end();it++)
		R[++rcnt]=((Range){(*it).first.first,(*it).first.second,(*it).second});
	for (int i=1;i<=rcnt;i++) R[i].key=min(R[i].key,R[i].r-R[i].l+1);
	sort(&R[1],&R[rcnt+1],cmp);
	//for (int i=1;i<=rcnt;i++) cout<<R[i].l<<" "<<R[i].r<<" "<<R[i].key<<endl;
	Modify(1,0,n,0,0);

	for (int i=1;i<=rcnt;i++){
		int f=Query(1,0,n,0,R[i].l-1);
		//cout<<i<<" "<<f<<endl;
		Modify(1,0,n,R[i].r,f+R[i].key);
	}

	printf("%d\n",n-Query(1,0,n,0,n));return 0;
}

bool cmp(Range A,Range B){
	return A.r<B.r;
}

void Modify(int now,int l,int r,int pos,int key){
	if (l==r){
		Mx[now]=max(Mx[now],key);return;
	}
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(lson,l,mid,pos,key);
	else Modify(rson,mid+1,r,pos,key);
	Mx[now]=max(Mx[lson],Mx[rson]);return;
}

int Query(int now,int l,int r,int ql,int qr){
	if ((l==ql)&&(r==qr)) return Mx[now];
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
	else return max(Query(lson,l,mid,ql,mid),Query(rson,mid+1,r,mid+1,qr));
}
