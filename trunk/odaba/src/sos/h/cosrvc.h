#include <process.h>

#include <sOService.hpp>

OService *OService::service_item = NULL;
logical   OService::servicesRunning= NO;

// SERVICE MAIN ROUTINE
void WINAPI ServiceMain(DWORD argc, char**argv)
{
  OService::serviceMain( argc, argv );
}
