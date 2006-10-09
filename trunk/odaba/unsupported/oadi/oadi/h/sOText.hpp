/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OText



\date     $Date: 2006/04/28 14:10:42,18 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OText_HPP
#define   OText_HPP

class     OText;

class     OText;
class     PropertyHandle;
#include  <sDString.hpp>
#include  <sOPersistent.hpp>
#pragma pack(4)

class  OText :public OPersistent
{
protected  :         char                                        *title;                                                     
protected  :         char                                        *tooltip;                                                   
protected  :         char                                        *long_text;                                                 

public     :
                     char                                        *get_title() { return(title); }
                     char                                        *get_tooltip() { return(tooltip); }
                     char                                        *get_long_text() { return(long_text); }
public     :                                        char *GetHelp ( );
public     :                                        char *GetTitle ( );
public     :                                        char *GetTooltip ( );
public     :                                             OText ( );
public     :                                             OText (OPersistent bcOPersistent, char *title, char *tooltip, char *long_text );
public     :                                        logical Read (PropertyHandle *ph );
public     :                                        void Reset ( );
public     :                                        void SetupText (OText *pOText );
public     : virtual                                     ~OText ( );
};

#pragma pack()
#endif
