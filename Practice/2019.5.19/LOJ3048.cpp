#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<iostream>
#include<cassert>
using namespace std;

typedef unsigned int uint;
const int maxN=505000;
const int Bit=31;

class Trie
{
public:
	int ch[2],cnt,id;
};
class HData
{
public:
	uint key;
	int l,r,p;
};

int n,K,ID;
uint A[maxN];
int tcnt,rt[maxN];
Trie T[maxN*(Bit+2)];
priority_queue<HData> H;

bool operator < (HData A,HData B);
void Insert(int &x,int b,uint key);
uint Query(int x,int y,int b,uint key);
int main()
{
	//freopen("in","r",stdin);
	scanf("%d%d",&n,&K);
	for (int i=2; i<=n+1; i++) scanf("%u",&A[i]),A[i]^=A[i-1];
	for (int i=1; i<=n+1; i++) ID=i,rt[i]=rt[i-1],Insert(rt[i],Bit,A[i]);
	for (int i=1; i<=n+1; i++) {
		H.push((HData) {
			Query(rt[0],rt[n+1],Bit,A[i]),1,n+1,i
		});
		//if (i!=1) H.push((HData){Query(rt[0],rt[i-1],Bit,A[i]),1,i-1,i});
		//if (i!=n+1) H.push((HData){Query(rt[i],rt[n+1],Bit,A[i]),i+1,n+1,i});
	}
	K<<=1;
	long long Ans=0;
	while (K--) {
		HData h=H.top();
		H.pop();
		Ans=Ans+h.key;
		Query(rt[h.l-1],rt[h.r],Bit,A[h.p]);
		int id=ID;
		//cout<<"H:"<<h.key<<" "<<h.p<<" ["<<h.l<<","<<h.r<<"]"<<" "<<ID<<endl;
		if (id>h.l) H.push((HData) {
			Query(rt[h.l-1],rt[id-1],Bit,A[h.p]),h.l,id-1,h.p
		});
		if (id<h.r) H.push((HData) {
			Query(rt[id],rt[h.r],Bit,A[h.p]),id+1,h.r,h.p
		});
	}
	printf("%lld\n",Ans>>1);
	return 0;
}
bool operator < (HData A,HData B)
{
	if (A.key==B.key) {
		if (A.p==B.p) return A.l<B.l;
		return A.p<B.p;
	}
	return A.key<B.key;
}
void Insert(int &x,int b,uint key)
{
	T[++tcnt]=T[x];
	x=tcnt;
	++T[x].cnt;
	if (b==-1) {
		T[x].id=ID;
		return;
	}
	Insert(T[x].ch[(key>>b)&1],b-1,key);
	return;
}
uint Query(int x,int y,int b,uint key)
{
	if (b==-1) {
		ID=T[y].id;
		return 0;
	}
	int k=(key>>b)&1;
	if (T[T[y].ch[k^1]].cnt-T[T[x].ch[k^1]].cnt) return Query(T[x].ch[k^1],T[y].ch[k^1],b-1,key)|(1ll<<b);
	else return Query(T[x].ch[k],T[y].ch[k],b-1,key);
}
