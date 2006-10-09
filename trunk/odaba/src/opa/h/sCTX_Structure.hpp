/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|08:31:15,81}|(REF)
\class    CTX_Structure

\brief    Structure Context
          A  structure context  is created  for each  structure type. It defines
          the  connection  between  the  instance  and the instance description.
          Moreover,  it allows determining the active con-text hierarchy for the
          structure  instance,  i.e.  the  parent property/extent, the structure
          the  parent property  is defined  in, the  parent parent property etc.
          Thus,  the structure context  defines the context  in which the object
          instance has been provided.
          The  parent  context  for  a  structure  context  is always a property
          context.  This  can  be  the  property  context  for  an extent or for
          another property within a structure instance.
          The  structure  context  allows  handling  read and updating events as
          well as creating or deleting events.

\date     $Date: 2006/03/13 08:31:18,12 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CTX_Structure_HPP
#define   CTX_Structure_HPP

class     CTX_Structure;

class     CTX_Base;
class     CTX_Property;
class     CTX_Structure;
class     DBStructDef;
class     binti;
#include  <sCTX_DBBase.hpp>
#include  <sInstance.hpp>
#include  <sPropertyHandle.hpp>
#include  <sbds.hpp>
#pragma pack(8)

class  CTX_Structure :public CTX_DBBase
{
protected  :         binti                                       *int_instance ATTR_ALIGN(4);                                //
protected  :         char                                        *old_instance;                                              //
protected  :         CTX_Structure                               *ref_context;                                               //
protected  :         logical                                      key_check;                                                 //

public     :
                     binti                                       *get_int_instance() { return(int_instance); }
                     char                                        *get_old_instance() { return(old_instance); }
                     logical                                      get_key_check() { return(key_check); }
public     :                                     logical BuildDefaultDescription (bds &string_buffer, logical html );
public     :                                     logical BuildDescription (bds &string_buffer, char *string, char ptype, int16 plevel, logical html );
public     :                                     logical BuildDescriptionByTemplate (PropertyHandle &templ_pi, bds &string_buffer, logical html );
public     :                                     logical BuildDescriptorText (PropertyHandle &templ_pi, PropertyHandle *data_pi, PropertyHandle &descr_pi, bds &string_buffer, logical html, logical in_table );
public     :                                     logical BuildInstanceText (PropertyHandle &templ_pi, PropertyHandle *data_pi, PropertyHandle &descr_pi, bds &string_buffer, logical html, logical in_table );
public     :         opa7ImpExp                  logical BuildObjDescription (PropertyHandle &templ_pi, logical html );
public     :                                     logical BuildPrefixSuffix (char *prefix, char *suffix, char ptype, int16 plevel, logical html );
public     :                                     logical BuildReference (PropertyHandle *data_pi, PropertyHandle &descr_pi, bds &string_buffer, logical html );
public     :                                     logical BuildTemplate (PropertyHandle *data_pi, PropertyHandle &descr_pi, bds &string_buffer, logical html );
public     :         opa7ImpExp                                          CTX_Structure ( );
public     :                                     logical CopyTo ( );
public     : virtual opa7ImpExp                  logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                     PropertyHandle *GetCollection ( );
public     :         opa7ImpExp                  ODABAClient GetConnectionClient ( );
public     : virtual opa7ImpExp                  CTX_Types GetContextType ( );
public     : virtual opa7ImpExp                  PropertyHandle GetDBField (char *fldname_w=NULL );
public     :         opa7ImpExp                  CTX_Structure *GetInstContext ( );
public     :         opa7ImpExp                  Instance GetInstance ( );
public     :         opa7ImpExp                  char *GetKey ( );
public     :         opa7ImpExp                  PropertyHandle GetOldField ( );
public     :         opa7ImpExp                  char *GetOldInstance ( );
public     : virtual opa7ImpExp                  CTX_Property *GetPropContext (char *w_fldnames=NULL );
public     : virtual opa7ImpExp                  PropertyHandle *GetPropertyHandle (char *fldname_w=NULL );
public     :         opa7ImpExp                  CTX_DisplayState GetReadOnly ( );
public     :         opa7ImpExp                  CTX_Structure *GetRefContext ( );
public     : virtual opa7ImpExp                  char *GetResourceName ( );
public     :         opa7ImpExp                  PropertyHandle GetSourceField ( );
public     : virtual opa7ImpExp                  CTX_Structure *GetStructContext (char *w_strnames=NULL );
public     :         opa7ImpExp                  logical HideInstance ( );
public     :                                     logical InitDescription (PropertyHandle &templ_pi, bds &string_buffer, logical html );
public     :                                     void Initialize (binti *bintiptr, CTX_Base *highctx );
public     : virtual opa7ImpExp                  logical IsEdit ( );
public     :         opa7ImpExp                  logical IsHidden ( );
public     :         opa7ImpExp                  logical IsReadOnly ( );
public     :         opa7ImpExp                  logical SetKey ( );
public     :         opa7ImpExp                  logical SetReadOnly (logical readonly );
public     :         opa7ImpExp                  logical SetRefContext (CTX_Structure *strctx );
public     :         opa7ImpExp                  void SetResult (char *result_string );
public     : virtual opa7ImpExp                  void SetTransactionError ( );
public     :         opa7ImpExp                  logical ShowInstance ( );
public     :                                     logical TermDescription (bds &string_buffer, logical html );
public     : virtual opa7ImpExp                                          ~CTX_Structure ( );
};

#pragma pack()
#endif
