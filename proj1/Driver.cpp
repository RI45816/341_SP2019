/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Driver.cpp
 * Author: Uzoma Uwanamodo
 *
 */

#include <cstdlib>
#include "Graph.h"

using namespace std;

/*
 * 
 */
int main(int argc, char **argv)
{

    Graph G1(50);
    G1.addEdge(18, 12, 3);
    G1.addEdge(37, 42, 13);
    G1.addEdge(49, 13, 41);
    G1.addEdge(48, 47, 2);
    G1.addEdge(3, 45, 35);
    G1.addEdge(44, 33, 20);
    G1.addEdge(1, 24, 16);
    G1.addEdge(4, 2, 27);
    G1.addEdge(42, 43, 31);
    G1.addEdge(33, 25, 4);
    G1.addEdge(29, 34, 45);
    G1.addEdge(19, 23, 5);
    G1.addEdge(11, 21, 15);
    G1.addEdge(19, 33, 20);
    G1.addEdge(44, 38, 48);
    G1.addEdge(48, 27, 43);

    Graph *G2 = new Graph(26);
    G2->addEdge(22, 16, 19);
    G2->addEdge(11, 12, 24);
    G2->addEdge(19, 3, 4);
    G2->addEdge(4, 7, 3);
    G2->addEdge(25, 7, 4);
    G2->addEdge(9, 22, 6);
    G2->addEdge(8, 24, 10);
    G2->addEdge(22, 3, 23);
    G2->addEdge(12, 4, 24);
    G2->addEdge(25, 16, 13);
    G2->addEdge(19, 10, 8);
    G2->addEdge(23, 19, 15);
    G2->addEdge(9, 8, 13);
    G2->addEdge(18, 18, 16);
    G2->addEdge(4, 25, 16);
    G2->addEdge(9, 24, 11);


    Graph G3 = *G2;
    Graph G4(G1);
    G1.dump();
    G4.dump();
    G3.dump();

    delete G2;
}
