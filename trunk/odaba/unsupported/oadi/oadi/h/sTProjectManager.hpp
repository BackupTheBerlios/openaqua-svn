/********************************* Class Declaration ***************************/
/**
\package  OADI - 
\class    TProjectManager

\brief    


\date     $Date: 2006/07/09 13:33:53,50 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TProjectManager_HPP
#define   TProjectManager_HPP

class     TProjectManager;

#include  <sGSRT.h>
class     TAction;
#ifndef   DLL_TProject_HPP
#define   DLL_TProject_HPP
#include  <sTProject.hpp>
#include  <sDLL.h>
#endif
#ifndef   VECTOR_std_string_HPP
#define   VECTOR_std_string_HPP
#include  <sVECTOR.h>
#endif
class     OApplicationO;
class     ODesktop;
class     OGUIErrorHandle;
class     OProject;
class     OResource;
class     OSplash;
class     ResourceCache;
class     TProjectManager;
#include  <sPropertyHandle.hpp>
#pragma pack(4)

class  TProjectManager
{
protected  :         void                                        *xx_b;                                                      // 
protected  :         OApplicationO                               *app;                                                       // 
protected  :         ODesktop                                    *desktop;                                                   // 
public     : static  TProjectManager                             *TPM;                                                       // 
protected  :         UtilityHandle                               *ucb;                                                       // 
protected  :         OGUIErrorHandle                             *errhdl;                                                    // 
protected  :         DLL(TProject)                                projects;                                                  // 
protected  :         GSRT(TAction)                               *std_actions;                                               // 
protected  :         PropertyHandle                               dict_pi;                                                   // 
protected  :         int32                                        dict_pi_reserved;                                          // 
protected  :         ResourceCache                               *cache;                                                     // 
protected  :         ResourceCache                               *design_cache;                                              // 
protected  :         OSplash                                     *splash;                                                    // 

public     :
                     OApplicationO                               *get_app() { return(app); }
                     DLL(TProject)                               &get_projects() { return(projects); }
                     GSRT(TAction)                               *get_std_actions() { return(std_actions); }
                     PropertyHandle                              &get_dict_pi() { return(dict_pi); }
                     int32                                        get_dict_pi_reserved() { return(dict_pi_reserved); }
                     ResourceCache                               *get_cache() { return(cache); }
                     ResourceCache                               *get_design_cache() { return(design_cache); }
                     OSplash                                     *get_splash() { return(splash); }
public     :                                        void Beep ( );
public     :                                        ResourceCache *Cache ( );
public     :                                        ResourceCache *Cache (PropertyHandle *ph );
public     :                                        ResourceCache *Cache (int8 cache_id );
public     :                  OADIImpExp            logical Create (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow );
public     :                  OADIImpExp            logical Create (int argc, char **argv );
public     :                                        void CreateErrHandle (DBObjectHandle &obhandle );
public     :                                        OProject *CreateProjectFromCmdLine (ODesktop *pODesktop, int iCount, char **ppArguments );
public     :                                        OProject *CreateProjectFromUtilityHandle (ODesktop *pODesktop, UtilityHandle *pUtilityHandle );
public     :                                        ODesktop *Desktop ( ) const;
public     :                                        OResource *GetResource (int id );
public     :                                        OResource *GetResource (PropertyHandle *ph, char *name );
public     :                                        void InitStandardActionTable ( );
public     :                                        logical InvalidateCache (int8 cache_id );
public     :                                        logical OpenDAT ( );
public     :                                        logical OpenProject ( );
public     :                                        void ReleaseDictPH ( );
public     :                                        PropertyHandle *ReserveDictPH (int32 res_id );
public     :                  OADIImpExp            logical Run ( );
public     :                                        logical SetErrHandle ( );
public     :                                        void SetErrorObject (DBObjectHandle &obhandle );
public     :                                        logical SetMainWindow (OProject *pOProject );
public     :                                        void SetupStandardActions ( );
public     :                                             TProjectManager ( );
public     :                                        UtilityHandle *UCB ( );
public     :                                             ~TProjectManager ( );
};

#pragma pack()
#endif
