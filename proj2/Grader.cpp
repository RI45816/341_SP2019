// File: Grader.cpp
//
// CMSC 341 Spring 2019
//
// Method stubs for Grader class
//

#include "Grader.h"
#include "BaselineGraph.h"
#include "Graph.h"
#include "Graph.h"
#include <string>
#include <set>
#include <algorithm>

/*
 *  Method: Grader::Grader()
 *   Descr: Constructor for Grader object
 * @param name Optional descriptive name
 */
Grader::Grader(string name) : m_name(name) {
}

/*
 *  Method: Grader::testCSRExact()
 *   Descr: Tests m_re, m_nz, m_ci to see if all the right values, in the right order, are present
 * @param numVert number of vertices of the Graph
 * @param edgeSeq vector of edges to insert into the Graph
 * @return Whether the program passed or failed the test
 */
bool Grader::testCSRExact(int numVert, vector<Edge> edgeSeq) {
    Graph submitted_graph(numVert); // Graph being tested
    Baseline::Graph baseline_graph(numVert); // Baseline graph by which the submitted graph will be judged
    bool error101, error102, error103 = error102 = error101 = false; // Whether or not errors have been encountered // Keep track of errors already put into m_error

    // Add all the edges and check to see if there are errors
    for (Edge e : edgeSeq) {
        submitted_graph.addEdge(get<0>(e), get<1>(e), get<2>(e));
        baseline_graph.addEdge(get<0>(e), get<1>(e), get<2>(e));

        // Turn m_re into a vector and compare it with the proctor
        if (!error101 && vector<int>(submitted_graph.m_re, submitted_graph.m_re + submitted_graph.numVert() + 1) != baseline_graph.m_re) {
            error101 = true;
            m_errors.push(Error(5, 101, "Incorrect values in m_re"));
        }

        if (!error102 && vector<int>(submitted_graph.m_nz, submitted_graph.m_nz + submitted_graph.numEdge() * 2) != baseline_graph.m_nz) {
            m_errors.push(Error(5, 102, "Incorrect values in m_nz"));
            error102 = true;
        }
        if (!error103 && vector<int>(submitted_graph.m_ci, submitted_graph.m_ci + submitted_graph.numEdge() * 2) != baseline_graph.m_ci) {
            m_errors.push(Error(5, 103, "Incorrect values in m_ci"));
            error103 = true;
        }
        if (error101 + error102 + error103 == 3)
            return false;
    }
    if (!(error101 + error102 + error103)) {
        m_errors.push(Error(0, 100, "No errors in testCSRExact()"));
        return true;
    } else {
        return false;
    }
}

/*
 *  Method: Grader::testCSRUnordered()
 *   Descr: Tests m_re, m_nz, m_ci to see if all the right values, correct order notwithstanding, are present
 * @param numVert number of vertices of the Graph
 * @param edgeSeq vector of edges to insert into the Graph
 * @return Whether the program passed or failed the test
 */
bool Grader::testCSRUnordered(int numVert, vector<Edge> edgeSeq) {
    Graph submitted_graph(numVert); // Graph being tested
    Baseline::Graph baseline_graph(numVert); // Baseline graph by which the submitted graph will be judged

    // Add all the edges to the graph to see if all the edges are inserted
    for (Edge e : edgeSeq) {
        submitted_graph.addEdge(get<0>(e), get<1>(e), get<2>(e));
        baseline_graph.addEdge(get<0>(e), get<1>(e), get<2>(e));
    }

    // Check to see if m_re is correct
    if (vector<int>(submitted_graph.m_re, submitted_graph.m_re + submitted_graph.numVert() + 1) != baseline_graph.m_re) {
        m_errors.push(Error(10, 201, "Incorrect m_re; cannot perform unordered test"));
        return false;
    } else {
        for (int i = 0, min = submitted_graph.m_re[i], max = submitted_graph.m_re[i + 1]; i < numVert; i++, min = submitted_graph.m_re[i], max = submitted_graph.m_re[i + 1]) {

            // Compare the m_ci and m_nz of the submitted graph with that of the baseline graph to see if the
            // same values, regardless of order
            set<int> submitted_graph_nz(submitted_graph.m_nz + min, submitted_graph.m_nz + max),
                    submitted_graph_ci(submitted_graph.m_ci + min, submitted_graph.m_ci + max),
                    baseline_graph_nz(baseline_graph.m_nz.begin() + min, baseline_graph.m_nz.begin() + max),
                    baseline_graph_ci(baseline_graph.m_ci.begin() + min, baseline_graph.m_ci.begin() + max);
            if (submitted_graph_nz != baseline_graph_nz || submitted_graph_ci != baseline_graph_ci) {
                m_errors.push(Error(10, 202, "Failure of undordered test of CSR"));
                return false;
            }
        }
    }
    m_errors.push(Error(0, 200, "No errors in testCSRUnordered()"));
    return true;
}

