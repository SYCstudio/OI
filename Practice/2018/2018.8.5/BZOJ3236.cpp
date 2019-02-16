#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lowbit(x) ((x)&(-x))
#define GetNum(x) (lower_bound(&Num[1],&Num[numcnt],x)-Num)

const int maxN=101000*4;
const int inf=2147483647;

int numcnt,Num[maxN];

class Data
{
public:
	int l,r,a,b,id;
};

class BIT
{
public:
	int num[maxN];
	void Add(int pos,int key){
		while (pos<=numcnt){
			num[pos]+=key;pos+=lowbit(pos);
		}
		return;
	}

	int Sum(int pos){
		int ret=0;
		while (pos){
			ret+=num[pos];pos-=lowbit(pos);
		}
		return ret;
	}

	int Query(int l,int r){
		if (l>r) return 0;
		if (l==0) return Sum(r);
		return Sum(r)-Sum(l-1);
	}
};

int n,m;
int Seq[maxN],Belong[maxN],Cnt[maxN],Ans1[maxN],Ans2[maxN];
Data D[maxN];
BIT B1,B2;

bool cmp(Data A,Data B);
void Add(int key);
void Del(int key);

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&Seq[i]),Num[++numcnt]=Seq[i];
	for (int i=1;i<=m;i++) scanf("%d%d%d%d",&D[i].l,&D[i].r,&D[i].a,&D[i].b),D[i].id=i,Num[++numcnt]=D[i].a,Num[++numcnt]=D[i].b;
	sort(&Num[1],&Num[numcnt+1]);numcnt=unique(&Num[1],&Num[numcnt+1])-Num-1;
	for (int i=1;i<=n;i++) Seq[i]=GetNum(Seq[i]);
	for (int i=1;i<=m;i++) D[i].a=GetNum(D[i].a),D[i].b=GetNum(D[i].b);

	int blocksize=max(1,(int)sqrt(n));
	for (int i=1;i<=n;i++) Belong[i]=i/blocksize+1;
	sort(&D[1],&D[m+1],cmp);

	int l=1,r=0;
	for (int i=1;i<=m;i++){
		while (l<D[i].l) Del(Seq[l++]);
		while (l>D[i].l) Add(Seq[--l]);
		while (r<D[i].r) Add(Seq[++r]);
		while (r>D[i].r) Del(Seq[r--]);

		Ans1[D[i].id]=B1.Query(D[i].a,D[i].b);
		Ans2[D[i].id]=B2.Query(D[i].a,D[i].b);
	}

	for (int i=1;i<=m;i++) printf("%d %d\n",Ans1[i],Ans2[i]);

	return 0;
}

bool cmp(Data A,Data B){
	if (Belong[A.l]==Belong[B.l])
		return A.r<B.r;
	return A.l<B.l;
}

void Add(int key){
	Cnt[key]++;B1.Add(key,1);
	if (Cnt[key]==1) B2.Add(key,1);
	return;
}

void Del(int key){
	Cnt[key]--;B1.Add(key,-1);
	if (Cnt[key]==0) B2.Add(key,-1);
	return;
}
