//后缀自动机上匹配循环串，类似AC自动机上跳fail指针，这里也是找到第一个有这个字符的出边的点，但是要注意一些特殊情况，还有不能重复计算
//endpos的计算可以用后缀树上统计完成
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxAlpha=26;
const int inf=2147483647;

class SAM
{
public:
	int ch[maxAlpha];
	int fa,len;
};

int n,nodecnt=1,root=1,last=1;
char str[maxN<<1];
SAM S[maxN<<1];
int Size[maxN<<1],Degree[maxN<<1],Q[maxN<<1];
bool vis[maxN<<1];

void Insert(int key);

int main()
{
	scanf("%s",str+1);
	int Len=strlen(str+1);
	for (int i=1;i<=Len;i++) Insert(str[i]-'a');

	/*
	for (int i=1;i<=nodecnt;i++)
		for (int j=0;j<maxAlpha;j++)
			if (S[i].ch[j]) cout<<i<<"->"<<S[i].ch[j]<<" "<<(char)(j+'a')<<endl;
    //*/
	
	for (int i=2;i<=nodecnt;i++) Degree[S[i].fa]++;
	int h=0,t=0;
	for (int i=1;i<=nodecnt;i++) if (Degree[i]==0) Q[++h]=i;
	do
	{
		int u=Q[++t];
		Degree[S[u].fa]--;Size[S[u].fa]+=Size[u];
		if (Degree[S[u].fa]==0) Q[++h]=S[u].fa;
	}
	while (t!=h);

	//for (int i=1;i<=nodecnt;i++) cout<<Size[i]<<" ";cout<<endl;
	//for (int i=1;i<=nodecnt;i++) cout<<S[i].len<<" ";cout<<endl;

	scanf("%d",&n);
	while (n--)
	{
		scanf("%s",str+1);
		//cout<<"Input:"<<(str+1)<<endl;
		int l=strlen(str+1);
		int now=root;mem(vis,0);
		int Ans=0,len=0;

		for (int i=1;i<l;i++) str[i+l]=str[i];
		//l=l+l-1;

		for (int i=1;i<=l+l-1;i++)
		{
			while ((now!=0)&&(S[now].ch[str[i]-'a']==0)) now=S[now].fa,len=S[now].len;
			if (S[now].ch[str[i]-'a']!=0) now=S[now].ch[str[i]-'a'],len++;
			else now=1,len=0;
			if (len>l)
				while (S[S[now].fa].len>=l) now=S[now].fa,len=S[now].len;
			if ((len>=l)&&(vis[now]==0)) vis[now]=1,Ans+=Size[now];
			//cout<<i<<" "<<now<<" "<<len<<" "<<Size[now]<<endl;
		}

		printf("%d\n",Ans);
	}
	return 0;
}

void Insert(int key)
{
	int np=++nodecnt,p=last;last=nodecnt;
	S[np].len=S[p].len+1;Size[np]=1;
	while ((p!=0)&&(S[p].ch[key]==0)) S[p].ch[key]=np,p=S[p].fa;
	if (p==0) S[np].fa=root;
	else
	{
		int q=S[p].ch[key];
		if (S[p].len+1==S[q].len) S[np].fa=q;
		else
		{
			int nq=++nodecnt;
			S[nq]=S[q];S[nq].len=S[p].len+1;
			S[q].fa=S[np].fa=nq;
			while ((p!=0)&&(S[p].ch[key]==q)) S[p].ch[key]=nq,p=S[p].fa;
		}
	}
	return;
}
