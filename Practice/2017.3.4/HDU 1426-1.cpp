#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

class Point
{
public:
    int x,y;
};

const int maxsize=90;
const int inf=2147483647;

int cnt;
Point Ques[maxsize];
int Map[10][10];

void dfs(int x);
bool OK(int x,int number);

int main()
{
    int i,j,k;
    char ch;
    
    while (cin>>ch)
    {
    	cnt=0;
        if (ch=='?')//��Ϊ�ж������ݣ�����Ҫ�ȶ�һ���Ա��ж��Ƿ�Ҫ������ 
        {
            Map[1][1]=0;
            cnt++;
            Ques[1].x=1;
            Ques[1].y=1;
		}
		else
		    Map[1][1]=ch-48;
		
		for (i=1;i<=9;i++)//��ʣ�µ����� 
		    for (j=1;j<=9;j++)
		        if (!((i==1)&&(j==1)))
		        {
		            cin>>ch;
		            if (ch=='?')
		            {
		                Map[i][j]=0;
		                cnt++;
		                Ques[cnt].x=i;
		                Ques[cnt].y=j;
					}
					else
					    Map[i][j]=ch-48;
				}
		
		dfs(1);
		
	}
    
    
}

void dfs(int x)
{
	int i,j;
	
    if (x==cnt+1)
    {
        for (i=1;i<=9;i++)
        {
            for (j=1;j<=9;j++)
                cout<<Map[i][j]<<" ";
            cout<<endl;
		}
	    return;
	}
	
	for (i=1;i<=9;i++)
	    if (OK(x,i))
	    {
	        Map[Ques[x].x][Ques[x].y]=i;
	        dfs(x+1);
		}
}

bool OK(int x,int number)
{
    int i,j;
    int x0=Ques[x].x;
    int y0=Ques[x].y;
    
    for (i=1;i<=9;i++)
        if ((Map[x0][i]==number)||(Map[i][y0]==number))//����к��� 
            return 0;
    
    x0=((x0-1)/3+1)*3;//�ҵ���ǰx���ڵĴ��������½ǵĸ��ӣ������߼�����ڴ���Ƿ����� 
    y0=((y0-1)/3+1)*3;
    
    for (i=-2;i<=0;i++)//��⵱ǰС�����ڵĴ�� 
        for (j=-1;j<=0;j++)
            if (Map[x0+i][y0+j]==number)
                return 0;
    
    return 1;
    
}
