#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxMap=101;
const int maxK=51*2;
const int maxP=maxK*2+10;
const int F1[]={0,0,1,-1};
const int F2[]={1,-1,0,0};
const int inf=2147483647;

class QueueData
{
public:
	int x,y,o;
};

int n,m,K,T;
int SX[maxK],SY[maxK];
int TX[maxP],TY[maxP],Val[maxP];
int Dist[maxK][maxP];
int H[maxMap][maxMap];
queue<QueueData> Qu;
int Map[maxMap][maxMap][2];
bool inq[maxMap][maxMap][2];
int edgecnt,Head[maxK+maxP],Next[maxK*maxP*10],V[maxK*maxP*10];
int Match[maxK+maxP];
bool vis[maxK+maxP];

void Spfa(int sx,int sy,int opt);
void Add_Edge(int u,int v);
bool Check(int limit);
bool Hungary(int u);

int main()
{
	scanf("%d%d%d%d",&n,&m,&K,&T);
	for (int i=1;i<=K*2+1;i++) scanf("%d%d",&SX[i],&SY[i]);
	for (int i=1,tot=0;i<=T;i++){
		int x,y,cnt;scanf("%d%d%d",&x,&y,&cnt);
		while (cnt--) TX[++tot]=x,TY[tot]=y;
	}
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) scanf("%d",&H[i][j]);

	for (int i=1;i<=K*2;i++)
	{
		if (i<=K) Spfa(SX[i],SY[i],0);
		else Spfa(SX[i],SY[i],1);
		for (int j=1;j<=K*2+1;j++) Dist[i][j]=min(Map[TX[j]][TY[j]][0],Map[TX[j]][TY[j]][1]);

		/*
		for (int j=1;j<=n;j++)
		{
			for (int k=1;k<=m;k++)
				cout<<"("<<Map[j][k][0]<<","<<Map[j][k][1]<<") ";
			cout<<endl;
		}
		cout<<endl;
		//*/
		/*
		for (int j=1;j<=n;j++)
		{
			for (int k=1;k<=m;k++)
				cout<<min(Map[j][k][0],Map[j][k][1])<<" ";
			cout<<endl;
		}
		cout<<endl;
		//*/
	}

	/*
	for (int i=1;i<=K*2;i++)
	{
		for (int j=1;j<=K*2+1;j++)
			cout<<Dist[i][j]<<" ";
		cout<<endl;
	}
	//*/

	int L=0,R=K*2;
	int Ans=-1;
	do
	{
		int mid=(L+R)>>1;
		if (Check(mid)) Ans=mid,R=mid-1;
		else L=mid+1;
	}
	while (L<=R);

	printf("%d\n",Ans);
	return 0;
}

void Spfa(int sx,int sy,int opt)
{
	mem(Map,63);Map[sx][sy][opt]=0;mem(inq,0);while (!Qu.empty()) Qu.pop();
	Qu.push((QueueData){sx,sy,opt});
	do
	{
		int x=Qu.front().x,y=Qu.front().y,o=Qu.front().o;Qu.pop();
		
		if (Map[x][y][o^1]>Map[x][y][o]+1)
		{
			Map[x][y][o^1]=Map[x][y][o]+1;
			if (inq[x][y][o^1]==0){
				inq[x][y][o^1]=1;Qu.push((QueueData){x,y,o^1});
			}
		}
		
		for (int f=0;f<4;f++)
		{
			int xx=x+F1[f],yy=y+F2[f];
			if ((xx>n)||(xx<1)||(yy>m)||(yy<1)) continue;
			if ((o==0)&&(H[xx][yy]>=H[x][y]))
				if (Map[xx][yy][o]>Map[x][y][o]){
					Map[xx][yy][o]=Map[x][y][o];
					if (inq[xx][yy][o]==0){
						inq[xx][yy][o]=1;Qu.push((QueueData){xx,yy,o});
					}
				}

			if ((o==1)&&(H[xx][yy]<=H[x][y]))
				if (Map[xx][yy][o]>Map[x][y][o]){
					Map[xx][yy][o]=Map[x][y][o];
					if (inq[xx][yy][o]==0){
						inq[xx][yy][o]=1;Qu.push((QueueData){xx,yy,o});
					}
				}
		}
		inq[x][y][o]=0;
	}
	while (!Qu.empty());
	return;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

bool Check(int limit)
{
	//cout<<"Check:"<<limit<<endl;
	edgecnt=0;mem(Head,-1);
	for (int i=1;i<=2*K;i++)
		for (int j=1;j<=K*2+1;j++)
			if (Dist[i][j]<=limit){
				Add_Edge(i,j+2*K);//cout<<"Link:"<<i<<" "<<j+2*K<<endl;
			}
	int maxmatch=0;mem(Match,-1);
	for (int i=1;i<=2*K;i++){
		mem(vis,0);
		if (Hungary(i)) maxmatch++;
	}
	return maxmatch+limit>=2*K;
}

bool Hungary(int u)
{
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0)
		{
			vis[V[i]]=1;
			if ((Match[V[i]]==-1)||(Hungary(Match[V[i]]))){
				Match[V[i]]=u;return 1;
			}
		}
	return 0;	
}
