#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxsize=2000;
const int inf=2147483647;

int n;
int Num[50];
int Size[50]={0,1,2,3,5,10,20};
bool Hash[maxsize];

int main()
{
    int Tot=0;
    memset(Hash,0,sizeof(Hash));
    //cin>>n;
    for (int i=1;i<=6;i++)
    {
        cin>>Num[i];
        Tot+=Num[i]*Size[i];
    }
    for (int a=0;a<=Num[1];a++)
        for (int b=0;b<=Num[2];b++)
            for (int c=0;c<=Num[3];c++)
                for (int d=0;d<=Num[4];d++)
                    for (int e=0;e<=Num[5];e++)
                        for (int f=0;f<=Num[6];f++)
                            Hash[a+b*2+c*3+d*5+e*10+f*20]=1;
    int cnt=0;
    for (int i=1;i<=Tot;i++)
        if (Hash[i]==1)
            cnt++;
    cout<<"Total="<<cnt<<endl;
    return 0;
}
