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

const int maxN=101000;
const int maxM=301000;
const int inf=2e9;

class Question
{
public:
	int l,r,id;
};

int n,m;
int Seq[maxN];
vector<int> Vr[maxN<<2];
int Mn[maxN<<2],Ans[maxM];
Question Qn[maxM];

bool cmp(Question A,Question B);
void Build(int now,int l,int r);
void Modify(int now,int l,int r,int pos,int key,int &mn);
int Query(int now,int l,int r,int ql,int qr);
void Outp(int now,int l,int r);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&Seq[i]);
	Build(1,1,n);
	//cout<<"Build complete"<<endl;
	scanf("%d",&m);
	for (int i=1;i<=m;i++) scanf("%d%d",&Qn[i].l,&Qn[i].r),Qn[i].id=i;
	sort(&Qn[1],&Qn[m+1],cmp);
	//Outp(1,1,n);cout<<endl;
	for (int i=1,nowr=1;i<=m;i++){
		while (nowr<Qn[i].r){
			int mn=inf;
			Modify(1,1,n,nowr,Seq[nowr+1],mn);nowr++;
			//Outp(1,1,n);cout<<endl;
		}
		Ans[Qn[i].id]=Query(1,1,n,Qn[i].l,Qn[i].r);
	}

	for (int i=1;i<=m;i++) printf("%d\n",Ans[i]);
	return 0;
}

bool cmp(Question A,Question B){
	return A.r<B.r;
}

void Build(int now,int l,int r){
	if (l==r){
		Vr[now].push_back(Seq[l]);Mn[now]=inf;return;
	}
	int mid=(l+r)>>1;
	Build(lson,l,mid);Build(rson,mid+1,r);
	int sz1=Vr[lson].size(),sz2=Vr[rson].size(),p1=0,p2=0;
	while ((p1!=sz1)||(p2!=sz2)){
		if ((p1!=sz1)&&((p2==sz2)||(Vr[lson][p1]<=Vr[rson][p2]))) Vr[now].push_back(Vr[lson][p1++]);
		else Vr[now].push_back(Vr[rson][p2++]);
	}
	Mn[now]=min(Mn[lson],Mn[rson]);
	for (int i=0,sz=Vr[now].size();i<sz-1;i++) Mn[now]=min(Mn[now],Vr[now][i+1]-Vr[now][i]);
	//cout<<"["<<l<<","<<r<<"] ";for (int i=0;i<Vr[now].size();i++) cout<<Vr[now][i]<<" ";cout<<endl;
	return;
}

void Modify(int now,int l,int r,int pos,int key,int &mn){
	//cout<<"Modify:"<<now<<" "<<l<<" "<<r<<" "<<pos<<" "<<key<<" "<<mn<<endl;
	if (l==r){
		mn=min(mn,abs(key-Vr[now][0]));
		Mn[now]=min(Mn[now],mn);return;
	}
	vector<int>::iterator it=lower_bound(Vr[now].begin(),Vr[now].end(),key);
	if ( ((it==Vr[now].end())||((*it)-pos>=mn)) && ((it==Vr[now].begin())||(pos-(*(it-1))>=mn)) ){
		mn=min(mn,Query(1,1,n,l,pos));
		return;
	}
	int mid=(l+r)>>1;
	if (pos>=mid+1) Modify(rson,mid+1,r,pos,key,mn),Modify(lson,l,mid,pos,key,mn);
	else Modify(lson,l,mid,pos,key,mn);
	Mn[now]=min(min(Mn[now],mn),min(Mn[lson],Mn[rson]));
	return;
}

int Query(int now,int l,int r,int ql,int qr){
	if ((l>=ql)&&(r<=qr)) return Mn[now];
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
	else return min(Query(lson,l,mid,ql,mid),Query(rson,mid+1,r,mid+1,qr));
}

void Outp(int now,int l,int r){
	cout<<"["<<l<<","<<r<<"] "<<Mn[now]<<endl;
	if (l==r) return;
	int mid=(l+r)>>1;
	Outp(lson,l,mid);Outp(rson,mid+1,r);
	return;
}
