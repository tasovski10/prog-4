#include <iostream>
#include <vector>
using namespace std;

void add(vector<vector<int>> &a,int x,int y) {
    a[x].push_back(y);
    a[y].push_back(x);
}

void print(const vector<vector<int>> &a,int n) {
    for(int i=0;i<n;i++) {
        cout<<i<<":"<<" ";
        for(int j=0;j<a[i].size();j++) {
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main() {
    int n,m;
    cin>>n>>m;
    vector<vector<int>> a(n);
    for(int i=0;i<m;i++) {
        int x,y;
        cin>>x>>y;
        add(a,x,y);
    }
    
    print(a,n);
}
