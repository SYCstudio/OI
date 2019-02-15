#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)

const int maxN=201000;
const int maxAlpha=2;
const int maxBit=20;
const int inf=2147483647;

class Option{
public:
	int pos,key,tim;
};

class Question{
public:
	int pl,pr,tl,tr,key;
};

int n,m;
int ocnt=0,qcnt=0;
Option On[maxN],Bp[maxN];
Question Qn[maxN];
vector<int> S[maxN<<2];
int nodecnt=0,root[maxN],son[maxAlpha][maxN*maxBit],cnt[maxN*maxBit];
int rtp[maxN];
int Ans[maxN];

void Insert(int &rt,int val);
int Query(int l,int r,int val);
void Add_Query(int now,int l,int r,int ql,int qr,int id);
bool ocmp(Option A,Option B);
void Divide(int now,int tl,int tr,int pl,int pr);

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++){
		root[i]=root[i-1];
		int val;scanf("%d",&val);
		Insert(root[i],val);
	}
	//cout<<"Init"<<endl;

	for (int i=1;i<=m;i++){
		int opt;scanf("%d",&opt);
		if (opt==0){
			int s,v;scanf("%d%d",&s,&v);ocnt++;
			On[ocnt]=((Option){s,v,ocnt});
		}
		if (opt==1){
			int l,r,val,d;scanf("%d%d%d%d",&l,&r,&val,&d);
			Qn[++qcnt]=((Question){l,r,max(1,ocnt-d+1),ocnt,val});
			Ans[qcnt]=Query(l-1,r,val);
		}
	}
	//for (int i=1;i<=qcnt;i++) cout<<Qn[i].tl<<" "<<Qn[i].tr<<" "<<Qn[i].pl<<" "<<Qn[i].pr<<endl;

	for (int i=1;i<=qcnt;i++) if (Qn[i].tl<=Qn[i].tr) Add_Query(1,1,ocnt,Qn[i].tl,Qn[i].tr,i);
	sort(&On[1],&On[ocnt+1],ocmp);

	Divide(1,1,ocnt,1,ocnt);

	for (int i=1;i<=qcnt;i++) printf("%d\n",Ans[i]);

	return 0;
}

void Insert(int &rt,int val){
	cnt[++nodecnt]=cnt[rt];son[0][nodecnt]=son[0][rt];son[1][nodecnt]=son[1][rt];
	rt=nodecnt;cnt[rt]++;
	for (int i=maxBit-1,now=rt;i>=0;i--){
		int c=(val&(1<<i))!=0;
		int s=son[c][now];
		cnt[++nodecnt]=cnt[s];son[0][nodecnt]=son[0][s];son[1][nodecnt]=son[1][s];
		cnt[nodecnt]++;son[c][now]=nodecnt;
		now=son[c][now];
	}
	return;
}

int Query(int l,int r,int val){
	int ret=0,n1=root[l],n2=root[r];
	for (int i=maxBit-1;i>=0;i--){
		int c=(val&(1<<i))!=0;
		if (cnt[son[c^1][n2]]-cnt[son[c^1][n1]]){
			ret|=(1<<i);n1=son[c^1][n1];n2=son[c^1][n2];
		}
		else{
			n1=son[c][n1];n2=son[c][n2];
		}
	}
	return ret;
}

void Add_Query(int now,int l,int r,int ql,int qr,int id){
	if ((l==ql)&&(r==qr)){
		S[now].push_back(id);return;
	}
	int mid=(l+r)>>1;
	if (qr<=mid) Add_Query(lson,l,mid,ql,qr,id);
	else if (ql>=mid+1) Add_Query(rson,mid+1,r,ql,qr,id);
	else{
		Add_Query(lson,l,mid,ql,mid,id);Add_Query(rson,mid+1,r,mid+1,qr,id);
	}
	return;
}

bool ocmp(Option A,Option B){
	return A.pos<B.pos;
}

void Divide(int now,int tl,int tr,int pl,int pr){
	//cout<<"Divide:"<<now<<" ["<<tl<<","<<tr<<"] ["<<pl<<","<<pr<<"]"<<endl;
	if (pl>pr) return;
	int rcnt=0;root[0]=0;nodecnt=0;
	for (int i=pl;i<=pr;i++){
		rcnt++;root[rcnt]=root[rcnt-1];rtp[rcnt]=On[i].pos;
		Insert(root[rcnt],On[i].key);
	}

	//cout<<"On:"<<endl;
	//for (int i=pl;i<=pr;i++) cout<<On[i].pos<<" "<<On[i].key<<" "<<On[i].tim<<endl;
	//cout<<"rtp:";for (int i=1;i<=rcnt;i++) cout<<rtp[i]<<" ";cout<<endl;
	
	for (int sz=S[now].size(),i=0;i<sz;i++){
		int q=S[now][i];
		int L=0,R=0;
		for (int j=maxBit-1;j>=0;j--) if ((L+(1<<j)<=rcnt)&&(rtp[L+(1<<j)]<=Qn[q].pl-1)) L=L+(1<<j);
		for (int j=maxBit-1;j>=0;j--) if ((R+(1<<j)<=rcnt)&&(rtp[R+(1<<j)]<=Qn[q].pr)) R=R+(1<<j);
		Ans[q]=max(Ans[q],Query(L,R,Qn[q].key));
		//cout<<"Q:"<<q<<" "<<Qn[q].pl<<" "<<Qn[q].pr<<" "<<L<<" "<<R<<endl;
	}
	if (tl==tr) return;

	int mid=(tl+tr)/2;
	int l=pl,r=pr;
	for (int i=pl;i<=pr;i++)
		if (On[i].tim<=mid) Bp[l++]=On[i];
		else Bp[r--]=On[i];
	for (int i=pl;i<l;i++) On[i]=Bp[i];
	for (int i=pr,j=l;i>r;i--,j++) On[j]=Bp[i];
	Divide(lson,tl,mid,pl,l-1);Divide(rson,mid+1,tr,r+1,pr);
	return;
}

/*
5 16
7 4 9 3 2
1 1 4 6 0
0 2 3
1 2 3 13 0
1 2 3 13 1
1 2 3 13 5
0 5 6
1 2 3 13 1
1 2 3 13 4
1 3 5 2 0
1 3 5 2 1
0 3 10
1 1 3 7 1
1 1 3 5 1
1 1 3 12 1
1 1 3 12 2
1 1 3 12 3
//*/

