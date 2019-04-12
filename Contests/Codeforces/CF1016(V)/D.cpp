#include<bits/stdc++.h>
using namespace std;

#define pw(x) (1<<(x))
const int maxN=110;

int n,m;
int A[maxN],B[maxN],C1[maxN],C2[maxN];
int Ans[maxN][maxN];

void IMP();
int main(){
    scanf("%d%d",&n,&m);for (int i=1;i<=n;i++) scanf("%d",&A[i]);for (int i=1;i<=m;i++) scanf("%d",&B[i]);
    for (int b=31;b>=0;b--){
	int cnt1=0,cnt2=0;
	for (int i=1;i<=n;i++) if (A[i]&pw(b)) C1[++cnt1]=i;
	for (int i=1;i<=m;i++) if (B[i]&pw(b)) C2[++cnt2]=i;
	int mnc=min(cnt1,cnt2);
	for (int i=1;i<=mnc;i++) Ans[C1[i]][C2[i]]|=pw(b);
	if (cnt1>mnc){
	    if ((cnt1-mnc)&1) IMP();
	    for (int i=mnc+1;i<=cnt1;i++) Ans[C1[i]][1]|=pw(b);
	}
	if (cnt2>mnc){
	    if ((cnt2-mnc)&1) IMP();
	    for (int i=mnc+1;i<=cnt2;i++) Ans[1][C2[i]]|=pw(b);
	}
    }
    puts("YES");
    for (int i=1;i<=n;i++){
	for (int j=1;j<=m;j++) printf("%d ",Ans[i][j]);printf("\n");
    }
    return 0;
}
void IMP(){
    puts("NO");exit(0);
}
