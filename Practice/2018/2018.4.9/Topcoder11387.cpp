#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=32;
const int inf=2147483647;

int n,m;
int Cnt1[maxN][maxN*maxN*2];
int Cnt2[maxN][maxN*maxN*2];
int Cnt3[maxN][maxN*maxN*2];
int Cnt4[maxN][maxN*maxN*2];
int Sum1[maxN][maxN];
int Sum2[maxN][maxN];
char Map[maxN][maxN];

void Max(int &x,int key){
	x=max(x,key);return;
}

int Calc1(int x1,int y1,int x2,int y2){
	return Sum1[x2][y2]-Sum1[x1-1][y2]-Sum1[x2][y1-1]+Sum1[x1-1][y1-1];
}

int Calc2(int x1,int y1,int x2,int y2){
	return Sum2[x2][y2]-Sum2[x1-1][y2]-Sum2[x2][y1-1]+Sum2[x1-1][y1-1];
}

class FoxAndFlowerShopDivOne
{
public:
	int theMaxFlowers(vector<string> flowers, int maxDiff){
		mem(Cnt1,-1);mem(Cnt2,-1);mem(Cnt3,-1);mem(Cnt4,-1);mem(Sum1,0);mem(Sum2,0);
		n=flowers.size();
		m=flowers[0].size();
		for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) Map[i][j]=flowers[i-1][j-1];
		/*
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=m;j++)
				cout<<Map[i][j];
			cout<<endl;
		}
		//*/
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
			{
				if (Map[i][j]=='L') Sum1[i][j]=1;
				else if (Map[i][j]=='P') Sum1[i][j]=-1;
				else Sum1[i][j]=0;
				if (Map[i][j]=='.') Sum2[i][j]=0;
				else Sum2[i][j]=1;
			}
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
			{
				Sum1[i][j]+=Sum1[i-1][j]+Sum1[i][j-1]-Sum1[i-1][j-1];
				Sum2[i][j]+=Sum2[i-1][j]+Sum2[i][j-1]-Sum2[i-1][j-1];
			}
		/*
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=m;j++)
				cout<<Sum1[i][j]<<" ";
			cout<<endl;
		}
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=m;j++)
				cout<<Sum2[i][j]<<" ";
			cout<<endl;
		}
		//*/
		for (int x1=1;x1<=n;x1++)
			for (int x2=x1;x2<=n;x2++)
				for (int y1=1;y1<=m;y1++)
					for (int y2=y1;y2<=m;y2++)
					{
						int s1=Calc1(x1,y1,x2,y2),s2=Calc2(x1,y1,x2,y2);
						//cout<<"("<<x1<<","<<y1<<") ("<<x2<<","<<y2<<") "<<s1<<" "<<s2<<endl;
						Max(Cnt1[x2][s1+n*m],s2);
						Max(Cnt2[x1][s1+n*m],s2);
						Max(Cnt3[y2][s1+n*m],s2);
						Max(Cnt4[y1][s1+n*m],s2);
					}
		for (int i=-n*m;i<=n*m;i++)
		{
			for (int j=1;j<=n;j++) Max(Cnt1[j][i+n*m],Cnt1[j-1][i+n*m]);
			for (int j=n;j>=1;j--) Max(Cnt2[j][i+n*m],Cnt2[j+1][i+n*m]);
			for (int j=1;j<=m;j++) Max(Cnt3[j][i+n*m],Cnt3[j-1][i+n*m]);
			for (int j=m;j>=1;j--) Max(Cnt4[j][i+n*m],Cnt4[j+1][i+n*m]);
		}
		/*
		for (int i=-n*m;i<=n*m;i++)
		{
			cout<<"i:"<<i<<endl;
			for (int j=1;j<=n;j++) cout<<Cnt1[j][i+n*m]<<" ";cout<<endl;
			for (int j=1;j<=n;j++) cout<<Cnt2[j][i+n*m]<<" ";cout<<endl;
			for (int j=1;j<=m;j++) cout<<Cnt3[j][i+n*m]<<" ";cout<<endl;
			for (int j=1;j<=m;j++) cout<<Cnt4[j][i+n*m]<<" ";cout<<endl;
			cout<<endl;
		}
		//*/
		int Ans=-1;
		for (int k1=-n*m;k1<=n*m;k1++)
			for (int k2=-n*m;k2<=n*m;k2++)
				if (abs(k1+k2)<=maxDiff)
				{
					//cout<<k1<<" "<<k2<<endl;
					for (int x=1;x<n;x++)
						if ((Cnt1[x][k1+n*m]!=-1)&&(Cnt2[x+1][k2+n*m]!=-1))
						{
							Max(Ans,Cnt1[x][k1+n*m]+Cnt2[x+1][k2+n*m]);
							//cout<<"x:"<<x<<" "<<Cnt1[x][k1+n*m]<<" "<<Cnt2[x+1][k2+n*m]<<endl;
						}
					for (int y=1;y<m;y++)
						if ((Cnt3[y][k1+n*m]!=-1)&&(Cnt4[y+1][k2+n*m]!=-1))
						{
							Max(Ans,Cnt3[y][k1+n*m]+Cnt4[y+1][k2+n*m]);
							//cout<<"y:"<<y<<" "<<Cnt3[y][k1+n*m]<<" "<<Cnt4[y+1][k2+n*m]<<endl;
						}
				}
		return Ans;
	}
};

string In[]={"LLLP..LLP.PLL.LL..LP",
			 "L.PL.L.LLLL.LPLLPLP.",
			 "PLL.LL.LLL..PL...L..",
			 ".LPPP.PPPLLLLPLP..PP",
			 "LP.P.PPL.L...P.L.LLL",
			 "L..LPLPP.PP...PPPL..",
			 "PP.PLLL.LL...LP..LP.",
			 "PL...P.PPPL..PLP.L..",
			 "P.PPPLPLP.LL.L.LLLPL",
			 "PLLPLLP.LLL.P..P.LPL",
			 "..LLLPLPPPLP.P.LP.LL",
			 "..LP..L..LLPPP.LL.LP",
			 "LPLL.PLLPPLP...LL..P",
			 "LL.....PLL.PLL.P....",
			 "LLL...LPPPPL.PL...PP",
			 ".PLPLLLLP.LPP...L...",
			 "LL...L.LL.LLLPLPPPP.",
			 "PLPLLLL..LP.LLPLLLL.",
			 "PP.PLL..L..LLLPPL..P",
			 ".LLPL.P.PP.P.L.PLPLL"};
vector<string> Input(In,In+20);
int diff=9;

int main()
{
	cout<<Do.theMaxFlowers(Input,diff)<<endl;
	return 0;
}
