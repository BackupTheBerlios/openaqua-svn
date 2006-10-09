/********************************* Class Declaration ***************************/
/**
\package  OXML - 
\class    OXMLBase

\brief    


\date     $Date: 2006/06/11 17:17:03,06 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OXMLBase_HPP
#define   OXMLBase_HPP

class     OXMLBase;

class     XMLElement;
#include  <sEB_Number.hpp>
class  OXMLBase
{
protected  :         XMLElement                                  *xdata;                                                     // 

public     :
                     XMLElement                                  *get_xdata() { return(xdata); }
public     :                                        XMLElement *GetElement (int32 lindx0 );
public     :                                        XMLElement *GetElement (char *names );
public     :                                             OXMLBase (XMLElement *xelement );
public     :                                        XMLElement *XElement (EB_Number entnr );
public     :                                        NOTYPE operator EB_Number ( );
public     :                                        XMLElement *operator= (EB_Number entnr );
};

#endif
