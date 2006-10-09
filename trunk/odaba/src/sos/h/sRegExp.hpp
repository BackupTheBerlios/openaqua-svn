/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    RegExp

\brief    


\date     $Date: 2006/03/12 19:20:15,35 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   RegExp_HPP
#define   RegExp_HPP

class     RegExp;

#ifndef   VECTOR_intPair_HPP
#define   VECTOR_intPair_HPP
#include  <sintPair.hpp>
#include  <sVECTOR.h>
#endif
#include  <srpattern.hpp>
class  RegExp
{
protected  :         regex::rpattern                             *pat;                                                       //

public     :
public     :         SOS7ImpExp                  logical IsValid ( ) const;
public     :         SOS7ImpExp                  logical Match (std::string &std_str ) const;
public     : static  SOS7ImpExp                  logical __cdecl MatchExpression (char *reg_expr, std::string &std_str );
public     :         SOS7ImpExp                                          RegExp (char *reg_expr, char *repl_string, logical submatches=NO );
public     :         SOS7ImpExp                                          RegExp (char *reg_expr, logical submatches=NO );
public     :         SOS7ImpExp                  VECTOR(intPair) Replace (std::string &std_str ) const;
public     :         SOS7ImpExp                  VECTOR(intPair) Replace (char *repl_string, std::string &std_str ) const;
public     : static  SOS7ImpExp                  VECTOR(intPair) __cdecl ReplaceExpression (char *reg_expr, char *repl_string, std::string &std_str, logical submatches=NO, logical case_sensitive=YES );
public     :         SOS7ImpExp                  VECTOR(intPair) Search (std::string &std_str ) const;
public     : static  SOS7ImpExp                  VECTOR(intPair) __cdecl SearchExpression (char *reg_expr, std::string &std_str, logical submatches=NO, logical case_sensitive=YES );
public     : static  SOS7ImpExp                  intPair __cdecl TextPositionToPoint (std::string &std_str, int32 posn );
public     :         SOS7ImpExp                                          ~RegExp ( );
};

#endif
