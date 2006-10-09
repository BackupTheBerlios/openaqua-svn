/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    BNF_cpp

\brief    


\date     $Date: 2006/03/12 19:19:33,40 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   BNF_cpp_HPP
#define   BNF_cpp_HPP

class     BNF_cpp;

#include  <sBNFParser.hpp>
class  BNF_cpp :public BNFParser
{

public     :
public     :         SOS7ImpExp                                          BNF_cpp (BNFParser *bs_parent=NULL, char *trace_path=NULL );
public     :         SOS7ImpExp                                          ~BNF_cpp ( );
};

#endif
