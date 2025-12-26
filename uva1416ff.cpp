#include <bits/stdc++.h>
using namespace std;

int bfs(
    int s,
    int t,
    vector<int>& parent,
    vector<vector<int>>& adj,
    vector<vector<int>>& cap
){
    fill(parent.begin(),parent.end(),-1);
    parent[s]=-2;

    queue<pair<int,int>> q;
    q.push({s,INT_MAX});

    while(!q.empty()){
        int u=q.front().first;
        int flow=q.front().second;
        q.pop();

        for(int v:adj[u]){
            if(parent[v]==-1&&cap[u][v]>0){
                parent[v]=u;
                int new_flow=min(flow,cap[u][v]);

                if(v==t){
                    return new_flow;
                }

                q.push({v,new_flow});
            }
        }
    }

    return 0;
}

int edmonds_karp(
    int n,
    int s,
    int t,
    vector<vector<int>>& adj,
    vector<vector<int>>& cap
){
    int max_flow=0;
    vector<int> parent(n);
    int flow;

    while((flow=bfs(s,t,parent,adj,cap))){
        max_flow+=flow;

        int v=t;
        while(v!=s){
            int u=parent[v];
            cap[u][v]-=flow;
            cap[v][u]+=flow;
            v=u;
        }
    }

    return max_flow;
}

int main(){
    int n,m,s,t;
    cin>>n>>m>>s>>t;

    vector<pair<pair<int,int>,int>> edges;
    vector<vector<int>> adj(n);
    vector<vector<int>> cap(n,vector<int>(n,0));
    vector<vector<int>> temp_cap;

    int min_flow=INT_MAX;
    pair<int,int> best_edge;

    for(int i=0;i<m;i++){
        int a,b,w;
        cin>>a>>b>>w;

        adj[a].push_back(b);
        adj[b].push_back(a);

        cap[a][b]=w;
        edges.push_back({{a,b},w});
    }

    for(auto& e:edges){
        temp_cap=cap;

        int a=e.first.first;
        int b=e.first.second;
        int w=e.second;

        temp_cap[a][b]=0;

        auto it1=find(adj[a].begin(),adj[a].end(),b);
        auto it2=find(adj[b].begin(),adj[b].end(),a);

        if(it1!=adj[a].end()){
            adj[a].erase(it1);
        }

        if(it2!=adj[b].end()){
            adj[b].erase(it2);
        }

        int flow=edmonds_karp(n,s,t,adj,temp_cap);

        if(flow<min_flow){
            min_flow=flow;
            best_edge={a,b};
        }

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    cout<<best_edge.first<<"->"<<best_edge.second<<"\n";
    cout<<min_flow<<"\n";

    return 0;
}

