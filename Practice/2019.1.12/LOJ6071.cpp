#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010000*2;
const int Alpha=26;
const int Mod=1e9+7;

class SAM
{
public:
	int son[Alpha],fail,len;
};

int n,nodecnt=0,lst=0,root=0,rt[maxN],F[maxN],D[maxN],Q[maxN];
SAM S[maxN];
char I[maxN];

void Extend(int c);
void Plus(int &x,int y);

int main()
{
	scanf("%d",&n);
	for (int i=1; i<=n; i++) {
		scanf("%s",I+1);
		int len=strlen(I+1);
		lst=root=rt[i]=++nodecnt;
		for (int i=1; i<=len; i++) Extend(I[i]-'a');
	}

	/*
	for (int i=1;i<=nodecnt;i++)
	for (int j=0;j<Alpha;j++)
	    if (S[i].son[j]) cout<<i<<" "<<S[i].son[j]<<" "<<(char)(j+'a')<<endl;
	//*/

	for (int i=n-1; i>=1; i--)
		for (int j=rt[i]; j<rt[i+1]; j++)
			for (int k=0; k<Alpha; k++)
				if (S[j].son[k]==0) S[j].son[k]=S[rt[i+1]].son[k];

	/*
	cout<<"new:"<<endl;
	for (int i=1;i<=nodecnt;i++)
	for (int j=0;j<Alpha;j++)
	    if (S[i].son[j]) cout<<i<<" "<<S[i].son[j]<<" "<<(char)(j+'a')<<endl;
	//*/

	for (int i=1; i<=nodecnt; i++) for (int j=0; j<Alpha; j++) if (S[i].son[j]) ++D[S[i].son[j]];
	int ql=0,qr=0;
	F[rt[1]]=1;
	for (int i=1; i<=nodecnt; i++) if (D[i]==0) Q[++qr]=i;
	while (ql<=qr)
		for (int u=Q[++ql],i=0; i<Alpha; i++)
			if (S[u].son[i]) {
				Plus(F[S[u].son[i]],F[u]);
				if ((--D[S[u].son[i]])==0) Q[++qr]=S[u].son[i];
			}
	int Ans=0;
	for (int i=1; i<=nodecnt; i++) Plus(Ans,F[i]);
	printf("%d\n",Ans);
	return 0;
}

void Extend(int c)
{
	int np=++nodecnt,p=lst;
	lst=nodecnt;
	S[np].len=S[p].len+1;
	while (p&&S[p].son[c]==0) S[p].son[c]=np,p=S[p].fail;
	if (p==0) S[np].fail=root;
	else {
		int q=S[p].son[c];
		if (S[q].len==S[p].len+1) S[np].fail=q;
		else {
			int nq=++nodecnt;
			S[nq]=S[q];
			S[nq].len=S[p].len+1;
			S[q].fail=S[np].fail=nq;
			while (p&&S[p].son[c]==q) S[p].son[c]=nq,p=S[p].fail;
		}
	}
	return;
}
void Plus(int &x,int y)
{
	x+=y;
	if (x>=Mod) x-=Mod;
	return;
}
