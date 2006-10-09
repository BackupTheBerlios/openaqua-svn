/*******************************************************************/
/*			      P I N S T				   */
/*                         Class Declaration                       */
/*   Version 0.1					  02.09.92 */
/*******************************************************************/

#ifndef PI_HPP
#define PI_HPP

#include  <cPIACC.h>
#include  <cPIREPL.h>
#include  <padcstd.h>

#define   PI(itp)		tc_ph<itp>

class    mem;
#define  MEMO  mem
#define   pmem PI(mem)

#include  <sPropertyHandle.hpp>

#pragma pack(4)

#define   PH(parent,name)					                        	 \
	  PropertyHandle	  name(parent,#name);

#define   GPH(name)	          GetPropertyHandle(name)

#define   PI_dcl(itp)	

template <class itp> class tc_ph : 
  public PropertyHandle
{
  public:
          itp       * Add         ( itp *instptr, long int indx0=AUTO)
                      { return( (itp *)PropertyHandle::Add(Instance(instptr),indx0).GetData());} 
          itp       * Add         ( long int indx0=AUTO )  
                      { return( (itp *)PropertyHandle::Add(indx0).GetData());} 
          itp       * Add         ( Key skey, Key identkey=Key(),   
                                    itp *initinst=NULL)  
                      { return( (itp *)PropertyHandle::Add(skey,identkey,Instance(initinst)).GetData());} 
          logical     AddReference(  PI(itp) &pienty, long int indx0=AUTO ) 
                      { return( PropertyHandle::AddReference(*(PropertyHandle *)&pienty,indx0)); } 

          itp       * Copy        ( PI(itp) &pienty, PIREPL replopt = REPL_none, PIREPL copy_type = REPL_all)
                      { return( (itp *)PropertyHandle::Copy(*(PropertyHandle *)&pienty,replopt,copy_type).GetData());}
          itp       * Copy        ( PI(itp) &pienty, Key newname, PIREPL replopt = REPL_none, PIREPL copy_type = REPL_all)
                      { return( (itp *)PropertyHandle::Copy(*(PropertyHandle *)&pienty,newname,replopt,copy_type).GetData());}

          itp       * Duplicate   ( Key identkey, PIREPL replopt = REPL_none)
                      { return( (itp *)PropertyHandle::Duplicate(identkey,replopt).GetData());}

          Key	      ExtractKey  ( Key skey = Key(), itp *instptr = NULL)
                      { return( PropertyHandle::ExtractKey(skey,Instance(instptr)) ); }
          Key	      ExtractSortKey  ( Key skey = Key(), itp *instptr = NULL)
                      { return( PropertyHandle::ExtractSortKey(skey,Instance(instptr)) ); }

          logical     FillAll     ( itp *instptr )
                      { return( PropertyHandle::Fill(Instance(instptr)));}
          logical     FillData    ( itp *instptr )
                      { return( PropertyHandle::FillData(Instance(instptr)));}

    	  itp	    * Get ( long int indx0=AUTO )
                      { return( (itp *)PropertyHandle::Get(indx0).GetData()); }
          itp       * Get ( Key skey )
                      { return( (itp *)PropertyHandle::Get(skey).GetData()); }

          itp       * GetInst     ( char *extinst)
                      { return( (itp *)PropertyHandle::GetInst(extinst).GetData());}
          itp       * GetInitInstance ( )
                      { return( (itp *)PropertyHandle::GetInitInstance().GetData());}
          PI(itp)     GetBasePI()
                      { return ( *(PI(itp) *)PropertyHandle::GetBaseProperty()); }
          PI(itp)   * GetBaseProperty()
                      { return ( (PI(itp) *)PropertyHandle::GetBaseProperty()); } 

          logical     Initialize  ( itp *instptr )
                      { return( PropertyHandle::Initialize(Instance(instptr)));} 

	  itp	    * Provide  ( long int indx0 ) 
                      { return( (itp *)PropertyHandle::Provide(indx0).GetData()); } 
          itp       * Provide     ( Key skey )  
                      { return( (itp *)PropertyHandle::Provide(skey).GetData()); } 
          itp       * Provide     ( itp *instptr ) 
                      { return( (itp *)PropertyHandle::Provide(Instance(instptr)).GetData()); } 

          logical     SetKey      ( Key key, itp *instptr = NULL) 
                      { return( PropertyHandle::SetKey(key,Instance(instptr)));} 
          logical     SetSortKey  ( Key key, itp *instptr = NULL) 
                      { return( PropertyHandle::SetSortKey(key,Instance(instptr)));} 
          logical     StoreData   ( itp *instptr )  
                      { return( PropertyHandle::StoreData(Instance(instptr)));} 

    	  PI(itp)   & operator=	( PI(itp) const &pienty_c ) 
                      { *(PropertyHandle *)this = *(PropertyHandle *)&pienty_c; return(*this); } 

    	  PI(itp)   & operator--	( int )	 
                      { (*(PropertyHandle *)this)--; return(*this); } 
          PI(itp)   & operator++  ( int ) 
                      { (*(PropertyHandle *)this)++; return(*this); } 
          PI(itp)   & operator--        ( void )  
                      { (*(PropertyHandle *)this)--; return(*this); } 
          PI(itp)   & operator++  ( void ) 
                      { (*(PropertyHandle *)this)++; return(*this); }  

    	  itp	    * operator->  ( void )  
                      { return((itp *)PropertyHandle::Provide(AUTO).GetData()); } 
    	  itp	    & operator*   ( void )   
                      { return(*((itp *)PropertyHandle::Provide(AUTO).GetData())); }
	  itp	    * operator() ( long int indx0=AUTO )
                      { return( (itp *)PropertyHandle::Get(indx0).GetData()); }
          itp       * operator() ( Key skey )   
                      { return( (itp *)PropertyHandle::Get(skey).GetData()); } 

                      tc_ph       ( DBObjectHandle &obhandle, char *extnames, 
                                    PIACC accopt = PI_Read)
                                 : PropertyHandle(obhandle,extnames,accopt) {} 
                      tc_ph       ( DBObjectHandle &obhandle, char *extnames, 
                                    char *keyname, 
                                    PIACC accopt = PI_Read)
                                 : PropertyHandle(obhandle,extnames,keyname,accopt) {} 
                      tc_ph       ( PI(itp) &pi_ref, char *prop_path )
                                 : PropertyHandle(pi_ref,prop_path) {}
                      tc_ph       ( node *nodptr ) 
                                 : PropertyHandle(nodptr) {}
                      tc_ph       ( PI(itp) const &pi_refc ) 
                                 : PropertyHandle(pi_refc) {}
                      tc_ph       ( PI(itp) *pi_ptr ) 
                                 : PropertyHandle(pi_ptr) {}  
		      tc_ph       () 
                                 : PropertyHandle() {}	
};

#pragma pack()
#endif
