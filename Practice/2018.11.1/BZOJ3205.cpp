#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG register

const int maxMap=502;
const int maxR=10;
const int F1[4]={-1,0,1,0};
const int F2[4]={0,1,0,-1};
const int meminf=1061109567;
const int maxQ=maxMap*maxMap;
const int inf=2147483647;

int n,m,H;
char Input[maxMap][maxMap];
int viscnt,vis[maxMap*maxMap];
bool inq[4][maxMap][maxMap];
int F[maxR][maxR][251000];
int Rc[4][maxMap][maxMap];
int pcnt=0,Num[maxR];
int Q[maxQ];
pair<int,int> Sorter[maxMap*maxMap],Seq[maxMap*maxMap];
int Cnt[maxMap*maxMap];

void Add_Edge(int u,int v);
int dfs(int x,int y,int f);

int main(){
	RG int i,j,f,x,y,u,k,l,r,scnt,L,R,area,now,mx;
	scanf("%d%d%d",&H,&m,&n);area=n*m;
	for (i=1;i<=n;++i) scanf("%s",Input[i]+1);

	for (i=1;i<=n;++i) for (j=1;j<=m;++j) if (isdigit(Input[i][j])) Num[Input[i][j]-'0'-1]=(i-1)*m+j;

	for (i=1;i<=n;++i) for (j=1;j<=m;++j) if (Input[i][j]!='x') for (f=0;f<4;++f) Rc[f][i][j]=dfs(i,j,f);
	mem(F,63);
	for (i=0;i<H;++i) F[i][i][Num[i]]=0;

	for (l=H-1;l>=0;--l)
		for (r=l;r<H;++r){
			scnt=0;++viscnt;mx=0;
			for (i=1;i<=area;++i)
				if (Input[(i-1)/m+1][(i-1)%m+1]!='x'){
					for (k=l;k<r;++k) F[l][r][i]=min(F[l][r][i],F[l][k][i]+F[k+1][r][i]);
					if (F[l][r][i]!=meminf) Seq[++scnt]=make_pair(F[l][r][i],i),mx=max(mx,F[l][r][i]);
				}
			if (scnt){
				for (i=1;i<=mx;++i) Cnt[i]=0;
				for (i=1;i<=scnt;++i) ++Cnt[Seq[i].first];
				for (i=1;i<=mx;++i) Cnt[i]+=Cnt[i-1];
				for (i=scnt;i>=1;--i) Sorter[Cnt[Seq[i].first]--]=Seq[i];
				L=0;R=0;now=0;
				while (now<scnt){
					++R;if (R>=maxQ) R=0;
					Q[R]=Sorter[++now].second;vis[Sorter[now].second]=viscnt;
					do{
						++L;if (L>=maxQ) L=0;
						u=Q[L];
						while ((now<scnt)&&(Sorter[now+1].first<=F[l][r][u])){
							++now;
							if ((vis[Sorter[now].second]!=viscnt)&&(F[l][r][Sorter[now].second]==Sorter[now].first)){
								vis[Sorter[now].second]=viscnt;
								++R;if (R>=maxQ) R=0;
								Q[R]=Sorter[now].second;
							}
						}
						x=(u-1)/m+1;y=(u-1)%m+1;
						for (f=0;f<4;++f)
							if ((Rc[f][x][y]!=-1)&&(F[l][r][Rc[f][x][y]]>F[l][r][u]+1)){
								F[l][r][Rc[f][x][y]]=F[l][r][u]+1;
								if (vis[Rc[f][x][y]]!=viscnt){
									++R;if (R>=maxQ) R=0;
									Q[R]=Rc[f][x][y];
									vis[Rc[f][x][y]]=viscnt;
								}
							}
					}
					while (L!=R);
				}
			}
		}

	int Ans=meminf;
	for (i=1;i<=area;++i) Ans=min(Ans,F[0][H-1][i]);
	if (Ans==meminf) printf("-1\n");
	else printf("%d\n",Ans);return 0;
}

int dfs(int x,int y,int f){
	if (inq[f][x][y]) return Rc[f][x][y]=-1;
	if (Rc[f][x][y]) return Rc[f][x][y];
	inq[f][x][y]=1;
	int ff=f;
	if (Input[x][y]=='A') ff=(ff+3)%4;
	if (Input[x][y]=='C') ff=(ff+1)%4;
	int nx=x+F1[ff],ny=y+F2[ff];
	if ((nx<=0)||(ny<=0)||(nx>n)||(ny>m)||(Input[nx][ny]=='x')){
		inq[f][x][y]=0;return Rc[f][x][y]=(x-1)*m+y;
	}
	Rc[f][x][y]=dfs(nx,ny,ff);
	inq[f][x][y]=0;
	return Rc[f][x][y];
}
