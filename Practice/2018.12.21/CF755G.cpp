#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define IL inline
#define RG register
#define Plus(x,y) (x+y)%Mod
#define Minus(x,y) (x-y+Mod)%Mod

const int maxN=40000*2;
const int maxL=33000;
const int Mod=998244353;
const int G=3;
const int inf=2147483647;

int n,K;

int N,L;
int Ans[maxN][3],Ret[maxN][3];
int R[maxN],I1[maxN],I2[maxN],I3[maxN],I4[maxN],C1[maxN],C2[maxN],C3[maxN];

//IL int Plus(RG int x,RG int y);
//IL int Minus(RG int x,RG int y);
IL int QPow(RG int x,RG int cnt);
void Convolution1();
void Convolution2();
IL void Mul( int *A,int *B);
void NTT(int *P,RG int N,RG int opt);

int main(){
	scanf("%d%d",&n,&K);--n;
	
	Ans[0][0]=Ret[0][0]=1;Ans[1][0]=Ret[1][0]=1;
	Ans[0][1]=Ret[0][1]=1;
	//for (int i=0;i<=K;i++) Ans.P[2][i]=((i&1)?(Mod-1):(1));
	//for (int i=0;i<=K;i++) cout<<Ans.P[0][i]<<" ";cout<<endl;
	//for (int i=0;i<=K;i++) cout<<Ans.P[1][i]<<" ";cout<<endl;
	//for (int i=0;i<=K;i++) cout<<Ans.P[2][i]<<" ";cout<<endl<<endl;
	/*
	while (n--){
		Ans=Convolution(Ans,Ret);
		//for (int i=0;i<=K;i++) cout<<Ans.P[0][i]<<" ";cout<<endl;
		//for (int i=0;i<=K;i++) cout<<Ans.P[1][i]<<" ";cout<<endl;
		//for (int i=0;i<=K;i++) cout<<Ans.P[2][i]<<" ";cout<<endl<<endl;
	}
	//*/

	int len=1;
	while (n){
		N=1;L=0;while (N<=len+len) N<<=1,++L;for (int i=0;i<N;i++) R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
		if (n&1) Convolution1();
		Convolution2();n>>=1;len=min(len<<1,K);
	}
	//*/
	for (int i=1;i<=K;i++) printf("%d ",Ans[i][0]);
	printf("\n");return 0;
}

/*
IL int Plus(RG int x,RG int y){
	x+=y;if (x>=Mod) x-=y;
	return x;
}

IL int Minus(RG int x,RG int y){
	x-=y;if (x<0) x+=Mod;
	return x;
}
//*/

IL int QPow(RG int x,RG int cnt){
	RG int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}

void Convolution1(){
	RG int i;
	for (i=0;i<=K;++i) I1[i]=Ans[i][0],I2[i]=Ret[i][0],I3[i]=Ans[i][1],I4[i]=Ret[i][1];
	Mul(I1,I2);Mul(I3,I4);
	C1[0]=I1[0];
	for (i=1;i<=K;++i) C1[i]=Plus(I1[i],I3[i-1]);
	mem(I1,0);mem(I2,0);mem(I3,0);mem(I4,0);

	for (i=0;i<=K;++i) I1[i]=Ans[i][0],I2[i]=Ret[i][1],I3[i]=Ans[i][1],I4[i]=Ret[i][2];
	Mul(I1,I2);Mul(I3,I4);
	C2[0]=I1[0];
	for (i=1;i<=K;++i) C2[i]=Plus(I1[i],I3[i-1]);
	mem(I1,0);mem(I2,0);mem(I3,0);mem(I4,0);

	for (i=0;i<=K;++i) I1[i]=Ans[i][1],I2[i]=Ret[i][1],I3[i]=Ans[i][2],I4[i]=Ret[i][2];
	Mul(I1,I2);Mul(I3,I4);
	C3[0]=I1[0];
	for (i=1;i<=K;++i) C3[i]=Plus(I1[i],I3[i-1]);
	mem(I1,0);mem(I2,0);mem(I3,0);mem(I4,0);

	for (i=0;i<=K;++i) Ans[i][0]=C1[i],Ans[i][1]=C2[i],Ans[i][2]=C3[i];
	return;
}

void Convolution2(){
	RG int i;
	for (i=0;i<=K;++i) I1[i]=Ret[i][0],I2[i]=Ret[i][0],I3[i]=Ret[i][1],I4[i]=Ret[i][1];
	Mul(I1,I2);Mul(I3,I4);
	C1[0]=I1[0];
	for (i=1;i<=K;++i) C1[i]=Plus(I1[i],I3[i-1]);
	mem(I1,0);mem(I2,0);mem(I3,0);mem(I4,0);

	for (i=0;i<=K;++i) I1[i]=Ret[i][0],I2[i]=Ret[i][1],I3[i]=Ret[i][1],I4[i]=Ret[i][2];
	Mul(I1,I2);Mul(I3,I4);
	C2[0]=I1[0];
	for (i=1;i<=K;++i) C2[i]=Plus(I1[i],I3[i-1]);
	mem(I1,0);mem(I2,0);mem(I3,0);mem(I4,0);

	for (i=0;i<=K;++i) I1[i]=Ret[i][1],I2[i]=Ret[i][1],I3[i]=Ret[i][2],I4[i]=Ret[i][2];
	Mul(I1,I2);Mul(I3,I4);
	C3[0]=I1[0];
	for (i=1;i<=K;++i) C3[i]=Plus(I1[i],I3[i-1]);
	mem(I1,0);mem(I2,0);mem(I3,0);mem(I4,0);

	for (int i=0;i<=K;i++) Ret[i][0]=C1[i],Ret[i][1]=C2[i],Ret[i][2]=C3[i];
	return;
}

IL void Mul(int *A,int *B){
	//cout<<"Mul:"<<endl;
	//for (int i=0;i<N;i++) cout<<A[i]<<" ";cout<<endl;
	//for (int i=0;i<N;i++) cout<<B[i]<<" ";cout<<endl;
	NTT(A,N,1);NTT(B,N,1);
	for (RG int i=0;i<N;++i) A[i]=1ll*A[i]*B[i]%Mod;
	NTT(A,N,-1);
	//for (int i=0;i<N;i++) cout<<A[i]<<" ";cout<<endl;
	return;
}

void NTT(int *P,RG int N,RG int opt){
	RG int i,j,k,dw,w,X,Y;
	for (i=0;i<N;++i) if (i<R[i]) swap(P[i],P[R[i]]);
	for (i=1;i<N;i<<=1){
		dw=QPow(G,(Mod-1)/(i<<1));if (opt==-1) dw=QPow(dw,Mod-2);
		for (j=0;j<N;j+=(i<<1))
			for (k=0,w=1;k<i;++k,w=1ll*w*dw%Mod){
				X=P[j+k];Y=1ll*P[j+k+i]*w%Mod;
				P[j+k]=Plus(X,Y);P[j+k+i]=Minus(X,Y);
			}
	}
	if (opt==-1){
		RG int inv=QPow(N,Mod-2);
		for (i=0;i<N;++i) P[i]=1ll*P[i]*inv%Mod;
	}
	return;
}
