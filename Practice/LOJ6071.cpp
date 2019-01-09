#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010000*2;
const int Alpha=26;
const int Mod=1e9+7;

class SAM{
public:
    int son[Alpha],len,fail;
};

char Input[maxN];
int nodecnt,lst,G[Alpha],F[maxN],D[maxN],Q[maxN];
bool use[Alpha];
SAM S[maxN];

void Extend(int c);
void Plus(int &x,int y);

int main(){
    int n;scanf("%d",&n);
    int Ans=1;
    for (int i=0;i<Alpha;i++) G[i]=1;
    for (int ni=1;ni<=n;ni++){
	scanf("%s",Input+1);int len=strlen(Input+1);
	nodecnt=lst=1;
	for (int i=1;i<=len+len+10;i++) F[i]=S[i].len=S[i].fail=D[i]=0,mem(S[i].son,0);
	for (int i=1;i<=len;i++) Extend(Input[i]-'a');

	for (int i=1;i<=nodecnt;i++)
	    for (int j=0;j<Alpha;j++)
		if (S[i].son[j]) cout<<i<<" -> "<<S[i].son[j]<<" ["<<(char)(j+'a')<<"]"<<endl;
	cout<<endl;
	
	for (int i=1;i<=nodecnt;i++)
	    for (int j=0;j<Alpha;j++)
		if (S[i].son[j]) ++D[S[i].son[j]];
	for (int i=0;i<Alpha;i++) if (S[1].son[i]) F[S[1].son[i]]=G[i],G[i]=0;
	
	int qL=0,qR=0;
	for (int i=1;i<=nodecnt;i++) if (D[i]==0) Q[++qR]=i;
	while (qL<=qR){
	    int u=Q[++qL];
	    for (int i=0;i<Alpha;i++)
		if (S[u].son[i]){
		    Plus(F[S[u].son[i]],F[u]);
		    if ((--D[S[u].son[i]])==0) Q[++qR]=S[u].son[i];
		}
		else Plus(G[i],F[u]);
	}
	for (int i=1;i<=nodecnt;i++) Plus(Ans,F[i]);
	
	for (int i=1;i<=nodecnt;i++) cout<<F[i]<<" ";cout<<endl;
	for (int i=0;i<Alpha;i++) cout<<G[i]<<" ";cout<<endl;
    }
    printf("%d\n",Ans);return 0;
}
void Extend(int c){
    int np=++nodecnt,p=lst;lst=nodecnt;S[np].len=S[p].len+1;
    while (p&&(S[p].son[c]==0)) S[p].son[c]=np,p=S[p].fail;
    if (p==0) S[np].fail=1;
    else{
	int q=S[p].son[c];
	if (S[q].len==S[p].len+1) S[np].fail=q;
	else{
	    int nq=++nodecnt;S[nq]=S[q];S[nq].len=S[p].len+1;
	    S[q].fail=S[np].fail=nq;
	    while (p&&(S[p].son[c]==q)) S[p].son[c]=nq,p=S[p].fail;
	}
    }
    return;
}

void Plus(int &x,int y){
    x+=y;if (x>=Mod) x-=Mod;return;
}
/*
5
ac
bbbb
dbcddbb
a
babaaca
11254
//*/
