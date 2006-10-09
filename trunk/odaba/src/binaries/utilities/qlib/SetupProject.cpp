//******************************************************************/
//* Setup project
//******************************************************************/

#define    OBJ_ID  "SetupProject"

#include  <iostream>
#include  <sstream>
#include  <fstream>
 
std::string dllpath="l:/odet";
std::string adkpath="l:/adk";

struct setting{
	std::string projectname;
	std::string projectpath;
	std::string odabapath;
	std::string doclanguage;
	bool klasseditor;
	bool designer;
	bool env;
	setting(): 
	  projectname()
	 ,projectpath()
	 ,odabapath()
	 ,doclanguage()
	 ,klasseditor(true)
	 ,designer(true)
	 ,env(false){}
};
void display(setting s){
	std::cout << "your choices" << std::endl;
	std::cout << "name:  " << s.projectname << std::endl;
	std::cout << "path:  " << s.projectpath << std::endl;
	std::cout << "odaba: " << s.odabapath << std::endl;
	std::cout << "klass: " << (s.klasseditor?"YES":"NO") << std::endl;
	std::cout << "designer:" << (s.designer?"YES":"NO") << std::endl;
	std::cout << "env:" << (s.env?"YES":"NO") << std::endl;
}
void label(std::string l,  std::string def = ""){
	std::cout<<l;
	if(def!="")
	  std::cout<<" ["<<def<<"] ";
	std::cout<< ": ";//<<std::endl;

}
void input(std::string l,std::string &value, std::string def = ""){
	label(l,def);
	std::getline(std::cin,value );
	if(def!=""&&value=="")
	   value = def;
}
void input(std::string l,bool &value, std::string def = ""){
	std::string svalue;
	label(l + " [Y]ES/[N]O ", def);
	std::getline(std::cin,svalue );
	if(def!="" && svalue=="")
	  svalue = def;
	if(svalue=="yes" || svalue=="YES" || svalue=="y" || svalue=="Y")
	  value = true;
	else
	  value = false;
}
void templatereplace(std::string tpl, std::string val, std::string &line){
	while(line.find(tpl)!=-1)
		line = line.replace(line.find(tpl),tpl.length(),val);
}
void backslash(std::string &s){
	while(s.find("/")!=-1)
		s = s.replace(s.find("/"),1,"\\");   
}
void generateini(setting q, std::string filename){
	  std::string inifile = q.projectpath + "/" + filename + ".ini";
	  std::string initempl = dllpath + "/tpl/ini/" +filename + ".ini.tpl";
	  std::string line;
	  std::ofstream ini(inifile.c_str(),std::ios::out);
	  std::ifstream init(initempl.c_str());
	  while(!init.eof()){
		  std::getline(init,line);
		  templatereplace("%projectpath%",q.projectpath,line);
		  templatereplace("%projectname%",q.projectname,line);
		  if(q.odabapath!=dllpath)
  		    templatereplace("%adkpath%","%odabapath%",line);
		  templatereplace("%odabapath%",q.odabapath,line);
		  templatereplace("%adkpath%",adkpath,line);
		  ini << line << std::endl;
	  }
	  ini.close();
	  init.close();
}

void generatecmd(setting q, std::string filename){
	  std::string cmdfile = q.projectpath + "/" + filename + ".cmd";
	  std::ofstream cmd(cmdfile.c_str(),std::ios::out);
	  cmd << "@cd " << q.odabapath << std::endl;
	  cmd << "@start " << q.odabapath << "/ode90.exe " << q.projectpath << "/" + filename + ".ini" << std::endl;
	  cmd.close;
}
void command(std::string cmd){
	backslash(cmd);
	system(cmd.c_str());
}
void createfiles(setting q){
	std::cout << "creating project directory..." << std::endl;
	command("mkdir " + q.projectpath);
	if(q.env){
		std::cout << "copy dll" <<std::endl;
		command("mkdir " + q.projectpath + "/sbin");		
		command("mkdir " + q.projectpath + "/sbin/res");
		command("cp " + dllpath + "/*.dll " + q.projectpath + "/sbin");
		command("cp " + dllpath + "/ode90.exe " + q.projectpath + "/sbin");
		command("cp " + dllpath + "/klasseditor.png " + q.projectpath + "/sbin");
		command("cp " + dllpath + "/designer.png " + q.projectpath + "/sbin");
		command("cp " + adkpath + "/adk.sys " + q.projectpath + "/sbin");
		command("cp " + adkpath + "/adk.dev " + q.projectpath + "/sbin");
		command("cp " + adkpath + "/res/* " + q.projectpath + "/sbin/res");
		q.odabapath = q.projectpath + "/sbin";		
	}
	if(q.klasseditor){
  	    std::cout << "creating klasseditor.ini" << std::endl;
		generateini(q,"klasseditor");
  	    std::cout << "creating klasseditor.cmd" << std::endl;
		generatecmd(q,"klasseditor");
	}
	if(q.designer){
  	    std::cout << "creating designer.ini" << std::endl;
		generateini(q,"designer");
  	    std::cout << "creating designer.cmd" << std::endl;
		generatecmd(q,"designer");
	}
	
    std::cout <<"done"<<std::endl;
}

void interactive(){
	setting q;
	std::cout<<"ode project initialisation"<<std::endl;
	input("project name",q.projectname);
	input("project path",q.projectpath,"q:/" + q.projectname);
	input("copy environment",q.env,"NO");
	if(!q.env)
		input("odaba path",  q.odabapath, dllpath);
	input("use klasseditor",q.klasseditor,"YES");
	input("use designer",q.designer,"YES");
	
	display(q);
	createfiles(q);
	
}





int main (int argc, char **argv )
{
  std::cout <<"Setup Project" << std::endl;
  interactive();
  return(0);
}
