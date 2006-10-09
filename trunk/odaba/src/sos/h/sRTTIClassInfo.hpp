/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    RTTIClassInfo

\brief    


\date     $Date: 2006/03/12 19:20:14,23 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   RTTIClassInfo_HPP
#define   RTTIClassInfo_HPP

class     RTTIClassInfo;

#pragma pack(8)

class  RTTIClassInfo
{
protected  :         char                                        *className;                                                 
protected  :         CRTTI                                       *baseClasses;                                               
protected  :         typedef void                                *(*Tcreator)();                                             
protected  :         Tcreator                                     creator;                                                   
protected  :         typedef void                                *(*TstaticCast)(void*,CRTTI);                               
protected  :         TstaticCast                                  staticCast;                                                
protected  :         typedef void*                                (*Treplicator)( const void* );                             
protected  :         Treplicator                                  replicator;                                                

public     :
public     :         SOS7ImpExp                  void *Create (CRTTI RTTI_castAs ) const;
public     : static  SOS7ImpExp                  CRTTI __cdecl FindClass (const char *cszName );
public     :         SOS7ImpExp                  logical Inherits (CRTTI vCRTTI ) const;
public     :         SOS7ImpExp                                          RTTIClassInfo (char *names, CRTTI *pCRTTI, Tcreator vTcreator, Treplicator vTreplicator, TstaticCast vTstaticCast );
public     :         SOS7ImpExp                  void *Replicate (CRTTI RTTI_castAs, const void *cpvoid ) const;
public     : static                              void __cdecl setup ( );
public     :                                     logical CanCreate ( ) const{

return creator != 0;

}

public     :                                     logical CanReplicate ( ) const{

return replicator != 0;

}

public     :                                     const char *ClassName ( ) const{

  return (className);

}

public     :         SOS7ImpExp                  void *Create ( ) const{

  if( !creator ) 
    return 0;
  return (*creator)();

}

public     :         SOS7ImpExp                  void *Replicate (const void *cpvoid ) const{

if( !replicator ) return 0;
return (*replicator)( cpvoid );

}

public     :         SOS7ImpExp                  void *StaticCast (CRTTI vCRTTI, void *entptr ) const{

  return entptr ? staticCast( entptr, vCRTTI ) : 0;

}

};

#pragma pack()
#endif
