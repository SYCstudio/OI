#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxL=60;

ll S,pw[maxL],dp[maxL][maxL+maxL][2];

int main()
{
	pw[0]=1;
	for (int i=1; i<maxL; i++) pw[i]=pw[i-1]<<1;
	scanf("%lld",&S);
	int dep=log2(S+1);
	ll Ans=0;
	for (int i=1; i<=dep; i++) {
		ll X=S%(pw[i]-1);
		for (int j=maxL-1; j>=0; j--) if (X>=pw[j]-1) X-=pw[j]-1;
		if (X==0) ++Ans;
	}
	for (int hl=1; hl<dep; hl++)
		for (int hr=1; hr<dep; hr++) {
			ll X=(S-pw[hr]+1)/(pw[hl+1]+pw[hr+1]-3);
			ll R=(S-pw[hr]+1)%(pw[hl+1]+pw[hr+1]-3);
			if (X==0) continue;
			if (R==0) {
				++Ans;
				continue;
			}
			if (hl==1&&hr==1) {
				if (S==X*5+1) ++Ans;
				continue;
			}

			for (int c=1; c<=hl+hr; c++) {
				ll NUM=R+c;
				if (NUM&1) continue;
				memset(dp,0,sizeof(dp));
				dp[0][0][0]=1;
				for (int i=1; i<=dep; i++)
					for (int j=0; j<=i+i-2&&j<=c; j++)
						for (int k=0; k<=1; k++)
							if (dp[i-1][j][k])
								for (int a=0; a<=(i<hl); a++)
									for (int b=0; b<=(i<hr); b++)
										if (((a+b+k)&1)==((NUM>>i)&1))
											dp[i][j+a+b][(a+b+k)>>1]+=dp[i-1][j][k];
				Ans+=dp[dep][c][0];
			}
		}
	printf("%lld\n",Ans);
	return 0;
}
