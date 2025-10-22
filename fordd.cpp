#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class pat { public: int a,b,w; };

int dfs(int x,int n,vector< vector<int>> &g,vector<int> &vis,vector<pat> &p,int mn=10000000){
    if(x==n-1)return mn;
    vis[x]=1;
    for(int y=0;y<n;y++){
        if(!vis[y]&&g[x][y]!=0){
            int val=dfs(y,n,g,vis,p,min(mn,g[x][y]));
            if(val!=0){
                p.push_back({x,y,g[x][y]});
                g[x][y]-=val;
                g[y][x]+=val;
                return val;
            }
        }
    }
    return 0;
}

int main(){
    int n,m,f=0;
    cin>>n>>m;
    vector<vector<int>> g(n,vector<int>(n,0));
    for(int i=0;i<m;i++) {
        int u,v,w;
        cin>>u>>v>>w;
        g[u][v]=w;
    }
    while(1){
        vector<int> vis(n,0);
        vector<pat> p;
        int flow=dfs(0,n,g,vis,p);
        if(flow==0)break;
        while(!p.empty()) {
            pat e=p.back();
            p.pop_back();
            cout<<e.a<<"->"<<e.b<<"("<<e.w<<"), ";
        }
        cout<<endl;
        f+=flow;
    }
    cout<<f;
}
