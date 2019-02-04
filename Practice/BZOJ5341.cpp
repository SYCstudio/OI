#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=404000*4;
const int maxM=maxN<<1;

namespace T1{
	int edgecnt=-1,Head[maxN],Next[maxM],V[maxM];
	ll W[maxM];
	void Init();
}
namespace T2{
	int edgecnt=-1,Head[maxN],Next[maxM],V[maxM];
	ll W[maxM],Dst[maxN];
	int Dep[maxN],
	void Init();
	void dfs_init(int u,int fa);
}

int main(){
	
}
