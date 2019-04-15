#include<bits/stdc++.h>
using namespace std;

typedef unsigned int uint;
const int maxN=50020;
const int maxK=10;

uint n,srt;uint A,B,C,D;
uint pcnt,notp[maxN+maxN],Pri[maxN+maxN];
uint num,Num[maxN],Id[maxN+maxN];
uint F[4][maxN],Stl[maxK][maxK],Sm[4][maxN];

void Init();
uint GetId(uint X);
uint GetSum(uint r,uint K);
uint QPow(uint x,uint cnt);
pair<uint,uint> S(uint n,uint p);
int main(){
    scanf("%u%u%u%u%u",&n,&A,&B,&C,&D);srt=sqrt(n);
    Init();
    for (uint l=1,r;l<=n;l=r+1){
	r=n/l;Num[++num]=r;for (uint j=0;j<4;j++) F[j][num]=GetSum(r,j)-1;
	if (r<=srt) Id[r]=num;else Id[l+maxN]=num;
	r=n/r;
    }
    
    for (uint i=1;i<=pcnt&&1ll*Pri[i]*Pri[i]<=Num[1];i++)
	for (uint j=1;j<=num&&1ll*Pri[i]*Pri[i]<=Num[j];j++)
	    for (uint k=0;k<4;k++)
		F[k][j]=F[k][j]-(F[k][GetId(Num[j]/Pri[i])]-Sm[k][i-1])*QPow(Pri[i],k);
    printf("%u\n",S(n,1).second);return 0;
}
void Init(){
    notp[1]=1;
    for (uint i=2;i<maxN;i++){
	if (!notp[i]){
	    Pri[++pcnt]=i;for (uint j=0;j<4;j++) Sm[j][pcnt]=Sm[j][pcnt-1]+QPow(i,j);
	}
	for (uint j=1;j<=pcnt&&1ll*i*Pri[j]<maxN;j++){
	    notp[i*Pri[j]]=1;if (i%Pri[j]==0) break;
	}
    }
    Stl[0][0]=1;
    for (uint i=1;i<maxK;i++) for (uint j=1;j<=i;j++) Stl[i][j]=Stl[i-1][j-1]+Stl[i-1][j]*j;
    return;
}
uint GetId(uint X){
    if (X<=srt) return Id[X];
    return Id[n/X+maxN];
}
uint GetSum(uint r,uint K){
    if (K==0) return r;uint ret=0;
    for (uint i=1;i<=min(r,K);i++){
	uint mul=Stl[K][i];bool flag=0;
	for (uint j=r+1;j>r-i;j--)
	    if (j%(i+1)==0&&flag==0) mul=mul*(j/(i+1)),flag=1;else mul=mul*j;
	ret=ret+mul;
    }
    return ret;
}
uint QPow(uint x,uint cnt){
    uint ret=1;
    while (cnt){
	if (cnt&1) ret=ret*x;
	x=x*x;cnt>>=1;
    }
    return ret;
}
pair<uint,uint> S(uint n,uint p){
    if (Pri[p]>n||n<=1) return make_pair(0,0);
    uint r1=0,id=GetId(n),r2=0;
    r1=F[0][id]-Sm[0][p-1];
    r2=A*(F[3][id]-Sm[3][p-1])+B*(F[2][id]-Sm[2][p-1])+C*(F[1][id]-Sm[1][p-1])+D*r1;
    for (uint i=p;i<=pcnt&&1ll*Pri[i]*Pri[i]<=n;i++){
	uint bf=A*QPow(Pri[i],3)+B*QPow(Pri[i],2)+C*Pri[i]+D,f=bf;
	for (uint x=Pri[i];1ll*x*Pri[i]<=n;x*=Pri[i],f=f+bf){
	    pair<uint,uint> rt=S(n/x,i+1);
	    r1+=rt.first;
	    r2=r2+rt.second+f*rt.first;
	    r1++;r2=r2+f+bf;
	}
    }
    return make_pair(r1,r2);
}
