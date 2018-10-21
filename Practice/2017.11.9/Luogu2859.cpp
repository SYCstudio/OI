#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<stack>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=50010;
const int maxT=1000010;
const int inf=2147483647;

int n;
int cnt=0,Head[maxT],Next[maxN*2],Id[maxN*2];
int Ans[maxN];
stack<int> S;

void Add_Edge(int u,int id);

int main()
{
    mem(Head,-1);
    scanf("%d",&n);
    int mxT=0;
    for (int i=1;i<=n;i++)
    {
	int u,v;scanf("%d%d",&u,&v);
	Add_Edge(u,i);
	Add_Edge(v+1,-i);
	mxT=max(mxT,v+1);
    }
    int sz=0;
    for (int i=1;i<=mxT;i++)
    {
	for (int j=Head[i];j!=-1;j=Next[j])
	    if (Id[j]<0)
		S.push(Ans[-Id[j]]);
	for (int j=Head[i];j!=-1;j=Next[j])
	    if (Id[j]>0)
	    {
		if (S.empty()) Ans[Id[j]]=++sz;
		else
		{
		    Ans[Id[j]]=S.top();
		    S.pop();
		}
	    }
    }
    printf("%d\n",sz);
    for (int i=1;i<=n;i++) printf("%d\n",Ans[i]);
    return 0;
}

void Add_Edge(int u,int id)
{
    cnt++;Next[cnt]=Head[u];Head[u]=cnt;Id[cnt]=id;
    return;
}
