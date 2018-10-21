#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=201000;
const int maxAlpha=26;
const int inf=2147483647;

class Node
{
public:
	int son[maxAlpha];
	int fa,len;
};

int l1,l2;
char str[maxN];
int nodecnt=1,root=1,last=1;
Node S[maxN<<1];
ll Endpos[maxN<<1];
ll Sorter[maxN<<1],Id[maxN<<1],Cnt[maxN<<1],F[maxN<<1];

void Insert(int c);

int main()
{
	scanf("%s",str+1);
	l1=strlen(str+1);
	for (int i=1;i<=l1;i++) Insert(str[i]-'a');

	/*
	for (int i=1;i<=nodecnt;i++)
		for (int j=0;j<maxAlpha;j++)
			if (S[i].son[j])
				cout<<i<<" -> "<<S[i].son[j]<<" ["<<(char)(j+'a')<<"]"<<endl;
	//*/

	for (int i=1;i<=nodecnt;i++) Sorter[S[i].len]++;
	for (int i=1;i<=l1;i++) Sorter[i]+=Sorter[i-1];
	for (int i=nodecnt;i>=1;i--) Id[Sorter[S[i].len]--]=i;

	for (int i=nodecnt;i>=1;i--) Endpos[S[Id[i]].fa]+=Endpos[Id[i]];

	//cout<<"Endpos:";for (int i=1;i<=nodecnt;i++) cout<<Endpos[i]<<" ";cout<<endl;

	scanf("%s",str+1);
	l2=strlen(str+1);

	ll Ans=0;
	for (int i=1,now=root,l=0;i<=l2;i++)
	{
		int c=str[i]-'a';
		if (S[now].son[c]) now=S[now].son[c],l++;
		else
		{
			while ((now!=0)&&(S[now].son[c]==0)) now=S[now].fa;
			if (S[now].son[c]) l=S[now].len+1,now=S[now].son[c];
			else l=0,now=root;
		}
		Cnt[now]++;
		//cout<<now<<" ";
		Ans=Ans+Endpos[now]*(l-S[S[now].fa].len);
	}
	//cout<<endl;
	//cout<<"Cnt:";for (int i=1;i<=nodecnt;i++) cout<<Cnt[i]<<" ";cout<<endl;

	for (int i=nodecnt;i>=1;i--) F[S[Id[i]].fa]+=F[Id[i]]+Cnt[Id[i]];

	//cout<<"F:";for (int i=1;i<=nodecnt;i++) cout<<F[i]<<" ";cout<<endl;

	for (int i=2;i<=nodecnt;i++) Ans=Ans+Endpos[i]*F[i]*(S[i].len-S[S[i].fa].len);

	printf("%lld\n",Ans);
	return 0;
}

void Insert(int c)
{
	int np=++nodecnt,p=last;last=nodecnt;
	S[np].len=S[p].len+1;Endpos[np]=1;
	while ((p!=0)&&(S[p].son[c]==0)) S[p].son[c]=np,p=S[p].fa;
	if (p==0) S[np].fa=root;
	else
	{
		int q=S[p].son[c];
		if (S[p].len+1==S[q].len) S[np].fa=q;
		else
		{
			int nq=++nodecnt;S[nq]=S[q];
			S[nq].len=S[p].len+1;
			S[q].fa=S[np].fa=nq;
			while ((p!=0)&&(S[p].son[c]==q)) S[p].son[c]=nq,p=S[p].fa;
		}
	}
	return;
}
