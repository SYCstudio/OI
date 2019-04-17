#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=101000;

char In[maxN];
int Sa[maxN],Ht[maxN],Rk[maxN];

void Sais(int n,int *s);
void Inducesort(int n,int m,int *s,int *lms,int *la);
int main(){
    scanf("%s",In+1);int len=strlen(In+1);
    static int Bk[40],Rk[maxN],Str[maxN];memset(Bk,0,sizeof(Bk));
    for (int i=1;i<=len;i++) Bk[In[i]-'a'+2]=1;
    Bk[1]=1;
    for (int i=1;i<=30;i++) Bk[i]+=Bk[i-1];
    for (int i=1;i<=len;i++) Str[i]=Bk[In[i]-'a'+2];
    Str[++len]=1;
    Sais(len,Str);
    for (int i=1;i<len;i++) Rk[Sa[i]]=i;
    for (int i=1,j=0;i<=len;i++){
	while (Str[i+j]==Str[Sa[Rk[i]+1]+j]) ++j;
	Ht[Rk[i]]=j;if (j) --j;
    }
    for (int i=2;i<=len;i++) printf("%d ",Sa[i]);printf("\n");
    for (int i=2;i<len;i++) printf("%d ",Ht[i]);printf("\n");
    return 0;
}
void Sais(int n,int *s){
    int Label[maxN],Lms[maxN],m=0,nS[maxN],tot=0;Label[n]=1;
    for (int i=n-1;i>=1;i--) Label[i]=(s[i]==s[i+1]?Label[i+1]:(s[i]<s[i+1]));
    for (int i=1;i<=n;i++) if (Label[i]&&!Label[i-1]) Lms[Rk[i]=++m]=i;else Rk[i]=-1;
    Inducesort(n,m,s,Lms,Label);Lms[m+1]=n+1;
    for (int i=1,lst=0;i<=n;i++)
	if (Rk[Sa[i]]!=-1){
	    int now=Rk[Sa[i]];
	    if (lst==0||Lms[now+1]-Lms[now]!=Lms[lst+1]-Lms[lst]) ++tot;
	    else for (int p=Lms[now],q=Lms[lst];p<=Lms[now+1];p++,q++)
		     if (s[p]*2+Label[p]!=s[q]*2+Label[q]){
			 ++tot;break;
		     }
	    nS[lst=now]=tot;
	}
    if (tot==m) for (int i=1;i<=m;i++) Sa[nS[i]]=i;else Sais(m,nS);
    for (int i=1;i<=m;i++) nS[i]=Lms[Sa[i]];
    Inducesort(n,m,s,nS,Label);
    return;
}
void Inducesort(int n,int m,int *s,int *lms,int *la){
    static int sum[maxN],pm[maxN];
    for (int i=1;i<=n;i++) Sa[i]=-1;
    for (int i=1;i<=n;i++) sum[i]=0;
    for (int i=1;i<=n;i++) ++sum[s[i]];
    for (int i=1;i<=n;i++) sum[i]+=sum[i-1],pm[i]=sum[i];
    for (int i=m;i>=1;i--) Sa[pm[s[lms[i]]]--]=lms[i];
    for (int i=1;i<=n;i++) pm[i]=sum[i-1]+1;
    for (int i=1;i<=n;i++) if (Sa[i]>1&&!la[Sa[i]-1]) Sa[pm[s[Sa[i]-1]]++]=Sa[i]-1;
    for (int i=1;i<=n;i++) pm[i]=sum[i];
    for (int i=n;i>=1;i--) if (Sa[i]>1&&la[Sa[i]-1]) Sa[pm[s[Sa[i]-1]]--]=Sa[i]-1;
    return;
}
