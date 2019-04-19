#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=3030;

int n,m;
char In[maxN][maxN];

int main(){
    scanf("%d%d",&n,&m);for (int i=1;i<=n;i++) scanf("%s",In[i]+1);
    int Ans=0;
    for (int i=1;i<n+m;i++){
	int x=min(n,i),y=max(1,i-n+1);
	int f0=0,f1=0,f2=0;
	while (x>=1&&y<=m){
	    int fd=f0;f0=max(f0,max(f1,f2));
	    if (In[x][y]=='G'){
		if (In[x][y-1]=='R'&&In[x][y+1]=='W') f1=max(f1,fd)+1;
		if (In[x-1][y]=='R'&&In[x+1][y]=='W') f2=max(f2,fd)+1;
	    }
	    --x;++y;
	}
	Ans=Ans+max(f0,max(f1,f2));
    }
    printf("%d\n",Ans);return 0;
}
