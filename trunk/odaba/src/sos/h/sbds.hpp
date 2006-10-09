/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    bds

\brief    


\date     $Date: 2006/03/12 19:20:25,37 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   bds_HPP
#define   bds_HPP

class     bds;

#include  <sbds.hpp>
#pragma pack(8)

class  bds
{
protected  :         char                                        *bdsarea;                                                   //
protected  :         uint16                                       bdslen;                                                    //
protected  :         uint16                                       bdsmax;                                                    //

public     :
                     char                                        *get_bdsarea() { return(bdsarea); }
                     uint16                                       get_bdslen() { return(bdslen); }
                     uint16                                       get_bdsmax() { return(bdsmax); }
public     :         SOS7ImpExp                  logical Append (char *string );
public     :         SOS7ImpExp                  logical Delete (uint16 pos, size_t len );
public     :         SOS7ImpExp                  int16 FindBalancedPar (uint16 curpos, logical bwd=NO );
public     :         SOS7ImpExp                  char *GetArea ( );
public     :         SOS7ImpExp                  uint16 GetFirstChar (uint16 curpos );
public     :         SOS7ImpExp                  int16 GetLineCount (uint16 curpos );
public     :         SOS7ImpExp                  uint16 GetLineLength (uint16 curpos );
public     :         SOS7ImpExp                  uint16 GetLinePosition (uint16 curpos );
public     :         SOS7ImpExp                  logical Insert (uint16 pos, char ichar, int16 num );
public     :         SOS7ImpExp                  logical Insert (uint16 pos, char *text );
public     :         SOS7ImpExp                                          bds ( );
public     :         SOS7ImpExp                                          bds (char *datarea, uint16 clen=UNDEF, uint16 mlen=UNDEF );
public     :         SOS7ImpExp                  char *bdsagt ( );
public     :         SOS7ImpExp                  logical bdsaloc (size_t len );
public     :         SOS7ImpExp                  char *bdsast (char *datarea );
public     :         SOS7ImpExp                  char *bdsend ( );
public     :         SOS7ImpExp                  void bdsfree ( );
public     :         SOS7ImpExp                  uint16 bdslgt ( );
public     :         SOS7ImpExp                  uint16 bdslst (size_t len );
public     :         SOS7ImpExp                  uint16 bdsmgt ( );
public     :         SOS7ImpExp                  uint16 bdsmst (uint16 mlen=UNDEF );
public     :         SOS7ImpExp                  bds &operator+ (bds &bdsptr );
public     :         SOS7ImpExp                  bds &operator+ (char *string );
public     :         SOS7ImpExp                  bds operator+= (bds &bdsptr );
public     :         SOS7ImpExp                  bds operator+= (char *string ){

  return(*this+string);

}

};

#pragma pack()
#endif
