/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    ODC_BaseContext

\brief    


\date     $Date: 2006/03/13 21:30:30,95 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODC_BaseContext_HPP
#define   ODC_BaseContext_HPP

class     ODC_BaseContext;

#include  <cContextTypes.h>
#pragma pack(8)

class  ODC_BaseContext
{
protected  :         char                                         classname[40];                                             
protected  :         ContextTypes                                 contexttype;                                               

public     :
                     char                                        *get_classname() { return(classname); }
                     ContextTypes                                 get_contexttype() { return(contexttype); }
};

#pragma pack()
#endif
