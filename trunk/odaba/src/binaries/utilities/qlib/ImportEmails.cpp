//******************************************************************/
//* BackupDB
//*
//*               ODABA II - Main Function Code
//*                          from  L:/OPI7/OPI7.dev
//*  PD Version 2.0                                     2005/10/03
//******************************************************************/

#define    OBJ_ID  "BackupDB"

#include  <codaba2.h>
#include  <sEmail.hpp>
 
#include  <fstream>
#include  <ifil.h>
 





//******************************************************************/
//* main                - 
//*
//* RETURN
//*   rc                - 
//*
//* PARAMETERS
//*   argc              - 
//*   argv              - 
//*
//******************************************************************/


#undef     MOD_ID
#define    MOD_ID  "main"

//void processPOPBox(PropertyHandle& notiz, PropertyHandle& dokument, PropertyHandle &action){

void processPOPBox(){
  StringVector::iterator it;
  StringVector::const_iterator ait;
  StringVector     maillist;
  int              id;
BEGINSEQ
  Email e;
  e.SetHost("192.168.0.250");
  e.SetPort(110);
  std::cout <<"Import Emails" << std::endl;
  // get username/pwd from somewhere
  if(e.POPLogin("bigbrother","nur"))    ERROR
  maillist = e.GetMessageList();
  for(it = maillist.begin(); it!= maillist.end(); it++){
	id = atoi(((*it).substr(0,(*it).find(" ",0))).c_str());
	if(id && e.GetMessage(id)){
	  std::cout << "notiz (" << e.Subject() <<") "<<e.Sender()<<std::endl;

	  std_string sFilename,sPath;
	  sFilename="undefiniert";
	  for(ait = e.Attachments().begin();ait!=e.Attachments().end();ait++){
		// store it to disk!
		Email attachment;
		attachment.Analyze(*ait);
		sFilename = attachment.FileName();
		if(sFilename!=""){
			sFilename = "e:/" + sFilename;
			std::ofstream file(sFilename.c_str(),std::ios::out);
			std::string data = attachment.get_body();
			// decode
			if(attachment.HeaderValue(attachment.get_header(),"Content-Transfer-Encoding")=="base64"){
				std::cout << data;
			}
			file << data;
			file.close();
			std::cout << "dokument (" << sFilename <<") "<<sPath<<std::endl;
		}
	  }
	}
  }
  e.POPDisconnect();
RECOVER
ENDSEQ
}
void replaceAll(std::string &hay, std::string needle,std::string replacement){
	int pos = 0;
	while(pos!=-1){
		pos = hay.find(needle,pos);
		if(pos!=-1){
			hay.replace(pos,needle.length(),replacement);
			pos++;
		}
	}
}
void umlauts(std::string &ht){
	replaceAll(ht,"&uuml;","ü");
	replaceAll(ht,"&ouml;","ö");
	replaceAll(ht,"&auml;","ä");
	replaceAll(ht,"&Uuml;","Ü");
	replaceAll(ht,"&Ouml;","Ö");
	replaceAll(ht,"&Auml;","Ä");
	replaceAll(ht,"&szlig;","ß");
}
void importPersonen(PropertyHandle &person){
  std::ifstream fin( "q:\\transparent\\knamen" );
  std::string key,nname,vname;
  int spos;
  while( !fin.eof()){
	  std::getline(fin,key);
	  umlauts(key);
	  spos = key.find("|");
	  if(spos!=-1){
		nname = key.substr(0,spos);
		vname = key.substr(spos+1,key.length()-(spos+1));
		std::cout << vname << "|" << nname << std::endl;
		person.Add(Key((char*)key.c_str()));
		(*person.GPH("nachname")) = (char*)nname.c_str();
		(*person.GPH("vorname"))  = (char*)vname.c_str();
	  }
  }
  fin.close();
}
int main (int argc, char **argv )

