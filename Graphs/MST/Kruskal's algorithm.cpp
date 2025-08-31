
#include<bits/stdc++.h>
using namespace std;

// } Driver Code Ends

class DisjointSet{


   vector<int>rank,parent,size;


   public:

    DisjointSet(int n)
    {

     rank.resize(n+1,0);

     parent.resize(n+1);
     size.resize(n+1);

     for(int i=0;i<=n;i++)
     {
         parent[i]=i;
           size[i]=i;

     }


    }


   int findUpar(int node)
   {

      if(node==parent[node])return node;


         return parent[node]=findUpar(parent[node]);


   }


   void unionByRank(int u,int v)
   {



      int p_u= findUpar(u);

      int p_v=findUpar(v);

      if(p_u==p_v){return;}

       if(rank[p_u]<rank[p_v])
       {
          parent[p_u]=p_v;

       }
       else if(rank[p_u]>rank[p_v])
       {

              parent[p_v]=p_u;

       }
       else{

           parent[p_v]=p_u;
         rank[p_u]++;


       }


   }



   void   unionBySize(int u,int v)
   {


     int p_u= findUpar(u);

      int p_v=findUpar(v);

      if(p_u==p_v){return;}

       if(rank[p_u]<rank[p_v])
       {
          parent[p_u]=p_v;
          size[p_v]+=size[p_u];

       }
        else{

           parent[p_v]=p_u;

            size[p_u]+=size[p_v];

       }





   }





};


class Solution
{

	public:
	//Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int v, vector<vector<int>> adj[])
    {


     vector<pair<int,pair<int,int>>>edges;



      for(int i=0;i<v;i++)
      {
       for(auto it:adj[i])
       {


    int adjNode=it[0];

     int wt=it[1];

       int node=i;

    edges.push_back({wt,{node,adjNode}});
     }




      }

    DisjointSet ds(v);

    sort(edges.begin(),edges.end());


     int mstwt=0;


        for(auto it:edges)
        {



       int wt=it.first;
       int u=it.second.first;

       int v=it.second.second;

        if(ds.findUpar(u)!=ds.findUpar(v))
        {


            mstwt+=wt;
            ds.unionByRank(u,v);


        }





        }




   return mstwt;
    }
};

//{ Driver Code Starts.


int main()
{
    int t;
    cin >> t;
    while (t--) {
        int V, E;
        cin >> V >> E;
        vector<vector<int>> adj[V];

       for(int i=0;i<E;i++){
            int u, v, w;
            cin >> u >> v >> w;
            vector<int> t1,t2;
            t1.push_back(v);
            t1.push_back(w);
            adj[u].push_back(t1);
            t2.push_back(u);
            t2.push_back(w);
            adj[v].push_back(t2);
        }

        Solution obj;
    	cout << obj.spanningTree(V, adj) << "\n";
    }

    return 0;
}

















