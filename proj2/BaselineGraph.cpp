#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include "BaselineGraph.h"
using namespace std;

namespace Baseline {

    //
    // Graph implementations go here
    //

    Graph::Graph(int n) : m_numVert(n), m_numEdge(0), m_ci(), m_nz(), m_re(n + 1, 0) {
        if (n <= 0) {
            throw out_of_range("Must have a positive number of vertices");
        }
    }

    /*
     *  Method: Graph::numVert()
     *   Descr: Getter for m_numVert
     * @return Number of verticies
     */
    int Graph::numVert() {
        return m_numVert;
    }

    /*
     *  Method: Graph::numEdge()
     *   Descr: Getter for m_numEdge
     * @return Number of unique (non-mirrored) edges
     */
    int Graph::numEdge() {
        return m_numEdge;
    }

    /*
     *  Method: Graph::addEdge()
     *   Descr: Add edge (and mirror edge) to Graph
     * @param u Row index
     * @param v Column index
     * @param x Weight of edge
     */
    void Graph::addEdge(int u, int v, int x) {
        // Determine which index is higher
        int max = u, min = v;
        if (u < v)
            min = u, max = v;

        // Determine if vertices are in graph
        if (max >= m_numVert || min < 0)
            throw out_of_range("Vertex index is out of range");

        vector<int>::iterator begin = m_ci.begin();

        // Check to see if the edge is already in the graph
        vector<int>::iterator insert;
        for (insert = begin + m_re[min]; insert != begin + m_re[min + 1] && *insert <= max; insert++) {
            // If edge in graph, change values in nonzero graph for original and transposed coordinates
            if (*insert == max) {
                vector<int>::iterator changeTransposed = find(begin + m_re[max], begin + m_re[max + 1], min);
                m_nz[insert - begin] = x;
                m_nz[changeTransposed - begin] = x;
                return;
            }
        }

        // Edge case for if edge is first in graph, insert first edge into Graph
        if (!m_numEdge++) {
            // Update nonzero and column index vectors with new edge data
            m_nz.push_back(x);
            m_nz.push_back(x);
            m_ci.push_back(max);
            m_ci.push_back(min);
        } else {
            // Insert edge into Graph at specified coordinates
            vector<int>::iterator insertTransposed = find_if(begin + m_re[max], begin + m_re[max + 1], [min](int i) {
                return i > min;
            });
            m_nz.insert(m_nz.begin() + (insertTransposed - begin), x);
            m_ci.insert(insertTransposed, min);
            m_nz.insert(m_nz.begin() + (insert - begin), x);
            m_ci.insert(m_ci.begin() + (insert - begin), max);
            // begin = m_ci.begin();
        }

        // Update row extent array
        for (int j = min; j < m_numVert; j++) {
            m_re[j + 1] += j >= max ? 2 : 1;
        }
    }

