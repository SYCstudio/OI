#include<bits/stdc++.h>
using namespace std;

const int maxN=5010;

int n,A[maxN];
int F[maxN][maxN/2][2];

int main(){
    scanf("%d",&n);for (int i=1;i<=n;i++) scanf("%d",&A[i]);
    memset(F,127,sizeof(F));
    F[0][0][0]=F[0][0][1]=0;
    for (int i=1;i<=n;i++){
	for (int j=0,limit=i/2+(i&1);j<=limit;j++){
	    F[i][j][0]=min(F[i-1][j][0],F[i-1][j][1]+max(0,A[i]-A[i-1]+1));
	    if (j){
		if (i==1) F[i][j][1]=0;
		else if (i==2) F[i][j][1]=F[i-1][j-1][0]+max(0,A[i-1]-A[i]+1);
		else F[i][j][1]=min(F[i-2][j-1][1]+max(0,max(A[i-1]-A[i-2]+1,A[i-1]-A[i]+1)),F[i-2][j-1][0]+max(0,A[i-1]-A[i]+1));
	    }
	    //cout<<"("<<F[i][j][0]<<" "<<F[i][j][1]<<") ";
	}
	//cout<<endl;
    }
    for (int i=1,limit=n/2+(n&1);i<=limit;i++) printf("%d ",min(F[n][i][0],F[n][i][1]));printf("\n");
    return 0;
}
