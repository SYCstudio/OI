// Copyright (C) 2017 SYCstudio.

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; version 3

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; If not, see <http://www.gnu.org/licenses/>.
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define mcp(Arr,Brr) memcpy(Arr,Brr,sizeof(Arr))

const int maxN=1000;
const int inf=2147483647;

char str[maxN];
int F[maxN][maxN];
int Path[maxN][maxN];

int read();
void Outp(int l,int r);

int main()
{
	int T=read();
	int cnt=0;
	while (T--)
	{
		cin.getline(str+1,maxN);
		cin.getline(str+1,maxN);
		int l=strlen(str+1);
		//printf("%d\n",l);
		mem(F,0);
		for (int i=1;i<=l;i++)
			F[i][i]=1;
		for (int i=l;i>=1;i--)
			for (int j=i+1;j<=l;j++)
			{
				//cout<<i<<" "<<j<<endl;
				F[i][j]=inf;
				if (((str[i]=='(')&&(str[j]==')'))||((str[i]=='[')&&(str[j]==']')))
					if (F[i+1][j-1]<F[i][j])
					{
						F[i][j]=F[i+1][j-1];
						Path[i][j]=-1;
					}
				for (int k=i;k<j;k++)
					if (F[i][k]+F[k+1][j]<F[i][j])
					{
						F[i][j]=F[i][k]+F[k+1][j];
						Path[i][j]=k;
					}
			}
		/*
		for (int i=1;i<=l;i++)
			for (int j=i+1;j<=l;j++)
				cout<<i<<" "<<j<<" "<<F[i][j]<<" "<<Path[i][j]<<endl;
		printf("%d\n",F[1][l]);
		//*/
		if (cnt)
			printf("\n");
		Outp(1,l);
		printf("\n");
		cnt++;
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}

int read()
{
	int x=0,k=1;
	char ch=getchar();
	while (((ch<'0')||(ch>'9'))&&(ch!='-'))
		ch=getchar();
	if (ch=='-')
	{
		k=-1;
		ch=getchar();
	}
	while ((ch>='0')&&(ch<='9'))
	{
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*k;
}

void Outp(int l,int r)
{
	if (l>r)
		return;
	if (l==r)
	{
		if ((str[l]=='(')||(str[l]==')'))
			printf("()");
		else
			printf("[]");
		return;
	}
	//printf("%c",str[l]);
	if (Path[l][r]==-1)
	{
		printf("%c",str[l]);
		Outp(l+1,r-1);
		printf("%c",str[r]);
	}
	else
	{
		Outp(l,Path[l][r]);
		Outp(Path[l][r]+1,r);
	}
	//printf("%c",str[r]);
	return;
}
