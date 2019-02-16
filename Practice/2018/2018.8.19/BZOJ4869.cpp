#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)

const int maxN=50100;
const int maxBit=31;
const int blocksize=100000;
const int inf=2147483647;

int n,m,P,C;
int pcnt,phi[maxN];
int A[maxBit][maxN];
int Pow1[maxBit][blocksize],Pow2[maxBit][blocksize];
bool By1[maxBit][blocksize],By2[maxBit][blocksize];
int Sum[maxN<<2];
int Cnt[maxN<<2];
int Tim[maxN];

int GetPhi(int x);
void Init();
int CQPow(int key,int id,bool &flag);
void Build(int now,int l,int r);
void Modify(int now,int l,int r,int ql,int qr);
int Query(int now,int l,int r,int ql,int qr);

int main(){
	//freopen("in.in","r",stdin);freopen("out.out","w",stdout);
	scanf("%d%d%d%d",&n,&m,&P,&C);
	for (int i=1;i<=n;i++) scanf("%d",&A[1][i]);

	int nowP=P;
	while (nowP!=1) phi[++pcnt]=nowP,nowP=GetPhi(nowP);
	phi[++pcnt]=1;phi[++pcnt]=1;

	//cout<<"phi:";for (int i=1;i<=pcnt;i++) cout<<phi[i]<<" ";cout<<endl;

	Init();

	/*
	for (int i=1;i<=n;i++){
		for (int j=1;j<=pcnt;j++) cout<<A[j][i]<<" ";
		cout<<endl;
	}
	return 0;
	//*/
	
	Build(1,1,n);

	while (m--){
		int opt,l,r;scanf("%d%d%d",&opt,&l,&r);
		if (opt==0) Modify(1,1,n,l,r);
		if (opt==1) printf("%d\n",Query(1,1,n,l,r));
	}

	return 0;
}

int GetPhi(int x){
	int ret=x;
	for (int i=2;1ll*i*i<=x;i++)
		if (x%i==0){
			ret=ret/i*(i-1);
			while (x%i==0) x/=i;
		}
	if (x!=1) ret=ret/x*(x-1);
	return ret;
}

void Init(){
	for (int i=1;i<=pcnt;i++){
		Pow1[i][0]=1;By1[i][0]=0;
		for (int j=1;j<blocksize;j++){
			Pow1[i][j]=1ll*Pow1[i][j-1]*C%phi[i];By1[i][j]=By1[i][j-1];
			if (1ll*Pow1[i][j-1]*C>=phi[i]) By1[i][j]=1;
		}
		Pow2[i][0]=1;Pow2[i][1]=1ll*Pow1[i][blocksize-1]*C%phi[i];
		By2[i][1]=By1[i][blocksize-1];
		if (1ll*Pow1[i][blocksize-1]*C>=phi[i]) By2[i][1]=1;
		for (int j=2;j<blocksize;j++){
			Pow2[i][j]=1ll*Pow2[i][j-1]*Pow2[i][1]%phi[i];By2[i][j]=By2[i][j-1];
			if (1ll*Pow2[i][j-1]*Pow2[i][1]>=phi[i]) By2[i][j]=1;
		}
	}
	/*
	for (int i=1;i<=pcnt;i++){
		for (int j=1;j<=10;j++) cout<<Pow1[i][j]<<" ";
		cout<<endl;
	}
	//*/

	for (int i=1;i<=n;i++)
		for (int j=2;j<=pcnt;j++){
			int key=A[1][i];
			for (int k=j-1;k>=1;k--){
				bool flag=0;
				key=CQPow(key,k,flag);
				if (flag) key=key%phi[k]+phi[k];
				//cout<<"QPow:"<<C<<" "<<key<<" "<<phi[k-1]<<" ["<<k-1<<"] "<<CQPow(key,k-1)<<endl;
			}
			A[j][i]=key%P;
		}
	/*
	for (int i=1;i<=3;i++)
	{
		for (int j=1;j<=n;j++){
			if (A[1][j]!=i) continue;
			for (int k=1;k<=pcnt;k++) cout<<A[k][j]<<" ";cout<<endl;
			break;
		}
	}
	//*/
	/*
	for (int i=1;i<=n;i++){
		for (int j=1;j<=pcnt;j++) cout<<A[j][i]<<" ";
		cout<<endl;
	}
	//*/
	return;
}

int CQPow(int key,int id,bool &flag){
	if (key<blocksize){
		flag=By1[id][key];
		return Pow1[id][key];
	}
	else{
		flag=By1[id][key%blocksize]|By2[id][key/blocksize];
		if (1ll*Pow2[id][key/blocksize]*Pow1[id][key%blocksize]>=phi[id]) flag=1;
		return 1ll*Pow2[id][key/blocksize]*Pow1[id][key%blocksize]%phi[id];
	}
}

void Build(int now,int l,int r){
	if (l==r){
		Tim[l]=1;Sum[now]=A[1][l];Cnt[now]=1;
		return;
	}
	int mid=(l+r)>>1;
	Build(lson,l,mid);Build(rson,mid+1,r);
	Sum[now]=(Sum[lson]+Sum[rson])%P;Cnt[now]=Cnt[lson]+Cnt[rson];return;
}

void Modify(int now,int l,int r,int ql,int qr){
	if (Cnt[now]==0) return;
	if (l==r){
		Tim[l]++;Sum[now]=A[Tim[l]][l];
		if (Tim[l]==pcnt) Cnt[now]=0;
		return;
	}
	int mid=(l+r)>>1;
	if (qr<=mid) Modify(lson,l,mid,ql,qr);
	else if (ql>=mid+1) Modify(rson,mid+1,r,ql,qr);
	else{
		Modify(lson,l,mid,ql,mid);Modify(rson,mid+1,r,mid+1,qr);
	}
	Sum[now]=(Sum[lson]+Sum[rson])%P;Cnt[now]=Cnt[lson]+Cnt[rson];return;
}

int Query(int now,int l,int r,int ql,int qr){
	if ((l==ql)&&(r==qr)) return Sum[now];
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
	else return (Query(lson,l,mid,ql,mid)+Query(rson,mid+1,r,mid+1,qr))%P;
}
