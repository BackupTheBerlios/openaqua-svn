/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OStringList

\brief    


\date     $Date: 2006/03/13 21:34:42,59 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OStringList_HPP
#define   OStringList_HPP

class     OStringList;

#define  EMPTY_STRING                              " --empty-- "
class     PropertyHandle;
class  OStringList :public QStringList
{

public     :
public     :                                     logical Fill (PropertyHandle *prophdl );
public     :                                                             OStringList ( );
public     :                                     void ProvideEmptyString ( );
public     : virtual                                                     ~OStringList ( );
};

#endif
