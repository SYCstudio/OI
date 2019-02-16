#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10010;
const int maxM=maxN*2;
const ll Hashbase=19491001;
const int Mod=1000003;
const int inf=2147483647;

int n,nowsum,root,len;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
char Node[maxN],S[maxN];
int Size[maxN],mxSon[maxN];
ll Hashpre[maxN],Hashsuf[maxN];
bool vis[maxN];
int histcnt=0,Hpre[Mod+10],Hsuf[Mod+10];
ll Seedret[maxN];
bool is_get_ans;

void Add_Edge(int u,int v);
void GetRoot(int u,int fa);
void Solve(int u);
void GetAns(int u,int fa,ll nowhash,int depth);
void Modify(int u,int fa,ll nowhash,int depth);

int main()
{
	ios::sync_with_stdio(false);
	int T;cin>>T;
	Seedret[1]=1;
	for (int i=2;i<maxN;i++) Seedret[i]=(ll)Seedret[i-1]*Hashbase%Mod;
	for (int tt=1;tt<=T;tt++)
	{
		edgecnt=0;mem(Head,-1);mem(vis,0);is_get_ans=0;
		cin>>n;
		for (int i=1;i<n;i++)
		{
			int u,v;cin>>u>>v;
			Add_Edge(u,v);Add_Edge(v,u);
		}
		cin>>(Node+1);cin>>(S+1);
		len=strlen(S+1);
		Hashpre[0]=0;
		for (int i=1;i<=len;i++)
			Hashpre[i]=((ll)Hashpre[i-1]*Hashbase+S[i])%Mod;
		Hashsuf[len+1]=0;
		for (int i=len;i>=1;i--)
			Hashsuf[i]=((ll)Hashsuf[i+1]*Hashbase+S[i])%Mod;
		//for (int i=1;i<=len;i++) cout<<Hashpre[i]<<" ";cout<<endl;
		//for (int i=1;i<=len;i++) cout<<Hashsuf[i]<<" ";cout<<endl;
		root=0;mxSon[0]=inf;nowsum=n;
		GetRoot(1,0);
		Solve(root);
		printf("Case #%d: ",tt);
		if (is_get_ans) printf("Find\n");
		else printf("Impossible\n");
	}
	return 0;
}

void Add_Edge(int u,int v)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void GetRoot(int u,int fa)
{
	Size[u]=1;mxSon[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((vis[V[i]]==0)&&(V[i]!=fa))
		{
			GetRoot(V[i],u);Size[u]+=Size[V[i]];
			mxSon[u]=max(mxSon[u],Size[V[i]]);
		}
	mxSon[u]=max(mxSon[u],nowsum-Size[u]);
	if (mxSon[u]<mxSon[root]) root=u;
	return;
}

void Solve(int u)
{
	//cout<<"Root:"<<root<<endl;
	vis[u]=1;
	histcnt++;
	if (Node[u]==S[1]) Hpre[1]=histcnt;
	if (Node[u]==S[len]) Hsuf[len]=histcnt;
	if (((Node[u]==S[1])||(Node[u]==S[len]))&&(len==1)) is_get_ans=1;
	for (int i=Head[u];(i!=-1)&&(is_get_ans==0);i=Next[i])
		if (vis[V[i]]==0)
		{
			GetAns(V[i],u,Node[V[i]],1);
			Modify(V[i],u,((ll)Node[V[i]]*Hashbase%Mod+Node[u])%Mod,2);
		}
	for (int i=Head[u];(i!=-1)&&(is_get_ans==0);i=Next[i])
		if (vis[V[i]]==0)
		{
			root=0;nowsum=Size[V[i]];
			GetRoot(V[i],0);
			Solve(root);
		}
	return;
}

void GetAns(int u,int fa,ll nowhash,int depth)
{
	//cout<<"GA:"<<u<<" "<<depth<<" "<<nowpre<<" "<<nowsuf<<endl;
	if ((nowhash==Hashpre[depth])&&(Hsuf[depth+1]==histcnt))
	{
		is_get_ans=1;
		return;
	}
	if ((nowhash==Hashsuf[len-depth+1])&&(Hpre[len-depth]==histcnt))
	{
		is_get_ans=1;
		return;
	}
	for (int i=Head[u];(i!=-1)&&(is_get_ans==0);i=Next[i])
		if ((V[i]!=fa)&&(vis[V[i]]==0))
			GetAns(V[i],u,(Seedret[depth+1]*Node[V[i]]%Mod+nowhash)%Mod,depth+1);
	return;
}

void Modify(int u,int fa,ll nowhash,int depth)
{
	//cout<<"MD:"<<u<<" "<<depth<<" "<<nowpre<<" "<<nowsuf<<endl;
	if (nowhash==Hashpre[depth])
	{
		Hpre[depth]=histcnt;
	}
	if (nowhash==Hashsuf[len-depth+1])
	{
		Hsuf[len-depth+1]=histcnt;
	}
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(vis[V[i]]==0))
			Modify(V[i],u,(Seedret[depth+1]*Node[V[i]]%Mod+nowhash)%Mod,depth+1);
	return;
}
