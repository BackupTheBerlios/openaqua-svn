/********************************* Class Declaration ***************************/
/**
\package  OXML - 
\class    XDictionary

\brief    


\date     $Date: 2006/06/28 13:41:26,84 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   XDictionary_HPP
#define   XDictionary_HPP

class     XDictionary;

class     DBExtend;
class     DBFieldDef;
class     DBStructDef;
class     XMLElement;
#include  <sDictionary.hpp>
class  XDictionary :public Dictionary
{
protected  :         char                                        *xs_prefix;                                                 // 
protected  :         char                                        *oxs_prefix;                                                // 

public     :
                     char                                        *get_xs_prefix() { return(xs_prefix); }
                     char                                        *get_oxs_prefix() { return(oxs_prefix); }
public     :                                        logical CreateAttribute (DBStructDef *strdefptr, XMLElement *xelement );
public     :                                        logical CreateInheritance (DBStructDef *strdefptr, XMLElement *xelement );
public     :                                        logical CreateKey (DBStructDef *strdefptr, XMLElement *xelement );
public     :                                        logical CreateMember (DBStructDef *strdefptr, XMLElement *xelement );
public     :                                        logical CreateReference (DBStructDef *strdefptr, XMLElement *xelement );
public     :                                        logical CreateRelationship (DBStructDef *strdefptr, XMLElement *xelement );
public     : virtual                                char *GetExtent (int32 indx0 );
public     :                                        logical InitCollection (DBFieldDef *fielddef, XMLElement *xelement );
public     :                                        logical InitExtent (DBExtend *extdef, XMLElement *xelement );
public     :                                        logical InitIndex (DBFieldDef *fielddef, char *indexes_str );
public     :                                        logical InitIndexes (DBFieldDef *fielddef, char *indexes_str );
public     :                                        logical InitMember (DBFieldDef *fielddef, XMLElement *xelement );
public     :                                        logical InitRelationship (DBFieldDef *fielddef, XMLElement *xelement );
public     :                                        logical Open (char *cpath, char *xs_prefix, char *oxs_prefix );
public     :                                        logical ReadXEnum (XMLElement *xelement );
public     :                                        logical ReadXExtent (XMLElement *xelement );
public     :                                        logical ReadXExtents (XMLElement *xelement );
public     :                                        logical ReadXStruct (XMLElement *xelement );
public     :                                             XDictionary (char *cpath, PIACC accopt, char *xs_prefix, char *oxs_prefix );
public     :                                             XDictionary ( );
};

#endif
