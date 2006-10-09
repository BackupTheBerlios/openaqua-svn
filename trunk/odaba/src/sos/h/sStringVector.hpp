/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    StringVector



\date     $Date: 2006/03/12 19:20:18,45 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   StringVector_HPP
#define   StringVector_HPP

class     StringVector;

#ifndef   VECTOR_std_string_HPP
#define   VECTOR_std_string_HPP
#include  <sVECTOR.h>
#endif
class  StringVector :public VECTOR(std_string)
{

public     :
};

#endif
