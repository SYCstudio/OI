#include<cstdio>
#include<algorithm>
using namespace std;

#define pw(x) (1<<(x))
const int maxL=20;
const int maxN=pw(maxL)+10;

int L,Q;
char In[maxN],S[maxL+10];
int Pre[maxN],Suf[maxN],C[maxN];

int main()
{
	scanf("%d%d",&L,&Q);
	scanf("%s",In);
	int N=pw(L);
	for (int i=0; i<N; i++) Pre[i]=Suf[i]=In[i]-'0',C[i]=C[i>>1]+(i&1);
	for (int i=0; i<L; i++) for (int j=0; j<N; j++) if (j&pw(i)) Pre[j]+=Pre[j^pw(i)];
			else Suf[j]+=Suf[j^pw(i)];
	while (Q--) {
		scanf("%s",S);
		int s0=0,s1=0,s2=0;
		for (int i=0; i<L; i++)
			if (S[L-i-1]=='0') s0|=pw(i);
			else if (S[L-i-1]=='1') s1|=pw(i);
			else s2|=pw(i);
		int Ans=0;
		if (C[s2]<=0)
			for (int ss=s2;; ss=(ss-1)&s2) {
				Ans=Ans+In[s1|ss]-'0';
				if (!ss) break;
			}
		else if (C[s0]<=6)
			for (int ss=s0;; ss=(ss-1)&s0) {
				if (C[ss]&1) Ans=Ans-Suf[ss|s1];
				else Ans=Ans+Suf[ss|s1];
				if (!ss) break;
			}
		else
			for (int ss=s1;; ss=(ss-1)&s1) {
				if ((C[ss]&1)^(C[s1]&1)) Ans=Ans-Pre[ss|s2];
				else Ans=Ans+Pre[ss|s2];
				if (!ss) break;
			}
		printf("%d\n",Ans);
	}
	return 0;
}
