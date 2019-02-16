#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lowbit(x) ((x)&(-(x)))

const int maxN=400010;
const int maxM=maxN*2;
const int maxAlpha=27;
//const int inf=2147483647;

class Trie
{
public:
	int fail,fa;
	int son[maxAlpha];
};

int n,nodecnt,m;
char str[maxN];
Trie T[maxN];
int idcnt=0,Id[maxN];
int Ques[maxN],Ans[maxN];
int qcnt=0,QHead[maxN],QNext[maxM],QV[maxM];
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Queue[maxN];
int dfncnt=0,Dfn[maxN],Last[maxN];
int BIT[maxN];

void GetFail();
void QAdd_Edge(int u,int v);
void Add_Edge(int u,int v);
void dfs(int u);
void Modify(int pos,int key);
int Query(int l,int r);
int Sum(int pos);

int main()
{
	mem(QHead,-1);mem(Head,-1);
	
	scanf("%s",str+1);
	int len=strlen(str+1);
	for (int i=1,now=0;i<=len;i++)
	{
		if (str[i]=='B') now=T[now].fa;
		else if (str[i]=='P') Id[++idcnt]=now/*,Outp(now),cout<<endl*/;
		else
		{
			if (T[now].son[str[i]-'a']==0)
			{
				T[now].son[str[i]-'a']=++nodecnt;
				T[nodecnt].fa=now;
			}
			now=T[now].son[str[i]-'a'];
		}
	}
	//cout<<"Build over"<<endl;
	scanf("%d",&m);
	for (int i=1;i<=m;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		QAdd_Edge(y,i);Ques[i]=x;
	}
	GetFail();
	//cout<<"Fail over"<<endl;
	dfs(0);
	for (int i=1,now=0,cnt=0;i<=len;i++)
	{
		if (str[i]=='B'){
			//cout<<"Delete:"<<now<<" "<<Dfn[now]<<endl;
			Modify(Dfn[now],-1);now=T[now].fa;
		}
		else if (str[i]=='P')
		{
			cnt++;
			for (int q=QHead[cnt];q!=-1;q=QNext[q])
			{
				int id=QV[q];
				int v=Id[Ques[id]];
				//cout<<"now:"<<now<<" v:"<<v<<" cnt:"<<cnt<<" id:"<<id<<" Q:"<<Dfn[v]<<" "<<Last[v]<<" "<<Query(Dfn[v],Last[v])<<endl;
				Ans[id]=Query(Dfn[v],Last[v]);
			}
		}
		else
		{
			now=T[now].son[str[i]-'a'];
			//cout<<"Add:"<<now<<" "<<Dfn[now]<<endl;
			Modify(Dfn[now],1);
		}
	}
	for (int i=1;i<=m;i++) printf("%d\n",Ans[i]);
	return 0;
}

void GetFail()
{
	int h=0,t=0;
	for (int i=0;i<maxAlpha;i++) if (T[0].son[i]) Queue[++h]=T[0].son[i];
	//cout<<"Init"<<endl;
	while (t!=h)
	{
		int u=Queue[++t];
		//cout<<u<<endl;
		for (int i=0;i<maxAlpha;i++)
			if (T[u].son[i])
			{
				T[T[u].son[i]].fail=T[T[u].fail].son[i];
				Queue[++h]=T[u].son[i];
			}
			else T[u].son[i]=T[T[u].fail].son[i];
	}
	//for (int i=1;i<=nodecnt;i++) cout<<i<<" "<<T[i].fail<<endl;
	for (int i=1;i<=nodecnt;i++) Add_Edge(T[i].fail,i);
	return;
}

void QAdd_Edge(int u,int v)
{
	qcnt++;QNext[qcnt]=QHead[u];QHead[u]=qcnt;QV[qcnt]=v;
	return;
}

void Add_Edge(int u,int v)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs(int u)
{
	Dfn[u]=++dfncnt;
	for (int i=Head[u];i!=-1;i=Next[i])
		dfs(V[i]);
	Last[u]=dfncnt;
	//cout<<u<<" ["<<Dfn[u]<<","<<Last[u]<<"]"<<endl;
	return;
}

void Modify(int pos,int key)
{
	while(pos<=dfncnt){
		BIT[pos]+=key;pos+=lowbit(pos);
	}
	return;
}

int Query(int l,int r)
{
	return Sum(r)-Sum(l-1);
}

int Sum(int pos)
{
	int ret=0;
	while(pos){
		ret+=BIT[pos];pos-=lowbit(pos);
	}
	return ret;
}
/*
void Outp(int now)
{
	if (T[now].fa!=0) Outp(T[now].fa);
	for (int i=0;i<maxAlpha;i++)
		if (T[T[now].fa].son[i]==now)
		{
			cout<<((char)(i+'a'));
			break;
		}
	return;
}
//*/
