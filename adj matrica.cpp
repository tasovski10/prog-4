
#include <iostream>
using namespace std;

void add(int a[][100],int x,int y) {
    a[x][y]=1;
    a[y][x]=1;
}

void print(int a[][100],int n) {
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) cout<<a[i][j]<<" ";
        cout<<"\n";
    }
}

int main() {
    int n,m;
    cin>>n>>m;
    int a[100][100]={0};
    for(int i=0;i<m;i++) {
        int x,y;
        cin>>x>>y;
        add(a,x,y);
    }
    print(a,n);
}
