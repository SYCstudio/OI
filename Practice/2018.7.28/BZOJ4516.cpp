#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000*2;
const int inf=2147483647;

class SAM
{
public:
	map<int,int> son;
	int fa,len;
};

int n;
int nodecnt=1,last=1;
SAM S[maxN];
ll Ans=0;

void Insert(int key);

int main()
{
	int n;scanf("%d",&n);
	for (int i=1;i<=n;i++){
		int key;scanf("%d",&key);
		Insert(key);
		printf("%lld\n",Ans);
	}

	/*
	for (int i=1;i<=nodecnt;i++)
		for (map<int,int>::iterator it=S[i].son.begin();it!=S[i].son.end();it++)
			cout<<i<<"->"<<it->second<<" "<<it->first<<endl;
	//*/
	
	return 0;
}

void Insert(int key){
	int np=++nodecnt,p=last;last=nodecnt;
	S[np].len=S[p].len+1;
	while ((p!=0)&&(S[p].son.count(key)==0)) S[p].son[key]=np,p=S[p].fa;
	if (p==0) S[np].fa=1;
	else{
		int q=S[p].son[key];
		if (S[q].len==S[p].len+1) S[np].fa=q;
		else{
			int nq=++nodecnt;S[nq]=S[q];S[nq].len=S[p].len+1;
			Ans=Ans+S[nq].len-S[S[nq].fa].len;
			Ans=Ans-(S[q].len-S[S[q].fa].len);
			S[q].fa=S[np].fa=nq;
			Ans=Ans+S[q].len-S[S[q].fa].len;
			while ((p!=0)&&(S[p].son.count(key)!=0)&&(S[p].son[key]==q)) S[p].son[key]=nq,p=S[p].fa;
		}
	}
	Ans=Ans+S[last].len-S[S[last].fa].len;
	return;
}
