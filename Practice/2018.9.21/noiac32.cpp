#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=50100;
const int inf=2147483647;

class Data
{
public:
	int key,pos;
};

int n;
int Arr[maxN],ZO[maxN];
Data D[maxN];

bool cmp(Data A,Data B);
void Solve(int l,int r);
void Merge(int l,int r);

int main(){
	//freopen("sort.in","r",stdin);freopen("sort.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&D[i].key),D[i].pos=i;
	sort(&D[1],&D[n+1],cmp);
	for (int i=1;i<=n;i++) Arr[D[i].pos]=i;

	Solve(1,n);

	//for (int i=1;i<=n;i++) cerr<<Arr[i]<<" ";cerr<<endl;

	printf("-1 -1\n");
	return 0;
}

bool cmp(Data A,Data B){
	return A.key<B.key;
}

void Solve(int l,int r){
	if (l==r) return;
	int midpos=(l+r)>>1,sz=midpos-l+1;
	int lkey=0,rkey=1e9,midnum=Arr[l];
	do{
		int limit=(lkey+rkey)>>1,cnt=0;
		for (int i=l;i<=r;i++) cnt+=(Arr[i]<=limit);
		//cerr<<"limit:"<<limit<<" "<<cnt<<endl;
		if (cnt>=sz) midnum=limit,rkey=limit-1;
		else lkey=limit+1;
	}
	while (lkey<=rkey);
	//cerr<<"["<<l<<","<<r<<"] "<<midpos<<" "<<sz<<" "<<midnum<<endl;
	//for (int i=1;i<=n;i++) cerr<<Arr[i]<<" ";cerr<<endl;
	for (int i=l;i<=r;i++) ZO[i]=Arr[i]>midnum;
	//for (int i=l;i<=r;i++) cerr<<ZO[i]<<" ";cerr<<endl;
	//LL=l;RR=r;
	Merge(l,r);
	//cerr<<"after:"<<endl;
	//for (int i=1;i<=n;i++) cerr<<Arr[i]<<" ";cerr<<endl;
	//for (int i=l;i<=r;i++) cerr<<ZO[i]<<" ";cerr<<endl;
	Solve(l,midpos);Solve(midpos+1,r);
	return;
}

void Merge(int l,int r){
	if (l==r) return;
	int mid=(l+r)>>1;
	Merge(l,mid);Merge(mid+1,r);
	int p1=mid,p2=mid+1;
	if (ZO[p1]>ZO[p2]){
		while ((p1>l)&&(ZO[p1-1]==1)) p1--;
		while ((p2<r)&&(ZO[p2+1]==0)) p2++;
		printf("%d %d\n",p1,p2);
		//cerr<<"reverse:"<<p1<<" "<<p2<<endl;
		for (int i=p1,j=p2;i<j;i++,j--) swap(ZO[i],ZO[j]),swap(Arr[i],Arr[j]);
		//for (int i=LL;i<=RR;i++) cerr<<ZO[i]<<" ";cerr<<endl;
	}
	return;
}
