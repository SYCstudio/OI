#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
#include<string>
#include<queue>
#include<vector>
using namespace std;

const int maxN=40;
const int inf=2147483647;

class Data
{
public:
	int v;
	double w;
};

int n,m;
vector<Data> E[maxN];
map<string,int> Map;
queue<int> Q;
bool inqueue[maxN];
double Dist[maxN];

bool spfa(int s);

int main()
{
	int ti=0;
	while (cin>>n)
	{
		if (n==0)
		    break;
		Map.clear();
		for (int i=1;i<=n;i++)
		    E[i].clear();
		for (int i=1;i<=n;i++)
		{
			string str;
			cin>>str;
			Map[str]=i;
		}
		cin>>m;
		for (int i=1;i<=m;i++)
		{
			string str1,str2;
			double r;
			cin>>str1>>r>>str2;
			E[Map[str1]].push_back((Data){Map[str2],r});
		}
		bool is_ans=0;
		for (int i=1;i<=n;i++)
		    if (spfa(i)==1)
		    {
		    	is_ans=1;
		    	break;
			}
		ti++;
		if (is_ans==1)
		    printf("Case %d: Yes\n",ti);
		else
		    printf("Case %d: No\n",ti);
	}
	return 0;
}

bool spfa(int s)
{
	memset(Dist,0,sizeof(Dist));
	memset(inqueue,0,sizeof(inqueue));
	while (!Q.empty())
	    Q.pop();
	Dist[s]=1;
	Q.push(s);
	inqueue[s]=1;
	do
	{
		if (Dist[s]>1)
		    return 1;
		int u=Q.front();
		Q.pop();
		inqueue[u]=0;
		for (int i=0;i<E[u].size();i++)
		{
			int v=E[u][i].v;
		    if (Dist[v]<Dist[u]*E[u][i].w)
		    {
		    	Dist[v]=Dist[u]*E[u][i].w;
		    	if (inqueue[v]==0)
		    	{
		    		Q.push(v);
		    		inqueue[v]=1;
				}
			}
		}
	}
	while (!Q.empty());
	return 0;
}
