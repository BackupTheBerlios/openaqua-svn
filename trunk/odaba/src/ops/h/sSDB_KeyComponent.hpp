/********************************* Class Declaration ***************************/
/**
\package  OPS
\class    SDB_KeyComponent

\brief    Key component
          A  key component defines refers to a single attribute, a key or a base
          structure. Key components can be referenced in different ways:
          -  by referring  to an  attribute of  the structure or one of its base
          structures using the attribute name
          - by referring to a near attribute property using a property path
          -  by  referring  to  a  key  name defined for a base structure, which
          provides the attributes defined for the referenced key
          -  by referring to a base  structure, which provides the attributes of
          its identifying key as key attributes
          When  a key component  refers to a  transient attribute, indexes based
          on  such keys are  not updated automatically,  i.e. the application is
          responsible  to update the index, when  the value of a transient field
          changes, which is defined as key component.

\date     $Date: 2006/05/11 13:10:39,48 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_KeyComponent_HPP
#define   SDB_KeyComponent_HPP

class     SDB_KeyComponent;

class     PropertyHandle;
class     fmcb;
#pragma pack(8)

class  SDB_KeyComponent
{
protected  :         char                                         member_path[82];                                           // Member path
protected  :         logical                                      ignore_case;                                               // Ignore case option
protected  :         logical                                      descending;                                                // Order option

public     :
                     char                                        *get_member_path() { return(member_path); }
                     logical                                      get_ignore_case() { return(ignore_case); }
                     logical                                      get_descending() { return(descending); }
public     :                  OPSImpExp             char *KeyDataDecl (PropertyHandle *prophdl, NString &nstring, PropertyHandle *dbs_ph );
};

#pragma pack()
#endif
