#include <sActivityManager.hpp>

#define _COMMA_(A,B) A,B

#define __ADD_(A,B,C,D,E) A##B##C##D##E
#define _ADD_(A,B,C,D,E) __ADD_(A,B,C,D,E)

#define __ADD2_(A,B) A##B
#define _ADD2_(A,B) __ADD2_(A,B)

#define DCL_ACTIVITY_CLASS(N) \
  typedef N ThisClass

#define ACTIVITY_MANAGER(A) \
  ActivityManager<ThisClass,A>

#define DCL_ACTIVITY(N) \
  ACTIVITY_MANAGER(void)& _ADD2_(A,N)() \
  { return _ADD2_(a,N); } \
  logical N() \
  { return ((_ADD2_(am,N)&)_ADD2_(A,N)()).Execute( this, 0, \
    ActivityVoidFunctor<void,void>( this, _ADD2_(sdispdo,N) ) ); } \
  private: class _ADD2_(am,N) : \
    public ACTIVITY_MANAGER(void) { \
      public: ACTIVITY_MANAGER(void)::Execute; }; \
  private: static void _ADD2_(sdispdo,N)(void* t,void* ,void*) \
  { ((ThisClass*)t)->_ADD2_(do,N)(); } \
  private: ACTIVITY_MANAGER(void) _ADD2_(a,N);

#define DCL_ACTIVITY_A(N,P) \
  ACTIVITY_MANAGER(P)& _ADD2_(A,N)() \
  { return _ADD2_(a,N); } \
  logical N(P& p) \
  { return ((_ADD2_(am,N)&)_ADD2_(A,N)()).Execute( this, (void*)&p, \
    ActivityVoidFunctor<void,void>( this, _ADD2_(sdispdo,N) ) ); } \
  private: class _ADD2_(am,N) : \
    public ACTIVITY_MANAGER(void) { \
      public: ACTIVITY_MANAGER(void)::Execute; }; \
  private: static void _ADD2_(sdispdo,N)(void* t,void* ,void* p) \
  { ((ThisClass*)t)->_ADD2_(do,N)(*(P*)p); } \
  private: ACTIVITY_MANAGER(P) _ADD2_(a,N);

#define ACTIVITY_MEMBER(C,M) _ADD_(_disp_,C,_,M,_)

#define DCL_ACTIVITY_MEMBER_P(AF,C,M,I,A,R,RET,MP) \
  class ACTIVITY_MEMBER(C,M) : public AF<I,A> \
  { \
  public: \
    class _disp_Dispatcher_ : public C \
    { \
    public: \
      static R _sdispCaller_( \
        void* _this, I* i, A* a ) \
      { \
        RET ((_disp_Dispatcher_*) _this)->M(MP); \
      } \
    }; \
    ACTIVITY_MEMBER(C,M)( C* _this ) : \
      AF<I,A>( _this, _disp_Dispatcher_::_sdispCaller_ ) \
      {}\
  }

#define DCL_ACTIVITY_VOID_MEMBER(C,M,I,A) \
DCL_ACTIVITY_MEMBER_P(ActivityVoidFunctor,C,M,I,A,void,,)

#define DCL_ACTIVITY_LOGICAL_MEMBER(C,M,I,A) \
DCL_ACTIVITY_MEMBER_P(ActivityLogicalFunctor,C,M,I,A,logical,return,)

#define DCL_ACTIVITY_VOID_MEMBER_IA(C,M,I,A) \
DCL_ACTIVITY_MEMBER_P(ActivityVoidFunctor,C,M,I,A,void,,_COMMA_(i,*a))

#define DCL_ACTIVITY_VOID_MEMBER_A(C,M,I,A) \
DCL_ACTIVITY_MEMBER_P(ActivityVoidFunctor,C,M,I,A,void,,*a)

#define DCL_ACTIVITY_VOID_MEMBER_I(C,M,I,A) \
DCL_ACTIVITY_MEMBER_P(ActivityVoidFunctor,C,M,I,A,void,,i)