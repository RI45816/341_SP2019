// GraphTest1.cpp
//
// CMSC 341 - Spring 2019
//
// GraphTest1.cpp should fail the following tests:
//   testCSRExact(): 102, 103
//   testNbIterator(): 301
//   testExceptions(): 511, 531, 551

#include <iostream>
#include "Graph.h"

Graph::Graph(int n) {
  if (n < 0)
    throw std::out_of_range("number of vertices must be positive");

  m_nz = new int[n];
  m_re = new int[n+1];  
  m_ci = new int[n];

  m_cap = n;
  
  // Initialize m_re to all zeros
  for (int i = 0; i <= n; i++) m_re[i] = 0;
  
  m_numVert = n;
  m_numEdge = 0;
}

Graph::Graph(const Graph& G) {

  m_numVert = G.m_numVert;
  m_numEdge = G.m_numEdge;
  m_cap = G.m_cap;

  m_nz = new int[m_cap];
  m_re = new int[m_numVert + 1];
  m_ci = new int[m_cap];
  
  for (int i = 0; i < m_numEdge; i++) {
    m_nz[i] = G.m_nz[i];
    m_ci[i] = G.m_ci[i];
  }

  for (int i = 0; i <= m_numVert; i++) {
    m_re[i] = G.m_re[i];
  }
}


Graph::~Graph() {

  delete [] m_nz;
  m_nz = nullptr;

  delete [] m_re;
  m_re = nullptr;

  delete [] m_ci;
  m_ci = nullptr;

  m_numVert = 0;
  m_numEdge = 0;
}

const Graph& Graph::operator=(const Graph& rhs) {

  if (this != &rhs) {

    m_numVert = rhs.m_numVert;
    m_numEdge = rhs.m_numEdge;
    m_cap = rhs.m_cap;
    
    int *tmp_nz = new int[m_cap];
    int *tmp_re = new int[m_numVert + 1];
    int *tmp_ci = new int[m_cap];
  
    for (int i = 0; i < m_numEdge; i++) {
      tmp_nz[i] = rhs.m_nz[i];
      tmp_ci[i] = rhs.m_ci[i];
    }

    for (int i = 0; i <= m_numVert; i++) {
      tmp_re[i] = rhs.m_re[i];
    }

    delete [] m_nz;
    m_nz = tmp_nz;

    delete[] m_re;
    m_re = tmp_re;

    delete [] m_ci;
    m_ci = tmp_ci;
  }
  
  return(*this);
}

int Graph::numVert() {
  return m_numVert;
}

int Graph::numEdge() {
  return m_numEdge;
}

void Graph::addEdge(int u, int v, int x) {
  if (u < 0 || u >= m_numVert)
    throw std::out_of_range("vertex u out-of-range");

  // Row u is in m_nz from index a to index b-1
  int a = m_re[u];
  int b = m_re[u+1];

  // Does edge already exist?
  int indx = a;
  while (indx < b && m_ci[indx] != v) indx++;
  if (indx < b) {
    std::cerr << "Warning: addEdge(): edge (" << u << ","
	      << v << ") already exists" << std::endl;
    return;
  }

  // Do we need to resize?  Need space for TWO new edges
  // since the graph is undirected
  if (m_cap - m_numEdge < 2) {

    int newCap = 2*m_cap;

    int *tmp_nz = new int[newCap];
    int *tmp_ci = new int[newCap];

    for (int i = 0; i < m_cap; i++) {
      tmp_nz[i] = m_nz[i];
      tmp_ci[i] = m_ci[i];
    }

    delete [] m_nz;
    m_nz = tmp_nz;

    delete [] m_ci;
    m_ci = tmp_ci;

    m_cap = newCap;
  }
    
  // Find location to insert new edge
  indx = a;

  // Shift entries of m_nz and m_ci up
  for (int j = m_numEdge; j > indx; j--) {
    m_nz[j] = m_nz[j-1];
    m_ci[j] = m_ci[j-1];
  }
  
  // Increment row extent for all rows after u
  // Note: m_re[m_numVert] is total number of edges in G
  for (int j = u+1; j <= m_numVert; j++)
    m_re[j]++;
  
  // Write new edge data and increment edge count
  m_nz[indx] = x;
  m_ci[indx] = v;
  m_numEdge++;  

  //
  // Now insert (v, u, x)...
  //

  if (v < 0) {
    throw std::out_of_range("vertex v out-of-range");
  }
  
  // Row v is in m_nz from index a to index b-1
  a = m_re[v];
  b = m_re[v+1];

  // Find location to insert new edge
  indx = a;
  while (indx < b && m_ci[indx] <= u) indx++;

  // Shift entries of m_nz and m_ci up
  for (int j = m_numEdge; j > indx; j--) {
    m_nz[j] = m_nz[j-1];
    m_ci[j] = m_ci[j-1];
  }

  // Increment row extent for all rows after v
  // Note: m_re[m_numVert] is total number of edges in G
  for (int j = v+1; j <= m_numVert; j++)
    m_re[j]++;
  
  // Write new edge data and increment edge count
  m_nz[indx] = x;
  m_ci[indx] = u;
  m_numEdge++;
}

