#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<map>
using namespace std;

map<string,int> Cnt;//���㱻�ն��Ĵ���
map<string,string> Name;//��ŵ�һ���ն��ĳ��ߵ�����

int main()
{
    string read;//ÿ�ζ���
    string Ans="";//�����
    while (cin>>read)
    {
        if (read==".")
            break;
        string s1="",s2="";
        bool ok=0;
        for (int i=0;i<read.size();i++)
        {
            if (read[i]==':')
            {
                ok=1;
                continue;
            }
            if (ok==0)
                s1+=read[i];
            else
                s2+=read[i];
        }
        if (Cnt[s2]==0)
            Name[s2]=s1;
        Cnt[s2]++;
        if (Cnt[Ans]<Cnt[s2])
            Ans=s2;
    }
    cout<<Name[Ans]<<endl<<Ans<<endl;
    return 0;
}
