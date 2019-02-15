#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000*2;
const int maxAlpha=26;
const int inf=2147483647;

class Node
{
public:
	int son[maxAlpha];
	int fail,len,depth;
	void clear(){
		fail=len=0;mem(son,0);return;
	}
};

int n;
ll Ans=0;
char str[maxN*2];
int last1,last2,nodecnt;
Node S[maxN*2];

void Insert(int pos,int c,int &last,int opt);

int main()
{
	while (scanf("%d",&n)!=EOF)
	{
		mem(str,'\0');
		int l=maxN/2,r=l-1;
		last1=last2=0;nodecnt=1;Ans=0;
		S[0].clear();S[1].clear();
		S[0].fail=S[1].fail=1;
		S[0].len=0;S[1].len=-1;
		S[0].depth=S[1].depth=0;

		for (int i=1;i<=n;i++)
		{
			int opt;scanf("%d",&opt);
			if (opt==1){
				char ch;scanf(" %c",&ch);
				str[--l]=ch;
				Insert(l,ch-'a',last1,-1);
			}
			if (opt==2){
				char ch;scanf(" %c",&ch);
				str[++r]=ch;
				Insert(r,ch-'a',last2,1);
			}
			if (opt==3) printf("%d\n",nodecnt-1);
			if (opt==4) printf("%lld\n",Ans);
			if (S[last1].len==(r-l+1)) last2=last1;
			if (S[last2].len==(r-l+1)) last1=last2;
			//cout<<"["<<l<<","<<r<<"]"<<endl;
		}
	}
	return 0;
}

void Insert(int pos,int c,int &last,int opt)
{
	//cout<<"Insert:"<<pos<<" "<<c<<" "<<opt<<endl;
	int p=last;
	while (str[pos-opt-opt*S[p].len]!=str[pos]) p=S[p].fail;
	if (S[p].son[c]==0)
	{
		int np=++nodecnt,q=S[p].fail;S[np].clear();
		while (str[pos-opt-opt*S[q].len]!=str[pos]) q=S[q].fail;
		S[np].len=S[p].len+2;S[np].fail=S[q].son[c];
		S[np].depth=S[S[np].fail].depth+1;S[p].son[c]=np;
	}
	last=S[p].son[c];
	Ans=Ans+S[last].depth;
	//cout<<S[last].depth<<" "<<S[last].len<<endl;
	return;
}
