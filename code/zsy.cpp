#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int gi(){
    int x=0,w=1;char ch=getchar();
    while ((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
    if (ch=='-') w=0,ch=getchar();
    while (ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    return w?x:-x;
}
#define ull unsigned long long
const int N = 2e5+5;
const int base = 20020415;
int n,f[N],g[N],ans;char a[N],b[N];
ull hsh[2][N],pw[N];
void manacher(char *s,int *p){
    int mx=0,id=0;
    s[n+n+1]='#';s[0]='-';
    for (int i=n;i;--i) s[i*2]=s[i],s[i*2-1]='#';
    for (int i=1;i<=n+n;++i){
        p[i]=mx>i?min(p[2*id-i],mx-i):0;
        while (s[i-p[i]-1]==s[i+p[i]+1]) ++p[i];
        if (i+p[i]>mx) mx=i+p[i],id=i;
    }
    for (int i=1;i<=n;++i) ans=max(ans,p[i]-1);
}
ull cal(int x,int l,int r){
    if (!x) return hsh[0][r]-hsh[0][l-1]*pw[r-l+1];
    else return hsh[1][l]-hsh[1][r+1]*pw[r-l+1];
}
int binary(int L,int R){
    int l=1,r=min(L,n-R+1),res=0;
    while (l<=r){
        int mid=l+r>>1;
        if (cal(0,L-mid+1,L)==cal(1,R,R+mid-1)) res=mid,l=mid+1;
        else r=mid-1;
    }
    return res;
}
int main(){
    n=gi();scanf("%s",a+1);scanf("%s",b+1);
    pw[0]=1;
    for (int i=1;i<=n;++i) pw[i]=pw[i-1]*base;
    for (int i=1;i<=n;++i) hsh[0][i]=hsh[0][i-1]*base+a[i]-'A';
    for (int i=n;i>=1;--i) hsh[1][i]=hsh[1][i+1]*base+b[i]-'A';
    manacher(a,f);manacher(b,g);
    for (int i=1;i<=n+n;++i){
        int L=i-f[i],R=i+f[i];L=(L+1)/2;R=R/2;
        ans=max(ans,f[i]+binary(L-1,R)*2);
    }
    for (int i=1;i<=n+n;++i){
        int L=i-g[i],R=i+g[i];L=(L+1)/2;R=R/2;
        ans=max(ans,g[i]+binary(L,R+1)*2);
    }
    printf("%d\n",ans);
    return 0;
}
