#include<bits/stdc++.h>
using namespace std;

const int maxN=1010;

int n,m,Q;
char S[maxN],T[maxN];
int Nxt[maxN],Mch[maxN];

int main(){
    scanf("%d%d%d",&n,&m,&Q);scanf("%s",S+1);scanf("%s",T+1);
    Nxt[0]=Nxt[1]=0;
    for (int i=2,j=0;i<=m;i++){
	while (j&&T[j+1]!=T[i]) j=Nxt[j];
	if (T[j+1]==T[i]) ++j;Nxt[i]=j;
    }
    for (int i=1,j=0;i<=n;i++){
	while (j&&T[j+1]!=S[i]) j=Nxt[j];
	if (T[j+1]==S[i]) ++j;
	if (j==m) Mch[i]=1,j=Nxt[j];
	Mch[i]+=Mch[i-1];
    }
    while (Q--){
	int l,r;scanf("%d%d",&l,&r);l+=m-1;
	if (l>r) puts("0");else printf("%d\n",Mch[r]-Mch[l-1]);
    }
    return 0;
}
