/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    HierarchicalIntervall

\brief    Hirarchical Intervall list


\date     $Date: 2006/03/12 19:20:02,81 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   HierarchicalIntervall_HPP
#define   HierarchicalIntervall_HPP

class     HierarchicalIntervall;

#ifndef   GSRT_HierIntEntry_HPP
#define   GSRT_HierIntEntry_HPP
#include  <sHierIntEntry.hpp>
#include  <sGSRT.h>
#endif
#include  <sHierIntEntry.hpp>
#pragma pack(8)

class  HierarchicalIntervall :public GSRT(HierIntEntry)
{
protected  :         logical                                      excludes ATTR_ALIGN(4);                                    //

public     :
                     logical                                      get_excludes() { return(excludes); }
public     :                                     char *GetExpression (char *string, char *expression );
public     :         SOS7ImpExp                                          HierarchicalIntervall (char *rule, logical exclude=NO );
public     :         SOS7ImpExp                  logical Includes (char *string );
public     :         SOS7ImpExp                                          ~HierarchicalIntervall ( );
};

#pragma pack()
#endif
