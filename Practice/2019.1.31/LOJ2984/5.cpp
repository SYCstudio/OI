#include<bits/stdc++.h>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=110;

int n,m;
vector<int> T[maxN];
int Mp[maxN][maxN];
bool vis[maxN];
vector<string> O[maxN];

int main(){
	freopen("oldcomputer5.in","r",stdin);
	freopen("oldcomputer5.out","w",stdout);
	scanf("%d%d%d",&n,&n,&m);
	for (int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		T[u].push_back(v);T[v].push_back(u);
	}
	for (int i=1;i<=10;i++) Mp[1][i]=i,vis[i]=1;
	for (int i=2;i<=10;i++)
		for (int j=1;j<=10;j++)
			for (int k=0,sz=T[Mp[i-1][j]].size();k<sz;k++)
				if (vis[T[Mp[i-1][j]][k]]==0){
					Mp[i][j]=T[Mp[i-1][j]][k];
					vis[Mp[i][j]]=1;
				}
	/*
	for (int i=1;i<=10;i++){
		for (int j=1;j<=10;j++) printf("%3d",Mp[i][j]);
		cout<<endl;
	}
	//*/

	for (int i=1;i<=10;i++)	O[Mp[1][i]].push_back("read 0 a");
	for (int i=2;i<=10;i++) O[Mp[1][i]].push_back("write a "+to_string(Mp[2][i]));
	for (int i=2;i<=10;i++)
		for (int j=i+1;j<=10;j++){
			O[Mp[i][j]].push_back("read "+to_string(Mp[i-1][j])+" a");
			O[Mp[i][j]].push_back("write a "+to_string(Mp[i+1][j]));
		}
	for (int i=2;i<=10;i++) O[Mp[i][i]].push_back("read "+to_string(Mp[i-1][i])+" a");
	for (int i=1;i<=5;i++){
		int k=10-i+1;
		O[Mp[i][i]].push_back("write a "+to_string(Mp[i][i+1]));
		for (int j=i+1;j<k;j++){
			O[Mp[i][j]].push_back("read "+to_string(Mp[i][j-1])+" a");
			O[Mp[i][j]].push_back("write a "+to_string(Mp[i][j+1]));
		}
		O[Mp[i][k]].push_back("read "+to_string(Mp[i][k-1])+" a");
	}
	for (int i=6;i<=10;i++){
		int k=10-i+1;
		O[Mp[i][i]].push_back("write a "+to_string(Mp[i][i-1]));
		for (int j=i-1;j>k;j--){
			O[Mp[i][j]].push_back("read "+to_string(Mp[i][j+1])+" a");
			O[Mp[i][j]].push_back("write a "+to_string(Mp[i][j-1]));
		}
		O[Mp[i][k]].push_back("read "+to_string(Mp[i][k+1])+" a");
	}
	for (int i=1;i<10;i++)
		O[Mp[i][10-i+1]].push_back("write a "+to_string(Mp[i+1][10-i+1]));
	for (int i=2;i<10;i++)
		for (int j=10-i+2;j<=10;j++){
			O[Mp[i][j]].push_back("read "+to_string(Mp[i-1][j])+" a");
			O[Mp[i][j]].push_back("write a "+to_string(Mp[i+1][j]));
		}
	for (int i=2;i<=10;i++) O[Mp[10][i]].push_back("read "+to_string(Mp[9][i])+" a");
	for (int i=1;i<=10;i++) O[Mp[10][i]].push_back("write a 0");

	
	for (int i=1;i<=n;i++){
		if (!O[i].size()) continue;
		cout<<"node "<<i<<endl;
		for (int j=0,sz=O[i].size();j<sz;j++)
			cout<<O[i][j]<<endl;
	}
	//*/

	/*
	for (int i=1;i<=10;i++)
		for (int j=1;j<=10;j++){
			cout<<"("<<i<<","<<j<<") "<<endl;
			for (int k=0,sz=O[Mp[i][j]].size();k<sz;k++)
				cout<<O[Mp[i][j]][k]<<endl;
		}
	//*/
	
	return 0;
}
