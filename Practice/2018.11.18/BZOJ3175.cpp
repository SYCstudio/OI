#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxMap=210;
const int maxN=maxMap*maxMap;
const int maxM=maxN*10;
const int F1[8]={-1,-2,1,2,-1,-2,1,2};
const int F2[8]={-2,-1,-2,-1,2,1,2,1};
const int inf=2147483647;

int n;
int Id[maxMap][maxMap];
int edgecnt,Head[maxN],Next[maxM],V[maxM];
int Match[maxN];
char Input[maxMap][maxMap];
int tim,Tim[maxN];

void Add_Edge(int u,int v);
bool Hungary(int u);

int main(){
	mem(Head,-1);mem(Match,-1);
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%s",Input[i]+1);
	for (int idcnt=1,i=1;i<=n;i++) for (int j=1;j<=n;j++) Id[i][j]=idcnt++;
	int cnt=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if (Input[i][j]=='0'){
				++cnt;
				for (int f=0;f<8;f++){
					int x=i+F1[f],y=j+F2[f];
					if ((x>=1)&&(x<=n)&&(y>=1)&&(y<=n)&&(Input[x][y]=='0'))
						Add_Edge(Id[i][j],Id[x][y]);
				}
			}
	for (int i=1;i<=n*n;i++,tim++) if ((Match[i]==-1)&&(Hungary(i))) --cnt;
	printf("%d\n",cnt);return 0;
}

void Add_Edge(int u,int v){
	//cout<<u<<" "<<v<<endl;
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

bool Hungary(int u){
	Tim[u]=tim;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (Tim[V[i]]!=tim){
			Tim[V[i]]=tim;
			if ((Match[V[i]]==-1)||(Hungary(Match[V[i]]))){
				Match[u]=V[i];Match[V[i]]=u;return 1;
			}
		}
	return 0;
}
