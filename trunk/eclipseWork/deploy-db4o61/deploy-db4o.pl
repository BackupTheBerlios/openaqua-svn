eval 'exec perl -S $0 "$@"'
if 0;


#Hint: Am Anfang der Datei befinden sich nur Subroutinen.
#Der eigentliche Einstiegspunkt in das Script ist die Funktion
#main()
#
#Dahinter kommt dann noch die unvermeidliche Doku



####################### LOAD LIBS    #########################################
use strict;         # checks for correct code
use warnings 'all'; # enable all warning for this script
use Getopt::Long;    # allows long command line parameters
use File::Basename;  # returns the basename of a full filename (path+file)
use Cwd;             # offers the getcwd function
##############################################################################



#################   global Variables   ##########################################
my $VERSION      = '1.0';
my $AUTHOR       = '';
my $VERBOSE;     # if set the compiler output will be shown
my $RELEASE;	  # if set the code will be compiled in release mode
##############################################################################




sub printShortHelp() {
#function not used!
	print "\n" .
			"This tools prepares a db4o package for maven, calls maven and let maven deploy the maven packages\n".
			"\n".
			"This tool expects a couple of paramters:\n".
			"--package=xxx\n" .
			"--version=yyy\n" .
			"\n".
			"xxx is the name/path of a db4o.zip file like db4o-61.zip\n".
			"yyy is the version number of that file. Might be something like \"6.1\"\n".
			"\n".
			"\n"
			;

}




sub execute($$$) {
	my $file = shift;
	my $pom = shift;
	my $target = shift;
	my $cmd = "mvn deploy:deploy-file ";
	my $maven = "$cmd -Dfile=$file  -DpomFile=$pom -Durl=$target";
	print "$maven \n";
	return system ("$maven");
}




sub main() {
   #define some variables
   my $result = 0; #the return code
	my $help;
#my $target="file:///users/dxccwl/user7/behrenan/workspace/tmp/deploy";
	my $target="/users/dxccwl/user7/behrenan/workspace/tools/maven-2.0.4/repro";

#	execute($version, "db4o-6.0-java1.1.jar", "./db4o-java11.xml", "file:///users/dxccwl/user7/behrenan/workspace/tmp/deploy", "db4o-java11");
	execute("db4o-6.0-java1.1.jar", "./db4o-java11.xml", $target);
	execute("db4o-6.0-java1.2.jar", "./db4o-java12.xml", $target);
}

exit main();#



