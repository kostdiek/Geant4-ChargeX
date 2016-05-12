// $Id: B4aActionInitialization.hh 68058 2013-03-13 14:47:43Z gcosmo $
//
/// \file B4aActionInitialization.hh
/// \brief Definition of the B4aActionInitialization class

#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization();
    virtual ~ActionInitialization();


 private:
    virtual void Build() const;
  
};

#endif

  
