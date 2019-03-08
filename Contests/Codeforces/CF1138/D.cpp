#include<bits/stdc++.h>
using namespace std;

const int maxN=705000;
const int inf=2000000000;

int n;
char In[maxN],T[maxN];
int Nxt[maxN];

int main(){
    scanf("%s",In+1);int len=strlen(In+1),cnt[2];cnt[0]=cnt[1]=0;
    for (int i=1;i<=len;i++) ++cnt[In[i]-'0'];
    scanf("%s",T+1);n=strlen(T+1);
    Nxt[0]=Nxt[1]=0;
    for (int i=2,j=0;i<=n;i++){
        while (j&&T[j+1]!=T[i]) j=Nxt[j];
        if (T[j+1]==T[i]) ++j;
        Nxt[i]=j;
    }
    int use[2];use[0]=use[1]=0;
    for (int i=1;i<=n;i++) ++use[T[i]-'0'];
    if (use[0]>cnt[0]||use[1]>cnt[1]){
        printf("%s",In+1);return 0;
    }
    printf("%s",T+1);cnt[0]-=use[0];cnt[1]-=use[1];
    use[0]=use[1]=0;
    for (int i=Nxt[n]+1;i<=n;i++) ++use[T[i]-'0'];
    int t=inf;
    if (use[0]) t=min(t,cnt[0]/use[0]);
    if (use[1]) t=min(t,cnt[1]/use[1]);
    cnt[0]-=use[0]*t;cnt[1]-=use[1]*t;
    while (t--) for (int i=Nxt[n]+1;i<=n;i++) printf("%c",T[i]);
    while (cnt[0]--) printf("0");
    while (cnt[1]--) printf("1");
    return 0;
}