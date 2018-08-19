#include<iostream>
#include<cstdio>
#include<map>
#include<cmath>
#include<vector>
using namespace std;

#define ull unsigned long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define IL inline
#define RG register

const int maxN=75;
const ull base=13;
const int Mod=20000007;
const int maxNum=300;
const int inf=2147483647;

int n,P;
class Matrix{
public:
	int M[maxN][maxN];
	IL ull GetHash(){
		RG ull ret=0;RG int i,j;
		for (i=0;i<n;++i) for (j=0;j<n;++j) ret=ret*base+(ull)M[i][j];
		return ret;
	}
	void Outp(){
		/*
		for (int i=0;i<n;i++){
			for (int j=0;j<n;j++)
				cout<<M[i][j]<<" ";
			cout<<endl;
		}
		cout<<endl;
		//*/
	}
};

class HashTable
{
private:
	int edgecnt,Next[maxNum];
	map<int,int> Head;
	pair<ull,int> V[maxNum];
public:
	void Insert(pair<ull,int> pr){
		int p=pr.first%Mod;
		Next[++edgecnt]=Head[p];Head[p]=edgecnt;V[edgecnt]=pr;return;
	}

	int Query(ull key){
		int p=key%Mod,i;
		if (Head.count(p)==0) return -1;
		for (i=Head[p];i;i=Next[i]) if (V[i].first==key) return V[i].second;
		return -1;
	}
};

Matrix A,B,T,now;
HashTable HT;

IL Matrix Mul(const Matrix A,const Matrix B);
IL Matrix QPow(RG Matrix A,RG int cnt);

int main(){
	//freopen("2.in","r",stdin);
	scanf("%d%d",&n,&P);
	RG int i,j;
	for (i=0;i<n;++i) for (j=0;j<n;++j) scanf("%d",&A.M[i][j]);
	for (i=0;i<n;++i) for (j=0;j<n;++j) scanf("%d",&B.M[i][j]);

	RG int m=ceil(sqrt(P));
	now=B;HT.Insert(make_pair(now.GetHash(),0));
	for (i=0;i<n;++i) T.M[i][i]=1;
	for (i=1;i<=m;++i){
		now=Mul(now,A);//T=Mul(T,A);
		HT.Insert(make_pair(now.GetHash(),i));
		//cout<<i<<":"<<now.GetHash()<<endl;
		//now.Outp();
	}
	for (i=0;i<n;++i) for (j=0;j<n;++j) now.M[i][j]=0;
	T=QPow(A,m);
	for (i=0;i<n;++i) now.M[i][i]=1;
	for (i=1;i<=m;++i){
		now=Mul(now,T);
		
		RG int hs=HT.Query(now.GetHash());
		if (hs!=-1){
			printf("%d\n",((i*m-hs)%P+P)%P);break;
		}
		//*/
	}

	return 0;
}

IL Matrix Mul(const Matrix A,const Matrix B){
	RG Matrix Ret;
	RG int i,j,k;
	for (i=0;i<n;++i) for (j=0;j<=n;++j) Ret.M[i][j]=0;
	for (k=0;k<n;++k)
		for (i=0;i<n;++i)
			for (j=0;j<n;++j)
				Ret.M[i][j]=(Ret.M[i][j]+A.M[i][k]*B.M[k][j]%P)%P;
	return Ret;
}

IL Matrix QPow(RG Matrix A,RG int cnt){
	RG Matrix Ret;RG int i;
	for (i=0;i<n;++i) Ret.M[i][i]=1;
	while (cnt){
		if (cnt&1) Ret=Mul(Ret,A);
		A=Mul(A,A);cnt>>=1;
	}
	return Ret;
}
/*
2 7
1 1
1 0
5 3
3 2
//*/

