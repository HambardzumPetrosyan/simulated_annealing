
#include <cassert>
#include <cmath>
#include <limits>
#include <iostream>

template <typename T, typename M, typename S>
SimulatedAnnealing::
Optimizer<T, M, S>::Optimizer(T* t, unsigned int* r, S s) throw() 
        : state_(t)
        , seed_(r)
        , coolingSchedule_(s)
        , temp_(std::numeric_limits<double>::max())
        , dist_(10)
        , cost_(0.0)
        , bestCost_(0.0)
        , costVariance_(0.0)
        , averageAcceptanceProb_(1.0)
        , minTemp_(1e-7)
{
    if (0 == seed_) {
        seed_ = new unsigned int(5);
    }
    requiredAttempts_ = 
        15 * (size_t) std::pow(state_->gNumberOfNodes(), 4.0/3.0);
    assert(0 != state_);
}
    
template <typename T, typename M, typename S>
SimulatedAnnealing::
Optimizer<T, M, S>::~Optimizer() throw()
{}

template <typename T, typename M, typename S>
void SimulatedAnnealing::
Optimizer<T, M, S>::setMinTemp(double t) throw() 
{
    minTemp_ = t;
}

template <typename T, typename M, typename S>
void SimulatedAnnealing::
Optimizer<T, M, S>::anneal() throw()
{
    doInitialMoves();
    temp_ = 20 * sqrt(costVariance_);
    if (temp_ < 1000) temp_ = 1000;
    bool b = true; 
    while (b) {
         b = doIterativeAnnealing();
    }
}

template <typename T, typename M, typename S>
void SimulatedAnnealing::
Optimizer<T, M, S>::quench() throw()
{
}

template <typename T, typename M, typename S>
void SimulatedAnnealing::
Optimizer<T, M, S>::doInitialMoves() throw()
{
    assert(0 != state_);
    double c = state_->gCost();
    bestCost_ = cost_ = c; 
    size_t n = state_->gNumberOfNodes();
    double s = 0; 
    double x = 0; 
    for (size_t i = 0; i < n; ++i) {
        M m = state_->gNextMove();
        double d = m.SAAttempt();
        m.SAAccept();
        cost_ += d;
        s += d; 
        x += d * d; 
    }
    if (1 == n) {
        costVariance_ = 1;
    } else {
        costVariance_ = (x - s * s / n ) / (n - 1); 
    }
}

template <typename T, typename M, typename S>
bool SimulatedAnnealing::
Optimizer<T, M, S>::isFinished() throw()
{
    //return temp_ < 0.005 * state_->gCost() / state_->gNumberOfNets();
    return temp_ < minTemp_;
}

template <typename T, typename M, typename S>
double SimulatedAnnealing::
Optimizer<T, M, S>::defaultSchedule(double t) throw()
{
    double f = 0;
    if (averageAcceptanceProb_ >= 0.96) {
        f = 0.5;
    } else if (averageAcceptanceProb_ >= 0.5) {
        f = 0.8;
    } else if (averageAcceptanceProb_ >= 0.15) {
        f = 0.98;
    } else {
        f = 0.8;
    }
    assert(0 != f);
    return f * t;
}
    
template <typename T, typename M, typename S>
void SimulatedAnnealing::
Optimizer<T, M, S>::updateTemp() throw()
{
    if (coolingSchedule_ != 0) {
        temp_ = coolingSchedule_(temp_);
    } else {
        temp_ = defaultSchedule(temp_); 
    }
}

template <typename T, typename M, typename S>
void SimulatedAnnealing::
Optimizer<T, M, S>::updateDist() throw()
{
    dist_ = dist_ * (1 - 0.44 + averageAcceptanceProb_);
    dist_ = std::max(1.0, dist_);
    dist_ = std::min(10.0, dist_);
    state_->setDist(size_t(dist_ + 0.5));
}

template <typename T, typename M, typename S>
bool SimulatedAnnealing::
Optimizer<T, M, S>::doIterativeAnnealing() throw()
{
    updateTemp();
    //updateDist();
    doMetropolisWalk();
    return ! isFinished();
}

template <typename T, typename M, typename S>
void SimulatedAnnealing::
Optimizer<T, M, S>::doMetropolisWalk() throw()
{
    assert(0 != state_);
    size_t attempts = 0;
    size_t accepts = 0;
    double delta_cost;
    size_t n = getRequiredAttemptsAtTemp();
    for (; attempts < n; ++attempts) {
        M m = state_->gNextMove();
        delta_cost = m.SAAttempt();
        if (delta_cost < 0 || rand_r(seed_) < RAND_MAX * 
                std::exp(- delta_cost / temp_)) {
            accepts++;
            m.SAAccept();
            cost_ += delta_cost;
            if (cost_ < bestCost_) {
                bestCost_ = cost_;
            }
        } else {
            m.SAReject();
        } 
    }
    averageAcceptanceProb_ = (double) accepts / (double) attempts;
}
    
template <typename T, typename M, typename S>
size_t SimulatedAnnealing::
Optimizer<T, M, S>::getRequiredAttemptsAtTemp() const throw() 
{
    return requiredAttempts_;
}

// vim: set expandtab tabstop=4 shiftwidth=4 autoindent smartindent expandtab softtabstop=4 :