void Graph::dump() {

  std::cout << "Dump of graph (numVert = "
	    << m_numVert << ", numEdge = "
	    << m_numEdge << ", m_cap = "
	    << m_cap << ")" << std::endl;
  
  std::cout << "m_re: ";
  for (int i = 0; i < m_numVert; i++)
    std::cout << m_re[i] << " ";
  std::cout << std::endl;

  std::cout << "m_nz: ";
  for (int i = 0; i < m_numEdge; i++)
    std::cout << m_nz[i] << " ";
  std::cout << std::endl;

  std::cout << "m_ci: ";
  for (int i = 0; i < m_numEdge; i++)
    std::cout << m_ci[i] << " ";
  std::cout << std::endl;
}


Graph::EgIterator::EgIterator(Graph *Gptr, int indx) {

  m_Gptr = Gptr;
  m_indx = 0;
  m_row = 0;

  if ( m_Gptr != nullptr ) {

    if (indx < 0 || indx > m_Gptr->m_numEdge)
      throw std::out_of_range("EgIterator(): indx out-of-range");
    
    m_indx = indx;

    // Find the row corresponding to indx
    if (m_Gptr->m_numEdge > 0) 
      for (m_row = 0; m_row < m_Gptr->m_numVert; m_row++)
	if ( (m_Gptr->m_re[m_row] <= m_indx) &&
	     (m_indx < m_Gptr->m_re[m_row + 1]) )
	  break;
  }
}
  
std::tuple<int,int,int> Graph::EgIterator::operator*() {
  int numNz = m_Gptr->m_re[m_Gptr->m_numVert];
  if (m_indx < 0 || m_indx >= numNz) {
    throw std::out_of_range("dereference of invalid edge iterator");
  }
  int col = m_Gptr->m_ci[m_indx];
  int val = m_Gptr->m_nz[m_indx];
  return std::tuple<int,int,int>(m_row, col, val);
}

bool Graph::EgIterator::operator!=(const EgIterator& rhs) {
  return m_indx != rhs.m_indx;
}

void Graph::EgIterator::operator++(int dummy) {

  // Already at end; just return
  if ( m_indx == m_Gptr->m_numEdge ) return;

  int numEdge = m_Gptr->m_numEdge;
  
  do {
    m_indx++;
    while ( (m_indx < numEdge) && (m_indx >= m_Gptr->m_re[m_row + 1]) )
      m_row++;
  } while ( (m_indx < numEdge) && (m_row > m_Gptr->m_ci[m_indx]) );
}

Graph::EgIterator Graph::egBegin() {
  return EgIterator(this, 0);
}
 
Graph::EgIterator Graph::egEnd() {
  return EgIterator(this, m_numEdge);
}
 
Graph::NbIterator::NbIterator(Graph *Gptr, int v, int indx) {

  m_Gptr = Gptr;

  if ( m_Gptr != nullptr ) {

    if (indx < 0 || indx > m_Gptr->m_numEdge)
      throw std::out_of_range("NbIterator(): indx out-of-range");

    if (v < 0 || v >= m_Gptr->m_numVert)
      throw std::out_of_range("NbIterator(): v out-of-range");

    if ( (indx < m_Gptr->m_re[v]) || (indx > m_Gptr->m_re[v+1]) )
      throw("NbIterator(): incompatible v and indx");

    m_indx = indx;
    m_row = v;
  }
}

bool Graph::NbIterator::operator!=(const NbIterator& rhs) {
  return m_indx != rhs.m_indx;
}

void Graph::NbIterator::operator++(int dummy) {
  m_indx++;
}

int Graph::NbIterator::operator*() {
  int start = m_Gptr->m_re[m_row];
  int end = m_Gptr->m_re[m_row+1];
  if (m_indx < start || m_indx >= end) {
    throw std::out_of_range("dereference of invalid neighbor iterator");
  }
  
  return m_Gptr->m_ci[m_indx];
}

Graph::NbIterator Graph::nbBegin(int v) {
  if (v < 0 || v >= m_numEdge)
    throw std::out_of_range("nbBegin(): invalid vertex");

  int indx = m_re[v];

  return NbIterator(this, v, indx);
}

Graph::NbIterator Graph::nbEnd(int v) {
  if (v < 0 || v >= m_numEdge)
    throw std::out_of_range("nbEnd(): invalid vertex");

  int indx = m_re[v];

  return NbIterator(this, v, indx);
}
