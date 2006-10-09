/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OperResources

\brief    


\date     $Date: 2006/03/12 19:20:18,71 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OperResources_HPP
#define   OperResources_HPP

class     OperResources;

class     ACObject;
class     Dictionary;
class  OperResources
{
protected  :         Dictionary                                  *dictionary;                                                
protected  :         ACObject                                    *resource_hdl;                                              
protected  :         ACObject                                    *object_ref;                                                

public     :
                     Dictionary                                  *get_dictionary() { return(dictionary); }
                     ACObject                                    *get_resource_hdl() { return(resource_hdl); }
                     ACObject                                    *get_object_ref() { return(object_ref); }
public     :                                                             OperResources (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle );
};

#endif
