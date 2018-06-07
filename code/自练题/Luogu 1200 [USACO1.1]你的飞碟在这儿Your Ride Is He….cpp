#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<cstring>
using namespace std;

int main()
{
    string s1,s2;
    cin>>s1>>s2;
    int sum1=1,sum2=1;
    for (int i=0;i<s1.size();i++)
        sum1=sum1*((int)(s1[i])-64)%47;
    for (int i=0;i<s2.size();i++)
        sum2=sum2*((int)(s2[i])-64)%47;
    if (sum1==sum2)
        cout<<"GO"<<endl;
    else
        cout<<"STAY"<<endl;
    return 0;
}
