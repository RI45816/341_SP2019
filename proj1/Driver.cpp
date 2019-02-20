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
int main(int argc, char** argv) {

    Graph G1(7);

    G1.addEdge(18, 12, 3);
    G1.dump();

    G1.addEdge(37, 42, 13);
    G1.dump();

    G1.addEdge(49, 13, 41);
    G1.dump();

    G1.addEdge(48, 47, 2);
    G1.dump();

    G1.addEdge(3, 45, 35);
    G1.dump();

    G1.addEdge(44, 33, 20);
    G1.dump();

    G1.addEdge(1, 24, 16);
    G1.dump();

    G1.addEdge(4, 2, 27);
    G1.dump();

    G1.addEdge(42, 43, 31);
    G1.dump();

    G1.addEdge(33, 25, 4);
    G1.dump();

    G1.addEdge(29, 34, 45);
    G1.dump();

    G1.addEdge(19, 23, 5);
    G1.dump();

    G1.addEdge(11, 21, 15);
    G1.dump();

    G1.addEdge(19, 33, 20);
    G1.dump();

    G1.addEdge(44, 38, 48);
    G1.dump();

    G1.addEdge(48, 27, 43);
    G1.dump();


}

