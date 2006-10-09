#ifndef __coamakros_h__
#define __coamakros_h__

#define COAMAKRO_DEKLARE_SINGLETONMETHODS(CLASSNAME)  public: \
                                                 static CLASSNAME* getInstance(); \
                                                 static void stopInstance(); \
                                                 static bool isInstance();\
                                              private: \
                                                static CLASSNAME  *INSTANCE; \
                                                CLASSNAME ();                \
                                                virtual ~CLASSNAME ();



#define  COAMAKRO_DEFINE_SINGLETONTHREADMETHODS(CLASSNAME) \
   static QMutex SINGLTON_MUTEX;                           \
   CLASSNAME* CLASSNAME::INSTANCE =  0;                    \
   void CLASSNAME::stopInstance()                          \
   {                                                       \
      SINGLTON_MUTEX.lock();                               \
      if (INSTANCE != 0) {                                 \
         INSTANCE->quit();                                 \
         INSTANCE->wait();                                 \
         delete INSTANCE;                                  \
         INSTANCE=0;                                       \
      }                                                    \
      SINGLTON_MUTEX.unlock();                             \
   }                                                       \
   CLASSNAME* CLASSNAME::getInstance()                     \
   {                                                       \
      if (INSTANCE == 0) {                                 \
         SINGLTON_MUTEX.lock();                            \
         if (INSTANCE == 0) {                              \
            INSTANCE  = new CLASSNAME();                   \
            INSTANCE->start();                             \
         }                                                 \
         SINGLTON_MUTEX.unlock();                          \
      }                                                    \
      return INSTANCE;                                     \
   }                                                       \
   bool CLASSNAME::isInstance()                            \
   {                                                       \
      if ( INSTANCE == 0 ) {                               \
         return false;                                     \
      } else {                                             \
         return true;                                      \
      }                                                    \
   }


#define  COAMAKRO_DEFINE_SINGLETONMETHODS(CLASSNAME)       \
   static QMutex SINGLTON_MUTEX;                           \
   CLASSNAME* CLASSNAME::INSTANCE =  0;                    \
   void CLASSNAME::stopInstance()                          \
   {                                                       \
      if (INSTANCE != 0) {                                 \
         delete INSTANCE;                                  \
         INSTANCE=0;                                       \
      }                                                    \
   }                                                       \
   CLASSNAME* CLASSNAME::getInstance()                     \
   {                                                       \
      if (INSTANCE == 0) {                                 \
         SINGLTON_MUTEX.lock();                            \
         if (INSTANCE == 0) {                              \
            INSTANCE  = new CLASSNAME();                   \
         }                                                 \
         SINGLTON_MUTEX.unlock();                          \
      }                                                    \
      return INSTANCE;                                     \
   }                                                       \
   bool CLASSNAME::isInstance()                            \
   {                                                       \
      if ( INSTANCE == 0 ) {                               \
         return false;                                     \
      } else {                                             \
         return true;                                      \
      }                                                    \
   }




#define COAMAKRO_NO_COPYCONSTRUCTOR(CLASSNAME) private: CLASSNAME(CLASSNAME const& );
#define COAMAKRO_NO_COMPARE(CLASSNAME)         private: void operator=(CLASSNAME const&);
#define COAMAKRO_NO_DEFAULT(CLASSNAME)         private: CLASSNAME ();

#endif //__coamakros_h__

