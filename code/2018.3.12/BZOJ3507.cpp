#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define ll long long
#define ull unsigned long long

const int maxN=100010;
const int Hashbase=1705;
const int inf=2147483647;

char str[maxN],SS[maxN];
ull Hash1[maxN],Hash2[maxN];
int pcnt=0,P[maxN];
ull Bret[maxN];
int F[13][maxN];

void InitHash(char *s,ull *hash);
ull GetHash(int l,int r,ull *hash);

int main()
{
	ios::sync_with_stdio(false);
	Bret[0]=1;for (int i=1;i<maxN;i++) Bret[i]=Bret[i-1]*Hashbase;
	cin>>(str+1);
	InitHash(str,Hash1);
	int L=strlen(str+1);
	str[++L]='?';
	
	for (int i=1;i<=L;i++) if ((str[i]=='?')||(str[i]=='*')) P[++pcnt]=i;

	int Q;cin>>Q;
	while (Q--)
	{
		cin>>(SS+1);InitHash(SS,Hash2);
		mem(F,0);F[0][0]=1;
		int len=strlen(SS+1);SS[++len]='#';
		for (int i=0;i<pcnt;i++)
		{
			if (str[P[i]]=='*')
				for (int j=1;j<=len;j++)
					if (F[i][j-1]) F[i][j]=1;
			for (int j=0;j<=len;j++)
				if (F[i][j])
					if (GetHash(P[i]+1,P[i+1]-1,Hash1)==GetHash(j+1,j+((P[i+1]-1)-(P[i]+1))+1,Hash2))
					{
						if (str[P[i+1]]=='?') F[i+1][j+((P[i+1]-1)-(P[i]+1))+1+1]=1;
						else F[i+1][j+((P[i+1]-1)-(P[i]+1))+1]=1;
					}
		}
		if (F[pcnt][len]) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}

void InitHash(char *s,ull *hash)
{
	int len=strlen(s+1);
	hash[0]=0;
	for (int i=1;i<=len;i++) hash[i]=hash[i-1]*Hashbase+s[i];
	return;
}

ull GetHash(int l,int r,ull *hash)
{
	if (r<l) return -1;
	return hash[r]-hash[l-1]*Bret[r-l+1];
}
