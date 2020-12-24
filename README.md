# simulated_annealing
C++ implementation of a simulated annealing algorithm.

Simulated annealing (SA) is a probabilistic technique for approximating the global optimum of a given function. Specifically, it is a metaheuristic to approximate global optimization in a large search space for an optimization problem. It is often used when the search space is discrete.

This project represents generic implementation of Simulated Annealing algorithm. Application to solve traveling salesman problem included as a testbench.

Steps to build the project:
  mkdir build
  cd build
  cmake ..
  make

To run tests:
  ctest
