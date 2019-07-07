#include<bits/stdc++.h>
using namespace std;

#define Min(x,y) x=min(x,y)
const int maxN=70700;
const int Alpha=11;

int n,ecnt;
char In[maxN];
int F[maxN][Alpha],G[maxN][Alpha][Alpha];
int Must[maxN];

int main(){
    scanf("%d",&n);scanf("%s",In+1);
    for (int i=1,flag=0;i<=n;i++)
	if (In[i]=='e') ++ecnt,flag=1,In[i]-='a';
	else Must[i]=flag,flag=0,In[i]-='a';

    memset(F,127,sizeof(F));memset(G,127,sizeof(G));

    F[0][In[1]]=0;
    for (int i=1;i<=n;i++)
	if (In[i]==4){
	    for (int j=0;j<Alpha;j++) F[i][j]=F[i-1][j];
	    for (int j=0;j<Alpha;j++) for (int k=0;k<Alpha;k++) G[i][j][k]=G[i-1][j][k];
	}
	else{
	    for (int j=0;j<Alpha;j++){
		if (In[i]!=j&&Must[i]==0) Min(F[i][j],F[i-1][j]);
		Min(F[i][j],F[i-1][In[i]]+2);
		if (In[i]!=j) Min(F[i][j],G[i-1][In[i]][j]);
		Min(F[i][j],G[i-1][In[i]][In[i]]+2);
		
		for (int k=0;k<Alpha;k++){
		    if (j!=In[i]) Min(G[i][j][k],F[i-1][j]+3);
		    Min(G[i][j][k],F[i-1][In[i]]+5);
		    if (j!=In[i]&&k!=In[i]) Min(G[i][j][k],G[i-1][j][k]+1);
		    if (k!=In[i]) Min(G[i][j][k],G[i-1][In[i]][k]+3);
		    if (j!=In[i]) Min(G[i][j][k],G[i-1][j][In[i]]+3);
		    Min(G[i][j][k],G[i-1][In[i]][In[i]]+5);
		}
	    }
	}
    printf("%d\n",F[n][Alpha-1]-2+ecnt+ecnt);
    return 0;
}
