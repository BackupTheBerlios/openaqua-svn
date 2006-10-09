/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    ODC_Function

\brief    


\date     $Date: 2006/03/13 21:30:32,57 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODC_Function_HPP
#define   ODC_Function_HPP

class     ODC_Function;

#include  <cMethodTypes.h>
#include  <cProcessingTypes.h>
#include  <sSDB_Member.hpp>
#pragma pack(8)

class  ODC_Function :public SDB_Member
{
protected  :         char                                         errorcase[32] ATTR_ALIGN(4);                               //
protected  :         logical                                      signal;                                                    //
protected  :         logical                                      slot;                                                      //
protected  :         MethodTypes                                  imp_type;                                                  //
protected  :         ProcessingTypes                              proc_type;                                                 // Processing type
protected  :         logical                                      action;                                                    
protected  :         logical                                      inter_face;                                                //
protected  :         char                                         retval_name[40];                                           //
protected  :         PI(ODC_Variable)                             retval;                                                    

public     :
                     char                                        *get_errorcase() { return(errorcase); }
                     logical                                      get_signal() { return(signal); }
                     logical                                      get_slot() { return(slot); }
                     MethodTypes                                  get_imp_type() { return(imp_type); }
                     ProcessingTypes                              get_proc_type() { return(proc_type); }
                     logical                                      get_action() { return(action); }
                     logical                                      get_inter_face() { return(inter_face); }
                     char                                        *get_retval_name() { return(retval_name); }
                     PI(ODC_Variable)                            &get_retval() { return(retval); }
};

#pragma pack()
#endif
