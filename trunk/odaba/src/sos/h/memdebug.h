// this file includes the evil memdumping methods
// it will slow down and cause the disk to fill
//#define _DEBUG

#ifdef _MEMORY_DEBUG
 barto hatte probleme damit
  #define _CRTDBG_MAP_ALLOC
  #include <CRTDBG.H>

  #define DEBUG_CLIENTBLOCK   new( _NORMAL_BLOCK, __FILE__, __LINE__)
  #define new DEBUG_CLIENTBLOCK


  #define  SET_CRT_DEBUG_FIELD(a)   _CrtSetDbgFlag((a) | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))

 // Send all reports to STDOUT, since this example is a console app
  #define memdbg_checkpoint \
	_CrtMemState checkPt; \
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);\
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);\
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);\
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);\
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);\
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);\
	SET_CRT_DEBUG_FIELD( _CRTDBG_LEAK_CHECK_DF | _CRTDBG_DELAY_FREE_MEM_DF);\
	checkPt = _Crt MemState();

#define memdbg_dump \
	_CrtMemDumpA llObjectsSince( &checkPt ); \
	_CrtMemCheckpoint( &checkPt ); \
	_CrtMemDumpStatistics( &checkPt ); \
	_CrtCheckMemory( ); \

#else
#define memdbg_checkpoint
#define memdbg_dump
#endif
