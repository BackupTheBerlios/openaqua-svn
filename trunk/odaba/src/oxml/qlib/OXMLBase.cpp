/********************************* Class Source Code ***************************/
/**
\package  OXML - 
\class    OXMLBase

\brief    


\date     $Date: 2006/06/11 17:17:04,00 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OXMLBase"

#include  <pOXML.h>
#include  <sXMLElement.hpp>
#include  <sOXMLBase.hpp>


/******************************************************************************/
/**
\brief  GetElement - 


\return xelement - 
-------------------------------------------------------------------------------
\brief  i00 - 


\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetElement"

XMLElement *OXMLBase :: GetElement (int32 lindx0 )
{

 return ( this && xdata ? xdata->GetElement(lindx0) : NULL );

}

/******************************************************************************/
/**
\brief  i01 - 


\param  names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetElement"

XMLElement *OXMLBase :: GetElement (char *names )
{

 return ( this && xdata ? xdata->GetElement(names) : NULL );

}

/******************************************************************************/
/**
\brief  OXMLBase - 



\param  xelement - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OXMLBase"

     OXMLBase :: OXMLBase (XMLElement *xelement )
                     :   xdata(xelement)
{



}

/******************************************************************************/
/**
\brief  XElement - 


\return xelement - 

\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "XElement"

XMLElement *OXMLBase :: XElement (EB_Number entnr )
{
  XMLElement    *xelement = NULL;
  xelement = (XMLElement *)entnr.get_ebsnum();
  return(xelement);
}

/******************************************************************************/
/**
\brief  operator EB_Number - 


\return notype - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator EB_Number"

NOTYPE OXMLBase :: operator EB_Number ( )
{

  return((int64)xdata);

}

/******************************************************************************/
/**
\brief  operator= - 


\return xelement - 

\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

XMLElement *OXMLBase :: operator= (EB_Number entnr )
{

  xdata = XElement(entnr);
  return(xdata);
}


