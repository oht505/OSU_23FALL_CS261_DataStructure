/*
 * In this file, you'll implement Dijkstra's algorithm to find the least
 * expensive paths in the graph defined in `airports.dat`.  Don't forget to
 * include your name and @oregonstate.edu email address below.
 *
 * Name: HyunTaek Oh
 * Email: ohhyun@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pq.h"

#define DATA_FILE "airports.dat"
#define START_NODE 0
#define INF 21344637

struct node_history{
  int curr;
  int prev;
};

int main(int argc, char const *argv[]) {
  /*
   * Write your code here to read the file `airports.dat` and to find the
   * least-cost paths from node 0 to all other nodes in the graph.  Make sure
   * to print out the least-cost paths you find at the end.
   */

  FILE *fp = fopen(DATA_FILE,"r");;
  int N=0, edge=0;
  
  fscanf(fp, "%d %d", &N, &edge);
  //printf("nodes: %d, edges: %d \n", N, edge);

  int cost[10];
  int prev[10];

  for(int i=0; i<N; i++){
    cost[i]=INF;
    prev[i]=0;
    //printf("cost[%d]: %d, prev[%d]: %d\n",i,cost[i],i,prev[i]);
  }

  
  // Vector Table
  int n=0, m=0, w=0, dist[10][10];
  fscanf(fp, "%d %d %d", &n, &m, &w);
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      if(n==i && m==j){
        dist[i][j]=w;
        fscanf(fp, "%d %d %d", &n, &m, &w);
      }
      else{
        dist[i][j]=INF;
      }
    }
  }
  //printf("%d\n", cost[9][7]);

  struct pq* pq = pq_create();
  struct node_history* nh = malloc(sizeof(struct node_history));
  nh->curr = START_NODE;
  nh->prev = 0;

  pq_insert(pq, nh, 0);

  int c=0;
  struct node_history* v;
  while(!pq_isempty(pq)){
    c = pq_first_priority(pq);
    v = pq_remove_first(pq);
    //printf("c: %d, v->curr: %d, v->prev: %d \n",c,v->curr,v->prev);
    if(c < cost[v->curr]){
        cost[v->curr]=c;
        prev[v->curr]=v->prev;

        for(int i=0;i<N;i++){
          if(dist[v->curr][i]!=INF){
            int c_i = dist[v->curr][i];
            struct node_history* node = malloc(sizeof(struct node_history));
            node->prev = v->curr;
            node->curr = i;
            
            pq_insert(pq, node, c+c_i);
          }
        }
    }
  }

  // for(int i=0; i<N; i++){
  //   printf("cost[%d]: %d, prev[%d]: %d \n",i,cost[i],i,prev[i]);
  // }

  for(int i=0;i<N;i++){
    printf("cost[%d]: ",i);
    int j = i;
    while(j!=0){
      printf("%d<-",j);
      j = prev[j];
    }
    printf("0 : %d\n",cost[i]);
  }

  pq_free(pq);
  fclose(fp);

  return 0;
}
