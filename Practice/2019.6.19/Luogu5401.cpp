#include<bits/stdc++.h>
using namespace std;

const int maxN=101000;

char S[maxN],T[maxN];
int Next[maxN],Extend[maxN];

int main(){
    scanf("%s",S+1);scanf("%s",T+1);
    int n=strlen(S+1),m=strlen(T+1);

    Next[1]=m;int pos=2,p=0;
    while (pos+p<=m&&T[1+p]==T[pos+p]) ++p;
    Next[2]=p;
    for (int i=3;i<=m;i++){
	//cout<<i<<" "<<pos<<" "<<p<<endl;
	int len=Next[i-pos+1];
	if (i+len<p) Next[i]=len;
	else{
	    Next[i]=max(p-i,0);
	    while (i+Next[i]<=m&&T[i+Next[i]]==T[1+Next[i]]) ++Next[i];
	    p=i+Next[i]-1;pos=i;
	}
    }

    for (int i=1;i<=m;i++) printf("%d ",Next[i]);puts("");

    pos=1;p=0;
    while (pos+p<=n&&pos+p<=m&&S[p+1]==T[p+1]) ++p;
    Extend[1]=p;
    for (int i=2;i<=n;i++){
	//cout<<i<<" "<<pos<<" "<<p<<endl;
	int len=Next[i-pos+1];
	if (i+len<p) Extend[i]=len;
	else{
	    Extend[i]=max(0,p-i);
	    while (i+Extend[i]<=n&&1+Extend[i]<=m&&S[i+Extend[i]]==T[Extend[i]+1]) ++Extend[i];
	    p=i+Extend[i]-1;pos=i;
	}
    }

    for (int i=1;i<=n;i++) printf("%d ",Extend[i]);return 0;
}
