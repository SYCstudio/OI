#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int inf=2147483647;

int n,m;

namespace cpp1
{
	const int maxN=110;
	const int maxM=10100;

	class HData
	{
	public:
		int u,v,key;
	};
	
	int Mp[maxN][maxN];
	int Color[maxN];
	priority_queue<HData> H[6];

	int GetId(int a,int b);
	void Do();
	bool operator < (HData A,HData B);
}

namespace cpp2
{
#define lson (now<<1)
#define rson (lson|1)
	
	const int maxN=101000;
	const int maxM=501000<<1;
	
	class SegmentData
	{
	public:
		int mov,val[9];
	};

	int edgecnt=-1,Head[maxN],Next[maxM],V[maxM],W[maxM],Color[maxN];
	bool vis[maxN],del[maxM];
	SegmentData S[3][maxN<<2];
	int dfn[3][maxN],lft[3][maxN],rht[3][maxN];
	int Que[maxN],Qval[maxN];

	void Do();
	void Add_Edge(int u,int v,int w);
	void Bfs(int id);
	void Build(int id,int now,int l,int r);
	void Modify(int id,int now,int l,int r,int ql,int qr,int mov);
	void PushDown(int id,int now);
	void Move(int id,int now,int mov);
}

int main(){
	scanf("%d%d",&n,&m);
	if ((n<=100)&&(m<=10000)) cpp1::Do();
	else cpp2::Do();
	return 0;
}

namespace cpp1
{
	int GetId(int a,int b){
		if (a>b) swap(a,b);
		if (a==0) return b;
		if (a==1) return b-a+3;
		return b-a+5;
	}
	
	void Do(){
		for (int i=1;i<=m;i++){
			int u,v,w;scanf("%d%d%d",&u,&v,&w);
			if ((Mp[u][v]==0)||(Mp[u][v]>w)) Mp[u][v]=Mp[v][u]=w;
		}
		for (int i=1;i<=n;i++)
			for (int j=i+1;j<=n;j++)
				if (Mp[i][j]) H[0].push((HData){i,j,Mp[i][j]});
		int Q;scanf("%d",&Q);char ipt[10];
		while (Q--){
			scanf("%s",ipt);
			if (ipt[0]=='M'){
				int u;scanf("%d",&u);Color[u]=ipt[4]-'A';
				for (int i=1;i<=n;i++) if (Mp[u][i]) H[GetId(Color[u],Color[i])].push((HData){u,i,Mp[u][i]});
			}
			if (ipt[0]=='A'){
				int a=ipt[3]-'A',b=ipt[4]-'A',id=GetId(a,b);
				if (a>b) swap(a,b);
				bool flag=0;
				while (!H[id].empty()){
					int u=H[id].top().u,v=H[id].top().v;
					if ( ((a==Color[u])&&(b==Color[v])) || ((a==Color[v])&&(b==Color[u])) ){
						printf("%d\n",H[id].top().key);flag=1;break;
					}
					H[id].pop();
				}
				if (flag==0) printf("No Found!\n");
			}
		}
		return;
	}

	bool operator < (HData A,HData B){
		return A.key>B.key;
	}
}

namespace cpp2
{
	void Do(){
		mem(Head,-1);
		for (int i=1;i<=m;i++){
			int u,v,w;scanf("%d%d%d",&u,&v,&w);
			Add_Edge(u,v,w);Add_Edge(v,u,w);
		}
		
		for (int i=0;i<3;i++){
			Bfs(i);
			Build(i,1,1,n);
			//cerr<<"bfs:"<<i<<endl;
			//cout<<"val:"<<S[i][1].val[0]<<" "<<S[i][1].val[1]<<" "<<S[i][1].val[2]<<endl;
		}

		int Q;scanf("%d",&Q);char ipt[10];
		while (Q--){
			scanf("%s",ipt);
			if (ipt[0]=='M'){
				int x;scanf("%d",&x);int c=ipt[4]-'A'-Color[x];Color[x]=ipt[4]-'A';
				for (int i=0;i<3;i++){
					if (lft[i][x]<=rht[i][x]) Modify(i,1,1,n,lft[i][x],rht[i][x],(c+3)%3*3);
					Modify(i,1,1,n,dfn[i][x],dfn[i][x],(c+9)%9);
				}
			}
			if (ipt[0]=='A'){
				int a=ipt[3]-'A',b=ipt[4]-'A';
				int Ans=inf;
				for (int i=0;i<3;i++){
					Ans=min(Ans,S[i][1].val[a*3+b]);
					Ans=min(Ans,S[i][1].val[b*3+a]);
				}
				if (Ans==inf) printf("No Found!\n");
				else printf("%d\n",Ans);
			}
		}
		return;
	}

