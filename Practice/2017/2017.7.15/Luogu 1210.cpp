#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<string>
using namespace std;

const int maxN=20001;
const int inf=2147483647;

int L;
char Text[maxN];
char str[maxN*2];
int P[maxN*2];
int f[maxN*2];

void Manacher();

int main()
{
    int l=0;
    while ((Text[l]=getchar())!=EOF)
        l++;
    L=0;
    str[0]='$';
    for (int i=0;i<=l;i++)
    {
        if ((Text[i]>='A')&&(Text[i]<='Z'))
        {
            L++;
            str[L]='@';
            L++;
            str[L]=Text[i];
            f[L]=i;
        }
        else
        if ((Text[i]>='a')&&(Text[i]<='z'))
        {
            L++;
            str[L]='@';
            L++;
            str[L]=Text[i]-'a'+'A';
            f[L]=i;
        }
    }
    L++;
    str[L]='@';
    L++;
    str[L]='\0';
    Manacher();
    int maxID=0;
    for (int i=1;i<=L;i++)
        if (P[i]>P[maxID])
            maxID=i;
    cout<<P[maxID]-1<<endl;
    //for (int i=maxID-P[maxID]+1;i<=maxID+P[maxID]-1;i++)
    //    cout<<str[i];
    //cout<<endl;
    for (int i=maxID-P[maxID]+2;i<maxID+P[maxID]-2;i++)
    {
        if (str[i]!='@')
            for (int j=f[i];j<f[i+2];j++)
                cout<<Text[j];
    }
    cout<<Text[f[maxID+P[maxID]-2]]<<endl;
    return 0;
}

void Manacher()
{
    int id=1,mx=-1;
    for (int i=1;i<=L;i++)
    {
        if (mx>i)
            P[i]=min(P[id*2-i],mx-i);
        else
            P[i]=1;
        while (str[i-P[i]]==str[i+P[i]])
            P[i]++;
        if (i+P[i]>mx)
        {
            mx=i+P[i];
            id=i;
        }
    }
    //for (int i=1;i<=L;i++)
    //    cout<<P[i]<<' ';
    //cout<<endl;
    return;
}