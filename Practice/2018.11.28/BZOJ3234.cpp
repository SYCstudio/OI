#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG 

const int maxN=210;
const int F1[]={1,-1,0,0,0,0};
const int F2[]={0,0,1,-1,0,0};
const int F3[]={0,0,0,0,1,-1};
const int inf=2147483647;

class QData
{
public:
	int x,y,z;
};

int n;
int Sum[maxN][maxN][maxN];
bool vis[maxN][maxN][maxN];
queue<QData> Q;

int main(){
	RG int i,j,k;
	scanf("%d",&n);
	int mx=0;
	for (i=1;i<=n;++i){
		int x1,y1,z1,x2,y2,z2;scanf("%d%d%d%d%d%d",&x1,&y1,&z1,&x2,&y2,&z2);
		++x1;++y1;++z1;mx=max(mx,x2+5);mx=max(mx,y2+5);mx=max(mx,z2+5);
		++Sum[x1][y1][z1];--Sum[x1][y2+1][z1];
		--Sum[x2+1][y1][z1];++Sum[x2+1][y2+1][z1];
		--Sum[x1][y1][z2+1];++Sum[x1][y2+1][z2+1];
		++Sum[x2+1][y1][z2+1];--Sum[x2+1][y2+1][z2+1];
	}
	for (i=1;i<=mx;++i) for (j=1;j<=mx;++j) for (k=1;k<=mx;++k) Sum[i][j][k]+=Sum[i][j-1][k];
	for (i=1;i<=mx;++i) for (j=1;j<=mx;++j) for (k=1;k<=mx;++k) Sum[i][j][k]+=Sum[i-1][j][k]+Sum[i][j][k-1]-Sum[i-1][j][k-1];

	for (i=0;i<=1;++i) for (j=0;j<=1;++j) for (k=0;k<=1;++k) if (Sum[mx*i][mx*j][mx*k]==0) Q.push((QData){mx*i,mx*j,mx*k}),vis[mx*i][mx*j][mx*k]=1;
	int Ans=0;
	while (!Q.empty()){
		int x=Q.front().x,y=Q.front().y,z=Q.front().z;Q.pop();
		for (int f=0;f<6;f++){
			int xx=x+F1[f],yy=y+F2[f],zz=z+F3[f];
			if ((xx<0)||(xx>mx)||(yy<0)||(yy>mx)||(zz<0)||(zz>mx)||(vis[xx][yy][zz])) continue;
			if (Sum[xx][yy][zz]){
				++Ans;continue;
			}
			vis[xx][yy][zz]=1;Q.push((QData){xx,yy,zz});
		}
	}
	printf("%d\n",Ans);
	return 0;
}
