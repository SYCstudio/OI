#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define Max(x,y) x=max(x,y)
const int maxN=40;
const int maxP=34;

ll F[maxN][5][5][5][2];
int Cnt[maxN],Twi[maxN],Mark[maxN];
ll C[5][5]={{1,0,0,0,0},{1,1,0,0,0},{1,2,1,0,0},{1,3,3,1,0},{1,4,6,4,1}};
int GSWS[13]={1,9,10,18,19,27,28,29,30,31,32,33,34};

int Get(char *s);
int main(){
	freopen("out","w",stdout);
	Mark[10]=Mark[19]=Mark[28]=Mark[29]=Mark[30]=Mark[31]=Mark[32]=Mark[33]=Mark[34]=1;
	int Case;scanf("%d",&Case);
	while (Case--){
		memset(Cnt,0,sizeof(Cnt));memset(Twi,0,sizeof(Twi));memset(F,0,sizeof(F));
		char in[5];
		while (scanf("%s",in)){
			if (in[0]=='0') break;
			Cnt[Get(in)]++;
		}
		while (scanf("%s",in)){
			if (in[0]=='0') break;
			Twi[Get(in)]=1;
		}
		for (int i=1;i<=34;i++) Cnt[i]=4-Cnt[i];
		F[0][0][0][0][0]=1;ll Ans=0;
		for (int i=0;i<34;i++){
			for (int k=0;k<=3;k++)
				for (int t=0;t<=Cnt[i+1];t++)
					for (int a=0;a<=4;a++)
						for (int b=a;b<=4;b++)
							for (int fl=0;fl<=1;fl++){
								if (F[i][k][a][b][fl]==0) continue;
								if (Mark[i+1]) if (a||b) continue;
								ll mul=C[Cnt[i+1]][t];if (Twi[i+1]) mul*=1<<t;
								//if (i+1==10) cout<<i<<" "<<k<<" "<<t<<" "<<a<<" "<<b<<" "<<fl<<endl;
								if (a<=t&&a<=b&&Mark[i]==0) Max(F[i+1][k+1][b-a][t-a][fl],F[i][k][a][b][fl]*mul);
								if (t>=3&&t-3>=a&&a<=b&&k+1+a<=4) Max(F[i+1][k+1+a][b-a][t-3-a][fl],F[i][k][a][b][fl]*mul);
								if (a==0) Max(F[i+1][k][b][t][fl],F[i][k][a][b][fl]*mul);
								if (t>=2&&t-2>=a&&a<=b&&k+a<=4&&fl==0) Max(F[i+1][k+a][b-a][t-2-a][1],F[i][k][a][b][fl]*mul);
								if (t==4&&a==0) Max(F[i+1][k+1][b][0][fl],F[i][k][a][b][fl]*mul);
							}
			for (int k=0;k<=4;k++)
				for (int a=0;a<=4;a++)
					for (int b=0;b<=4;b++)
						for (int fl=0;fl<=1;fl++)
							if (F[i][k][a][b][fl]) cout<<"("<<i<<" "<<k<<" "<<a<<" "<<b<<" "<<fl<<") "<<F[i][k][a][b][fl]<<endl;
			Max(Ans,F[i][4][0][0][1]);
		}
		bool flag=1;
		for (int i=0;i<13;i++) if (Cnt[GSWS[i]]==0) flag=0;
		if (flag){
			for (int i=0;i<13;i++)
				if (Cnt[GSWS[i]]>=2){
					ll mul=C[Cnt[GSWS[i]]][2];if (Twi[GSWS[i]]) mul*=1<<2;
					for (int j=0;j<13;j++)
						if (i!=j){
							mul*=C[Cnt[GSWS[j]]][1];
							if (Twi[GSWS[i]]) mul<<=1;
						}
					Max(Ans,mul);
				}
		}
		printf("%lld\n",Ans);
	}
	return 0;
}
int Get(char *S){
	if (S[1]=='m') return S[0]-'0';
	if (S[1]=='p') return S[0]-'0'+9;
	if (S[1]=='s') return S[0]-'0'+9+9;
	if (S[0]=='E') return 28;
	if (S[0]=='S') return 29;
	if (S[0]=='W') return 30;
	if (S[0]=='N') return 31;
	if (S[0]=='Z') return 32;
	if (S[0]=='B') return 33;
	if (S[0]=='F') return 34;
}
