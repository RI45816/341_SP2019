#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include "BaselineGraph.h"
using namespace std;

namespace Baseline
{

//
// Baseline::Graph implementations go here
//

Graph::Graph(int n) : m_numVert(n), m_numEdge(0), m_ci(), m_nz(), m_re(n + 1, 0)
{
    if (n <= 0)
    {
        throw out_of_range("Must have a positive number of vertices");
    }
}

} // namespace Baseline

/*
 *  Method: Baseline::Graph::numVert()
 *   Descr: Getter for m_numVert
 * @return Number of verticies
 */
int Baseline::Graph::numVert()
{
    return m_numVert;
}

/*
 *  Method: Baseline::Graph::numEdge()
 *   Descr: Getter for m_numEdge
 * @return Number of unique (non-mirrored) edges
 */
int Baseline::Graph::numEdge()
{
    return m_numEdge;
}

/*
 *  Method: Baseline::Graph::addEdge()
 *   Descr: Add edge (and mirror edge) to Graph
 * @param u Row index
 * @param v Column index
 * @param x Weight of edge
 */
void Baseline::Graph::addEdge(int u, int v, int x)
{
    // Determine which index is higher
    int max = u, min = v;
    if (u < v)
        min = u, max = v;

    // Determine if vertices are in graph
    if (max >= m_numVert || min < 0)
        throw out_of_range("Vertex index is out of range");

    vector<int>::iterator begin = m_ci.begin();

    // Check to see if the edge is already in the graph
    vector<int>::iterator insert = find_if(begin + m_re[min], begin + m_re[min + 1], [max](int i) {
        return i >= max;
    });
    if (insert != m_ci.end())
    cout << "Insert: " << *insert << "" << endl;

    // Edge case for if edge is first in graph, insert first edge into Graph
    if (!m_numEdge++)
    {
        m_nz.push_back(x);
        m_nz.push_back(x);
        m_ci.push_back(max);
        m_ci.push_back(min);

        // Update nonzero and column index vectors with new edge data
    }
    else
    {
        // If edge in graph, change values in nonzero graph for original and transposed coordinates
        if (insert != m_ci.end() && *insert == max)
        {
            vector<int>::iterator changeTransposed = find_if(begin + m_re[max], begin + m_re[max + 1], [min](int i){return i==min;});
            cout << "Insert - Begin: "<< insert-begin << "" << endl;
            cout << "changeTransposed: "<< *changeTransposed << "" << endl;
            m_nz[insert - begin] = x;
            m_nz[changeTransposed - begin] = x;
            return;
        }

        vector<int>::iterator beginNonZero = m_nz.begin();
        m_nz.insert(beginNonZero + (insert - begin), x);
        m_ci.insert(insert, max);
        vector<int>::iterator insertTransposed = find_if(begin + m_re[max], begin + m_re[max + 1], [min](int i) {
            return i > min;
        });
        m_nz.insert(beginNonZero + (insertTransposed - begin), x);
        m_ci.insert(insertTransposed, min);
    }

    // Update row extent array
    for (int j = min; j < m_numVert; j++)
    {
        m_re[j + 1] += j >= max ? 2 : 1;
    }
}

/*
 *  Method: Baseline::Graph::dump()
 *   Descr: Debug Graph by displaying number of edges, vertices, and contents of three arrays
 */
void Baseline::Graph::dump()
{

    cout << "Dump of graph (numVert = " << m_numVert << ", numEdge = " << m_numEdge << ")\n"
              << endl;

    // Print out row extent array
    cout << "m_re: ";
    for (vector<int>::iterator it = m_re.begin(); it != m_re.end(); it++)
        cout << *it << " ";
    cout << endl;

    // Print out nonzero array
    cout << "m_nz: ";
    for (vector<int>::iterator it = m_nz.begin(); it != m_nz.end(); it++)
        cout << *it << " ";
    cout << endl;

    // Print out column index array
    cout << "m_ci: ";
    for (vector<int>::iterator it = m_ci.begin(); it != m_ci.end(); it++)
        cout << *it << " ";
    cout << endl;
}

/*
 *  Method: Baseline::Graph::EgIterator::EgIterator()
 *   Descr: 
 */
Baseline::Graph::EgIterator::EgIterator(Graph *Gptr, int indx)
{
}

/*
 *  Method: Baseline::Graph::EgIterator::operator!=()
 *   Descr: 
 */
bool Baseline::Graph::EgIterator::operator!=(const EgIterator &rhs)
{
    bool dummy;

    return dummy;
}

/*
 *  Method: Baseline::Graph::EgIterator::operator++()
 *   Descr: 
 */
void Baseline::Graph::EgIterator::operator++(int dummy)
{
}

/*
 *  Method: Baseline::Graph::EgIterator::operator*()
 *   Descr: 
 */
tuple<int, int, int> Baseline::Graph::EgIterator::operator*()
{
    tuple<int, int, int> dummy;

    return dummy;
}

/*
 *  Method: Baseline::Graph::egBegin()
 *   Descr: 
 */
Baseline::Graph::EgIterator Baseline::Graph::egBegin()
{
    return EgIterator();
}

/*
 *  Method: Baseline::Graph::egEnd()
 *   Descr: 
 */
Baseline::Graph::EgIterator Baseline::Graph::egEnd()
{
    return EgIterator();
}

/*
 *  Method: Baseline::Graph::NbIterator::NbIterator()
 *   Descr: 
 */
Baseline::Graph::NbIterator::NbIterator(Graph *Gptr, int v, int indx)
{
}

/*
 *  Method: Baseline::Graph::NbIterator::operator!=()
 *   Descr: 
 */
bool Baseline::Graph::NbIterator::operator!=(const NbIterator &rhs)
{
    bool dummy;

    return dummy;
}

/*
 *  Method: Baseline::Graph::NbIterator::operator++()
 *   Descr: 
 */
void Baseline::Graph::NbIterator::operator++(int dummy)
{
}

/*
 *  Method: Baseline::Graph::NbIterator::operator*()
 *   Descr: 
 */
int Baseline::Graph::NbIterator::operator*()
{
    int dummy;

    return dummy;
}

/*
 *  Method: Baseline::Graph::nbBegin()
 *   Descr: 
 */
Baseline::Graph::NbIterator Baseline::Graph::nbBegin(int v)
{
    return NbIterator();
}

/*
 *  Method: Baseline::Graph::nbEnd()
 *   Descr: 
 */
Baseline::Graph::NbIterator Baseline::Graph::nbEnd(int v)
{
    return NbIterator();
}

/*------------------------------------------------------------------------------*/
