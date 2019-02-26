/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Graph.cpp
 * Author: Uzoma Uwanamodo
 * 
 */
using namespace std;
#include "Graph.h"
#include <iostream>
//#include <stdexcept>
//#include <tuple>

/*
 *  Method: Graph::Graph()
 *   Descr: Create a new Graph with n vertices
 */
Graph::Graph(int n) : m_numVert(n),
                      m_cap(n),
                      m_numEdge(0),
                      m_nz(new int[n]),
                      m_re(new int[n + 1]),
                      m_ci(new int[n])
{
    if (n <= 0)
    {
        throw std::out_of_range("Must have a positive number of vertices");
    }
    for (int i = 0; i < n; i++)
    {
        m_nz[i] = 0;
        m_re[i] = 0;
        m_ci[i] = 0;
    }
    m_re[n] = 0;
}

/*
 *  Method: Graph::Graph()
 *   Descr: Copy constructor for Graph, create deep copy
 */
Graph::Graph(const Graph &G) : m_cap(G.m_cap),
                               m_numEdge(G.m_numEdge),
                               m_numVert(G.m_numVert),
                               m_nz(new int[G.m_cap]),
                               m_re(new int[G.m_numVert + 1]),
                               m_ci(new int[G.m_cap])
{

    for (int i = 0; i < m_cap; i++)
    {
        if (i < m_numVert + 1)
            m_re[i] = G.m_re[i];
        m_ci[i] = G.m_ci[i];
        m_nz[i] = G.m_nz[i];
    }
}

/*
 *  Method: Graph::~Graph()
 *   Descr: Destructor for Graph, deallocate memory
 */
Graph::~Graph()
{
    delete[] m_nz;
    delete[] m_ci;
    delete[] m_re;
}

/*
 *  Method: Graph::operator=()
 *   Descr: Assignment operator for Graph set one equal to the other
 */
const Graph &Graph::operator=(const Graph &rhs)
{
    if (this == &rhs)
        return *this;

    delete[] m_ci;
    delete[] m_re;
    delete[] m_nz;
    m_numEdge = rhs.m_numEdge;
    m_numVert = rhs.m_numVert;
    m_cap = rhs.m_cap;
    m_ci = new int[m_cap];
    m_re = new int[m_numVert + 1];
    m_nz = new int[m_cap];
    for (int i = 0; i < m_cap; i++)
    {
        if (i < m_numVert + 1)
            m_re[i] = rhs.m_re[i];
        m_ci[i] = rhs.m_ci[i];
        m_nz[i] = rhs.m_nz[i];
    }
    return *this;
}

/*
 *  Method: Graph::numVert()
 *   Descr: Getter for m_numVert
 */
int Graph::numVert()
{
    return m_numVert; // return the number of vertices in graph
}

/*
 *  Method: Graph::numEdge()
 *   Descr: Getter for m_numEdge
 */
int Graph::numEdge()
{
    return m_numEdge; // return number of edges in graph
}

/*
 *  Method: Graph::addEdge()
 *   Descr: Add an edge between vertices u and v with weight x
 */
void Graph::addEdge(int u, int v, int x)
{
    // Determine which index is higher
    int max = u, min = v;
    if (u < v)
        min = u, max = v;

    // Determine if vertices are in graph
    if (max >= m_numVert || min < 0)
        throw out_of_range("Vertex index is out of range");

    int i = m_re[min];
    // Loop through to see if the edge is already in the graph
    for (; i < m_numEdge * 2 && i < m_re[min + 1] && m_ci[i] <= max; i++)

        // If the edge is already in the graph change the weight and do the same for the transposed coordinates
        if (m_ci[i] == max)
        {
            m_nz[i] = x;
            for (int j = m_re[max]; j < m_re[max + 1]; j++)
            {
                if (m_ci[j] == min)
                {
                    m_nz[j] = x;
                    return;
                }
            }
        }

    // Expand column index and nonzero arrays if necessary
    if (m_numEdge + 1 << 1 > m_cap)
    {
        m_cap <<= 1;
        int *new_nz = new int[m_cap], *new_ci = new int[m_cap];
        for (int k = 0; k < m_numEdge << 1; k++)
        {
            new_nz[k] = m_nz[k];
            new_ci[k] = m_ci[k];
        }
        delete[] m_nz;
        delete[] m_ci;
        m_nz = new_nz;
        m_ci = new_ci;
    }
    m_numEdge++; // Increment the total number of edges

    // First element in Graph, special case
    if (m_numEdge == 1)
    {
        m_nz[0] = m_nz[1] = x;
        m_ci[0] = max;
        m_ci[1] = min;
        //        return;
    }
    else
    {
        // Update the column index and non-zero arrays
        //    i--;
        bool max_added = false; // Prevent adding value multiple times
        for (int j = m_numEdge * 2 - 1, slider = 2; j > i; j--)
        {
            if (!max_added && ((j - 1 > m_re[max] && j - 1 <= m_re[max + 1] && m_ci[j - slider] < min) || j - 1 == m_re[max]))
            {
                m_ci[j] = min;
                m_nz[j] = x;
                max_added = !0;
                slider--;
                continue;
            }
            m_ci[j] = m_ci[j - slider];
            m_nz[j] = m_nz[j - slider];
        }
        m_ci[i] = max;
        m_nz[i] = x;
    }

    // Update the row extent array
    for (int j = min; j < m_numVert; j++)
    {
        m_re[j + 1] += j >= max ? 2 : 1;
    }
}

