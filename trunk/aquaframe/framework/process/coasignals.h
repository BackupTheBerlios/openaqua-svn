#ifndef __CoaSignals_h__
#define __CoaSignals_h__


/**@brief a _very_ simple class to send signals between objects in a Coa Application
*/
class CoaSignal {
public:
   CoaSignal();
};

class CoaFileSignal : public CoaSignal {};
class CoaApplicationSignal : public CoaSignal {};
class CoaApplicationQuitSignal : public CoaApplicationSignal {};
class CoaApplicationAboutSignal : public CoaApplicationSignal {};


#endif //__CoaSignals_h__

