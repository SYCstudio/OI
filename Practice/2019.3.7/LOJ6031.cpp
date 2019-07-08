#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

typedef long long ll;
const int maxN=101000;
const int Alpha=26;
const int maxB=20;

class SAM
{
public:
	int son[Alpha],len,fail;
};

int n,m,Q,K,lstp=1,scnt=1,Enp[maxN<<1],Fa[maxB][maxN<<1];
char In[maxN];
SAM S[maxN<<1];
vector<int> Ft[maxN<<1];

void Extend(int c);
void dfs_sam(int u);
namespace QMIN
{
int Ml[maxN],Mr[maxN],Ps[maxN],Ln[maxN];
char T[maxN];
int main();
}
namespace KMIN
{
const int maxK=350;
int Ps[maxN],Ln[maxN];
vector<int> Vr[maxK][maxK];
char T[maxN];
int main();
}

int main()
{
	scanf("%d%d%d%d",&n,&m,&Q,&K);
	scanf("%s",In+1);
	for (int i=1; i<=n; i++) Extend(In[i]-'a');
	//for (int i=1;i<=scnt;i++) for (int j=0;j<Alpha;j++) if (S[i].son[j]) cout<<i<<"->"<<S[i].son[j]<<" "<<(char)(j+'a')<<endl;
	for (int i=2; i<=scnt; i++) Ft[S[i].fail].push_back(i),Fa[0][i]=S[i].fail;
	dfs_sam(1);
	for (int i=1; i<maxB; i++) for (int j=1; j<=scnt; j++) Fa[i][j]=Fa[i-1][Fa[i-1][j]];
	//for (int i=1;i<=scnt;i++) cout<<Enp[i]<<" ";cout<<endl;
	if (Q<=K) QMIN::main();
	else KMIN::main();
}
void Extend(int c)
{
	int np=++scnt,p=lstp;
	lstp=np;
	S[np].len=S[p].len+1;
	Enp[np]=1;
	while (p&&!S[p].son[c]) S[p].son[c]=np,p=S[p].fail;
	if (!p) S[np].fail=1;
	else {
		int q=S[p].son[c];
		if (S[q].len==S[p].len+1) S[np].fail=q;
		else {
			int nq=++scnt;
			S[nq]=S[q];
			S[nq].len=S[p].len+1;
			S[q].fail=S[np].fail=nq;
			while (p&&S[p].son[c]==q) S[p].son[c]=nq,p=S[p].fail;
		}
	}
	return;
}
void dfs_sam(int u)
{
	for (int i=0,sz=Ft[u].size(); i<sz; i++) dfs_sam(Ft[u][i]),Enp[u]+=Enp[Ft[u][i]];
	return;
}
namespace QMIN
{
int main()
{
	for (int i=1; i<=m; i++) scanf("%d%d",&Ml[i],&Mr[i]),++Ml[i],++Mr[i];
	while (Q--) {
		scanf("%s",T+1);
		int a,b;
		scanf("%d%d",&a,&b);
		++a;
		++b;
		for (int i=1,len=0,now=1; i<=K; i++) {
			int c=T[i]-'a';
			while (now&&!S[now].son[c]) now=S[now].fail,len=S[now].len;
			if (!now) {
				Ps[i]=1;
				Ln[i]=0;
				now=1;
				len=0;
				continue;
			}
			now=S[now].son[c];
			++len;
			Ps[i]=now;
			Ln[i]=len;
		}
		//for (int i=1;i<=K;i++) cout<<Ps[i]<<" "<<Ln[i]<<endl;
		ll Ans=0;
		for (int i=a; i<=b; i++) {
			int l=Mr[i]-Ml[i]+1;
			if (Ln[Mr[i]]<Mr[i]-Ml[i]+1) continue;
			int now=Ps[Mr[i]],len=Ln[now];
			for (int j=maxB-1; j>=0; j--) if (Fa[j][now]&&S[Fa[j][now]].len>=l) now=Fa[j][now],len=S[now].len;
			//cout<<i<<" final:"<<now<<" "<<Enp[now]<<endl;
			Ans=Ans+Enp[now];
		}
		printf("%lld\n",Ans);
	}
	return 0;
}
}
namespace KMIN
{
int main()
{
	for (int i=1; i<=m; i++) {
		int l,r;
		scanf("%d%d",&l,&r);
		++l;
		++r;
		Vr[l][r].push_back(i);
	}
	while (Q--) {
		scanf("%s",T+1);
		int a,b;
		scanf("%d%d",&a,&b);
		++a;
		++b;
		for (int i=1,now=1,len=0; i<=K; i++) {
			int c=T[i]-'a';
			while (now&&!S[now].son[c]) now=S[now].fail,len=S[now].len;
			if (now==0) {
				now=1;
				len=0;
				Ps[i]=now;
				Ln[i]=len;
				continue;
			}
			now=S[now].son[c];
			++len;
			Ps[i]=now;
			Ln[i]=len;
		}
		ll Ans=0;
		for (int r=1; r<=K; r++)
			for (int l=1; l<=r; l++) {
				int now=Ps[r],len=r-l+1;
				if (Ln[r]<len) continue;
				for (int i=maxB-1; i>=0; i--) if (Fa[i][now]&&S[Fa[i][now]].len>=len) now=Fa[i][now];
				int cnt=upper_bound(Vr[l][r].begin(),Vr[l][r].end(),b)-lower_bound(Vr[l][r].begin(),Vr[l][r].end(),a);
				Ans=Ans+cnt*Enp[now];
			}
		printf("%lld\n",Ans);
	}
	return 0;
}
}