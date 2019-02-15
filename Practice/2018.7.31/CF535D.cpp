#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010000;
const int Mod=1e9+7;
const int inf=2147483647;

int n,m,q;
int qcnt,Seq[maxN];
char str[maxN];
int Next[maxN];
bool mark[maxN];

int main()
{
    scanf("%d%d",&n,&q);
    scanf("%s",str+1);m=strlen(str+1);
    for (int i=1;i<=q;i++) scanf("%d",&Seq[i]);

    Next[0]=Next[1]=0;
    for (int i=2;i<=m;i++){
        int j=Next[i-1];
        while ((j!=0)&&(str[j+1]!=str[i])) j=Next[j];
        if (str[j+1]==str[i]) j++;Next[i]=j;
    }

    mark[m]=1;
    for (int i=m;i;i=Next[i]) mark[m-i]=1;

    bool flag=1;
    for (int i=2;i<=q;i++)
        if ((Seq[i]-Seq[i-1]<=m)&&(mark[Seq[i]-Seq[i-1]]==0)){
            flag=0;break;
        }
    if (flag==0){
        printf("0\n");return 0;
    }

    ll empty=n;
    for (int i=2;i<=q;i++) empty-=min(m,Seq[i]-Seq[i-1]);
    if (q!=0) empty-=m;

    ll ans=1;
    while (empty--) ans=1ll*ans*26%Mod;
    printf("%lld\n",ans);
    return 0;
}
