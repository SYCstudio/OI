#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=230;
const int maxR=140;

int n,R,D[maxN];
ld P[maxN][maxR],F[maxN][maxR];

int main(){
    int Case;scanf("%d",&Case);
    while (Case--){
	mem(P,0);mem(F,0);
	scanf("%d%d",&n,&R);
	for (int i=1;i<=n;i++) scanf("%LF%d",&P[i][1],&D[i]);
	for (int i=0;i<=n;i++){
	    P[i][0]=1;P[i][1]=1.0-P[i][1];
	    for (int j=2;j<=R+5;j++) P[i][j]=P[i][j-1]*P[i][1];
	}
	/*
	for (int i=1;i<=n;i++){
	    for (int j=0;j<=R;j++) cout<<P[i][j]<<" ";
	    cout<<endl;
	}
	//*/
	ld Ans=0;
	F[0][R]=1;
	for (int i=1;i<=n;i++)
	    for (int j=1;j<=R;j++){
		F[i][j]=F[i-1][j]*P[i-1][j]+F[i-1][j+1]*(1-P[i-1][j+1]);
		Ans+=F[i][j]*(1-P[i][j])*D[i];
	    }

	/*
	for (int i=1;i<=n;i++){
	    for (int j=1;j<=R;j++) cout<<F[i][j]<<" ";
	    cout<<endl;
	}
	//*/
	
	printf("%.10LF\n",Ans);
    }
    return 0;
}
