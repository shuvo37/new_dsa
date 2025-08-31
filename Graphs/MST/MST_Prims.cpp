#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,int> pii;
const int  mx=1e5+3;




ll spanningTree(int V, int E,vector<pair<int,ll>>adj[])
{


    priority_queue<pii, vector<pii>, greater<pii>> pq;



    vector<bool> visited(V, false);


    ll  res = 0;


    pq.push({0, 1});


    while(!pq.empty()){

        auto p = pq.top();
        pq.pop();

        ll wt = p.first;
        int u = p.second;

        if(visited[u] == true){
            continue;
        }

        res += wt;
        visited[u] = true;


        for(auto x : adj[u]){

              int v=x.first;
            if(visited[v] == false){
                pq.push({x.second, x.first});
            }
        }
    }

    return res;
}

int main()
{
      int n,m;
      cin>>n>>m;

   vector<pair<int,ll>>adj[n+1];
     int x,y;
      ll w;
    for(int i=1;i<=m;i++)
    {
       cin>>x>>y>>w;

     adj[x].push_back({y,w});
     adj[y].push_back({x,w});


    }


    cout << spanningTree(n,m,adj) << endl;

    return 0;
}
