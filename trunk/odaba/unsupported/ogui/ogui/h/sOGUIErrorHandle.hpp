/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    OGUIErrorHandle

\brief    


\date     $Date: 2006/08/28 07:46:57,57 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OGUIErrorHandle_HPP
#define   OGUIErrorHandle_HPP

class     OGUIErrorHandle;

class     Error;
class     ErrorMessage;
#include  <sDBErrorHandle.hpp>
#include  <sDBObjectHandle.hpp>
class  OGUIErrorHandle :public DBErrorHandle
{

public     :
public     : virtual          OGUIImpExp            logical GetDecision (Error *error_obj );
public     :                  OGUIImpExp                 OGUIErrorHandle (DBObjectHandle &_obhandle );
public     :                                        logical ShowMessage (Error *pError );
public     :                                        void SetErrorObject (DBObjectHandle &_obhandle ){

  ob_handle = _obhandle;


}

};

#endif
