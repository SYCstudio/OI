#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
#include<vector>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=52010*2;
const int maxTrie=140000;
const int inf=2147483647;

class TrieData
{
public:
	int id,fail,cnt;
	map<int,int> Son;
	TrieData()
		{
			id=cnt=0;return;
		}
};

int n,m;
int nodecnt=0;
TrieData T[maxTrie];
vector<int> FName[maxN],LName[maxN];
queue<int> Queue;
int idcnt=0,Ans1[maxN],Ans2[maxN];
int Hist[maxN];
int NodeId[maxN];
map<int,int>::iterator iii;

void Insert(int id);
void GetFail();
void AhoCorasick(vector<int> V,int id);

int main()
{
	//ios::sync_with_stdio(false);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	{
		int l;scanf("%d",&l);
		for (int j=1;j<=l;j++){
			int a;scanf("%d",&a);
			FName[i].push_back(a);
		}
		scanf("%d",&l);
		for (int j=1;j<=l;j++){
			int a;scanf("%d",&a);
			LName[i].push_back(a);

		}
	}
	//cout<<"Input 1 over"<<endl;
	for (int i=1;i<=m;i++) Insert(i);
	//cout<<"Insert over"<<endl;
	GetFail();
	//cout<<"GetFail over!"<<endl;
	for (int i=1;i<=n;i++) AhoCorasick(FName[i],i),AhoCorasick(LName[i],i);
	for (int i=1;i<=m;i++) printf("%d\n",Ans1[NodeId[i]]);
	for (int i=1;i<=n;i++)
	{
		printf("%d",Ans2[i]);
		if (i!=n) printf(" ");
	}
	return 0;
}

vector<int> Input;

void Insert(int id)
{
	Input.clear();
	int L;scanf("%d",&L);
	for (int i=1;i<=L;i++){
		int a;scanf("%d",&a);
		Input.push_back(a);
	}
	int now=0;
	for (int i=0;i<L;i++)
	{
		if (T[now].Son[Input[i]]==0) T[now].Son[Input[i]]=++nodecnt;
		now=T[now].Son[Input[i]];
	}
	//T[now].Id.push_back(id);
	if (T[now].id==0) T[now].id=++idcnt;
	NodeId[id]=T[now].id;T[now].cnt++;
	return;
}

void GetFail()
{
	int h=0,t=0;
	for (iii=T[0].Son.begin();iii!=T[0].Son.end();iii++) Queue.push(iii->second);
	while (!Queue.empty())
	{

		int u=Queue.front();Queue.pop();
		if (T[u].Son.size()==0) continue;
		for (iii=T[u].Son.begin();iii!=T[u].Son.end();iii++)
		{
			int key=iii->first,id=iii->second;
			int now=T[u].fail;
			while ((now!=0)&&(T[now].Son[key]==0)) now=T[now].fail;
			if (T[now].Son[key]!=0) T[id].fail=T[now].Son[key];
			Queue.push(id);
		}
	}
	return;
}

void AhoCorasick(vector<int> V,int id)
{
	//cout<<"Aho!"<<endl;
	int L=V.size();//cout<<L<<endl;
	int now=0;
	for (int i=0;i<L;i++)
	{
		//cout<<"i:"<<i<<endl;
		if (T[now].Son[V[i]]!=0) now=T[now].Son[V[i]];
		else
		{
			while ((now!=0)&&(T[now].Son[V[i]]==0)) now=T[now].fail;
			if (T[now].Son[V[i]]!=0) now=T[now].Son[V[i]];
		}
		//cout<<"now:"<<now<<endl;
		int p=now;
		while (p)
		{
			//cout<<"p:"<<p<<" "<<T[p].Id.size()<<endl;
			if (Hist[p]!=id)
			{
				Hist[p]=id;Ans2[id]+=T[p].cnt;Ans1[T[p].id]++;
			}
			/*
			for (int j=0;j<T[p].Id.size();j++)
			{
				//cout<<j<<endl;
				if (Hist[T[p].Id[j]]!=id)
				{
					Ans1[T[p].Id[j]]++;
					Hist[T[p].Id[j]]=id;
					Ans2[id]++;
				}
			}
			//*/
			p=T[p].fail;
		}
	}
	return;
}
