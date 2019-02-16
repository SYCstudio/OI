#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define ull unsigned long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=50500;
const int maxL=606000;
const ull base=233;


class Question
{
public:
	int opt,l,r;
};

int n,m;
char Input[maxL],Bp[maxL],S[maxL];int bcnt,scnt;
int IB[maxN],IE[maxN],IR[maxN],QB[maxN],QE[maxN],QR[maxN];
Question Qn[maxN];
ull Pow[maxL];

int Lcp(int u,int v);

namespace CS{
	class SegmentData{
	public:
		int ls,rs,sz;
		ull hash;
	};
	int nodecnt=0,root;
	SegmentData T[maxL*50];
	void Init(int &x,int l,int r);
	void Update(int x);
	void Build(int &x,int l,int r,int ql,int qr);
	int Merge(int u,int v);
	ull QueryK(int x,int k);
	void Outp(int x);
}
namespace ANS{
	class SegmentData{
	public:
		int mn,plus,rt,len;
	};
	SegmentData T[maxN<<2];
	void Init(int x,int l,int r);
	void Update(int x);
	void PushDown(int x);
	void Plus(int x,int l,int r,int ql,int qr,int k);
	void Extend(int x,int l,int r,int ql,int qr,int k);
	void Addstr(int x,int l,int r,int ql,int qr,int rt);
	void Modify(int x,int l,int r,int pos,int key);
	int GetRt(int x,int l,int r,int pos);
	int GetMn(int x,int l,int r,int ql,int qr);
	int GetLn(int x,int l,int r,int pos);
}

int main(){
	//freopen("in","r",stdin);freopen("out","w",stdout);
	Pow[0]=1;for (int i=1;i<maxL;i++) Pow[i]=Pow[i-1]*base;
	int sum=0;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++){
		scanf("%s",Input+1);int len=strlen(Input+1);sum+=len;
		IB[i]=bcnt+1;IE[i]=bcnt+len;for (int j=1;j<=len;j++) Bp[++bcnt]=Input[j];
	}
	for (int i=1;i<=m;i++){
		char ipt[8];scanf("%s",ipt);
		scanf("%d%d",&Qn[i].l,&Qn[i].r);
		Qn[i].opt=ipt[0]=='Q';
		if (Qn[i].opt==0){
			scanf("%s",Input+1);int len=strlen(Input+1);
			QB[i]=bcnt+1;QE[i]=bcnt+len;for (int j=1;j<=len;j++) Bp[++bcnt]=Input[j];
		}
	}
	for (int i=m;i>=1;i--)
		if (Qn[i].opt==0){
			int l=scnt+1;
			for (int j=QB[i];j<=QE[i];j++) S[++scnt]=Bp[j];
			QB[i]=l;QE[i]=scnt;
		}
	for (int i=1;i<=n;i++){
		int l=scnt+1;
		for (int j=IB[i];j<=IE[i];j++) S[++scnt]=Bp[j];
		IB[i]=l;IE[i]=scnt;
	}

	//for (int i=1;i<=scnt;i++) cout<<S[i];cout<<endl;
	//for (int i=1;i<=n;i++) cout<<"I:"<<i<<":"<<IB[i]<<" "<<IE[i]<<endl;
	//for (int i=1;i<=m;i++) if (Qn[i].opt==0) cout<<"Q:"<<i<<":"<<QB[i]<<" "<<QE[i]<<endl;

	CS::Init(CS::root,1,scnt);
	for (int i=1;i<=n;i++) CS::Build(IR[i]=CS::root,1,scnt,IB[i],IE[i]);
	for (int i=1;i<=m;i++) if (Qn[i].opt==0) CS::Build(QR[i]=CS::root,1,scnt,QB[i],QE[i]);
	ANS::Init(1,1,n);

	//for (int i=1;i<=n;i++) cout<<i<<" : ",CS::Outp(IR[i]),cout<<endl;
	//for (int i=1;i<=m;i++) if (Qn[i].opt==0) cout<<i<<" ",CS::Outp(QR[i]),cout<<endl;

	for (int i=1;i<=m;i++){
		//cout<<"Running on :"<<i<<endl;
		if (Qn[i].opt==0){
			if (Qn[i].l<Qn[i].r) ANS::Plus(1,1,n,Qn[i].l,Qn[i].r-1,QE[i]-QB[i]+1);
			ANS::Addstr(1,1,n,Qn[i].l,Qn[i].r,QR[i]);
			ANS::Extend(1,1,n,Qn[i].l,Qn[i].r,QE[i]-QB[i]+1);
			if (Qn[i].l!=1){
				int r1=ANS::GetRt(1,1,n,Qn[i].l-1),r2=ANS::GetRt(1,1,n,Qn[i].l);
				//cout<<"GetLcp:"<<Qn[i].l-1<<" "<<Qn[i].l<<" : ";
				//CS::Outp(r1);cout<<" ";CS::Outp(r2);cout<<" "<<Lcp(r1,r2)<<endl;
				ANS::Modify(1,1,n,Qn[i].l-1,Lcp(r1,r2));
			}
			if (Qn[i].r!=n){
				int r1=ANS::GetRt(1,1,n,Qn[i].r),r2=ANS::GetRt(1,1,n,Qn[i].r+1);
				//cout<<"GetLcp:"<<Qn[i].r<<" "<<Qn[i].r+1<<" : ";
				//CS::Outp(r1);cout<<" ";CS::Outp(r2);cout<<" "<<Lcp(r1,r2)<<endl;
				ANS::Modify(1,1,n,Qn[i].r,Lcp(r1,r2));
			}
		}
		else{
			if (Qn[i].l==Qn[i].r) printf("%d\n",ANS::GetLn(1,1,n,Qn[i].l));
			else printf("%d\n",ANS::GetMn(1,1,n,Qn[i].l,Qn[i].r-1));
		}
	}
	return 0;
}

