#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10000010*2;
const int maxAlpha=4;
const int inf=2147483647;

class SAM
{
public:
	int len,ch[maxAlpha];
	int fa;
};

int nodecnt=1,last=1;
SAM S[maxN];
char Input[maxN/2];
int Mp[128];

void Insert(int x);

int main(){
	Mp['E']=0;Mp['S']=1;Mp['W']=2;Mp['N']=3;
	int n,m;scanf("%d%d",&n,&m);
	scanf("%s",Input);
	for (int i=0;i<n;i++) Insert(Mp[Input[i]]);

	/*
	for (int i=0;i<=nodecnt;i++)
		for (int j=0;j<maxAlpha;j++)
			if (S[i].ch[j]) cout<<i<<" -> "<<S[i].ch[j]<<" "<<j<<endl;
	//*/
	
	while (m--){
		scanf("%s",Input);
		int now=1,ans=0,len=strlen(Input);
		for (int i=0;i<len;i++)
			if (S[now].ch[Mp[Input[i]]]==0) break;
			else now=S[now].ch[Mp[Input[i]]],++ans;
		printf("%d\n",ans);
	}
	return 0;
}

void Insert(int x){
	int np=++nodecnt,p=last;last=np;
	S[np].len=S[p].len+1;
	while ((p)&&(S[p].ch[x]==0)) S[p].ch[x]=np,p=S[p].fa;
	if (p==0){
		S[np].fa=1;return;
	}
	int q=S[p].ch[x];
	if (S[q].len==S[p].len+1){
		S[np].fa=q;return;
	}
	int nq=++nodecnt;S[nq]=S[q];S[nq].len=S[p].len+1;
	S[q].fa=S[np].fa=nq;
	while ((p)&&(S[p].ch[x]==q)) S[p].ch[x]=nq,p=S[p].fa;
	return;
}

/*
7 3
SNNSSNS
NNSS
NNN
WSEE
//*/
