/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:32:37,32}|(REF)
\class    AH

\brief    


\date     $Date: 2006/03/13 21:32:39,28 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   AH_HPP
#define   AH_HPP

class     AH;

class  AH :public ActivityHandler<void,void>
{
public     :         const char                                  *name;                                                      

public     :
public     :                                                             AH (const char *_namec );
};

#endif
