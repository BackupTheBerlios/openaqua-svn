/********************************* Class Declaration ***************************/
/**
\package  OPI
\class    CheckOptions

\brief    


\date     $Date: 2006/04/24 19:58:13,93 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CheckOptions_HPP
#define   CheckOptions_HPP


#include "copadll.h"
class     CheckOptions;

class  CheckOptions
{
public     :         bit                                          guids: 1;                                                  // 
public     :         bit                                          deleted_references: 1;                                     // 
public     :         bit                                          inverse_references: 1;                                     // 
public     :         bit                                          ref_indexes: 1;                                            // 
public     :         bit                                          key_values: 1;                                             
public     :         bit                                          instances: 1;                                              
public     :         bit                                          collections: 1;                                            
public     :         bit                                          repair_all: 1;                                             
public     :         bit                                          show_warnings: 1;                                          
public     :         bit                                          remote: 1;                                                 

public     :
public     :         OPIImpExp                                           CheckOptions ( );
public     :         OPIImpExp                                           CheckOptions (char *parmstring );
public     :         OPIImpExp                   logical Initialize (char *parmstring );
};

#endif
