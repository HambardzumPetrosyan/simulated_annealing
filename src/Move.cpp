
template <typename T>
double SimulatedAnnealing:: 
Move<T>::SAAttempt() throw()
{
    return static_cast<T*>(this)->Attempt();
}

template <typename T>
void SimulatedAnnealing:: 
Move<T>::SAAccept() throw()
{
    static_cast<T*>(this)->Accept();
}

template <typename T>
void SimulatedAnnealing:: 
Move<T>::SAReject() throw()
{
    static_cast<T*>(this)->Reject();
}

template <typename T>
std::string SimulatedAnnealing:: 
Move<T>::gName() const throw()
{
    return name_;
}
    
template <typename T>
void SimulatedAnnealing:: 
Move<T>::sName(const std::string& n) throw() 
{
    name_ = n;
}

template <typename T>
SimulatedAnnealing:: 
Move<T>::Move() throw()
{}
    
template <typename T>
SimulatedAnnealing:: 
Move<T>::Move(const Move& m) throw()
    : name_(m.name_)
{}

template <typename T>
SimulatedAnnealing::Move<T>& 
SimulatedAnnealing:: 
Move<T>::operator= (const Move& m) throw()
{
    if (this == &m) {
        return *this;
    }
    this->name_ = m.name_;
    return *this;
}

template <typename T>
SimulatedAnnealing:: 
Move<T>::~Move() throw()
{}

// vim: set expandtab tabstop=4 shiftwidth=4 autoindent smartindent expandtab softtabstop=4 :