/*
 *  Method: Grader::testNbIterator()
 *   Descr: Test NbIterator to make sure the neighbors are correct every time
 * @param numVert number of vertices of the Graph
 * @param edgeSeq vector of edges to insert into the Graph
 * @return Whether the program passed or failed the test
 */
bool Grader::testNbIterator(int numVert, vector<Edge> edgeSeq) {
    Graph submitted_graph(numVert); // Graph being tested
    Baseline::Graph baseline_graph(numVert); // Baseline graph by which the submitted graph will be judged

    // Populate graph
    for (Edge e : edgeSeq) {
        submitted_graph.addEdge(get<0>(e), get<1>(e), get<2>(e));
        baseline_graph.addEdge(get<0>(e), get<1>(e), get<2>(e));
    }

    bool error301, error302 = error301 = false; // Keep track of errors already put into m_error
    for (int i = 0; i < numVert; i++) {

        // Create sets to compare the NbIterators of the submitted and baseline graphs
        set<int> submitted_graph_NbIterator, baseline_graph_NbIterator, difference;

        for (Graph::NbIterator it = submitted_graph.nbBegin(i); it != submitted_graph.nbEnd(i); it++)
            submitted_graph_NbIterator.insert(*it);

        for (Baseline::Graph::NbIterator it2 = baseline_graph.nbBegin(i); it2 != baseline_graph.nbEnd(i); it2++)
            baseline_graph_NbIterator.insert(*it2);

        // Compare NbIterator sizes
        if (baseline_graph_NbIterator.size() != submitted_graph_NbIterator.size()) {
            m_errors.push(Error(5, 301, "Incorrect neighbor set size"));
            return false;
        }

        // Compare NbIterator values
        insert_iterator<set<int>> it3 = set_difference(submitted_graph_NbIterator.begin(), submitted_graph_NbIterator.end(), baseline_graph_NbIterator.begin(), baseline_graph_NbIterator.end(), inserter(difference, difference.end()));
        //        set<int>::iterator it3 = set_difference(submitted_graph_NbIterator.begin(), submitted_graph_NbIterator.end(), baseline_graph_NbIterator.begin(), baseline_graph_NbIterator.end(), iterator<set<int>> difference.begin());
        if (difference.size()) {
            m_errors.push(Error(5, 302, "Incorrect values from neighbor iterator"));
            return false;
        }
    }
    m_errors.push(Error(0, 300, "No errors in testNbIterator()"));
    return true;
}

/*
 *  Method: Grader::testEgIterator()
 *   Descr: Check the edge iterator to see if it produces the correct set of edges (non-repeating)
 * @param numVert number of vertices of the Graph
 * @param edgeSeq vector of edges to insert into the Graph
 * @return Whether the program passed or failed the test
 */
