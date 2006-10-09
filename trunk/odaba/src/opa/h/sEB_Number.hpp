/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EB_Number

\brief    Entry number
          A  database entry number is a  64-Bit number, which contains the entry
          number  in 48  low order  bytes. 15  high order bytes are reserved for
          database  and mainbase numbers. The top high  order byte is a flag and
          reserved for internal use. 
          0xFFFF0000  in the 32 high order bytes indicates an empty entry number
          regardless on the remaining part of the number.

\date     $Date: 2006/03/12 19:13:17,54 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EB_Number_HPP
#define   EB_Number_HPP

class     EB_Number;

#include  <sEB_Number.hpp>
#pragma pack(1)

class  EB_Number
{
protected  :         uint64                                       ebsnum;                                                    //

public     :
                     uint64                                       get_ebsnum() { return(ebsnum); }
public     :         opa7ImpExp                                          EB_Number (uint64 ebsnumber );
public     :                                     EB_Number FromPIF (logical pif );
public     :                                     int16 GetLevel (logical largedb=NO );
public     :                                     int64 GetLockPos ( );
public     :         opa7ImpExp                  logical IsEmpty (logical pif_opta=AUTO );
public     :                                     uint16 Position (int16 ebilevel );
public     :                                     void SetPosition (int16 ebilevel, int32 position );
public     :                                     EB_Number ToPIF (logical pif );
public     :                                     EB_Number operator++ ( );
public     :                                     logical operator<= (EB_Number entnr );
public     :                                     logical operator<= (uint64 entnr_val );
public     :         opa7ImpExp                  EB_Number operator= (uint64 entnr_val );
public     :         opa7ImpExp                  EB_Number operator= (EB_Number entnr );
public     :         opa7ImpExp                                          EB_Number ( )                     :   ebsnum(0)
{



}

public     :                                     int16 GetMBIdent ( ){

  return( (int16)(ebsnum<<1)>>49 );

}

public     :         opa7ImpExp                  logical operator!= (EB_Number entnr ){

  return( ebsnum != entnr.get_ebsnum() );

}

public     :         opa7ImpExp                  logical operator!= (uint64 entnr_val ){

  return( ebsnum != entnr_val );

}

public     :                                     EB_Number operator+= (uint64 entnr_val ){

  return ( ebsnum += entnr_val );


}

public     :                                     logical operator< (EB_Number entnr ){

  return( ebsnum < entnr.get_ebsnum() );

}

public     :                                     logical operator< (uint64 entnr_val ){

  return( ebsnum < entnr_val );

}

public     :         opa7ImpExp                  logical operator== (EB_Number entnr ){

  return( ebsnum == entnr.get_ebsnum() );

}

public     :         opa7ImpExp                  logical operator== (uint64 entnr_val ){

  return( ebsnum == entnr_val );

}

public     :                                     logical operator> (EB_Number entnr ){

  return( ebsnum > entnr.get_ebsnum() );

}

public     :                                     logical operator> (uint64 entnr_val ){

  return( ebsnum > entnr_val );

}

};

#pragma pack()
#endif
