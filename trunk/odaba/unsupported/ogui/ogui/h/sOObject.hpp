/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OObject

\brief    


\date     $Date: 2006/03/13 21:34:29,37 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OObject_HPP
#define   OObject_HPP

class     OObject;

#define  ODW_NAME                                  "ODataWidget"
class     ODataWidget;
class  OObject :public QObject
{
protected  :         void                                        *o_ptr;                                                     

public     :
public     : static                              ODataWidget *__cdecl GetODW (QObject *pQObject );
public     :                                                             OObject (QObject *pQObject, void *extra_data, char *names );
public     : static                              logical __cdecl RegisterODW (ODataWidget *pODataWidget );
};

#endif
