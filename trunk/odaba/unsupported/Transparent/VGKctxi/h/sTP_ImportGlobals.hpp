/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    TP_ImportGlobals

\brief    


\date     $Date: 2006/07/07 18:11:19,93 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TP_ImportGlobals_HPP
#define   TP_ImportGlobals_HPP

class     TP_ImportGlobals;

class     PropertyHandle;
class     pc0_Stammdaten;
#include  <sDatabaseHandle.hpp>
#include  <spc0_HausratVS.hpp>
#include  <spc0_HundehaftpflichtVS.hpp>
#include  <spc0_KFZVS.hpp>
#include  <spc0_PrivathaftpflichtVS.hpp>
#include  <spc0_RechtsschutzVS.hpp>
#include  <spc0_RosshaftpflichtVS.hpp>
#include  <spc0_UnfallVS.hpp>
#include  <spc0_WohngebaeudeVS.hpp>
#include  <spc0_s_Bank.hpp>
#include  <spc0_s_Beruf.hpp>
#include  <spc0_s_Berufsgruppe.hpp>
#include  <spc0_s_Branche.hpp>
#include  <spc0_s_Gesellschaft.hpp>
#include  <spc0_s_Hunderasse.hpp>
#include  <spc0_s_KFZ_Zulassungsbezirk.hpp>
#include  <spc0_s_Partner.hpp>
#include  <spc0_s_Pferderasse.hpp>
#include  <spc0_s_Portal.hpp>
#include  <spc0_s_Staat.hpp>
#include  <spc0_s_Tarif.hpp>
#include  <spc0_s_Zahlungsweise.hpp>
class  TP_ImportGlobals
{
protected  :         pc0_s_Gesellschaft                           versicherer;                                               // 
protected  :         pc0_s_Portal                                 portale;                                                   // 
protected  :         pc0_s_Partner                                partner;                                                   // 
protected  :         pc0_s_Tarif                                  tarife;                                                    // 
protected  :         pc0_s_Bank                                   banken;                                                    // 
protected  :         pc0_s_Staat                                  laender;                                                   // 
protected  :         pc0_s_Beruf                                  berufe;                                                    // 
protected  :         pc0_s_Berufsgruppe                           berufsgruppen;                                             // 
protected  :         pc0_s_Branche                                branchen;                                                  // 
protected  :         pc0_s_KFZ_Zulassungsbezirk                   kfz_zulassungsbezirke;                                     // 
protected  :         pc0_s_Hunderasse                             hunderassen;                                               // 
protected  :         pc0_s_Pferderasse                            pferderassen;                                              // 
protected  :         pc0_s_Zahlungsweise                          zahlungsweisen;                                            // 
protected  :         int32                                        err_num;                                                   // 
protected  :         NString                                      message_start;                                             // 
protected  :         NString                                      messages;                                                  // 
protected  :         pc0_HausratVS                                vs_hr;                                                     // 
protected  :         pc0_RechtsschutzVS                           vs_rs;                                                     // 
protected  :         pc0_UnfallVS                                 vs_un;                                                     // 
protected  :         pc0_PrivathaftpflichtVS                      vs_phv;                                                    // 
protected  :         pc0_HundehaftpflichtVS                       vs_hhv;                                                    // 
protected  :         pc0_RosshaftpflichtVS                        vs_rhv;                                                    // 
protected  :         pc0_WohngebaeudeVS                           vs_whg;                                                    // 
protected  :         pc0_KFZVS                                    vs_kfz;                                                    // 

public     :
                     pc0_s_Gesellschaft                          &get_versicherer() { return(versicherer); }
                     pc0_s_Portal                                &get_portale() { return(portale); }
                     pc0_s_Partner                               &get_partner() { return(partner); }
                     pc0_s_Tarif                                 &get_tarife() { return(tarife); }
                     pc0_s_Bank                                  &get_banken() { return(banken); }
                     pc0_s_Staat                                 &get_laender() { return(laender); }
                     pc0_s_Beruf                                 &get_berufe() { return(berufe); }
                     pc0_s_Berufsgruppe                          &get_berufsgruppen() { return(berufsgruppen); }
                     pc0_s_Branche                               &get_branchen() { return(branchen); }
                     pc0_s_KFZ_Zulassungsbezirk                  &get_kfz_zulassungsbezirke() { return(kfz_zulassungsbezirke); }
                     pc0_s_Hunderasse                            &get_hunderassen() { return(hunderassen); }
                     pc0_s_Pferderasse                           &get_pferderassen() { return(pferderassen); }
                     pc0_s_Zahlungsweise                         &get_zahlungsweisen() { return(zahlungsweisen); }
                     int32                                        get_err_num() { return(err_num); }
                     NString                                     &get_message_start() { return(message_start); }
                     NString                                     &get_messages() { return(messages); }
                     pc0_HausratVS                               &get_vs_hr() { return(vs_hr); }
                     pc0_RechtsschutzVS                          &get_vs_rs() { return(vs_rs); }
                     pc0_UnfallVS                                &get_vs_un() { return(vs_un); }
                     pc0_PrivathaftpflichtVS                     &get_vs_phv() { return(vs_phv); }
                     pc0_HundehaftpflichtVS                      &get_vs_hhv() { return(vs_hhv); }
                     pc0_RosshaftpflichtVS                       &get_vs_rhv() { return(vs_rhv); }
                     pc0_WohngebaeudeVS                          &get_vs_whg() { return(vs_whg); }
                     pc0_KFZVS                                   &get_vs_kfz() { return(vs_kfz); }
public     :                                        void Clear ( );
public     :                                        int32 GetError ( );
public     :                                        NString &GetMessages ( );
public     :                                        logical ImportBank (PropertyHandle *target_ph, PropertyHandle *source_ph );
public     :                                        logical ImportBeruf (PropertyHandle *target_ph, PropertyHandle *source_ph );
public     :                                        logical ImportBerufsgruppe (PropertyHandle *target_ph, PropertyHandle *source_ph );
public     :                                        logical ImportBranche (PropertyHandle *target_ph, PropertyHandle *source_ph );
public     :                                        logical ImportHunderasse (PropertyHandle *target_ph, PropertyHandle *source_ph );
public     :                                        logical ImportKFZ_Zulassungsbezirk (PropertyHandle *target_ph, PropertyHandle *source_ph );
public     :                                        logical ImportPferderasse (PropertyHandle *target_ph, PropertyHandle *source_ph );
public     :                                        logical ImportPortal (PropertyHandle *target_ph, PropertyHandle *source_ph );
public     :                                        logical ImportStaat (PropertyHandle *target_ph, PropertyHandle *source_ph );
public     :                                        logical ImportStammdatum (pc0_Stammdaten *stammdaten_pc, PropertyHandle *target_ph, PropertyHandle *source_ph, char *source_prop );
public     :                                        logical ImportTarif (PropertyHandle *target_ph, PropertyHandle *source_ph );
public     :                                        logical ImportVersicherer (PropertyHandle *target_ph, PropertyHandle *source_ph );
public     :                                        logical ImportWerbePartner (PropertyHandle *target_ph, PropertyHandle *source_ph );
public     :                                        logical ImportZahlungsweise (PropertyHandle *target_ph, PropertyHandle *source_ph );
public     :                                        void Message (char *string );
public     :                                        void SetError (int32 errnum );
public     :                                        void SetMessageStart (char *string );
public     :                                             TP_ImportGlobals (DatabaseHandle &dbhandle );
};

#endif
