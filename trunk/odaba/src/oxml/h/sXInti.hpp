/********************************* Class Declaration ***************************/
/**
\package  OXML - 
\class    XInti

\brief    


\date     $Date: 2006/06/11 19:56:25,85 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   XInti_HPP
#define   XInti_HPP

class     XInti;

class     DBStructDef;
class     XMLAttribute;
class     XMLElement;
class     fmcb;
class     node;
#include  <sEB_Number.hpp>
#include  <sOXMLBase.hpp>
#include  <sbinti.hpp>
class  XInti :public binti,
public OXMLBase
{

public     :
public     : virtual                                logical Cancel ( );
public     : virtual                                logical Get (EB_Number entnr );
public     : virtual                                logical Get (char *extinst );
public     :                                        logical GetData (XMLElement *xelement, DBStructDef *strdef, char *inst_data );
public     : virtual                                EB_Number GetID (int32 w_indx0=-1 );
public     : virtual                                int16 GetSID (EB_Number entnr );
public     : virtual                                logical IsPositioned ( );
public     : virtual                                void Reset ( );
public     :                                        logical SetupAttribute (XMLAttribute *xattribute, fmcb *fmcbptr, char *inst_data );
public     :                                        logical SetupAttribute (XMLElement *xelement, fmcb *fmcbptr, char *inst_data );
public     :                                        void SetupInst (logical update );
public     :                                        logical SetupReference (XMLElement *xelement, fmcb *fmcbptr, char *inst_data );
public     :                                             XInti (node *nodeptr, DBStructDef *strdefptr, void *instptr, logical crt_opt );
public     : virtual                                     ~XInti ( );
};

#endif
