#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxN=101000;
const int maxT=26;
const int Mod=1e9+7;

ll n;
char In[maxN];
int M1[maxT][maxT],M2[maxT],Bp[maxT][maxT];

void Mul1();
void Mul2();
int main(){
    scanf("%lld",&n);scanf("%s",In+1);int m=strlen(In+1);
    for (int i=0;i<maxT;i++) for (int j=0;j<maxT;j++) M1[i][j]=1;
    for (int i=1;i<m;i++) M1[In[i+1]-'a'][In[i]-'a']=0;
    --n;for (int i=0;i<maxT;i++) M2[i]=1;
    while (n){
	if (n&1) Mul1();
	Mul2();n>>=1;
    }
    int Ans=0;for (int i=0;i<maxT;i++) Ans=(Ans+M2[i])%Mod;
    printf("%d\n",Ans);return 0;
}
void Mul1(){
    for (int i=0;i<maxT;i++) Bp[0][i]=M2[i],M2[i]=0;
    for (int j=0;j<maxT;j++)
	for (int k=0;k<maxT;k++)
	    M2[j]=(M2[j]+1ll*Bp[0][k]*M1[k][j]%Mod)%Mod;
    return;
}
void Mul2(){
    for (int i=0;i<maxT;i++) for (int j=0;j<maxT;j++) Bp[i][j]=M1[i][j],M1[i][j]=0;
    for (int i=0;i<maxT;i++)
	for (int j=0;j<maxT;j++)
	    for (int k=0;k<maxT;k++)
		M1[i][j]=(M1[i][j]+1ll*Bp[i][k]*Bp[k][j]%Mod)%Mod;
    return;
}
