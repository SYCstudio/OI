#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

class Pos{
public:
	int x,y;
};

const int maxN=210;
const int maxStr=1010000;
const int maxAlpha=10;
const Pos Zero=((Pos){0,0});
const int inf=2147483647;

int n,m,Q;
int Dx[maxAlpha],Dy[maxAlpha];
char Map[maxN][maxN],Input[maxStr];
Pos Trans[maxN][maxN][maxAlpha];
Pos St[maxN*maxN];
bool vis[maxN][maxN];

void dfs(int x,int y,int d);
bool operator == (Pos A,Pos B);

int main()
{
	scanf("%d%d%d",&n,&m,&Q);
	for (int i=1;i<=n;i++) scanf("%s",Map[i]+1);
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) Map[i][j]-='0';
	for (int i=0;i<=9;i++) scanf("%d%d",&Dx[i],&Dy[i]);

	mem(vis,0);
	for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) if (vis[i][j]==0) dfs(i,j,1);

	while (Q--){
		mem(vis,0);scanf("%s",Input+1);
		bool getans=0;int len=strlen(Input+1);
		for (int i=1;i<=len;i++) Input[i]-='0';
		for (int bx=1;bx<=n;bx++)
			for (int by=1;by<=m;by++)
				if ((Map[bx][by]==Input[1])&&(vis[bx][by]==0)){
					int x=bx,y=by;bool flag=1;vis[x][y]=1;
					for (int i=2;i<=len;i++){
						//cout<<i<<":"<<(int)(Input[i])<<" "<<Trans[x][y][Input[i]].x<<" "<<Trans[x][y][Input[i]].y<<endl;
						if (Trans[x][y][Input[i]]==Zero){
							flag=0;break;
						}
						int xx=Trans[x][y][Input[i]].x,yy=Trans[x][y][Input[i]].y;
						x=xx;y=yy;vis[x][y]=1;
						//cout<<"("<<xx<<" "<<yy<<")"<<endl;
					}
					if (flag){
						getans=1;break;
					}
				}
		if (getans) printf("YES\n");
		else printf("NO\n");
	}

	return 0;
}

void dfs(int x,int y,int d){
	for (int i=d-1;i>=1;i--)
		if (Trans[St[i].x][St[i].y][Map[x][y]]==Zero) Trans[St[i].x][St[i].y][Map[x][y]]=((Pos){x,y});
		else break;
	if (vis[x][y]){
		for (int i=0;i<maxAlpha;i++)
			if (!(Trans[x][y][i]==Zero))
				for (int j=d-1;j>=1;j--)
					if (Trans[St[j].x][St[j].y][i]==Zero) Trans[St[j].x][St[j].y][i]=Trans[x][y][i];
					else break;
		return;
	}
	vis[x][y]=1;St[d]=((Pos){x,y});
	int xx=x+Dx[Map[x][y]],yy=y+Dy[Map[x][y]];
	if ((xx<=0)||(xx>n)||(yy<=0)||(yy>m)) Trans[x][y][Map[x][y]]=((Pos){x,y});
	else dfs(xx,yy,d+1);
	return;
}

bool operator == (Pos A,Pos B){
	return (A.x==B.x)&&(A.y==B.y);
}
