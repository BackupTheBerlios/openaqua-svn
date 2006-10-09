#ifndef __standard_hpp__
#define __standard_hpp__
// this is a hack for the ode7 where no includes could get
// added before the class definition, but often it was nessesary
// to use the std classes
// you still have to namespace address them (std::) but not to think about how
// they get into your project
// just add "tandard" to the references and set them "SensiRef and Member"
// this creates a include directive #include <standard.hpp>
// adding sos/h to your includepath everything should go fine
// when you add tandard the first time in your project the
// referencing project is std
// implementation is a class
// and the language is pl_cpp
// have fun

// when you need more (algorithm/list...) just add it, but 
// DONT use the std namespace!
// a*men

#include <string>
#include <vector>
#include <list>

#include <iostream>
#include <sstream>
#include <fstream>
//typedef std::string std_string;

#endif //__standard_hpp__

