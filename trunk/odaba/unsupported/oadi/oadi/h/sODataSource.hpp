/********************************* Class Declaration ***************************/
/**
\package  OADI - 
\class    ODataSource

\brief    


\date     $Date: 2006/07/27 11:23:34,78 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODataSource_HPP
#define   ODataSource_HPP

class     ODataSource;

class     ODataSource;
#include  <cADK_DataReferenceType.h>
#include  <cODSPropertyType.h>
#include  <sDString.hpp>
#include  <sOPersistent.hpp>
#include  <sPropertyHandle.hpp>
#pragma pack(4)

class  ODataSource :public OPersistent
{
protected  :         ADK_DataReferenceType                        referenceType;                                             // 
protected  :         PIACC                                        accmode;                                                   // 
protected  :         char                                        *dataReference;                                             // 
protected  :         char                                        *baseCollection;                                            // 
protected  :         char                                        *structureName;                                             // 
protected  :         char                                        *sortOrder;                                                 // 
protected  :         logical                                      isCollection;                                              // 
protected  :         logical                                      use_key;                                                   // 
protected  :         logical                                      use_copy;                                                  // 
protected  :         int32                                        index;                                                     // 
protected  :         PropertyHandle                               dataPH;                                                    // 

public     :
                     ADK_DataReferenceType                        get_referenceType() { return(referenceType); }
                     PIACC                                       &get_accmode() { return(accmode); }
                     char                                        *get_dataReference() { return(dataReference); }
                     char                                        *get_baseCollection() { return(baseCollection); }
                     char                                        *get_structureName() { return(structureName); }
                     char                                        *get_sortOrder() { return(sortOrder); }
                     logical                                      get_isCollection() { return(isCollection); }
                     PropertyHandle                              &get_dataPH() { return(dataPH); }
public     :                                        const char *GetPath ( );
public     :                                        ODSPropertyType GetPathType ( );
public     :                  OADIImpExp                 ODataSource ( );
public     :                  OADIImpExp                 ODataSource (OPersistent bcOPersistent, int64 adk_reference_type, PIACC accmode, char *dataReference, char *baseCollection, char *structureName, char *sortOrder, logical isCollection, logical use_key, logical use_copy, int index, PropertyHandle dataPH );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     :                                        void SetEditProperty ( );
public     :                                        logical SetProperties (logical as_collection, PropertyHandle *prophdl );
public     :                                        ODataSource &operator= (ODataSource &rODataSource );
public     :                                        void set_baseCollection (char *string );
public     :                                        void set_dataReference (char *prop_path );
public     :                                        void set_isCollection (logical as_collection );
public     :                                        void set_referenceType (ADK_DataReferenceType data_ref_type );
public     :                                        void set_sortOrder (char *string );
public     :                                        void set_structureName (char *strnames );
public     : virtual                                     ~ODataSource ( );
};

#pragma pack()
#endif
