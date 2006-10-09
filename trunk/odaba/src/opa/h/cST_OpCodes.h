/******************************** Enumeration Declaration *****************************************************/
/**
\class ST_OpCodes

\brief 

\date $Date: 2006/06/12 13:33:57,21 $
\dbsource l:\oql\oql.dev - ODABA Version 9.0

 */
/*************************************************************************************/
#ifndef   ST_OpCodes_HPP
#define   ST_OpCodes_HPP

enum ST_OpCodes
{
  ST_and                          = 1,
  ST_assign                       = 2,
  ST_assign_ref                   = 6,
  ST_binop                        = 7,
  ST_block                        = 8,
  ST_bool                         = 9,
  ST_const                        = 10,
  ST_db_output                    = 11,
  ST_decrement                    = 72,
  ST_divi                         = 12,
  ST_divi_assign                  = 13,
  ST_else                         = 3,
  ST_end                          = 4,
  ST_equal                        = 14,
  ST_file_output                  = 15,
  ST_greater                      = 16,
  ST_greaterEqual                 = 17,
  ST_increment                    = 73,
  ST_lower                        = 18,
  ST_lowerEqual                   = 19,
  ST_minus                        = 20,
  ST_minus_assign                 = 21,
  ST_mult_assign                  = 22,
  ST_multi                        = 28,
  ST_not                          = 25,
  ST_or                           = 23,
  ST_plus                         = 31,
  ST_plus_assign                  = 24,
  ST_power                        = 27,
  ST_remainder                    = 30,
  ST_set_create                   = 48,
  ST_set_distinct                 = 52,
  ST_set_from                     = 75,
  ST_set_group_by                 = 57,
  ST_set_intersect                = 46,
  ST_set_join                     = 47,
  ST_set_locate                   = 70,
  ST_set_minus                    = 45,
  ST_set_order_by                 = 50,
  ST_set_output                   = 71,
  ST_set_select                   = 51,
  ST_set_union                    = 44,
  ST_set_use                      = 49,
  ST_set_where                    = 58,
  ST_shift_left                   = 77,
  ST_shift_right                  = 76,
  ST_typecast                     = 74,
  ST_undefined                    = 0,
  ST_unequal                      = 38,
  ST_uniop                        = 62,
  ST_xor                          = 41,
};

#endif