{
  ODABAClient      oclient;
  char            *target   = NULL;
  char             string[1024];
  DataSourceHandle dsh;
  logical          term      = NO;

BEGINSEQ
  dsh.Setup(argv[1],"ImportEmails");
  oclient.Initialize(argv[1],"ImportEmails");
  dsh.Open( oclient,PI_Read);
  /*
  PropertyHandle notiz(DBObjectHandle(),"Notiz",PI_Write); 
  PropertyHandle dokument(notiz,"dokumente");
  PropertyHandle action(dsh.dbhandle,"Action",PI_Write);
  PropertyHandle person(dsh.dbhandle,"Person",PI_Write);
  */
/**/
  // read new mails
  //processPOPBox(notiz,dokument,action);
  //processPOPBox();
  // send mails
  
  Email smtp;
  smtp.SetHost("192.168.0.250");
  smtp.SetPort(25);
  smtp.SetSender("bigbrother@run-software.com");
  smtp.SetMessage("emailsend","line1\nline2\n\nend","line1\n<b>line2</b>\n\n\n<u>line3</u>\nend");
  std::cout << (char*)(!smtp.Deliver("bigbr other@r un-softw are.com ")?"mail sent":"no mail send")<<std::endl;
   
  /*
  EmailSend smtpaction("192.168.0.250");
  smtpaction.SetMessage("transparent@run-software.com","auto action 200","usefull text\nfrom the software\n");
  std::cout << (char*)(smtpaction.Deliver()?"mail sent":"no mail send")<<std::endl;
  */
  // import namen
  //importPersonen(person);
  // beispiel kommunikation
  // t -> baade, baade -> t, t->baade

  /*
  std::string ss = "192.168.0.250";
  std::string r  = "transparent@run-software.com";
  EmailSend *nachfrage;
  nachfrage = new EmailSend(ss);
  nachfrage->SetSender("info@transparent.de");
  nachfrage->SetMessage(r,"Aufnahmeantrag 100", "Sehr geehrter Herr Baade,\n\nin der Anlage erhalten Sie wie besprochen den Aufnahmeantrag.\nBitte senden Sie mir diesen ausgefuellt und unterschrieben an folgende Fax-Nr: 01803 2022 5346.\nGanz wichtig bei den Angaben im Antrag sind die Versicherungszeiten der letzten 18 Monate vor Antragstellung.\n\nMit freundlichen Gruessen\n\nJanet Hederich\nMitgliederbetreuung\nTAUNUS BKK\nWilhelminenhofstr. 83\n12459 Berlin\n\nTel.: 01803 / 20 22 03 46\nFax: 01803 / 20 22 53 46\nE-Mail: Janet.Hederich@taunus-bkk.de \ni-Net:    www.taunus-bkk.de \n\n ");
  std::cout << (char*)(nachfrage->Deliver()?"mail sent":"no mail send")<<std::endl;
  delete nachfrage;
  nachfrage = new EmailSend(ss);
  nachfrage->SetSender("baade@web.de");
  nachfrage->SetMessage(r,"Re: Aufnahmeantrag 100", "Hallo Frau Hederich,\n\nHaben sie das fax gestern erhalten? Stimmen die angaben/sind sie vollstaendig?\nUeber eine nachricht wuerde ich mich freuen.\nmit freundlichen gruessen\n\nJohann Baade\n\nJanette Hederich wrote:\nSehr geehrter Herr Angermann,\n\nin der Anlage erhalten Sie wie besprochen den Aufnahmeantrag.\nBitte senden Sie mir diesen ausgefuellt und unterschrieben an folgende Fax-Nr: 01803 2022 5346.\nGanz wichtig bei den Angaben im Antrag sind die Versicherungszeiten der letzten 18 Monate vor Antragstellung.\n\nMit freundlichen Gruessen\n\nJanet Hederich\nMitgliederbetreuung\nTAUNUS BKK\nWilhelminenhofstr. 83\n12459 Berlin\n\nTel.: 01803 / 20 22 03 46\nFax: 01803 / 20 22 53 46\nE-Mail: Janet.Hederich@taunus-bkk.de \ni-Net:    www.taunus-bkk.de \n\n ");
  std::cout << (char*)(nachfrage->Deliver()?"mail sent":"no mail send")<<std::endl;
  delete nachfrage;
  nachfrage = new EmailSend(ss);
  nachfrage->SetSender("info@transparent.de");
  nachfrage->SetMessage(r,"AW: Aufnahmeantrag 100", "Sehr geehrter Herr Baade,\n\nich habe Ihnen heute den Antrag erneut zugefaxt, da ich noch folgende\nAngaben benötige:\n\nHaben Sie bereits eine Rentenversicherungsnummer? Wenn ja, dann geben Sie diese bitte auf dem Antrag an. \nSollten Sie noch keinen Sozialversicherungsausweis besitzen, so teilen Sie uns dies bitte mit. Wir werden dann einen für Sie beantragen.\n\nDie Betriebsnummer des Arbeitgebers fehlte noch sowie Angaben zur vorgerigen Versicherung der letzten 18 Monate. Sie haben leider keine Angaben zur Versicherung ab dem 01.03.2003 gemacht, sondern erst ab dem 01.10.2003.\n\nBitte senden Sie mir den Antrag vollständig ausgefüllt und unterschrieben zurück.\n\nVielen Dank und ein schönes Wochenende.\n\nMit freundlichen Grüßen\n\nJanet Hederich\nMitgliederbetreuung\nTAUNUS BKK\nWilhelminenhofstr. 83\n12459 Berlin\n\nTel.: 01803 / 20 22 03 46\nFax: 01803 / 20 22 53 46\nE-Mail: Janet.Hederich@taunus-bkk.de \ni-Net:    www.taunus-bkk.de \n\n ");
  std::cout << (char*)(nachfrage->Deliver()?"mail sent":"no mail send")<<std::endl;
  delete nachfrage;

  nachfrage = new EmailSend(ss);
  nachfrage->SetSender("info@transparent.de");
  nachfrage->SetMessage(r,"Aufnahmeantrag 101", "Sehr geehrter Herr Buchlandt,\n\nin der Anlage erhalten Sie wie besprochen den Aufnahmeantrag.\nBitte senden Sie mir diesen ausgefuellt und unterschrieben an folgende Fax-Nr: 01803 2022 5346.\nGanz wichtig bei den Angaben im Antrag sind die Versicherungszeiten der letzten 18 Monate vor Antragstellung.\n\nMit freundlichen Gruessen\n\nJanet Hederich\nMitgliederbetreuung\nTAUNUS BKK\nWilhelminenhofstr. 83\n12459 Berlin\n\nTel.: 01803 / 20 22 03 46\nFax: 01803 / 20 22 53 46\nE-Mail: Janet.Hederich@taunus-bkk.de \ni-Net:    www.taunus-bkk.de \n\n ");
  std::cout << (char*)(nachfrage->Deliver()?"mail sent":"no mail send")<<std::endl;
  delete nachfrage;
  nachfrage = new EmailSend(ss);
  nachfrage->SetSender("buchlandt@web.de");
  nachfrage->SetMessage(r,"Re: Aufnahmeantrag 101", "Hallo Frau Hederich,\n\nHaben sie das fax gestern erhalten? Stimmen die angaben/sind sie vollstaendig?\nUeber eine nachricht wuerde ich mich freuen.\nmit freundlichen gruessen\n\nJohann Baade\n\nJanette Hederich wrote:\nSehr geehrter Herr Angermann,\n\nin der Anlage erhalten Sie wie besprochen den Aufnahmeantrag.\nBitte senden Sie mir diesen ausgefuellt und unterschrieben an folgende Fax-Nr: 01803 2022 5346.\nGanz wichtig bei den Angaben im Antrag sind die Versicherungszeiten der letzten 18 Monate vor Antragstellung.\n\nMit freundlichen Gruessen\n\nJanet Hederich\nMitgliederbetreuung\nTAUNUS BKK\nWilhelminenhofstr. 83\n12459 Berlin\n\nTel.: 01803 / 20 22 03 46\nFax: 01803 / 20 22 53 46\nE-Mail: Janet.Hederich@taunus-bkk.de \ni-Net:    www.taunus-bkk.de \n\n ");
  std::cout << (char*)(nachfrage->Deliver()?"mail sent":"no mail send")<<std::endl;
  delete nachfrage;
  nachfrage = new EmailSend(ss);
  nachfrage->SetSender("info@transparent.de");
  nachfrage->SetMessage(r,"AW: Aufnahmeantrag 101", "Sehr geehrter Herr Buchlandt,\n\nich habe Ihnen heute den Antrag erneut zugefaxt, da ich noch folgende\nAngaben benötige:\n\nHaben Sie bereits eine Rentenversicherungsnummer? Wenn ja, dann geben Sie diese bitte auf dem Antrag an. \nSollten Sie noch keinen Sozialversicherungsausweis besitzen, so teilen Sie uns dies bitte mit. Wir werden dann einen für Sie beantragen.\n\nDie Betriebsnummer des Arbeitgebers fehlte noch sowie Angaben zur vorgerigen Versicherung der letzten 18 Monate. Sie haben leider keine Angaben zur Versicherung ab dem 01.03.2003 gemacht, sondern erst ab dem 01.10.2003.\n\nBitte senden Sie mir den Antrag vollständig ausgefüllt und unterschrieben zurück.\n\nVielen Dank und ein schönes Wochenende.\n\nMit freundlichen Grüßen\n\nJanet Hederich\nMitgliederbetreuung\nTAUNUS BKK\nWilhelminenhofstr. 83\n12459 Berlin\n\nTel.: 01803 / 20 22 03 46\nFax: 01803 / 20 22 53 46\nE-Mail: Janet.Hederich@taunus-bkk.de \ni-Net:    www.taunus-bkk.de \n\n ");
  std::cout << (char*)(nachfrage->Deliver()?"mail sent":"no mail send")<<std::endl;
  delete nachfrage;

  nachfrage = new EmailSend(ss);
  nachfrage->SetSender("info@transparent.de");
  nachfrage->SetMessage(r,"Nachfragen zu Ihrem Unfall 200", "Sehr geehrter Herr Constantin,\n\nBitte senden sie das aerztliche attest an die angegebene faxnummer\n\nMit freundlichen Gruessen\n\nJanet Hederich\nMitgliederbetreuung\nTAUNUS BKK\nWilhelminenhofstr. 83\n12459 Berlin\n\nTel.: 01803 / 20 22 03 46\nFax: 01803 / 20 22 53 46\nE-Mail: Janet.Hederich@taunus-bkk.de \ni-Net:    www.taunus-bkk.de \n\n ");
  std::cout << (char*)(nachfrage->Deliver()?"mail sent":"no mail send")<<std::endl;
  delete nachfrage;
  nachfrage = new EmailSend(ss);
  nachfrage->SetSender("buchlandt@web.de");
  nachfrage->SetMessage(r,"Re: Aufnahmeantrag 200", "Hallo Frau Hederich,\n\nIch hatte gar keinen Unfall \n\n ");
  std::cout << (char*)(nachfrage->Deliver()?"mail sent":"no mail send")<<std::endl;
  delete nachfrage;
  nachfrage = new EmailSend(ss);
  nachfrage->SetSender("info@transparent.de");
  nachfrage->SetMessage(r,"AW: Aufnahmeantrag 200", "Sehr geehrter Herr Constantin,\n\nWir haben doch gestern deswegen telefoniert\n\n ");
  std::cout << (char*)(nachfrage->Deliver()?"mail sent":"no mail send")<<std::endl;
  delete nachfrage;
  nachfrage = new EmailSend(ss);
  nachfrage->SetSender("buchlandt@web.de");
  nachfrage->SetMessage(r,"Re: Aufnahmeantrag 200", "Hallo Frau Hederich,\n\nachso das - keine angst alles gut\n\n ");
  std::cout << (char*)(nachfrage->Deliver()?"mail sent":"no mail send")<<std::endl;
  nachfrage = new EmailSend(ss);
  nachfrage->SetSender("info@transparent.de");
  nachfrage->SetMessage(r,"AW: Aufnahmeantrag 200", "Sehr geehrter Herr Constantin,\n\nok dann gibt es kein schadensfall\n\n ");
  std::cout << (char*)(nachfrage->Deliver()?"mail sent":"no mail send")<<std::endl;
  delete nachfrage;

  nachfrage = new EmailSend(ss);
  nachfrage->SetSender("info@transparent.de");
  nachfrage->SetMessage(r,"Unvollstaendige Daten 300", "hallo herr Gess, sie haben nicht angegeben wieoft sie schon verklagt wurden\nmfg transparent\n\n ");
  std::cout << (char*)(nachfrage->Deliver()?"mail sent":"no mail send")<<std::endl;
  delete nachfrage;
  nachfrage = new EmailSend(ss);
  nachfrage->SetSender("gess@web.de");
  nachfrage->SetMessage(r,"Re: Unvollstaendige Daten 300", "Hallo transparent, ich wurde noch nie verklagt moechte mich dennoch absichern\nmfg\n\n ");
  std::cout << (char*)(nachfrage->Deliver()?"mail sent":"no mail send")<<std::endl;
  delete nachfrage;
*/
  printf("\n ... terminated successfully.\n");
RECOVER

  printf("\n ... terminated with errors.\n");
  term = YES;

ENDSEQ

  //oclient.ShutDown();
  return(term);
}
