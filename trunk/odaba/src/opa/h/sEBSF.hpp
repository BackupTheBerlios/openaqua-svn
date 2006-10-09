/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EBSF

\brief    


\date     $Date: 2006/03/12 19:13:15,90 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EBSF_HPP
#define   EBSF_HPP

class     EBSF;

class     eb_SubBase;
#pragma pack(8)

class  EBSF
{
protected  :         int32                                        ebsfnxt;                                                   
protected  :         int16                                        ebsfcnt;                                                   
protected  :         int16                                        ebsfres;                                                   
protected  :         ofe                                          ebsfofe;                                                   

public     :
public     : static                              logical __cdecl ebsfadd (eb_SubBase *odbptr, int32 ebsfpos, int32 odblen, uint64 odbpos, logical real=NO );
public     : static                              logical __cdecl ebsfchk (eb_SubBase *odbptr, int32 ebsfpos, uint64 odbpos, int32 odblen, logical real=NO );
public     : static                              int32 __cdecl ebsfget (eb_SubBase *odbptr, int32 ebsfpos, int32 odblen, char stype, logical real=NO );
};

#pragma pack()
#endif
