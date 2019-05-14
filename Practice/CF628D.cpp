#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=2010;
const int Mod=1e9+7;

int M,D;
char In[maxN];
int L[maxN],R[maxN];
int F[maxN][2][maxN];

int Calc(int len,int *Num);
void Plus(int &x,int y);
int main(){
    scanf("%d%d",&M,&D);
    scanf("%s",In+1);int l1=strlen(In+1);for (int i=1;i<=l1;i++) L[i]=In[i]-'0';reverse(&L[1],&L[l1+1]);
    scanf("%s",In+1);int l2=strlen(In+1);for (int i=1;i<=l2;i++) R[i]=In[i]-'0';reverse(&R[1],&R[l2+1]);
    ++R[1];for (int i=1;i<=l2;i++) R[i+1]+=R[i]/10,R[i]%=10;
    if (R[l2+1]) ++l2;

    printf("%d\n",(Calc(l2,R)-Calc(l1,L)+1)%Mod);
    return 0;
}
void Plus(int &x,int y){
    x+=y;if (x>=Mod) x-=Mod;return;
}
int Calc(int len,int *Num){
    memset(F,0,sizeof(F));
    F[0][1][0]=1;
    for (int i=1,mul=1;i<=len;i++,mul=10ll*mul%M)
	for (int b=0;b<=1;b++)
	    for (int r=0;r<M;r++)
		if (F[i-1][b][r]){
		    int key=F[i-1][b][r];
		    if (~i&1){
			for (int k=D;k<=D;k++)
			    if ((b==0&&D<=Num[i])||(b==1&&D<Num[i])) Plus(F[i][0][(r+1ll*k*mul%M)%M],key);
			    else Plus(F[i][1][(r+1ll*k*mul%M)%M],key);
		    }
		    else
			for (int k=0;k<=9;k++)
			    if ((b==0&&D<=Num[i])||(b==1&&D<Num[i])) Plus(F[i][0][(r+1ll*k*mul%M)%M],key);
			    else Plus(F[i][1][(r+1ll*k*mul%M)%M],key);
		}
    cout<<F[len][0][0]<<endl;
    return F[len][0][0];
}