int Lcp(int u,int v){
	int sz=min(CS::T[u].sz,CS::T[v].sz);
	int l=1,r=sz,ret=0;
	do{
		int mid=(l+r)>>1;
		if (CS::QueryK(u,mid)==CS::QueryK(v,mid)) ret=mid,l=mid+1;
		else r=mid-1;
	}
	while (l<=r);
	return ret;
}

namespace CS{
	void Init(int &x,int l,int r){
		x=++nodecnt;
		if (l==r){
			T[x].sz=1;T[x].hash=S[l]-'a'+1;
			return;
		}
		int mid=(l+r)>>1;
		Init(T[x].ls,l,mid);Init(T[x].rs,mid+1,r);Update(x);
		return;
	}

	void Update(int x){
		T[x].sz=T[T[x].ls].sz+T[T[x].rs].sz;
		T[x].hash=T[T[x].ls].hash*Pow[T[T[x].rs].sz]+T[T[x].rs].hash;
		return;
	}
	
	void Build(int &x,int l,int r,int ql,int qr){
		T[++nodecnt]=T[x];x=nodecnt;
		if ((l==ql)&&(r==qr)) return;
		int mid=(l+r)>>1;
		if (qr<=mid) Build(T[x].ls,l,mid,ql,qr),T[x].rs=0;
		else if (ql>=mid+1) Build(T[x].rs,mid+1,r,ql,qr),T[x].ls=0;
		else Build(T[x].ls,l,mid,ql,mid),Build(T[x].rs,mid+1,r,mid+1,qr);
		Update(x);return;
	}
	
	int Merge(int u,int v){
		if ((!u)||(!v)) return u+v;
		int x=++nodecnt;
		T[x].ls=Merge(T[u].ls,T[v].ls);T[x].rs=Merge(T[u].rs,T[v].rs);
		Update(x);return x;
	}
	
