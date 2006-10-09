/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|15:30:38,17}|(REF)
\class    OC_Panel

\brief    


\date     $Date: 2006/03/13 15:30:53,68 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OC_Panel_HPP
#define   OC_Panel_HPP

class     OC_Panel;

#ifndef   P_OC_Collection_HPP
#define   P_OC_Collection_HPP
#include  <sPI.hpp>
class       OC_Collection;
PI_dcl     (OC_Collection)
#endif
#include  <sDataSourceHandle.hpp>
class  OC_Panel
{
protected  :         DataSourceHandle                             datasource;                                                //
protected  :         int32                                        number;                                                    
protected  :         PI(OC_Collection)                            extents;                                                   //

public     :
                     int32                                        get_number() { return(number); }
                     PI(OC_Collection)                           &get_extents() { return(extents); }
public     :                                                             OC_Panel ( );
public     :                                     logical Open ( );
public     :                                                             ~OC_Panel ( );
};

#endif
