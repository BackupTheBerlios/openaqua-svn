//******************************************************************/
//*  InternalEvent      
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    2003/09/27*/ 
//******************************************************************/

#ifndef   InternalEvent_HPP 
#define   InternalEvent_HPP 

typedef enum 
{

  CA_Leave                         = 1,
  CA_Enter                         = 2,
  CA_Open                          = 4,
  CA_Close                         = 5,
  CA_SaveData                      = 6,
  CA_Push                          = 12,
  CA_Clear                         = 17,
  CA_DeleteData                    = 18,
  CA_EditData                      = 19,
  CA_InsertData                    = 20,
  CA_ResetData                     = 21,
  CA_StoreData                     = 22,
  CA_FillData                      = 23,
  CA_Validate                      = 24,
  CA_NextData                      = 25,
  CA_PreviousData                  = 27,
  CA_HelpIndex                     = 28,
  CA_SelectData                    = 29,
  CA_Modify                        = 30,
  CA_Click                         = 31,
  CA_KeyInput                      = 32,
  CA_Repaint                       = 33,

} InternalEvent;
#endif
