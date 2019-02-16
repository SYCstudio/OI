#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define GetNum(x) (lower_bound(&Num[1],&Num[numcnt+1],x)-Num)
#define lson (now<<1)
#define rson (lson|1)

const int maxN=201000*2;
const int maxBit=20;
const int inf=2147483647;

class Range
{
public:
	int l,r,id;
};

int numcnt,Num[maxN];

class SegmentTree
{
public:
	int Key[maxN<<2];

	void Modify(int now,int l,int r,int pos,int key){
		Key[now]+=key;
		if (l==r) return;
		int mid=(l+r)>>1;
		if (pos<=mid) Modify(lson,l,mid,pos,key);
		else Modify(rson,mid+1,r,pos,key);
		return;
	}
	
	void Insert(int key){
		Modify(1,1,numcnt,key,1);return;
	}
	
	int Query(int now,int l,int r,int ql,int qr){
		if ((l==ql)&&(r==qr)) return Key[now];
		int mid=(l+r)>>1;
		if (qr<=mid) return Query(lson,l,mid,ql,qr);
		else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
		else return Query(lson,l,mid,ql,mid)+Query(rson,mid+1,r,mid+1,qr);
	}
	
	int Right(int now,int l,int r,int pos,int sum){
		if (l==r) return l;
		int mid=(l+r)>>1;
		if (pos<=mid) return Right(lson,l,mid,pos,sum);
		else{
			if (Key[lson]<sum) return Right(rson,mid+1,r,pos,sum-Key[lson]);
			else return Right(lson,l,mid,pos,sum);
		}
	}
	
	int Left(int now,int l,int r,int pos,int sum){
		if (l==r) return l;
		int mid=(l+r)>>1;
		if (pos>=mid+1) return Left(rson,mid+1,r,pos,sum);
		else{
			if (Key[rson]<sum) return Left(lson,l,mid,pos,sum-Key[rson]);
			else return Left(rson,mid+1,r,pos,sum);
		}
	}
	
	int GetMax(int pos){
		int sum=Query(1,1,numcnt,1,pos);
		return Right(1,1,numcnt,pos,sum);
	}
	
	int GetMin(int pos){
		int sum=Query(1,1,numcnt,pos,numcnt);
		return Left(1,1,numcnt,pos,sum);
	}
};

int n;
Range Rg[maxN],St[maxN];
int Next[maxBit][maxN];
SegmentTree LS,RS;
set<int> S1,S2;

bool cmp1(Range A,Range B);
bool cmp2(Range A,Range B);
int Calc(int l,int r);

int main(){
	//freopen("f.out","w",stderr);
	//freopen("12.in","r",stdin);freopen("out.out","w",stdout);
	Num[++numcnt]=-inf;Num[++numcnt]=inf;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d%d",&Rg[i].l,&Rg[i].r),Num[++numcnt]=Rg[i].l,Num[++numcnt]=Rg[i].r,Rg[i].id=i;
	sort(&Num[1],&Num[numcnt+1]);numcnt=unique(&Num[1],&Num[numcnt+1])-Num-1;
	for (int i=1;i<=n;i++) Rg[i].l=GetNum(Rg[i].l),Rg[i].r=GetNum(Rg[i].r);

	sort(&Rg[1],&Rg[n+1],cmp1);

	//for (int i=1;i<=n;i++) cout<<"("<<Rg[i].l<<","<<Rg[i].r<<") ";cout<<endl;

	int top=0;
	for (int i=n,last=inf;i>=1;i--) if (Rg[i].r<last) last=Rg[i].r,St[++top]=Rg[i];

	//cout<<"top:"<<top<<endl;
	//for (int i=1;i<=top;i++) cout<<"("<<St[i].l<<","<<St[i].r<<") ";cout<<endl;

	mem(Next,0x3f);
	for (int i=numcnt,j=1;i>=1;i--){
		Next[0][i]=Next[0][i+1];
		if (St[j].l==i){
			Next[0][i]=min(Next[0][i],St[j].r);
			//cerr<<i<<":"<<St[j].r<<endl;
		}
		for (int k=1;k<maxBit;k++)
			if (Next[k-1][i]!=0x3f3f3f3f) Next[k][i]=Next[k-1][Next[k-1][i]+1];
		while (St[j].l==i) j++;
	}

	printf("%d\n",Calc(1,numcnt));

	//cerr<<numcnt<<endl;

	sort(&Rg[1],&Rg[n+1],cmp2);

	LS.Insert(1);LS.Insert(numcnt);RS.Insert(1);RS.Insert(numcnt);
	for (int i=1,opt=0;i<=n;i++){
		if (LS.GetMin(Rg[i].l)>RS.GetMin(Rg[i].l)) continue;
		if (LS.GetMax(Rg[i].r)>RS.GetMax(Rg[i].r)) continue;
		if (LS.GetMax(Rg[i].l)>RS.GetMax(Rg[i].l)) continue;
		if (LS.GetMin(Rg[i].r)>RS.GetMin(Rg[i].r)) continue;
		if (LS.GetMin(Rg[i].l)<=Rg[i].r) continue;
		if (RS.GetMax(Rg[i].r)>=Rg[i].l) continue;
		if (RS.GetMin(Rg[i].l)<=Rg[i].r) continue;
		if (LS.GetMax(Rg[i].r)>=Rg[i].l) continue;
		if (LS.GetMax(Rg[i].l)==Rg[i].l) continue;
		if (RS.GetMin(Rg[i].r)==Rg[i].r) continue;
		int L=RS.GetMax(Rg[i].l)+1,R=LS.GetMin(Rg[i].r)-1;
		//cerr<<i<<"["<<Rg[i].l<<","<<Rg[i].r<<"] ("<<L<<","<<R<<") "<<Calc(L,Rg[i].l-1)<<" "<<Calc(Rg[i].r+1,R)<<" "<<Calc(L,R)<<endl;
		
		if (Calc(L,Rg[i].l-1)+Calc(Rg[i].r+1,R)+1==Calc(L,R)){
			if (opt==1) printf(" ");opt=1;
			printf("%d",i);
			//cerr<<Rg[i].l<<" "<<Rg[i].r<<endl;
			LS.Insert(Rg[i].l);RS.Insert(Rg[i].r);
			S1.insert(Rg[i].l);S2.insert(Rg[i].r);
		}
	}
	printf("\n");return 0;
}

bool cmp1(Range A,Range B){
	if (A.l!=B.l) return A.l<B.l;
	else return A.r<B.r;
}

bool cmp2(Range A,Range B){
	return A.id<B.id;
}

int Calc(int l,int r){
	int ret=0;
	for (int i=maxBit-1;i>=0;i--)
		if (Next[i][l]<=r){
			l=Next[i][l]+1;ret|=(1<<i);
		}
	return ret;
}

