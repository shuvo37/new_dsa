#include<bits/stdc++.h>
using namespace std;

#define pb push_back
const int mx=1e5+2;
//unordered_map<int,vector<int>> adj,rev;
     int v,n;
   vector<int> adj[mx],rev[mx];
  int curr;
 bool vis[mx];


   void dfs1(int node,stack<int>&st)
   {

        vis[node]=true;
         for(auto x:adj[node])
         {
            if(!vis[x])
            {

             dfs1(x,st);

            }


         }

       st.push(node);

   }

  void reverse()
  {

    for(int i=1;i<=v;i++)
    {

      for(auto j:adj[i])
      {

        rev[j].push_back(i);

      }


    }

  }

  void dfs2(int node)
  {
      cout<<node<<" ";
      vis[node]=true;

      for(auto x:rev[node])
      {

         if(!vis[x])
         {

          dfs2(x);

         }


      }




  }

   void findSCCs(){


      stack<int>st;

      for(int i=1;i<=v;i++)
      {

        if(!vis[i])
        {

          dfs1(i,st);

        }


      }

     // while(!st.empty()){cout<<st.top()<<" ";st.pop();}
 //   cout<<"\n";


     reverse();
      for(int i=0;i<=v;i++)
      {
          vis[i]=false;
      }

     while(!st.empty())
     {

         curr=st.top();
         st.pop();
           if(!vis[curr])
             {
               dfs2(curr);
               cout<<"\n";

             }




     }



   }






int main()
{

     cin>>v>>n;
       int u,v;
     for(int i=1;i<=n;i++){
      cin>>u>>v;
	  adj[u].pb(v);
     }

	findSCCs();
	return 0;
}
