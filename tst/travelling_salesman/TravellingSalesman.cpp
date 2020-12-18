
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <fstream>
#include <sstream>

#include "src/Optimizer.hpp"
#include "src/Move.hpp"

/** 
 * Application of Simulated Annealing algorithm to solve Travelling Salesman
 * problem.
 */

size_t SIZE;

std::vector<std::vector<double> > dist;

typedef std::vector<int> path;

path optimal_path;

size_t attempts = 0;
size_t accepts = 0;
size_t rejects = 0;

int Gen() throw()
{
    static int x = 0;
    return x++; 
}

double ComputeLength(const path& v) throw()
{
    double l = 0;
    for (size_t i = 0; i < v.size(); ++i) {
        if (i == v.size() - 1) {
            l += dist[v[i]][v[0]];
        } else {
            l += dist[v[i]][v[i+1]];
        }
    }
    return l;
}

void PrintAllPaths() throw()
{
    path v(SIZE);
    std::generate_n(v.begin(), SIZE, &Gen);
    do {
        std::copy(v.begin(), v.end(), 
                std::ostream_iterator<int>(std::cout, " "));
        std::cout << *(v.begin()) << " : length = " 
            << ComputeLength(v) << std::endl; 
    } while (std::next_permutation(v.begin(), v.end()));
}

void InitDists(const std::string& f) throw()
{
    std::ifstream in(f.c_str());
    assert(in.good());
    std::string s;
    std::getline(in, s);
    std::string::size_type k = s.find("SIZE:");
    if (std::string::npos == k) {
        std::cerr << "Error: Matrix size is not defined." << std::endl;
        exit(1);
    }
    std::stringstream q;
    q << s.substr(k + 5, s.size()); 
    q >> SIZE; 
    dist.resize(SIZE);
    for (size_t x = 0; x < SIZE; ++x) {
        dist[x].resize(SIZE);
    }
    for (size_t i = 0; i < SIZE; ++i) {
        for (size_t j = 0; j < SIZE; ++j) {
            in >> dist[i][j];
        }
    }
}

class UserMove : public SimulatedAnnealing::Move<UserMove>
{
private:
    path from_;
    path to_;

public:
    void Accept() throw()
    {
        optimal_path = to_;
        ++accepts;
        //std::cout << "Accepted : " << ComputeLength(optimal_path) << std::endl; 
    }
    
    double Attempt() throw()
    {
        ++attempts;
        return ComputeLength(to_) - ComputeLength(from_);
    }
    
    void Reject() throw()
    {
        ++rejects;
    }

    UserMove(const path& f, const path& t) throw()
        : from_(f)
        , to_(t)
    {}
};

class TravellingSalesman 
{
public:
    UserMove gNextMove() throw()
    {
        size_t r = std::rand() % SIZE;
        path p = optimal_path;
        if (r < SIZE - 1) {
            std::swap(p[r], p[r + 1]);
        } else {
            assert(r == SIZE - 1);
            std::swap(p[r], p[0]);
        }
        return UserMove(optimal_path, p);
    }

    double gCost() throw()
    {
        return ComputeLength(optimal_path);
    }

    size_t gNumberOfNodes() throw()
    {
        return SIZE;
    }

    size_t gNumberOfNets() throw()
    {
        return SIZE;
    }

    void setDist(size_t) {}
};

double GetNewTemp(double t) throw()
{
    return 0.99 * t; 
}

int main (int argc, char** argv) 
{
    assert(2 == argc);
    std::string f = argv[1];  
    InitDists(f);
    optimal_path.resize(SIZE);
    //PrintAllPaths();
    std::generate_n(optimal_path.begin(), SIZE, &Gen);
    typedef double (*S) (double); 
    TravellingSalesman* t = new TravellingSalesman(); assert(0 != t);
    SimulatedAnnealing::Optimizer<TravellingSalesman, UserMove, S> 
                    o(t, 0, GetNewTemp);
    o.anneal();
    std::cout << ComputeLength(optimal_path) << std::endl;
    return 0;
}


// vim: set expandtab tabstop=4 shiftwidth=4 autoindent smartindent expandtab softtabstop=4 :
