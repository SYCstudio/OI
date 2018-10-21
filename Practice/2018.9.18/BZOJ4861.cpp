#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=55;
const int maxAlpha=26;
const int maxNode=110;
const int Mod=1e9+7;
const int inf=2147483647;

class Trie
{
public:
	int son[maxAlpha],fail,end;
};

int nodecnt,n,m,L,Len[maxN];
Trie T[maxNode];
char Input[maxNode],Basic[maxN][maxNode];
queue<int> Qu;

void Insert(char *str);
void GetFail();
void Plus(int &x,int y);

namespace cpp1
{
	const int maxL=110;

	int Trans[maxNode][maxN];
	int F[maxL][maxNode];

	void Dp();
}

namespace cpp2
{
	const int maxMat=210;

	int Sz;
	int Mat1[maxMat][maxMat],Mat2[maxMat][maxMat],Bp[maxMat][maxMat];
	
	void Dp();
	void Mul1();
	void Mul2();
}

int main(){
	scanf("%d%d%d",&n,&m,&L);
	for (int i=1;i<=n;i++) scanf("%s",Basic[i]+1),Len[i]=strlen(Basic[i]+1);
	for (int i=1;i<=m;i++){
		scanf("%s",Input+1);
		Insert(Input);
	}

	/*
	for (int i=0;i<=nodecnt;i++)
		for (int j=0;j<maxAlpha;j++)
			if (T[i].son[j]) cout<<i<<" -> "<<T[i].son[j]<<" ["<<(char)(j+'a')<<"]"<<endl;
	//*/
	
	GetFail();

	if (L<=100) cpp1::Dp();
	else cpp2::Dp();
	return 0;
}

void Insert(char *str){
	int len=strlen(str+1);
	int now=0;
	for (int i=1;i<=len;i++){
		if (T[now].son[str[i]-'a']==0) T[now].son[str[i]-'a']=++nodecnt;
		now=T[now].son[str[i]-'a'];
	}
	T[now].end|=1;return;
}

void GetFail(){
	for (int i=0;i<maxAlpha;i++) if (T[0].son[i]) Qu.push(T[0].son[i]);
	while (!Qu.empty()){
		int u=Qu.front();Qu.pop();
		for (int i=0;i<maxAlpha;i++)
			if (T[u].son[i]){
				T[T[u].son[i]].fail=T[T[u].fail].son[i];
				T[T[u].son[i]].end|=T[T[T[u].fail].son[i]].end;
				Qu.push(T[u].son[i]);
			}
			else T[u].son[i]=T[T[u].fail].son[i];
	}
	return;
}

void Plus(int &x,int y){
	x=(x+y)%Mod;return;
}

namespace cpp1
{
	void Dp(){
		for (int i=0;i<=nodecnt;i++)
			for (int j=1;j<=n;j++){
				int now=i;bool flag=1;
				if (T[now].end) flag=0;
				for (int k=1;k<=Len[j];k++){
					now=T[now].son[Basic[j][k]-'a'];
					if (T[now].end){
						flag=0;break;
					}
				}
				if (flag==0) Trans[i][j]=-1;
				else Trans[i][j]=now;

				//cout<<i<<" + "<<j<<" "<<Trans[i][j]<<endl;
			}
		F[0][0]=1;
		for (int i=0;i<L;i++)
			for (int j=0;j<=nodecnt;j++)
				if ((F[i][j])&&(T[j].end==0))
					for (int k=1;k<=n;k++)
						if ((Trans[j][k]!=-1)&&(i+Len[k]<=L))
							Plus(F[i+Len[k]][Trans[j][k]],F[i][j]);
		int Ans=0;
		for (int i=0;i<=nodecnt;i++) Ans=(Ans+F[L][i])%Mod;
		printf("%d\n",Ans);
		return;
	}
}

namespace cpp2
{
	void Dp(){
		Sz=nodecnt*2+1;
		for (int i=0;i<=nodecnt;i++) Mat2[nodecnt+i+1][i]=1;
		for (int i=0;i<=nodecnt;i++)
			if (T[i].end==0){
				for (int j=1;j<=n;j++)
					if (Len[j]==1){
						int k=T[i].son[Basic[j][1]-'a'];
						if (T[k].end) continue;
						Mat2[i][k]++;
						//cout<<"Trans:"<<i<<" "<<j<<" -> "<<k<<" l=1"<<endl;
					}
					else{
						int k=T[T[i].son[Basic[j][1]-'a']].son[Basic[j][2]-'a'];
						if ((T[T[i].son[Basic[j][1]-'a']].end)||(T[k].end)) continue;
						Mat2[i][k+nodecnt+1]++;
						//cout<<"Trans:"<<i<<" "<<j<<" -> "<<k<<" l=2"<<endl;
					}
			}

		/*
		for (int i=0;i<=Sz;i++){
			for (int j=0;j<=Sz;j++)
				cout<<Mat2[i][j]<<" ";
			cout<<endl;
		}
		//*/
		
		Mat1[0][0]=1;
		/*
		for (int i=1;i<=L;i++){
			Mul1();
			cout<<"Mul:"<<i<<endl;
			for (int j=0;j<=nodecnt;j++){
				for (int k=0;k<=nodecnt;k++)
					cout<<Mat1[j][k]<<" ";
				cout<<endl;
			}
		}
		//*/
		
		int Cnt=L;
		while (Cnt){
			if (Cnt&1) Mul1();
			Mul2();Cnt>>=1;
		}
		//*/

		int Ans=0;
		for (int i=0;i<=nodecnt;i++) Plus(Ans,Mat1[0][i]);
		printf("%d\n",Ans);
		return;
	}

	void Mul1(){
		for (int i=0;i<=1;i++) for (int j=0;j<=Sz;j++) Bp[i][j]=Mat1[i][j],Mat1[i][j]=0;
		for (int k=0;k<=Sz;k++)
			for (int i=0;i<=1;i++)
				for (int j=0;j<=Sz;j++)
					Plus(Mat1[i][j],1ll*Bp[i][k]*Mat2[k][j]%Mod);
		return;
	}

	void Mul2(){
		for (int i=0;i<=Sz;i++) for (int j=0;j<=Sz;j++) Bp[i][j]=Mat2[i][j],Mat2[i][j]=0;
		for (int k=0;k<=Sz;k++)
			for (int i=0;i<=Sz;i++)
				for (int j=0;j<=Sz;j++)
					Plus(Mat2[i][j],1ll*Bp[i][k]*Bp[k][j]%Mod);
		return;
	}
}
