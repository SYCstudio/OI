#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
#include<vector>
using namespace std;

#define mp make_pair
#define ft first
#define sd second
const int maxN=110;
const int maxState=4000;
const int Mod=998244353;

int Use[maxN];
int idcnt=0;
map<int,int> Id;
vector<int> Hd[maxState];

void Init();
void dfs(int b,int i,int j,int k);
int Hash(int b,int i,int j,int k);
int main(){
    Init();
    scanf("%d",&n);
    for (int i=1;i<=13;i++){
	int w,t;scanf("%d%d",&w,&t);++Use[w];
    }
}
void Init(){
    dfs(0,0,0,0);
}
int Hash(int b,int i,int j,int k){
    return (((b)*10+i)*100+j)*10+k;
}
void dfs(int b,int i,int j,int k){
    int cnt=0;
}