    /*
     *  Method: Graph::dump()
     *   Descr: Debug Graph by displaying number of edges, vertices, and contents of three arrays
     */
    void Graph::dump() {

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
     *  Method: Graph::EgIterator::EgIterator()
     *   Descr: 
     */
    Graph::EgIterator::EgIterator(Graph *Gptr, int indx) : m_Gptr(Gptr), m_indx(indx) {
        if (Gptr)
            m_row = m_Gptr->m_re.rend() - 1 - find_if(m_Gptr->m_re.rbegin(), m_Gptr->m_re.rend(), [indx](int i) {
                return i <= indx; });
    }

    /*
     *  Method: Graph::EgIterator::operator!=()
     *   Descr: Override iterator comparison operator
     * @param rhs EgIterator being compared to this EgIterator
     * @return If the EgIterators are the same
     */
    bool Graph::EgIterator::operator!=(const EgIterator &rhs) {
        return m_Gptr != rhs.m_Gptr || m_row != rhs.m_row || m_indx != rhs.m_indx;
    }

    /*
     *  Method: Graph::EgIterator::operator++()
     *   Descr: Override iterator increment operator
     */
    void Graph::EgIterator::operator++(int dummy) {
        // Update m_indx and m_row to point to the next unique edge
        int m_row2 = m_row;
        int m_indx2 = m_indx = find_if(m_Gptr->m_ci.begin() + (++m_indx), m_Gptr->m_ci.end(), [m_row2](int i) {
            return m_row2 < i; }) - m_Gptr->m_ci.begin();
        m_row = m_Gptr->m_re.rend() - 1 - find_if(m_Gptr->m_re.rbegin(), m_Gptr->m_re.rend(), [m_indx2](int i) {
            return i <= m_indx2; });
    }

    /*
     *  Method: Graph::EgIterator::operator*()
     *   Descr: Override iterator dereference operator
     * @return Tuple containing row, column, and weight of edge
     */
    tuple<int, int, int> Graph::EgIterator::operator*() {
        if (m_indx >= m_Gptr->m_numEdge << 1)
            throw out_of_range("EgIterator is at end of Graph");

        return make_tuple(m_row, m_Gptr->m_ci[m_indx], m_Gptr->m_nz[m_indx]);
    }

    /*
     *  Method: Graph::egBegin()
     *   Descr: Create a EgIterator at beginning of graph
     * @return An EgIterator pointing to beginning of Graph
     */
    Graph::EgIterator Graph::egBegin() {
        return EgIterator(this);
    }

    /*
     *  Method: Graph::egEnd()
     *   Descr: Create a EgIterator at end of graph
     * @return An EgIterator pointing to end of Graph
     */
    Graph::EgIterator Graph::egEnd() {
        return EgIterator(this, m_numEdge << 1);
    }

    /*
     *  Method: Graph::NbIterator::NbIterator()
     *   Descr: Loop through all the vertices that share an edge with a specified vertex
     * @param Gptr Graph being iterated
     * @param v Index of vertex
     * @param indx Where in neighborhood to set iterator
     */
    Graph::NbIterator::NbIterator(Graph *Gptr, int v, int indx) : m_Gptr(Gptr), m_indx(indx || !Gptr ? indx : Gptr->m_re[v]), m_row(v) {
        if (Gptr && v >= Gptr->m_numVert)
            throw out_of_range("NbIterator: Vertex is not in Graph");
    }

    /*
     *  Method: Graph::NbIterator::operator!=()
     *   Descr: Override iterator comparison operator
     * @param rhs NbIterator being compared to this operator
     * @return If the NbIterators are the same
     */
    bool Graph::NbIterator::operator!=(const NbIterator &rhs) {
        return m_Gptr != rhs.m_Gptr || m_row != rhs.m_row || m_indx != rhs.m_indx;
    }

    /*
     *  Method: Graph::NbIterator::operator++()
     *   Descr: Override iterator increment operator
     */
    void Graph::NbIterator::operator++(int dummy) {
        if (++m_indx > m_Gptr->m_re[m_row + 1])
            m_indx--;
    }

    /*
     *  Method: Graph::NbIterator::operator*()
     *   Descr: Override iterator dereference operator
     * @return Neighbor of specified vertex
     */
    int Graph::NbIterator::operator*() {
        if (m_indx >= m_Gptr->m_re[m_row + 1])
            throw out_of_range("NbIterator is already at end of row");

        return m_Gptr->m_ci[m_indx];
    }

    /*
     *  Method: Graph::nbBegin()
     *   Descr: Create a NbIterator at beginning of row for specified vertex
     * @param v index of vertex
     * @return NbIterator pointing to beginning of row
     */
    Graph::NbIterator Graph::nbBegin(int v) {
        return NbIterator(this, v);
    }

    /*
     *  Method: Graph::nbEnd()
     *   Descr: Create a NbIterator at end of row for specified vertex
     * @param v index of vertex
     * @return NbIterator pointing to end of row
     */
    Graph::NbIterator Graph::nbEnd(int v) {
        return NbIterator(this, v, m_re[v + 1]);
    }

} // namespace Baseline

/*------------------------------------------------------------------------------*/
