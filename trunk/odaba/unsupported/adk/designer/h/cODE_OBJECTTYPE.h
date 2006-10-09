//******************************************************************/
//*  ODE_OBJECTTYPE     
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    27.06.2005*/ 
//******************************************************************/

#ifndef   ODE_OBJECTTYPE_HPP 
#define   ODE_OBJECTTYPE_HPP 

typedef enum 
{

  OT_undef                         = 0,
  OT_Class                         = 1,
  OT_Function                      = 2,
  OT_Implementation                = 3,
  OT_BaseClass                     = 4,
  OT_Attribute                     = 5,
  OT_Reference                     = 6,
  OT_Relationship                  = 7,
  OT_Parameter                     = 8,
  OT_LocalVariable                 = 9,

} ODE_OBJECTTYPE;
#endif
