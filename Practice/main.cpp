#include<bits/stdc++.h>
using namespace std;

int main(){
    int cas=0;
    while (1){
        system("./gen");system("./C <in >out");system("./zsy <in >zout");
        if (system("diff out zout")){
            cout<<"Wrong"<<endl;break;
        }
        cout<<"OK "<<++cas<<endl;
    }
    return 0;
}