	ull QueryK(int x,int k){
		if (T[x].sz<k) return 0;
		if (T[T[x].ls].sz>=k) return QueryK(T[x].ls,k);
		if (T[x].sz==k) return T[x].hash;
		else return T[T[x].ls].hash*Pow[k-T[T[x].ls].sz]+QueryK(T[x].rs,k-T[T[x].ls].sz);
	}
	void Outp(int x){
		if (T[x].sz==1){
			cout<<(char)(T[x].hash+'a'-1);return;
		}
		if (T[x].ls) Outp(T[x].ls);
		if (T[x].rs) Outp(T[x].rs);
		return;
	}
}
namespace ANS{
#define ls (x<<1)
#define rs (ls|1)
	void Init(int x,int l,int r){
		if (l==r){
			T[x].rt=IR[l];T[x].len=IE[l]-IB[l]+1;
			if (l!=n) T[x].mn=Lcp(IR[l],IR[l+1]);
			else T[x].mn=0;
			return;
		}
		int mid=(l+r)>>1;
		Init(ls,l,mid);Init(rs,mid+1,r);Update(x);return;
	}
	void Update(int x){
		T[x].mn=min(T[ls].mn,T[rs].mn);return;
	}
	void PushDown(int x){
		if (T[x].plus){
			T[ls].plus+=T[x].plus;T[ls].mn+=T[x].plus;
			T[rs].plus+=T[x].plus;T[rs].mn+=T[x].plus;
			T[x].plus=0;
		}
		if (T[x].rt){
			T[ls].rt=CS::Merge(T[x].rt,T[ls].rt);
			T[rs].rt=CS::Merge(T[x].rt,T[rs].rt);
			T[x].rt=0;
		}
		if (T[x].len){
			T[ls].len+=T[x].len;T[rs].len+=T[x].len;
			T[x].len=0;
		}
		return;
	}
	void Plus(int x,int l,int r,int ql,int qr,int k){
		if ((l==ql)&&(r==qr)){
			T[x].plus+=k;T[x].mn+=k;return;
		}
		PushDown(x);int mid=(l+r)>>1;
		if (qr<=mid) Plus(ls,l,mid,ql,qr,k);
		else if (ql>=mid+1) Plus(rs,mid+1,r,ql,qr,k);
		else Plus(ls,l,mid,ql,mid,k),Plus(rs,mid+1,r,mid+1,qr,k);
		Update(x);return;
	}
	void Addstr(int x,int l,int r,int ql,int qr,int rt){
		if ((l==ql)&&(r==qr)){
			T[x].rt=CS::Merge(rt,T[x].rt);return;
		}
		PushDown(x);int mid=(l+r)>>1;
		if (qr<=mid) Addstr(ls,l,mid,ql,qr,rt);
		else if (ql>=mid+1) Addstr(rs,mid+1,r,ql,qr,rt);
		else Addstr(ls,l,mid,ql,mid,rt),Addstr(rs,mid+1,r,mid+1,qr,rt);
		Update(x);return;
	}
	void Modify(int x,int l,int r,int pos,int key){
		if (l==r){
			T[x].mn=key;return;
		}
		PushDown(x);int mid=(l+r)>>1;
		if (pos<=mid) Modify(ls,l,mid,pos,key);
		else Modify(rs,mid+1,r,pos,key);
		Update(x);return;
	}
	void Extend(int x,int l,int r,int ql,int qr,int k){
		if ((l==ql)&&(r==qr)){
			T[x].len+=k;return;
		}
		PushDown(x);int mid=(l+r)>>1;
		if (qr<=mid) Extend(ls,l,mid,ql,qr,k);
		else if (ql>=mid+1) Extend(rs,mid+1,r,ql,qr,k);
		else Extend(ls,l,mid,ql,mid,k),Extend(rs,mid+1,r,mid+1,qr,k);
	}
	int GetRt(int x,int l,int r,int pos){
		if (l==r) return T[x].rt;
		PushDown(x);int mid=(l+r)>>1;
		if (pos<=mid) return GetRt(ls,l,mid,pos);
		else return GetRt(rs,mid+1,r,pos);
	}
	int GetMn(int x,int l,int r,int ql,int qr){
		if ((l==ql)&&(r==qr)) return T[x].mn;
		PushDown(x);int mid=(l+r)>>1;
		if (qr<=mid) return GetMn(ls,l,mid,ql,qr);
		else if (ql>=mid+1) return GetMn(rs,mid+1,r,ql,qr);
		else return min(GetMn(ls,l,mid,ql,mid),GetMn(rs,mid+1,r,mid+1,qr));
	}
	int GetLn(int x,int l,int r,int pos){
		if (l==r) return T[x].len;
		PushDown(x);int mid=(l+r)>>1;
		if (pos<=mid) return GetLn(ls,l,mid,pos);
		else return GetLn(rs,mid+1,r,pos);
	}
}
/*
2 3
noi
noip
Q 1 2
I 2 2 ctsc
Q 1 2
//*/
