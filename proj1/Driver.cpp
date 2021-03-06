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

// #include <cstdlib>
#include <iostream>
#include <tuple>
#include "Graph.h"

using namespace std;

/*
 * 
 */
int main(int argc, char **argv)
{

    Graph G1(21);

    G1.addEdge(3, 1, 12);
    G1.addEdge(16, 7, 15);
    G1.addEdge(5, 3, 19);
    G1.addEdge(5, 17, 8);
    G1.addEdge(6, 17, 14);
    G1.addEdge(15, 6, 9);
    G1.addEdge(7, 10, 12);
    G1.addEdge(15, 2, 10);
    G1.addEdge(19, 4, 1);
    G1.addEdge(8, 5, 10);
    G1.addEdge(17, 6, 11);
    G1.addEdge(10, 13, 16);
    G1.addEdge(5, 11, 2);
    G1.addEdge(3, 1, 18);
    G1.addEdge(20, 11, 18);
    G1.addEdge(10, 9, 20);
    G1.addEdge(19, 11, 10);
    G1.addEdge(16, 8, 9);
    G1.addEdge(20, 4, 8);
    G1.addEdge(17, 7, 11);
    G1.addEdge(6, 17, 10);
    G1.addEdge(11, 17, 16);
    G1.addEdge(6, 4, 16);
    G1.addEdge(5, 14, 10);
    G1.addEdge(10, 16, 5);

    Graph *G2 = new Graph(10);
    G2->addEdge(8, 6, 2);
    G2->addEdge(1, 9, 1);
    G2->addEdge(8, 5, 6);
    G2->addEdge(5, 3, 7);
    G2->addEdge(1, 3, 1);
    G2->addEdge(2, 9, 7);
    G2->addEdge(9, 5, 1);
    G2->addEdge(4, 3, 2);
    G2->addEdge(3, 4, 3);
    G2->addEdge(1, 4, 6);
    G2->addEdge(5, 8, 2);
    G2->addEdge(1, 9, 3);
    G2->addEdge(4, 2, 1);
    G2->addEdge(1, 3, 8);
    G2->addEdge(2, 8, 6);
    G2->addEdge(2, 7, 6);
    G2->addEdge(4, 1, 4);
    G2->addEdge(0, 6, 6);
    G2->addEdge(9, 5, 6);
    G2->addEdge(1, 6, 8);
    G2->addEdge(3, 2, 1);
    G2->addEdge(2, 8, 1);
    G2->addEdge(3, 2, 7);
    G2->addEdge(9, 2, 8);
    G2->addEdge(8, 7, 1);

    Graph G3 = *G2;
    Graph G4(G1);

    Graph::NbIterator nit;
    Graph::EgIterator eit;
    tuple<int, int, int> edge;

    // Test to see if G1 works
    cout << "\nG1?" << endl;
    G1.dump();

    // Test to see if G4 is a copy of G1
    cout << "\nG4 ~= G1?" << endl;
    G4.dump();

    // Loop through G1 using edge and neighbor iterators

    cout << "\nThe edges of G1 are: ";

    for (eit = G1.egBegin(); eit != G1.egEnd(); eit++)
    {

        edge = *eit; // get current edge

        // the two data members of a pair are first and second
        cout << "(" << get<0>(edge) << ", "
             << get<1>(edge) << ", "
             << get<2>(edge) << ") ";
    }
    cout << endl;

    for (int i = 0; i < 21; i++)
    {
        cout << "\nThe neighbors of vertex " << i << " in G1 are: ";
        for (nit = G1.nbBegin(i); nit != G1.nbEnd(i); nit++)
        {
            cout << *nit << " ";
        }
    }
    cout << endl;

    // Test to see if G3 is a copy of G2
    cout << "\nG2" << endl;
    G2->dump();

    cout << "\nG3 = G2?" << endl;
    G3.dump();

    // Loop through G2 using edge and neighbor iterators

    cout << "\nThe edges of G2 are: ";

    for (eit = G2->egBegin(); eit != G2->egEnd(); eit++)
    {

        edge = *eit; // get current edge

        // the two data members of a pair are first and second
        cout << "(" << get<0>(edge) << ", "
             << get<1>(edge) << ", "
             << get<2>(edge) << ") ";
    }
    cout << endl;

    for (int i = 0; i < 10; i++)
    {
        cout << "\nThe neighbors of vertex " << i << " in G2 are: ";
        for (nit = G2->nbBegin(i); nit != G2->nbEnd(i); nit++)
        {
            cout << *nit << " ";
        }
    }
    cout << endl;

    delete G2;

    // See if G3 still exists after G2 is deleted
    cout << "\nG3?" << endl;
    G3.dump();

    // Loop through G2 using edge and neighbor iterators

    cout << "\nThe edges of G3 are: ";

    for (eit = G3.egBegin(); eit != G3.egEnd(); eit++)
    {

        edge = *eit; // get current edge

        // the two data members of a pair are first and second
        cout << "(" << get<0>(edge) << ", "
             << get<1>(edge) << ", "
             << get<2>(edge) << ") ";
    }
    cout << endl;

    for (int i = 0; i < 10; i++)
    {
        cout << "\nThe neighbors of vertex " << i << " in G3 are: ";
        for (nit = G3.nbBegin(i); nit != G3.nbEnd(i); nit++)
        {
            cout << *nit << " ";
        }
    }
    cout << endl; // Loop through G2 using edge and neighbor iterators
}