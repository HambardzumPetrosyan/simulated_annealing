
#ifndef __SIMULATED_ANNEALING_MOVE
#define __SIMULATED_ANNEALING_MOVE

/**
 * @file src/simulated_annealing/Move.hpp
 *
 * @brief Definition of class @ref SimulatedAnnealing::Move.  
 */

// Headers from standard libraries
#include <string>

namespace SimulatedAnnealing {

/**
 * @brief This class is a generic representation of Simulated Annealer move.
 *
 * CRTP pattern is used. User specified move should be inherited from
 * instantiation of the generic move using itself as template argument. 
 *
 * Example:
 * @code
 * class UserMove : public SimulatedAnnealing::Move<UserMove>
 * {
 * public:
 *      void Accept() throw();
 *
 *      double Attempt() throw();
 *
 *      void Reject() throw();
 * }; 
 * @endcode
 */
template <typename T>
class Move
{
    /// @name Move interface 
public:
    /**
     * @brief Simulates the move without updating the state. 
     *
     * @returns change of the cost function produced by move.
     */
    double SAAttempt() throw();

    /**
     * @brief Applies the move and updates state of the system. 
     */
    void SAAccept() throw();

    /**
     * @brief Rejects the move. 
     */
    void SAReject() throw();

    /// @name Name
private:
    std::string name_;

public:
    /// Gets the name of the move
    std::string gName() const throw();
    
    /**
     * @brief Sets the name of the move.
     *
     * @param n - string to be set as a name of the move 
     */
    void sName(const std::string& n) throw(); 

    /// @name Special member functions
protected:
    /// Default constructor. 
	Move() throw();
    
    /// Copy constructor 
    Move(const Move& m) throw();

    /// Assignment operator 
    Move& operator= (const Move& m) throw();

    /// Destructor
    ~Move() throw();

}; //class Move 

} //namespace SimulatedAnnealing 

#include "Move.cpp"

#endif //__SIMULATED_ANNEALING_MOVE

// vim: set expandtab tabstop=4 shiftwidth=4 autoindent smartindent expandtab softtabstop=4 :
