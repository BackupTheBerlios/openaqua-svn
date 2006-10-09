/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    NumFraction

\brief    


\date     $Date: 2006/03/12 19:20:07,12 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   NumFraction_HPP
#define   NumFraction_HPP

class     NumFraction;

#define  BLANKVAL                                  
#include  <sNumFraction.hpp>
#pragma pack(8)

class  NumFraction
{
protected  :         int32                                        den;                                                       
protected  :         int32                                        num;                                                       

public     :
public     :         SOS7ImpExp                  int8 GetDenominator ( ) const;
public     : static                              int32 __cdecl GetGGT (int32 val1, int32 val2 );
public     :                                     int64 GetGGT64 (int64 i64_val1, int64 i64_val2 );
public     :         SOS7ImpExp                  int32 GetNumerator ( );
public     :         SOS7ImpExp                  logical IsValid ( ) const;
public     :                                     void Normalize ( );
public     :         SOS7ImpExp                                          NumFraction (int32 numerator, int32 denominator );
public     :         SOS7ImpExp                                          NumFraction ( );
public     :         SOS7ImpExp                                          NumFraction (double dblval );
public     :         SOS7ImpExp                                          NumFraction (const NumFraction &fraction_ref );
public     :         SOS7ImpExp                                          NumFraction (int64 i64_val1, int64 i64_val2 );
public     :         SOS7ImpExp                  BLANKVAL operator double ( ) const;
public     :         SOS7ImpExp                  BLANKVAL operator long ( ) const;
public     :         SOS7ImpExp                  logical operator!= (const NumFraction &fraction_ref ) const;
public     :         SOS7ImpExp                  NumFraction operator* (const NumFraction &fraction_ref );
public     :         SOS7ImpExp                  NumFraction &operator*= (const NumFraction &fraction_ref );
public     :         SOS7ImpExp                  NumFraction operator+ (const NumFraction &fraction_ref );
public     :         SOS7ImpExp                  NumFraction &operator+= (const NumFraction &fraction_ref );
public     :         SOS7ImpExp                  NumFraction operator- (const NumFraction &fraction_ref );
public     :         SOS7ImpExp                  NumFraction &operator-= (const NumFraction &fraction_ref );
public     :         SOS7ImpExp                  NumFraction operator/ (const NumFraction &fraction_ref );
public     :         SOS7ImpExp                  NumFraction &operator/= (const NumFraction &fraction_ref );
public     :         SOS7ImpExp                  logical operator< (const NumFraction &fraction_ref ) const;
public     :         SOS7ImpExp                  logical operator<= (const NumFraction &fraction_ref ) const;
public     :         SOS7ImpExp                  NumFraction &operator= (const NumFraction &fraction_ref );
public     :         SOS7ImpExp                  logical operator== (const NumFraction &fraction_ref ) const;
public     :         SOS7ImpExp                  logical operator> (const NumFraction &fraction_ref ) const;
public     :         SOS7ImpExp                  logical operator>= (const NumFraction &fraction_ref ) const;
public     :         SOS7ImpExp                                          ~NumFraction ( );
};

#pragma pack()
#endif
