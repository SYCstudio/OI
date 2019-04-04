#include<bits/stdc++.h>
using namespace std;

const int maxN=4040000;
const int Alpha=26;

class Trie{
public:
    int son[Alpha];
};
class SAM{
public:
    int son[Alpha],len,fail;
};

int n,Q,Qu[maxN],Lst[maxN],Edp[maxN];
Trie T[maxN];
int scnt=1;
SAM S[maxN];
vector<int> Vt[maxN];
char In[maxN];

int Extend(int c,int lst);
void dfs_init(int u);
int main(){
    scanf("%d%d",&n,&Q);
    for (int i=1;i<=n;i++){
	int fa;char ch;scanf(" %c%d",&ch,&fa);
	T[fa].son[ch-'A']=i;
    }
    Lst[0]=1;int ql=1,qr=1;Qu[1]=0;
    while (ql<=qr){
	int u=Qu[ql++];
	for (int i=0;i<Alpha;i++) if (T[u].son[i]) ++Edp[Lst[Qu[++qr]=T[u].son[i]]=Extend(i,Lst[u])];
    }
    for (int i=2;i<=scnt;i++) Vt[S[i].fail].push_back(i);
    dfs_init(1);
    while (Q--){
	scanf("%s",In+1);int len=strlen(In+1);
	int now=1;
	for (int i=1;i<=len;i++) now=S[now].son[In[len-i+1]-'A'];
	printf("%d\n",Edp[now]);
    }
    return 0;
}
int Extend(int c,int lst){
    if (S[lst].son[c]&&S[S[lst].son[c]].len==S[lst].len+1) return lst=S[lst].son[c];
    int np=++scnt,p=lst;lst=np;S[np].len=S[p].len+1;
    while (p&&S[p].son[c]==0) S[p].son[c]=np,p=S[p].fail;
    if (!p) S[np].fail=1;
    else{
	int q=S[p].son[c];
	if (S[q].len==S[p].len+1) S[np].fail=q;
	else{
	    int nq=++scnt;S[nq]=S[q];S[nq].len=S[p].len+1;S[np].fail=S[q].fail=nq;
	    while (p&&S[p].son[c]==q) S[p].son[c]=nq,p=S[p].fail;
	}
    }
    return lst;
}
void dfs_init(int u){
    for (int i=0,sz=Vt[u].size();i<sz;i++) dfs_init(Vt[u][i]),Edp[u]+=Edp[Vt[u][i]];
    return;
}
