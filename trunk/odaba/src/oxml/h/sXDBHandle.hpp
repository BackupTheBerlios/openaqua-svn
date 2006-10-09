/********************************* Class Declaration ***************************/
/**
\package  OXML - 
\class    XDBHandle

\brief    


\date     $Date: 2006/06/29 18:01:04,45 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   XDBHandle_HPP
#define   XDBHandle_HPP

class     XDBHandle;

class     DBExtend;
class     Dictionary;
class     node;
#include  <cPIACC.h>
#include  <sDBHandle.hpp>
#include  <sLACObject.hpp>
#include  <sXMLString.hpp>
class  XDBHandle :public virtual DBHandle,
public LACObject
{
protected  :         XMLString                                    xs;                                                        // 

public     :
                     XMLString                                   &get_xs() { return(xs); }
public     : virtual                                EB_Number *AddExtendRef (DBExtend *dbextdef );
public     : virtual                                char *GetExtent (int32 indx0 );
public     :                                        logical InitExtents ( );
public     :                                        void Initialize (Dictionary *dict_ptr, char *cpath, PIACC accopt );
public     :                                        void Initialize (Dictionary *dict_ptr, PIACC accopt, uint16 version_nr=CUR_VERSION );
public     : virtual                                logical IsXMLBase ( );
public     :                                             XDBHandle (Dictionary *dict_ptr, char *cpath, PIACC accopt );
};

#endif
