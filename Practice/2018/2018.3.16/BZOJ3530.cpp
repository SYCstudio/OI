#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101;
const int maxTrie=1700;
const int maxAlpha=10;
const int Mod=1e9+7;
const int inf=2147483647;

class TrieData
{
public:
	int fail,end;
	int son[maxAlpha];
};

int nodecnt=0,Queue[maxTrie];
char N[maxTrie],str[maxTrie];
TrieData T[maxTrie];
ll F[maxTrie][maxTrie][2];

void Insert(char *s);
void GetFail();

int main()
{
	scanf("%s",N+1);
	int n;scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%s",str+1);
		Insert(str);
	}
	GetFail();
	int L=strlen(N+1);
	
	F[0][0][0]=1;
	for (int i=0;i<L;i++)
		for (int j=0;j<=nodecnt;j++)
		{
			if (T[j].end!=0) continue;
			if (F[i][j][0])
			{
				for (int c=(i==0)?(1):(0);c<maxAlpha;c++)
					if (T[T[j].son[c]].end==0)
						F[i+1][T[j].son[c]][0]+=F[i][j][0],F[i+1][T[j].son[c]][0]%=Mod;
			}
		}
	//*/
	ll Ans=0;
	for (int i=1;i<L;i++) for (int j=0;j<=nodecnt;j++) if (T[j].end==0) Ans=(Ans+F[i][j][0])%Mod;
	mem(F,0);
	F[0][0][0]=1;//[0]危险态，[1]安全态
	for (int i=0;i<L;i++)
	{
		for (int j=0;j<=nodecnt;j++)
		{
			if (T[j].end!=0) continue;
			if (F[i][j][0])
			{
				for (int c=(i==0)?(1):(0);c<N[i+1]-'0';c++)
					if (T[T[j].son[c]].end==0) F[i+1][T[j].son[c]][1]+=F[i][j][0],F[i+1][T[j].son[c]][1]%=Mod/*,cout<<j<<" D:"<<c<<" "<<T[j].son[c]<<endl*/;
				if (T[T[j].son[N[i+1]-'0']].end==0) F[i+1][T[j].son[N[i+1]-'0']][0]+=F[i][j][0],
														F[i+1][T[j].son[N[i+1]-'0']][0]%=Mod/*,cout<<j<<" Danger! "<<T[j].son[N[i+1]-'0']<<endl*/;
			}
			if (F[i][j][1])
				for (int c=(i==0)?(1):(0);c<maxAlpha;c++)
					if (T[T[j].son[c]].end==0) F[i+1][T[j].son[c]][1]+=F[i][j][1],
												   F[i+1][T[j].son[c]][1]%=Mod/*,cout<<j<<" S:"<<c<<" "<<T[j].son[c]<<endl*/;
			
		}
		//for (int j=0;j<=nodecnt;j++) cout<<F[i+1][j][0]<<" "<<F[i+1][j][1]<<endl;
		//cout<<endl;
	}
	//for (int j=0;j<=nodecnt;j++) cout<<F[L][j][0]<<" "<<F[L][j][1]<<endl;
	//cout<<endl;
	for (int i=0;i<=nodecnt;i++) if (T[i].end==0) Ans+=F[L][i][0]+F[L][i][1],Ans%=Mod;
	printf("%lld\n",Ans);
	return 0;
}

void Insert(char *s)
{
	int len=strlen(s+1);
	//cout<<(s+1)<<" "<<len<<endl;
	int now=0;
	for (int i=1;i<=len;i++)
	{
		if (T[now].son[s[i]-'0']==0) T[now].son[s[i]-'0']=++nodecnt;
		now=T[now].son[s[i]-'0'];
	}
	T[now].end=1;
	return;
}

void GetFail()
{
	int h=0,t=0;
	for (int i=0;i<maxAlpha;i++) if (T[0].son[i]) Queue[++h]=T[0].son[i];
	while (t!=h)
	{
		int u=Queue[++t];
		for (int i=0;i<maxAlpha;i++)
			if (T[u].son[i])
			{
				T[T[u].son[i]].fail=T[T[u].fail].son[i];
				T[T[u].son[i]].end|=T[T[T[u].fail].son[i]].end;
				Queue[++h]=T[u].son[i];
			}
			else T[u].son[i]=T[T[u].fail].son[i];
	}
	return;
}