bool Grader::testEgIterator(int numVert, vector<Edge> edgeSeq) {
    Graph submitted_graph(numVert); // Graph being tested
    Baseline::Graph baseline_graph(numVert); // Baseline graph by which the submitted graph will be judged

    // Populate Graph
    for (Edge e : edgeSeq) {
        submitted_graph.addEdge(get<0>(e), get<1>(e), get<2>(e));
        baseline_graph.addEdge(get<0>(e), get<1>(e), get<2>(e));
    }

    bool error401, error402 = error401 = false; // Keep track of errors already put into m_error

    // Create sets to compare the NbIterators of the submitted and baseline graphs
    set<Edge> submitted_graph_EgIterator, baseline_graph_EgIterator, difference;

    for (Graph::EgIterator it = submitted_graph.egBegin(); it != submitted_graph.egEnd(); it++)
        submitted_graph_EgIterator.insert(*it);

    for (Baseline::Graph::EgIterator it2 = baseline_graph.egBegin(); it2 != baseline_graph.egEnd(); it2++)
        baseline_graph_EgIterator.insert(*it2);

    // Compare EgIterator sizes
    if (baseline_graph_EgIterator.size() != submitted_graph_EgIterator.size()) {
        m_errors.push(Error(5, 401, "Incorrect edge set size"));
        return false;
    }

    // Compare EgIterator values
    insert_iterator<set < Edge>> it3 = set_difference(submitted_graph_EgIterator.begin(), submitted_graph_EgIterator.end(), baseline_graph_EgIterator.begin(), baseline_graph_EgIterator.end(), inserter(difference, difference.end()));
    //        set<Edge>::iterator it3 = set_difference(submitted_graph_EgIterator.begin(), submitted_graph_EgIterator.end(), baseline_graph_EgIterator.begin(), baseline_graph_EgIterator.end(), iterator<set<int>> difference.begin());
    if (difference.size()) {
        m_errors.push(Error(5, 402, "Incorrect values from edge iterator"));
        return false;
    }
    m_errors.push(Error(0, 400, "No errors in testEgIterator()"));
    return true;
}

/*
 *  Method: Grader::testExceptions()
 *   Descr: Test to make sure out_of_range exceptions are thrown
 * @param numVert number of vertices of the Graph
 * @param edgeSeq vector of edges to insert into the Graph
 * @return Whether the program passed or failed the test
 */
