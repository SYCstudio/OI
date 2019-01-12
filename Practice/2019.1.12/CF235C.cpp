#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010000*2;
const int Alpha=26;

class SAM{
public:
    int son[Alpha],len,fail;
};

int n;
char In[maxN];
int nodecnt=1,root=1,lst=1;
SAM S[maxN];
int tim,Tim[maxN],Eps[maxN];
vector<int> T[maxN];

void Extend(int c);
void dfs(int x);

int main(){
    scanf("%s",In+1);int len=strlen(In+1);
    for (int i=1;i<=len;i++) Extend(In[i]-'a');
    for (int i=2;i<=nodecnt;i++) T[S[i].fail].push_back(i);
    dfs(1);

    scanf("%d",&n);
    while (n--){
	scanf("%s",In+1);int L=strlen(In+1),Ans=0;++tim;
	for (int i=1;i<L;i++) In[i+L]=In[i];
	for (int i=1,now=1,l=0;i<=L+L-1;i++){
	    while ((now)&&(S[now].son[In[i]-'a']==0)) now=S[now].fail,l=S[now].len;
	    if (now==0){
		now=1;continue;
	    }
	    now=S[now].son[In[i]-'a'];++l;
	    while (S[S[now].fail].len+1>L) now=S[now].fail,l=S[now].len;
	    if (l>=L) if (Tim[now]!=tim) Ans+=Eps[now],Tim[now]=tim;
	}
	printf("%d\n",Ans);
    }
    return 0;
}

void Extend(int c){
    int np=++nodecnt,p=lst;lst=nodecnt;S[np].len=S[p].len+1;Eps[np]=1;
    while (p&&S[p].son[c]==0) S[p].son[c]=np,p=S[p].fail;
    if (p==0) S[np].fail=root;
    else{
	int q=S[p].son[c];
	if (S[q].len==S[p].len+1) S[np].fail=q;
	else{
	    int nq=++nodecnt;S[nq]=S[q];S[nq].len=S[p].len+1;S[q].fail=S[np].fail=nq;
	    while (p&&S[p].son[c]==q) S[p].son[c]=nq,p=S[p].fail;
	}
    }
    return;
}
void dfs(int x){
    for (int i=0,sz=T[x].size();i<sz;i++) dfs(T[x][i]),Eps[x]+=Eps[T[x][i]];
    return;
}
