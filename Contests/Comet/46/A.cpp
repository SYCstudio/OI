#include<bits/stdc++.h>
using namespace std;

const int maxN=303000;

int n,Cnt[10];
char S[maxN];

int main(){
    scanf("%s",S+1);n=strlen(S+1);
    for (int i=1;i<=n;i++) ++Cnt[S[i]-'0'];int ans=0;
    while (Cnt[1]>=3&&Cnt[4]>=2&&Cnt[5]>=1){
	++ans;
	Cnt[1]-=3;Cnt[4]-=2;Cnt[5]-=1;
    }
    cout<<ans<<endl;return 0;
}
