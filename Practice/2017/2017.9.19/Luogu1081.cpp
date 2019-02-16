#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=100011;
const int maxTwo=20;
const int inf=2147483647;

class HEIGHT
{
public:
	int h,num;
	int nex,pre;
};

bool operator < (HEIGHT A,HEIGHT B)
{
	return A.h<B.h;
}

int n,X;
int Height[maxN];
HEIGHT Hclass[maxN];
int New_bh[maxN];
int Next_A[maxN];
int Path_A[maxN];
int Next_B[maxN];
int Path_B[maxN];
int Skip[23][maxN];
int Skip_A[23][maxN];
int Skip_B[23][maxN];

int read();
void Update(int &m1,int &m2,int h,int &id1,int &id2,int city);

int main()
{
	n=read();
	for (int i=1;i<=n;i++)
	{
		Height[i]=read();
		Hclass[i].h=Height[i];
		Hclass[i].num=i;
	}

	sort(&Hclass[1],&Hclass[n+1]);

	for (int i=1;i<=n;i++)
	{
		Hclass[i].pre=i-1;
		Hclass[i].nex=i+1;
		New_bh[Hclass[i].num]=i;
	}
	/*
	for (int i=1;i<=n;i++)
		cout<<Hclass[i].h<<"["<<Hclass[i].num<<"] ";
	cout<<endl;
	for (int i=1;i<=n;i++)
		cout<<New_bh[i]<<" ";
	cout<<endl;
	//*/
	Hclass[1].pre=-1;
	Hclass[n].nex=-1;

	for (int i=1;i<=n;i++)
	{
		//cout<<i<<" :"<<New_bh[i]<<endl;
		int now=New_bh[i];
		int m1=inf,m2=inf,h;
		int id1=-1,id2=-1;
		if (Hclass[now].pre!=-1)
		{
			h=Hclass[Hclass[now].pre].h-Hclass[now].h;
			Update(m1,m2,h,id1,id2,Hclass[now].pre);
			int p=Hclass[now].pre;
			if (Hclass[p].pre!=-1)
			{
				h=Hclass[Hclass[p].pre].h-Hclass[now].h;
				Update(m1,m2,h,id1,id2,Hclass[p].pre);
			}
			Hclass[p].nex=Hclass[now].nex;
		}
		if (Hclass[now].nex!=-1)
		{
			h=Hclass[Hclass[now].nex].h-Hclass[now].h;
			Update(m1,m2,h,id1,id2,Hclass[now].nex);
			int nx=Hclass[now].nex;
			if (Hclass[nx].nex!=-1)
			{
				h=Hclass[Hclass[nx].nex].h-Hclass[now].h;
				Update(m1,m2,h,id1,id2,Hclass[nx].nex);
			}
			Hclass[nx].pre=Hclass[now].pre;
		}
		Next_A[i]=Next_B[i]=-1;
		Path_A[i]=Path_B[i]=0;
		if (id1==-1)
			continue;
		Next_B[i]=id1;
		Path_B[i]=m1;
		if (id2==-1)
			continue;
		Next_A[i]=id2;
		Path_A[i]=m2;
	}
	/*
	for (int i=1;i<=n;i++)
		cout<<Next_A[i]<<" "<<Path_A[i]<<" "<<Next_B[i]<<" "<<Path_B[i]<<endl;
	cout<<endl;
	//*/

	memset(Skip,-1,sizeof(Skip));
	for (int i=1;i<=n;i++)
	{
		if (Next_A[i]==-1)
			continue;
		int nxa=Next_A[i];
		if (Next_B[nxa]==-1)
			continue;
		Skip[0][i]=Next_B[nxa];
		Skip_A[0][i]=Path_A[i];
		Skip_B[0][i]=Path_B[nxa];
		//cout<<i<<" "<<nxa<<" "<<Skip[0][i]<<" "<<Skip_A[0][i]<<" "<<Skip_B[0][i]<<endl;
	}
	//cout<<endl;
	for (int i=1;i<=maxTwo;i++)
		for (int j=1;j<=n;j++)
		    if (Skip[i-1][j]==-1)
				continue;
			else
			{
				Skip[i][j]=Skip[i-1][Skip[i-1][j]];
				Skip_A[i][j]=Skip_A[i-1][j]+Skip_A[i-1][Skip[i-1][j]];
				Skip_B[i][j]=Skip_B[i-1][j]+Skip_B[i-1][Skip[i-1][j]];
			}
	/*
	for (int i=1;i<=n;i++)
	{
		for (int j=0;(j<=maxTwo)&&(Skip[j][i]!=-1);j++)
		    cout<<'('<<Skip[j][i]<<','<<Skip_A[j][i]<<','<<Skip_B[j][i]<<") ";
		cout<<endl;
	}
	//*/

	X=read();
	int id;
	double sol=inf;
	for (int i=1;i<=n;i++)
	{
		int pA=0,pB=0;
		int ii=i;
		for (int j=maxTwo;j>=0;j--)
			if (Skip[j][ii]!=-1)
				if (Skip_A[j][ii]+Skip_B[j][ii]+pA+pB<=X)
				{
					pA+=Skip_A[j][ii];
					pB+=Skip_B[j][ii];
					ii=Skip[j][ii];
				}
		if ((Next_A[ii]!=-1)&&(Path_A[ii]+pA+pB<=X))
		{
			pA+=Path_A[ii];
			ii=Next_A[ii];
		}
		if (pB==0)
			continue;
		if (1.0*pA/pB<sol)
		{
			sol=1.0*pA/pB;
			id=i;
		}
	}
	printf("%d\n",id);

	int M=read();
	while (M--)
	{
		int st=read();
		X=read();
		int pA=0,pB=0;
		for (int j=maxTwo;j>=0;j--)
			if (Skip[j][st]!=-1)
				if (Skip_A[j][st]+Skip_B[j][st]+pA+pB<=X)
				{
					pA+=Skip_A[j][st];
					pB+=Skip_B[j][st];
					st=Skip[j][st];
				}
		if ((Next_A[st]!=-1)&&(Path_A[st]+pA+pB<=X))
		{
			pA+=Path_A[st];
			st=Next_A[st];
		}
		printf("%d %d\n",pA,pB);
	}
	return 0;
}

int read()
{
	int x=0,k=1;
	char ch=getchar();
	while (((ch>'9')||(ch<'0'))&&(ch!='-'))
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

void Update(int &m1,int &m2,int h,int &id1,int &id2,int city)
{
	city=Hclass[city].num;
	int h2=abs(h);
	if ((h2<m1)||((h2==m1)&&(h<0)))
	{
		m2=m1;
		m1=h2;
		id2=id1;
		id1=city;
	}
	else
		if ((h2<m2)||((h2==m2)&&(h<0)))
		{
			m2=h2;
			id2=city;
		}
	return;
}
