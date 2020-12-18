
#ifndef __SIMULATED_ANNEALING_OPTIMIZER
#define __SIMULATED_ANNEALING_OPTIMIZER

/**
 * @file src/simulated_annealing/Optimizer.hpp
 *
 * @brief Definition of class @ref SimulatedAnnealing::Optimizer.  
 */

// Headers from standard libraries
#include <boost/concept_check.hpp>

/// Namespace for the Simulated Annealing project.
namespace SimulatedAnnealing {

/**
 * @brief This class represents generic implementation of simulated annealing
 * algorithm.
 *
 * @param T - type representing the states set on which annealer should find
 * the global optimum
 * @param M - user specified move type
 * @param S - functor representing SA cooling schedule 
 *
 * @pre Type T provides following methods :
 *          - M T::gNextMove()
 *          - double T::gCost()
 *          - size_t T::gNumberOfNodes()
 * @pre S is a model of unary function 
 * @pre S::argument_type is convertible to double 
 * @pre S::result_type is convertible to double
 */
template <typename T, typename M, typename S = double (*) (double)>
class Optimizer
{
    BOOST_CONCEPT_ASSERT((boost::UnaryFunctionConcept<S, double, double>));

public:
    /// Runs the annealer.
    void anneal() throw();
    
    /// Performs a zero temperature quenching. 
    void quench() throw();

    /**
     * Sets temperature at which annealing should be stopped.
     * 
     * @param t - temperature to be set as minimal 
     */
    void setMinTemp(double t) throw(); 

    /// @name Helper member functions
private:
    void doInitialMoves() throw();
    bool doIterativeAnnealing() throw();
    bool isFinished() throw();
    size_t getRequiredAttemptsAtTemp() const throw(); 
    void doMetropolisWalk() throw();
    double defaultSchedule(double) throw();
    void updateTemp() throw();
    void updateDist() throw();

private:
    T* state_;
    unsigned int* seed_;
    S coolingSchedule_;
    double temp_;
    double dist_;
    double cost_;
    double bestCost_;
    double costVariance_;
    double averageAcceptanceProb_;
    double minTemp_;
    size_t requiredAttempts_;

    /// @name Special member functions
public:
    /**
     * @brief The only available constructor.
     *
     * @param t - Annealer will try to find the global optima from the states
     * of this object
     * @param r - seed for random number generation
     * @param s - SA cooling schedule functor
     */
	Optimizer(T* t, unsigned int* r = 0, S s = 0) throw(); 

    /// Destructor
    ~Optimizer() throw();

    /// @name Undefined special member functions
private:
    /// This class is not default constructable
	Optimizer() throw();

    /// This class is not copy-constructable
    Optimizer(const Optimizer&) throw();

    /// This class is not assignable
    Optimizer& operator= (const Optimizer&) throw();

}; //class Optimizer 
	
} //namespace SimulatedAnnealing 

#include "Optimizer.cpp"

#endif //__SIMULATED_ANNEALING_OPTIMIZER

// vim: set expandtab tabstop=4 shiftwidth=4 autoindent smartindent expandtab softtabstop=4 :
