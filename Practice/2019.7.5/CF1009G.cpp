#include<bits/stdc++.h>
using namespace std;

#define pw(x) (1<<(x))
const int maxN=101000;
const int maxA=1<<6;

int n;
char S[maxN];
int req[maxN];
int cnt[maxA+10],alpha[maxA+10],sum[maxA+10];

int main()
{
	scanf("%s",S+1);
	int len=strlen(S+1);
	for (int i=1; i<=len; i++) ++alpha[pw(S[i]-'a')];
	for (int i=1; i<maxA; i++) alpha[i]=alpha[i-((i)&(-i))]+alpha[i&(-i)];

	scanf("%d",&n);
	memset(req,-1,sizeof(req));
	for (int i=1; i<=n; i++) {
		char ipt[10];
		int pos,S=0;
		scanf("%d %s",&pos,ipt);
		int l=strlen(ipt);
		for (int j=0; j<l; j++) S|=pw(ipt[j]-'a');
		++cnt[S];
		req[pos]=S;
	}

	//for (int i=0;i<maxA;i++) cout<<alpha[i]<<" ";cout<<endl;
	//for (int i=0;i<maxA;i++) cout<<cnt[i]<<" ";cout<<endl;

	for (int i=1; i<=len; i++) {
		S[i]=0;
		for (int j=0; j<6; j++)
			if (alpha[pw(j)]&&(req[i]==-1||(req[i]&pw(j)))) {
				bool flag=1;
				if (req[i]!=-1) --cnt[req[i]];
				for (int k=0; k<maxA; k++) if (k&pw(j)) --alpha[k];
				for (int k=0; k<maxA; k++) sum[k]=cnt[k];
				for (int a=0; a<6; a++)
					for (int b=0; b<maxA; b++)
						if (b&pw(a)) sum[b]+=sum[b^pw(a)];
				for (int k=0; k<maxA; k++) if (sum[k]>alpha[k]) flag=0;
				if (flag) {
					S[i]=j+'a';
					break;
				}
				++cnt[req[i]];
				for (int k=0; k<maxA; k++) if (k&pw(j)) ++alpha[k];
			}
		if (S[i]==0) {
			puts("Impossible");
			return 0;
		}
	}
	for (int i=1; i<=len; i++) printf("%c",S[i]);
	puts("");
	return 0;
}