/*
 *  Method: Graph::dump()
 *   Descr: Debug Graph by displaying number of edges, vertices, and contents of three arrays
 */
void Graph::dump()
{

    cout << "Dump of graph (numVert = " << m_numVert << ", numEdge = " << m_numEdge << ", m_cap = " << m_cap << ")\n"
         << endl;

    // Print out row extent array
    cout << "m_re: ";
    for (int i = 0; i < m_numVert + 1; i++)
        cout << m_re[i] << " ";
    cout << endl;

    // Print out nonzero array
    cout << "m_nz: ";
    for (int i = 0; i < m_numEdge << 1; i++)
        cout << m_nz[i] << " ";
    cout << endl;

    // Print out column index array
    cout << "m_ci: ";
    for (int i = 0; i < m_numEdge << 1; i++)
        cout << m_ci[i] << " ";
    cout << endl;
}

/*
 *  Method: Graph::EgIterator::EgIterator()
 *   Descr: Create an iterator that shows all the edges
 */
Graph::EgIterator::EgIterator(Graph *Gptr, int indx) : m_Gptr(Gptr), m_indx(indx)
{
    if (Gptr)
    {

        for (m_row = 0; m_row < Gptr->m_numVert && (indx >= Gptr->m_re[m_row + 1] || (indx == Gptr->m_re[m_row] && indx == Gptr->m_re[m_row + 1])); m_row++)
            ;
    }
}

/*
 *  Method: Graph::EgIterator::operator!=()
 *   Descr: Override iterator comparison operator
 */
bool Graph::EgIterator::operator!=(const EgIterator &rhs)
{

    return m_Gptr != rhs.m_Gptr || m_row != rhs.m_row || m_indx != rhs.m_indx;
}

/*
 *  Method: Graph::EgIterator::operator++()
 *   Descr: Override iterator increment operator
 */
void Graph::EgIterator::operator++(int dummy)
{

    for (m_indx++; m_indx < m_Gptr->m_numEdge << 1 && m_row >= m_Gptr->m_ci[m_indx]; m_indx++)
        ;
    for (; m_row < m_Gptr->m_numVert && (m_indx >= m_Gptr->m_re[m_row + 1] || (m_indx == m_Gptr->m_re[m_row] && m_indx == m_Gptr->m_re[m_row + 1])); m_row++)
        ;
}

/*
 *  Method: Graph::EgIterator::operator*()
 *   Descr: Override iterator dereference operator
 */
std::tuple<int, int, int> Graph::EgIterator::operator*()
{
    //    printf("[%i]:<%i, %i, %i>",m_indx,m_row,m_Gptr->m_ci[m_indx],m_Gptr->m_nz[m_indx]);
    if (m_indx >= m_Gptr->m_numEdge << 1)
        throw out_of_range("EgIterator is at end of Graph");

    return make_tuple(m_row, m_Gptr->m_ci[m_indx], m_Gptr->m_nz[m_indx]);
}

/*
 *  Method: Graph::egBegin()
 *   Descr: Create a EgIterator at beginning of graph
 */
Graph::EgIterator Graph::egBegin()
{
    return EgIterator(this);
}

/*
 *  Method: Graph::egEnd()
 *   Descr: Create a EgIterator at end of graph
 */
Graph::EgIterator Graph::egEnd()
{
    return EgIterator(this, m_numEdge * 2);
}

/*
 *  Method: Graph::NbIterator::NbIterator()
 *   Descr: Loop through all the vertices that share an edge with a specified vertex
 */
Graph::NbIterator::NbIterator(Graph *Gptr, int v, int indx) : m_Gptr(Gptr), m_indx(indx || !Gptr ? indx : Gptr->m_re[v]), m_row(v)
{
    if (Gptr && v >= Gptr->m_numVert)
    {
        throw out_of_range("NbIterator: Vertex is not in Graph");
    }
}

/*
 *  Method: Graph::NbIterator::operator!=()
 *   Descr: Override iterator comparison operator
 */
bool Graph::NbIterator::operator!=(const NbIterator &rhs)
{

    return m_Gptr != rhs.m_Gptr || m_row != rhs.m_row || m_indx != rhs.m_indx;
}

/*
 *  Method: Graph::NbIterator::operator++()
 *   Descr: Override iterator increment operator
 */
void Graph::NbIterator::operator++(int dummy)
{

    if (++m_indx > m_Gptr->m_re[m_row + 1])
        m_indx--;
}

/*
 *  Method: Graph::NbIterator::operator*()
 *   Descr: Override iterator dereference operator
 */
int Graph::NbIterator::operator*()
{
    if (m_indx >= m_Gptr->m_re[m_row + 1])
        throw out_of_range("NbIterator is already at end of row");

    return m_Gptr->m_ci[m_indx];
}

/*
 *  Method: Graph::nbBegin()
 *   Descr: Create a NbIterator at beginning of row for specified vertex
 */
Graph::NbIterator Graph::nbBegin(int v)
{

    return NbIterator(this, v);
}

/*
 *  Method: Graph::nbEnd()
 *   Descr: Create a NbIterator at end of row for specified vertex
 */
Graph::NbIterator Graph::nbEnd(int v)
{
    return NbIterator(this, v, m_re[v + 1]);
}

/*------------------------------------------------------------------------------*/
