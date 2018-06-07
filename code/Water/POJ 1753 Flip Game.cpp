#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<cstring>
using namespace std;

const int maxsize=70000;
const int inf=2147483647;

bool Hash[70000]={0};
int FFF[20];
int Q[maxsize]={0};
int step[maxsize]={0};
//65535

int Change(int k,int i);

int main()
{
    int i,j,k;
    string str;
    for (i=0;i<=16;i++)
        FFF[i]=1<<i;
    for (i=1;i<=4;i++)
    {
        cin>>str;
        for (j=0;j<=3;j++)
            if (str[j]=='w')
                Q[1]+=FFF[(i-1)*4+j];
        //cout<<Q[1]<<endl;
    }
    //cout<<Q[1]<<endl;
    Hash[Q[1]]=1;
    step[1]=0;
    int h,t;
    t=0;h=1;
    do
    {
        t++;
        if ((Q[t]==65535)||(Q[t]==0))
        {
            cout<<step[t]<<endl;
            return 0;
        }
        for (i=0;i<=15;i++)
        {
            int k=Q[t];
            k=Change(k,i);
            if (Hash[k]==0)
            {
                h++;
                Q[h]=k;
                Hash[k]=1;
                step[h]=step[t]+1;
            }
        }
    }
    while (t<h);
    cout<<"Impossible"<<endl;
    return 0;
}

int Change(int k,int i)
{
    k=k^FFF[i];
    if (i>=4)
    {
        k=k^FFF[i-4];
    }
    if (i<=11)
    {
        k=k^FFF[i+4];
    }
    if (i%4!=0)
    {
        k=k^FFF[i-1];
    }
    if (i%4!=3)
    {
        k=k^FFF[i+1];
    }
    return k;
}
