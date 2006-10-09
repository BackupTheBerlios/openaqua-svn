/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    TListBoxField



\date     $Date: 2006/04/28 15:21:52,06 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TListBoxField_HPP
#define   TListBoxField_HPP

class     TListBoxField;

class     OComboBox;
class     OComboListBox;
class     OListView;
class     OSListBox;
#include  <sTField.hpp>
#pragma pack(4)

class  TListBoxField :public TField
{

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateControl (TControl **tc_ptr );
public     : virtual                                logical DoCreate ( );
public     : virtual                                logical DoCreated ( );
public     :                                        OSListBox *Style ( ) const;
public     :                                             TListBoxField ( );
};

#pragma pack()
#endif
