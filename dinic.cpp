#include <bits/stdc++.h>
using namespace std;

struct edge{
    int u,v;
    long long cap,fl=0;
    edge(int u,int v,long long cap):u(u),v(v),cap(cap){}
};

struct dinic{
    vector<edge> e;
    vector<vector<int>> g;

    int n,idx=0;
    int src,snk;

    vector<int> lvl,it;
    queue<int> que;

    dinic(int n,int src,int snk):n(n),src(src),snk(snk){
        g.resize(n);
        lvl.resize(n);
        it.resize(n);
    }

    void add_edge(int u,int v,long long cap){
        e.emplace_back(u,v,cap);
        e.emplace_back(v,u,0);

        g[u].push_back(idx);
        g[v].push_back(idx+1);
        idx+=2;
    }

    bool bfs(){
        while(!que.empty()){
            int x=que.front();
            que.pop();

            for(int id:g[x]){
                if(e[id].cap==e[id].fl)continue;
                if(lvl[e[id].v]!=-1)continue;

                lvl[e[id].v]=lvl[x]+1;
                que.push(e[id].v);
            }
        }

        return lvl[snk]!=-1;
    }

    long long dfs(int x,long long pushed){
        if(pushed==0)return 0;
        if(x==snk)return pushed;

        for(int &cid=it[x];cid<(int)g[x].size();cid++){
            int id=g[x][cid];
            int y=e[id].v;

            if(lvl[x]+1!=lvl[y])continue;

            long long tr=dfs(y,min(pushed,e[id].cap-e[id].fl));
            if(tr==0)continue;

            e[id].fl+=tr;
            e[id^1].fl-=tr;
            return tr;
        }

        return 0;
    }

    long long max_flow(){
        long long ans=0;

        while(1){
            fill(lvl.begin(),lvl.end(),-1);
            lvl[src]=0;

            que.push(src);
            if(!bfs())break;

            fill(it.begin(),it.end(),0);

            long long pushed;
            while((pushed=dfs(src,INT_MAX))){
                ans+=pushed;
            }
        }

        return ans;
    }
};

int main(){
    int n,m,src,snk;
    cin>>n>>m>>src>>snk;

    dinic d(n,src,snk);

    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        d.add_edge(u,v,w);
    }

    cout<<d.max_flow();
    return 0;
}
