
#include "src/Optimizer.hpp"
#include "src/Move.hpp"

class UserMove : public SimulatedAnnealing::Move<UserMove>
{
public:
    void Accept() throw()
    {}
    
    double Attempt() throw()
    {
        return 0.0;
    }
    
    void Reject() throw()
    {}
};

class ResourceMap 
{
public:
    UserMove gNextMove() throw()
    {
        return UserMove();
    }

    double gCost() throw()
    {
        return 0.0;
    }

    size_t gNumberOfNodes() throw()
    {
        return 1000;
    }
};

double UpdateTemp(double t)
{
    return 0.5 * t;
}

int main()
{
    typedef double (*S) (double); 
    ResourceMap* rm = new ResourceMap();
    SimulatedAnnealing::Optimizer<ResourceMap, UserMove, S> 
                            o(rm, 0, &UpdateTemp);
    return 0;
}


// vim: set expandtab tabstop=4 shiftwidth=4 autoindent smartindent expandtab softtabstop=4 :
