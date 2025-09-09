#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
 
const int maks = 101;
 
int brgrad, brpat;
vector<pair<int, int>> graf[maks];
 
vector<int> dikstra(int poc) 
{
    vector<int> dist;
    dist.resize(maks);
    for (int i=0; i<maks; i++)
    {
        dist[i] = 1000000000; 
    }
      
    priority_queue<pair<int, int>> pq;
    dist[poc] = 0;
    pq.push({0, poc});
      
    int poseteni[maks];
    memset(poseteni, 0, sizeof(poseteni));
      
    while (!pq.empty()) 
    {
        pair<int, int> sostojba = pq.top();
        pq.pop();
           
        int grad = sostojba.second, dograd = -sostojba.first;
           
        if (poseteni[grad] == 0) 
        {
            poseteni[grad] = 1;
                
            for (auto rab : graf[grad]) 
            {
                int sled = rab.first, tezina = rab.second;
                     
                if (dist[sled] > dist[grad] + tezina) 
                {
                    dist[sled] = dist[grad] + tezina;
                    pq.push({ -dist[sled], sled });
                }
            }
        }
    }
      
    return dist;
}
 
 
int main() 
{
    cin >> brgrad;
    cin >> brpat;
    
    for (int i=0; i<brpat; i++)
    {
        int od, doo, tezina;
        cin >> od >> doo >> tezina;
           
        graf[od].push_back({doo, tezina});
    }
      
    int poc;
    cin >> poc;
      
    vector<int> dist = dikstra(poc);
      
    for(int i=0; i<brgrad; i++)
    {
        cout <<  dist[i] << endl;
    }
      
    return 0;
}
