#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=110;
const int maxM=5010*2;
const int maxS=18;
const int inf=2147483647;

int n,m;
vector<int> To[maxN];
int scnt,Seq[maxN],Id[maxN];
bool ind[maxS];
ll F[maxS][1<<maxS],G[1<<maxS];

int main(){
	scanf("%d%d%d",&n,&m,&scnt);
	for (int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		To[u].push_back(v);To[v].push_back(u);
	}
	for (int i=1;i<=n;i++){
		sort(To[i].begin(),To[i].end());
		vector<int>::iterator it=unique(To[i].begin(),To[i].end());
		To[i].erase(it,To[i].end());
	}

	/*
	for (int i=1;i<=n;i++){
		for (int j=0,sz=To[i].size();j<sz;j++)
			cout<<i<<" -> "<<To[i][j]<<endl;
	}
	//*/
	
	for (int i=0;i<scnt;i++) scanf("%d",&Seq[i]),ind[Seq[i]]=1,Id[Seq[i]]=i;

	for (int i=0;i<scnt;i++) F[i][1<<i]=1;
	for (int S=0;S<(1<<scnt);S++){
		for (int i=0;i<scnt;i++)
			if (S&(1<<i)){
				/*
				if (F[i][S]){
					for (int k=0;k<s;k++) cout<<((S&(1<<k))!=0);
					cout<<" "<<i<<":"<<F[i][S]<<endl;
				}
				//*/
				G[S]+=F[i][S];
				int u=Seq[i];
				for (int j=0,sz=To[u].size();j<sz;j++){
					int v=To[u][j];
					if ((ind[v])&&((S&(1<<Id[v]))==0)){
						//cout<<"   -> "<<Id[v]<<" "<<(S|(1<<Id[v]))<<endl;
						F[Id[v]][S|(1<<Id[v])]+=F[i][S];
					}
				}
			}
		bool flag=1;
		for (int i=0;i<scnt;i++)
			if (S&(1<<i)){
				int u=Seq[i];
				for (int j=0,sz=To[u].size();j<sz;j++){
					int v=To[u][j];
					if ((ind[v]==0)||((ind[v])&&( (S&(1<<Id[v]))==0 ))){
						flag=0;break;
					}
				}
				if (flag==0) break;
			}
		//if (G[S]) cout<<"flag:"<<flag<<endl;
		if (flag){
			for (int i=0;i<scnt;i++)
				if ( (S&(1<<i))==0)
					F[i][S|(1<<i)]+=G[S];
		}
	}

	printf("%lld\n",G[(1<<scnt)-1]);return 0;
}
/*
8 7 5
1 2
1 3
1 6
3 4
2 5
7 8
8 7
1 2 3 7 8
//*/
