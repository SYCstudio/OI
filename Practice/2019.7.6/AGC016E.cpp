#include<bits/stdc++.h>
using namespace std;

const int maxN=410;
const int maxM=101000;

int n,m;
int P1[maxM],P2[maxM],Mark[maxN];
bitset<maxN> B[maxN];

int main(){
    scanf("%d%d",&n,&m);for (int i=1;i<=m;i++) scanf("%d%d",&P1[i],&P2[i]);
    for (int i=1;i<=n;i++){
	B[i][i]=1;
	for (int j=m;j>=1;j--)
	    if (B[i][P1[j]]&&B[i][P2[j]]){
		Mark[i]=1;break;
	    }
	    else if (B[i][P1[j]]||B[i][P2[j]]) B[i][P1[j]]=B[i][P2[j]]=1;
    }
    int Ans=0;
    for (int i=1;i<=n;i++) for (int j=i+1;j<=n;j++) if (!Mark[i]&&!Mark[j]&&!(B[i]&B[j]).any()) ++Ans;
    printf("%d\n",Ans);return 0;
}