	void Add_Edge(int u,int v,int w){
		Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
		return;
	}
	
	void Bfs(int id){
		int h=0,t=0;mem(vis,0);
		for (int x=1;x<=n;x++)
			if (vis[x]==0){
				Que[++h]=x;Qval[h]=inf;dfn[id][x]=h;vis[x]=1;
				do{
					int u=Que[++t];
					lft[id][u]=h+1;dfn[id][u]=t;
					for (int i=Head[u];i!=-1;i=Next[i])
						if ((vis[V[i]]==0)&&(del[i]==0)&&(del[i^1]==0)){
							//cout<<u<<"->"<<V[i]<<endl;
							del[i]=del[i^1]=1;vis[V[i]]=1;
							Que[++h]=V[i];Qval[h]=W[i];
						}
					rht[id][u]=h;
				}
				while (t!=h);
			}
		/*
		cout<<"Bfs:"<<id<<endl;
		for (int i=1;i<=n;i++) cout<<Que[i]<<" ";cout<<endl;
		for (int i=1;i<=n;i++) cout<<Qval[i]<<" ";cout<<endl;
		for (int i=1;i<=n;i++) cout<<dfn[id][i]<<" ";cout<<endl;
		for (int i=1;i<=n;i++) cout<<lft[id][i]<<" ";cout<<endl;
		for (int i=1;i<=n;i++) cout<<rht[id][i]<<" ";cout<<endl;
		//*/
		return;
	}
	
	void Build(int id,int now,int l,int r){
		//if (id==2) cout<<"Build:"<<id<<" "<<now<<" "<<l<<" "<<r<<endl;
		for (int i=0;i<9;i++) S[id][now].val[i]=inf;
		if (l==r){
			S[id][now].val[0]=Qval[l];return;
		}
		int mid=(l+r)>>1;
		Build(id,lson,l,mid);Build(id,rson,mid+1,r);
		S[id][now].val[0]=min(S[id][lson].val[0],S[id][rson].val[0]);
		return;
	}
	
	void Modify(int id,int now,int l,int r,int ql,int qr,int mov){
		if ((l==ql)&&(r==qr)){
			Move(id,now,mov);return;
		}
		PushDown(id,now);
		int mid=(l+r)>>1;
		if (qr<=mid) Modify(id,lson,l,mid,ql,qr,mov);
		else if (ql>=mid+1) Modify(id,rson,mid+1,r,ql,qr,mov);
		else{
			Modify(id,lson,l,mid,ql,mid,mov);
			Modify(id,rson,mid+1,r,mid+1,qr,mov);
		}
		for (int i=0;i<9;i++) S[id][now].val[i]=min(S[id][lson].val[i],S[id][rson].val[i]);
		return;
	}
	
	void PushDown(int id,int now){
		if (S[id][now].mov){
			Move(id,lson,S[id][now].mov);
			Move(id,rson,S[id][now].mov);
			S[id][now].mov=0;
		}
		return;
	}

	void Move(int id,int now,int mov){
		int tmp[9];mem(tmp,0);
		for (int i=0;i<9;i++) tmp[(i+mov)%9]=S[id][now].val[i];
		for (int i=0;i<9;i++) S[id][now].val[i]=tmp[i];
		S[id][now].mov=(S[id][now].mov+mov)%9;return;
	}
}
