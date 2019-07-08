#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

#define ft first
#define sd second
#define mp make_pair
const int maxN=101000;
const int Block=330;
const int maxM=202000;

int n,m,Q,Sz[maxN],Mark[maxN];
vector<int> T[maxN];
pair<int,int> Fr[maxN][Block+5];

int main()
{
	scanf("%d%d%d",&n,&m,&Q);
	for (int i=1; i<=m; i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		T[u].push_back(v);
	}
	for (int i=1; i<=n; i++) Sz[i]=1,Fr[i][1]=mp(0,i);
	for (int i=1; i<=n; i++)
		for (int j=0,sz=T[i].size(); j<sz; j++) {
			static pair<int,int> Bp[Block+5];
			int to=T[i][j];
			int s1=Sz[i],s2=Sz[to],p1=1,p2=1,K=0;
			//cout<<"Work:"<<i<<" "<<to<<"|"<<s1<<" "<<s2<<endl;
			while ((p1<=s1||p2<=s2)&&K<=Block) {
				//cout<<p1<<" "<<p2<<endl;
				if (p1<=s1&&Mark[Fr[i][p1].sd]) {
					++p1;
					continue;
				}
				if (p2<=s2&&Mark[Fr[to][p2].sd]) {
					++p2;
					continue;
				}
				if (p2>s2||(p1<=s1&&Fr[i][p1].ft+1>=Fr[to][p2].ft)) {
					Bp[++K]=Fr[i][p1++];
					++Bp[K].ft;
					Mark[Bp[K].sd]=1;
				} else {
					Bp[++K]=Fr[to][p2++];
					Mark[Bp[K].sd]=1;
				}
			}
			Sz[to]=K;
			for (int k=1; k<=Sz[to]; k++) Fr[to][k]=Bp[k],Mark[Bp[k].sd]=0;
		}
	/*
	for (int i=1;i<=n;i++){
	cout<<"At:"<<i<<" "<<Sz[i]<<endl;
	for (int j=1;j<=Sz[i];j++) cout<<"("<<Fr[i][j].ft<<" "<<Fr[i][j].sd<<") ";cout<<endl;
	}
	//*/

	while (Q--) {
		static int Seq[maxN];
		int S,C;
		scanf("%d%d",&S,&C);
		for (int i=1; i<=C; i++) scanf("%d",&Seq[i]),Mark[Seq[i]]=1;
		if (C<Block) {
			bool flag=0;
			for (int i=1; i<=Sz[S]; i++)
				if (!Mark[Fr[S][i].sd]) {
					flag=1;
					printf("%d\n",Fr[S][i].ft);
					break;
				}
			if (!flag) puts("-1");
		} else {
			static int F[maxN];
			memset(F,-1,sizeof(F));
			for (int i=1; i<=n; i++) {
				if (!Mark[i]) F[i]=max(F[i],0);
				if (F[i]!=-1) for (int j=0,sz=T[i].size(); j<sz; j++) F[T[i][j]]=max(F[T[i][j]],F[i]+1);
			}
			printf("%d\n",F[S]);
		}
		for (int i=1; i<=C; i++) Mark[Seq[i]]=0;
	}
	return 0;
}