bool Grader::testExceptions(int numVert, vector<Edge> edgeSeq) {
    bool passOrFail = true, exceptionCaught = false; // Keep track of if any of the tests failed

    // Test n = 0 exception
    try {
        Graph submitted_graph(0); // Graph being tested
    } catch (const out_of_range &e) { // Graph correctly throws out of range
        exceptionCaught = true;
        m_errors.push(Error(0, 510, "No errors in testExceptions(), construtor with n = 0"));
    } catch (const exception &e) { // Graph throws error, but not out of range
        exceptionCaught = true;
        m_errors.push(Error(2, 512, "Constructor with n = 0 threw incorrect exception"));
        passOrFail = false;

    }
    if (!exceptionCaught) { // Graph does not throw error
        m_errors.push(Error(5, 511, "Constructor with n = 0 did not throw an exception"));
        passOrFail = false;
    }

    // Test n < 0 exception
    exceptionCaught = false;
    try {
        Graph submitted_graph(-1); // Graph being tested
    } catch (const out_of_range &e) { // Graph correctly throws out of range
        exceptionCaught = true;
        m_errors.push(Error(0, 520, "No errors in testExceptions(), construtor with n < 0"));
    } catch (const exception &e) { // Graph throws error, but not out of range
        exceptionCaught = true;
        m_errors.push(Error(2, 522, "Constructor with n < 0 threw incorrect exception"));
        passOrFail = false;
    }
    if (!exceptionCaught) { // Graph does not throw error
        m_errors.push(Error(5, 521, "Constructor with n < 0 did not throw an exception"));
        passOrFail = false;
    }

    Graph submitted_graph(7); // Graph being tested


    // Test bad destination vertex exception
    bool error530, error532 = error530 = false;
    exceptionCaught = false;
    try {
        submitted_graph.addEdge(0, -1, 1);
    } catch (const out_of_range &e) { // Graph correctly throws out of range
        error530 = true;
    } catch (const exception &e) { // Graph throws error, but not out of range
        error532 = true;
        passOrFail = false;
    }
    if (error530 + error532) {
        exceptionCaught = false;
        try {
            submitted_graph.addEdge(0, 8, 1);
        } catch (const out_of_range &e) { // Graph correctly throws out of range
            if (error530) {
                exceptionCaught = true;
                m_errors.push(Error(0, 530, "No errors in testExceptions(), addEdge() with bad destination vertex"));
            }
        } catch (const exception &e) { // Graph throws error, but not out of range
            exceptionCaught = true;
            m_errors.push(Error(2, 532, "addEdge() with bad destination vertex threw incorrect exception"));
            passOrFail = false;
        }
    }
    if (!exceptionCaught) { // Graph does not throw error
        m_errors.push(Error(5, 531, "addEdge() with bad destination vertex did not throw an exception"));
        passOrFail = false;
    }

    // Test bad source vertex exception
    bool error540, error542 = error540 = false;
    exceptionCaught = false;
    try {
        submitted_graph.addEdge(-1, 0, 1);
    } catch (const out_of_range &e) { // Graph correctly throws out of range
        error540 = true;
    } catch (const exception &e) { // Graph throws error, but not out of range
        error542 = true;
        passOrFail = false;
    }
    if (error540 + error542) {
        exceptionCaught = false;
        try {
            submitted_graph.addEdge(8, 0, 1);
        } catch (const out_of_range &e) { // Graph correctly throws out of range
            if (error540) {
                exceptionCaught = true;
                m_errors.push(Error(0, 540, "No errors in testExceptions(), addEdge() with bad source vertex"));
            }
        } catch (const exception &e) { // Graph throws error, but not out of range
            exceptionCaught = true;
            m_errors.push(Error(2, 542, "addEdge() with bad source vertex threw incorrect exception"));
            passOrFail = false;
        }
    }
    if (!exceptionCaught) { // Graph does not throw error
        m_errors.push(Error(5, 541, "addEdge() with bad source vertex did not throw an exception"));
        passOrFail = false;
    }


    // Test end NbIterator exception
    exceptionCaught = false;
    try {
        *(submitted_graph.nbEnd(0));
    } catch (const out_of_range &e) { // Graph correctly throws out of range
        exceptionCaught = true;
        m_errors.push(Error(0, 550, "No errors in testExceptions(), dereference of neighbor end iterator"));
    } catch (const exception &e) { // Graph throws error, but not out of range
        exceptionCaught = true;
        m_errors.push(Error(2, 552, "Dereference of neighbor end iterator threw incorrect exception"));
        passOrFail = false;
    }
    if (!exceptionCaught) { // Graph does not throw error
        m_errors.push(Error(5, 551, "Dereference of neighbor end iterator threw no exception"));
        passOrFail = false;
    }

    // Test end EgIterator exception
    exceptionCaught = false;
    try {
        *(submitted_graph.egEnd());
    } catch (const out_of_range &e) { // Graph correctly throws out of range
        exceptionCaught = true;
        m_errors.push(Error(0, 560, "No errors in testExceptions(), dereference of edge end iterator"));
    } catch (const exception &e) { // Graph throws error, but not out of range
        exceptionCaught = true;
        m_errors.push(Error(2, 562, "Dereference of edge end iterator threw incorrect exception"));
        passOrFail = false;
    }
    if (!exceptionCaught) { // Graph does not throw error
        m_errors.push(Error(5, 561, "Dereference of edge end iterator threw no exception"));
        passOrFail = false;
    }


    return passOrFail;
}

/*
 *  Method: Grader::resetErrorQueue()
 *   Descr: 
 */
void Grader::resetErrorQueue() {
}

// Formatted output of Error object:
// deduction: (id) description

ostream &operator<<(ostream &outStream, const Error &err) {
    if (err.m_deduction > 0) {
        outStream << "-" << err.m_deduction << ": (" << err.m_id
                << ") " << err.m_description;
    } else {

        outStream << err.m_deduction << ": (" << err.m_id
                << ") " << err.m_description;
    }
    return outStream;
}

/*
 *  Method: Grader::printAllErrors()
 *   Descr: Print all the errors
 */
void Grader::printAllErrors() {
    int totalDeductions = 0;

    while (m_errors.size()) {
        totalDeductions += m_errors.front().getDeduction();
        cout << m_errors.front() << endl;
        m_errors.pop();
    }
    cout << "\nTotal Deductions: " << totalDeductions << "" << endl;
}
/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/
