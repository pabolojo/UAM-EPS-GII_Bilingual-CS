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

int mainCleanUp (int ret_value, Graph *gc, FILE *pf){

    graph_destroy(gc);
    fclose (pf);
    exit (ret_value);
}

int main (int argc, char **argv) {
    //variable declaration
    FILE *f=NULL;
    Graph *g;
    Status st;
    int pr;

    if(argc!=2) return EXIT_FAILURE;

    f=fopen(argv[1],"r");

    if(!f) return EXIT_FAILURE;


    g = graph_ini();
    if(!g) mainCleanUp(1,g,f);

    // read file
    st = graph_readFromFile(f,g);
    if(st==ERROR) mainCleanUp(2,g,f);
    
    // print graph
    pr = graph_print (stdout, g);
    if(pr==-1) mainCleanUp(EXIT_FAILURE,g,f);

    // free resources
    mainCleanUp(0,g,f);
    return EXIT_SUCCESS;
}

