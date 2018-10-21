#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)
#define lowbit(x) ((x)&(-x))

const int maxN=301000;
const int maxM=1010000;
const int maxAlpha=26;
const int Mod=1e9+7;
const int inf=2147483647;

class Node
{
public:
	int son[maxAlpha];
	int len,fail,nxt,diff;
};

class Question
{
public:
	int L,id;
};

int n,m;
char str[maxN];
int last,nodecnt;
Node P[maxN];
int Mx[maxN<<2];
int Bit[maxN];
vector<Question> Q[maxN];
vector<int> Son[maxN];
int dfncnt,fst[maxN],lst[maxN];
int Ans[maxM];

void Insert(int pos,int c);
void dfs(int u);
void Modify(int now,int l,int r,int pos,int key);
int Query(int now,int l,int r,int ql,int qr);
void Add(int pos,int key);
int Sum(int pos);

int main()
{
	scanf("%d%d",&n,&m);
	scanf("%s",str+1);

	last=0;nodecnt=1;
	P[0].fail=P[1].fail=1;
	P[0].len=0;P[1].len=-1;
	for (int i=1;i<=n;i++) Insert(i,str[i]-'a');

	for (int i=0;i<=nodecnt;i++) if (i!=1) Son[P[i].fail].push_back(i);
	dfs(1);

	for (int i=1;i<=m;i++){
		int l,r;scanf("%d%d",&l,&r);
		Q[r].push_back((Question){l,i});
	}

	for (int i=1,now=1;i<=n;i++){
		while (str[i-1-P[now].len]!=str[i]) now=P[now].fail;
		now=P[now].son[str[i]-'a'];
		//cout<<i<<":"<<i<<endl;
		for (int j=now;j;j=P[P[j].nxt].fail)
		{
			Add(max(1,Query(1,1,dfncnt,fst[j],lst[j])-P[j].len+2),1);
			Add(i-P[P[j].nxt].len+2,-1);
		}
		Modify(1,1,dfncnt,fst[now],i);

		for (int sz=Q[i].size(),j=0;j<sz;j++) Ans[Q[i][j].id]=Sum(Q[i][j].L);
	}

	//for (int i=1;i<=m;i++) cout<<Ans[i]<<" ";cout<<endl;

	int outp=0;
	for (int i=1;i<=m;i++) outp=(outp+1ll*Ans[i]*i%Mod)%Mod;

	printf("%d\n",outp);

	return 0;
}

void Insert(int pos,int c){
	int p=last;
	while (str[pos-1-P[p].len]!=str[pos]) p=P[p].fail;
	if (P[p].son[c]==0){
		int np=++nodecnt,q=P[p].fail;
		while (str[pos-1-P[q].len]!=str[pos]) q=P[q].fail;
		P[np].fail=P[q].son[c];P[np].len=P[p].len+2;
		P[np].diff=P[np].len-P[P[np].fail].len;
		if (P[np].diff==P[P[np].fail].diff) P[np].nxt=P[P[np].fail].nxt;
		else P[np].nxt=np;

		P[p].son[c]=np;
	}
	last=P[p].son[c];
	return;
}
	
void dfs(int u){
	fst[u]=++dfncnt;
	for (int sz=Son[u].size(),i=0;i<sz;i++) dfs(Son[u][i]);
	lst[u]=dfncnt;
	return;
}

void Modify(int now,int l,int r,int pos,int key){
	if (l==r){
		Mx[now]=key;return;
	}
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(lson,l,mid,pos,key);
	else Modify(rson,mid+1,r,pos,key);
	Mx[now]=max(Mx[lson],Mx[rson]);
	return;
}

int Query(int now,int l,int r,int ql,int qr){
	if ((l==ql)&&(r==qr)) return Mx[now];
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
	else return max(Query(lson,l,mid,ql,mid),Query(rson,mid+1,r,mid+1,qr));
}

void Add(int pos,int key){
	//cout<<"Add:"<<pos<<" "<<key<<endl;
	while (pos<=n){
		Bit[pos]+=key;pos+=lowbit(pos);
	}
	return;
}

int Sum(int pos){
	int ret=0;
	while (pos){
		ret+=Bit[pos];pos-=lowbit(pos);
	}
	return ret;
}
