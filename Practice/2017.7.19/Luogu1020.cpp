#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int maxN=200;
const int inf=2147483647;

int n;
int Height[maxN];
vector<int> Arr;

int main()
{
    n=1;
    while (cin>>Height[n])
        n++;
    n--;
    Arr.clear();
    vector<int>::iterator Find;
    for (int i=n;i>=1;i--)//第一问，求倒序的最长不下降子序列
    {
        if ((Arr.size()==0)||(Arr[Arr.size()-1]<=Height[i]))//注意这里可以取等
            Arr.push_back(Height[i]);
        else
        {
            Find=lower_bound(Arr.begin(),Arr.end(),Height[i]);
            while (*Find==Height[i])//这里的while是求出第一个大于Height[i]的
                Find++;
            *Find=Height[i];
        }
    }
    cout<<Arr.size()<<endl;
    Arr.clear();
    for (int i=1;i<=n;i++)//第二问，求最长递增子序列
    {
        if ((Arr.size()==0)||(Arr[Arr.size()-1]<Height[i]))//注意这里不能取等
            Arr.push_back(Height[i]);
        else
        {
            Find=lower_bound(Arr.begin(),Arr.end(),Height[i]);
            *Find=Height[i];
        }
    }
    cout<<Arr.size()<<endl;
    return 0;
}
