#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define pw(x) (1<<(x))
const int maxN=30300;
const int maxW=12;

int W,n,m,pw3[maxW+10];
int S1[pw(maxW)+10],S2[531451];

int main(){
    pw3[0]=1;for (int i=1;i<=maxW;i++) pw3[i]=pw3[i-1]*3;
    scanf("%d%d%d",&W,&n,&m);int N=pw(W),N3=pw3[W];
    for (int i=1;i<=n;i++){
	int x;scanf("%d",&x);++S1[x];
    }
    for (int i=0;i<N;i++){
	int p=0;
	for (int j=0;j<W;j++) if (i&pw(j)) p+=pw3[j];
	S2[p]=S1[i];
    }
    for (int i=0;i<W;i++) for (int j=0;j<N3;j++) if (j/pw3[i]%3==2) S2[j]=S2[j]+S2[j-pw3[i]]+S2[j-pw3[i]-pw3[i]];
    while (m--){
	char str[maxW+10];scanf("%s",str);reverse(&str[0],&str[W]);
	long long Ans=0;int opt[maxW+10][2];
	for (int i=0;i<W;i++)
	    if (str[i]=='A') opt[i][0]=2,opt[i][1]=0;
	    else if (str[i]=='O') opt[i][0]=0,opt[i][1]=-1;
	    else if (str[i]=='X') opt[i][0]=0,opt[i][1]=1;
	    else if (str[i]=='a') opt[i][0]=-1,opt[i][1]=1;
	    else if (str[i]=='o') opt[i][0]=1,opt[i][1]=2;
	    else opt[i][0]=1,opt[i][1]=0;
	for (int i=0;i<N;i++)
	    if (S1[i]){
		bool flag=1;int S=0;
		for (int j=0;j<W;j++){
		    int b=(i>>j)&1;
		    if (opt[j][b]==-1){
			flag=0;break;
		    }
		    S=S+pw3[j]*opt[j][b];
		}
		if (flag==0) continue;
		Ans=Ans+1ll*S1[i]*S2[S];
	    }
	printf("%lld\n",Ans);
    }
    return 0;
}
