/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.c
 *
 * Created on 5 de febrero de 2019, 13:03
 */

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void p1_e2_cleanup(Graph *g){
    graph_destroy(g);
}

int main () {

   //variable declaration
    Node *node1=NULL;
    Node *node2=NULL;
    int id1=111,id2=222;
    Status st=ERROR;

    Graph *graph = NULL;
    graph = graph_ini();
    if(!graph) p1_e2_cleanup(graph);

    node1=node_ini();
    if(!node1) p1_e2_cleanup(graph);

    //node set id and name
    node_setId(node1,id1);
    node_setName(node1,"first");

    node2=node_ini();
    if(!node2) p1_e2_cleanup(graph);

    //node set id and name
    node_setId(node2,id2);
    node_setName(node2,"second");

    st = graph_insertNode(graph,node1);
    printf("\nInserting node 1...result...:%d", st);
    if(!st) p1_e2_cleanup(graph);

    st = graph_insertNode(graph,node2);
    printf("\nInserting node 2...result...:%d", st);
    if(!st) p1_e2_cleanup(graph);

    printf("\nInserting edge: node 2 --> node 1");
    graph_insertEdge(graph,id2,id1);

    printf("\nConnected node 1 y node 2? %s", (graph_areConnected(graph,id1,id2)==TRUE?"Yes":"No"));
    printf("\nConnected node 2 y node 1? %s\n", (graph_areConnected(graph,id2,id1)==TRUE?"Yes":"No"));

    st = graph_insertNode(graph,node2);
    fprintf (stdout, "Inserting node 2....result: %d" , st);
    free(node1);
    free(node2);

    //print graph
    fputs("\n Graph", stdout);
    graph_print(stdout, graph);


    /*--------- free-------------------*/
    p1_e2_cleanup(graph);
    return EXIT_SUCCESS;
}

