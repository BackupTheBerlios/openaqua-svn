#ifndef __CoaCommands_h__
#define __CoaCommands_h__


/**
@brief CoaCommand - the pure virtual base class for Coa Application Commands

The CoaCommand class base on the command pattern.
*/

class CoaCommand 
{
public:
   virtual ~CoaCommand();
   virtual void execute() = 0;
protected:
   CoaCommand();
};

#endif // __CoaCommands_h__