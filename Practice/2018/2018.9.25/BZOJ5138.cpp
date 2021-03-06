#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1600;
const int maxNode=maxN*maxN;
const int maxM=maxNode*8;
const int F1[]={-1,0,1,0};
const int F2[]={0,-1,0,1};
const int inf=2147483647;

class QueueData
{
public:
	int x,y,f;
};

int n,m,stx,sty,bxx,bxy;
char Input[maxN][maxN];
int edgecnt=0,Head[maxNode],Next[maxM],V[maxM],Id[maxN][maxN];
int dfncnt,dfn[maxNode],low[maxNode],bcccnt,top,St[maxNode];
bool inq[4][maxN][maxN],ok[maxN][maxN],vis[maxN][maxN],mark[maxNode];
queue<QueueData> Q;
vector<int> Bcc[maxNode];

void Add_Edge(int u,int v);
void tarjan(int u,int fa);
void Bfs();

int main(){
	mem(Head,-1);
	int Qs;
	scanf("%d%d%d",&n,&m,&Qs);
	for (int i=1,idcnt=0;i<=n;i++) for (int j=1;j<=m;j++) Id[i][j]=++idcnt;
	for (int i=1;i<=n;i++){
		scanf("%s",Input[i]+1);
		for (int j=1;j<=m;j++)
			if (Input[i][j]=='A') stx=i,sty=j,Input[i][j]='.';
			else if (Input[i][j]=='B') bxx=i,bxy=j,Input[i][j]='.';
	}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			if (Input[i][j]=='.')
				for (int f=0;f<4;f++)
					if (Input[i+F1[f]][j+F2[f]]=='.')
						Add_Edge(Id[i][j],Id[i+F1[f]][j+F2[f]]);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		if ((dfn[Id[i][j]]==0)&&(Input[i][j]=='.')) tarjan(Id[i][j],Id[i][j]);
	/*
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++) cout<<dfn[Id[i][j]]<<" ";
		cout<<endl;
	}
	cout<<endl;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++) cout<<low[Id[i][j]]<<" ";
		cout<<endl;
	}
	//*/

	Bfs();

	while (!Q.empty()){
		int x=Q.front().x,y=Q.front().y,ff=Q.front().f;Q.pop();
		//cout<<"Q:"<<x<<" "<<y<<" "<<ff<<endl;
		int xx=x+F1[ff^2],yy=y+F2[ff^2];
		if (Input[xx][yy]=='.'){
			if (inq[ff][xx][yy]==0)
				inq[ff][xx][yy]=1,ok[xx][yy]=1,Q.push((QueueData){xx,yy,ff});
		}
		int u=x+F1[ff],v=y+F2[ff];
		for (int i=0,sz=Bcc[Id[u][v]].size();i<sz;i++) mark[Bcc[Id[u][v]][i]]=1;
		for (int f=0;f<4;f++){
			xx=x+F1[f];yy=y+F2[f];
			if ((f!=ff)&&(xx<=n)&&(xx>=1)&&(yy<=m)&&(yy>=1)&&(inq[f][x][y]==0)){
				bool flag=0;
				for (int i=0,sz=Bcc[Id[xx][yy]].size();i<sz;i++)
					if (mark[Bcc[Id[xx][yy]][i]]) {flag=1;break;}
				if ((flag)&&(inq[f][x][y]==0)){
					//cout<<x<<" "<<y<<" "<<ff<<" -> "<<f<<endl;
					inq[f][x][y]=1;ok[x][y]=1;
					Q.push((QueueData){x,y,f});
				}
			}
		}
		for (int i=0,sz=Bcc[Id[u][v]].size();i<sz;i++) mark[Bcc[Id[u][v]][i]]=0;
	}

	while (Qs--){
		int x,y;scanf("%d%d",&x,&y);
		printf(ok[x][y]?("YES\n"):("NO\n"));
	}

	return 0;
}

void Add_Edge(int u,int v){
	//cout<<"Add:"<<u<<" "<<v<<endl;
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void tarjan(int u,int fa){
	dfn[u]=low[u]=++dfncnt;St[++top]=u;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			if (dfn[V[i]]==0){
				tarjan(V[i],u);
				low[u]=min(low[u],low[V[i]]);
				if (low[V[i]]>=dfn[u]){
					bcccnt++;int v;
					//cout<<bcccnt<<":";
					do Bcc[v=St[top--]].push_back(bcccnt)/*,cout<<v<<" "*/;
					while (v!=V[i]);
					Bcc[u].push_back(bcccnt);//cout<<endl;
				}
			}
			else low[u]=min(low[u],dfn[V[i]]);
		}
	return;
}

void Bfs(){
	Q.push((QueueData){stx,sty,0});
	Input[bxx][bxy]='#';
	do{
		int x=Q.front().x,y=Q.front().y;Q.pop();
		for (int f=0;f<4;f++){
			int xx=x+F1[f],yy=y+F2[f];
			if ((xx<=n)&&(xx>=1)&&(yy<=m)&&(yy>=1)&&(Input[xx][yy]=='.')&&(vis[xx][yy]==0)) vis[xx][yy]=1,Q.push((QueueData){xx,yy,0});
		}
	}
	while (!Q.empty());
	Input[bxx][bxy]='.';
	ok[bxx][bxy]=1;
	for (int f=0;f<4;f++){
		int xx=bxx+F1[f],yy=bxy+F2[f];
		if (vis[xx][yy]) Q.push((QueueData){xx,yy,f});
	}
	return;
}
/*
5 5 16
##..A
#..##
..B..
#....
..###
1 3
1 4
1 5
2 2
2 3
3 1
3 2
3 3
3 4
3 5
4 2
4 3
4 4
4 5
5 1
5 2
//*/

