/* RTTI-Implementation-Generator
   *****************************
   Parameters:
   GRTTI_CLS  <class>               e.g. Test
   GRTTI_NAME "<identifier>"        e.g. "SOS.Test"
   GRTTI_BASEx <x-th base class>    e.g. TestBase
   (first: x=1)
   GRTTI_CREATE
    define to enable dynamic creation
     class must have a default constructor

   GRTTI_REPLICATE
    define to enable dynamic replication
     class must have a copy constructor, i.e.
     one that gets a parameter of type const GRTTI_CLS&
*/

#ifdef GRTTI_CLS
#define GRTTI_ADD(s1,s2) s1 ## s2

static CRTTI GRTTI_ADD(rtti_base_,GRTTI_CLS)[] = 
  { 
#ifdef GRTTI_BASE1
  STATIC_CLASS_INFO(GRTTI_BASE1),
#endif
#ifdef GRTTI_BASE2
  STATIC_CLASS_INFO(GRTTI_BASE2),
#endif
#ifdef GRTTI_BASE3
  STATIC_CLASS_INFO(GRTTI_BASE3),
#endif
  0 };

#ifdef GRTTI_CREATE
void* GRTTI_CLS::RTTI_Create()
{
  return new GRTTI_CLS;
}
#endif

#ifdef GRTTI_REPLICATE
void* GRTTI_CLS::RTTI_Replicate( const void* p )
{
  return new GRTTI_CLS( *(const GRTTI_CLS*) p );
}
#endif

void* GRTTI_CLS::RTTI_StaticCast( void* ths, CRTTI c )
{
  return ((GRTTI_CLS*) ths)->RTTI_Cast( c );
}

void* GRTTI_CLS::RTTI_Cast( CRTTI c )
{
  if( c == &RTTI_classInfo ) return this;
  void* p;
  #ifdef GRTTI_BASE1
  if( p= GRTTI_BASE1::RTTI_Cast(c) ) return p; 
  #endif
  #ifdef GRTTI_BASE2
  if( p= GRTTI_BASE2::RTTI_Cast(c) ) return p; 
  #endif
  #ifdef GRTTI_BASE3
  if( p= GRTTI_BASE3::RTTI_Cast(c) ) return p; 
  #endif
  return 0;
}

const RTTIClassInfo
    GRTTI_CLS::RTTI_classInfo( 
      GRTTI_NAME, 
      GRTTI_ADD(rtti_base_,GRTTI_CLS),
#ifdef GRTTI_CREATE
      GRTTI_CLS::RTTI_Create,
#else
      0,
#endif
#ifdef GRTTI_REPLICATE
      GRTTI_CLS::RTTI_Replicate,
#else
      0,
#endif
      GRTTI_CLS::RTTI_StaticCast );

#undef GRTTI_ADD
#undef GRTTI_CLS
#undef GRTTI_NAME
#undef GRTTI_BASE1
#undef GRTTI_BASE2
#undef GRTTI_BASE3
#undef GRTTI_CREATE
#undef GRTTI_REPLICATE
#endif