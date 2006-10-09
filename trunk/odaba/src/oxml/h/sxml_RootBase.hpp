/********************************* Class Declaration ***************************/
/**
\package  OXML - 
\class    xml_RootBase

\brief    


\date     $Date: 2006/06/11 13:01:05,35 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   xml_RootBase_HPP
#define   xml_RootBase_HPP

class     xml_RootBase;

class     acb;
#include  <cRootBase_Types.h>
#include  <sXMLString.hpp>
#include  <sdb_RootBase.hpp>
class  xml_RootBase :public db_RootBase
{
protected  :         XMLString                                    xml_data;                                                  // 
protected  :         logical                                      modified;                                                  // 

public     :
                     XMLString                                   &get_xml_data() { return(xml_data); }
                     logical                                      get_modified() { return(modified); }
public     : virtual                                logical Open (char *path, logical outopt, logical exclusive, char sysenv=NO );
public     : virtual                                RootBase_Types RBType ( );
public     :                                             xml_RootBase (logical netopt, logical shared_rb );
public     :                                             ~xml_RootBase ( );
};

#endif
