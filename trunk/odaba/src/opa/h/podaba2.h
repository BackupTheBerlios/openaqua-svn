/*******************************************************************/
/*			     S D B - Internal Error Macros         */
/*         Project Includes - General Defines and Error Class      */
/*   Version 0.1                                          24.06.97 */
/*******************************************************************/ 

#ifndef   PODABA2_H
#define   PODABA2_H

#define   SDBERR(x)           { SDBError().SetError( x,OBJ_ID,MOD_ID);                                          \
		            	        goto on_error;              }

#define   SDBERR1(x,p1)       { SDBError().SetErrorWithVariables( x,OBJ_ID,MOD_ID,p1,NULL,NULL,NULL,NULL,NULL); \
		            	        goto on_error;              }

#define   SDBERR2(x,p1,p2)    { SDBError().SetErrorWithVariables( x,OBJ_ID,MOD_ID,p1,p2,NULL,NULL,NULL,NULL);   \
		            	        goto on_error;              }

#define   SDBERR3(x,p1,p2,p3) { SDBError().SetErrorWithVariables( x,OBJ_ID,MOD_ID,p1,p2,p3,NULL,NULL,NULL);     \
		            	        goto on_error;              }

#define   SDBIERR(x)          { SDBError().SetError( x,NULL,NULL);	                                            \
		            	        goto on_error;              }

#define   SDBCERR             { if ( SDBError().CheckError() )	                                                \
                                goto on_error;              }

#define   SDBCTXCERR          { if ( CTXError().CheckError() )                                                  \
                                { SDBError().SetError(CONTEXT_ERROR,OBJ_ID,MOD_ID);                             \
                                  goto on_error;  }         }

#define   SDBCTXCERROR        { if ( CTXError().CheckError() )                                                  \
                                  SDBError().SetError(CONTEXT_ERROR,OBJ_ID,MOD_ID);                             \
                                goto on_error;              }

#define   SDBOQLCERR          { if ( OQLError().CheckError() )                                                  \
                                { SDBError().SetError(OQL_ERROR,OBJ_ID,MOD_ID);                                 \
                                  goto on_error;  }         }

#define   SDBSET(x)           { SDBError().SetError( x,OBJ_ID,MOD_ID); }

#define   SDBISET(x)          { SDBError().SetError( x,NULL,NULL);     }

#define   SDBRESET            { SDBError().ResetError();               }

#define   SDBDISPLAY_ERROR    { SDBError().DisplayMessage();           }

#define   SDB_DSPL_ON  { SDBError().tdspl = YES; } 
#define   SDB_DSPL_OFF { SDBError().tdspl = NO;  } 
#define   SDB_LIST_ON  { SDBError().tlist = YES; }
#define   SDB_LIST_OFF { SDBError().tlist = NO;  }
#define   SDB_HIER_ON  { SDBError().thier = YES; } 
#define   SDB_HIER_OFF { SDBError().thier = NO;  }

#ifdef    _TST_
#undef    BEGINSEQ
#undef    RECOVER 
#undef    ENDSEQ  

#define   BEGINSEQ       static void *tptr=NULL; { SDBError().TraceFunction(&tptr,MOD_ID,OBJ_ID,'B');
#define   RECOVER        } goto on_end; on_error: { SDBError().TraceFunction(&tptr,MOD_ID,OBJ_ID,'R');
#define   ENDSEQ         } on_end: SDBError().TraceFunction(&tptr,MOD_ID,OBJ_ID,'E');   
#endif // _TST_

#define   STARTSEQ       static void *tptr=NULL; \
                         {                       \
                           SDBError().tlist = YES;   \
                           SDBError().TraceFunction(&tptr,MOD_ID,OBJ_ID,'B'); \
                           SDBError().tlist = NO;    \
                         }
#define   STOPSEQ        {                       \
                           SDBError().tlist = YES;   \
                           SDBError().TraceFunction(&tptr,MOD_ID,OBJ_ID,'E'); \
                           SDBError().tlist = NO;    \
                         }   

 /*******************************************************************/ 

#define   SDBEV1(str,len)  { SDBError().SetErrorVariable(1, str, len); }
#define   SDBEV2(str,len)  { SDBError().SetErrorVariable(2, str, len); }
#define   SDBEV3(str,len)  { SDBError().SetErrorVariable(3, str, len); }
#define   SDBEV4(str,len)  { SDBError().SetErrorVariable(4, str, len); }
#define   SDBEV5(str,len)  { SDBError().SetErrorVariable(5, str, len); }

 /*******************************************************************/ 

#endif    // PODABA2_H
