eval 'exec perl -S $0 "$@"'
if 0;

#Hint: the entry point is the main() function at the end
#      behind the main() function comes some docu



####################### LOAD LIBS    #########################################
use strict;         # checks for correct code
use warnings 'all'; # enable all warning for this script
use Getopt::Long;    # allows long command line parameters
use File::Basename;  # returns the basename of a full filename (path+file)
use Cwd;             # offers the getcwd function
use Mail::IMAPClient;# offers functions to connect to a IMAP Daemon
use IO::Socket::SSL;
##############################################################################


#################   global Variales   ##########################################

my $VERSION      = '0.9';
my $ProgName     = 'GenerateRock.pl';
my $AUTHOR       = 'Andrey.Behrens@external.t-mobile.de';


##############################################################################



############################################
# Function: prints Author and Version
# Params:
# Result: 0==ok
sub printVersion {
   print "Version:\t$VERSION\n";
   print "Author :\t$AUTHOR\n";
   return 0;
}


############################################
# Function: prints Author and Version
# Params:
# Result: 0==ok
sub printShortHelp() {
   
   print "imapBackup.pl: -h => print help\n" .
         "               -v => print version\n" .
         "\n"
         ;   
   return 0;
}



############################################
# Function: prints Author and Version
# Params:
# Result: 0==ok
sub printHelp() {
   system("perldoc $0");
   return 0;
}


sub connectImap {
   #http://www.heise.de/ix/artikel/2005/02/132/
   my $ssl  = IO::Socket::SSL->new("servername:imaps") or die $@;
   my $imap = <$ssl>;
   $imap = Mail::IMAPClient->new(Socket=>$ssl, User=>$user,
   Password=>$password);
   $imap->State($imap->Connected());
   $imap->login() or die 'login failed';
   my $imap = Mail::IMAPClient->new("host", "user", "password") or die "Verbindungsaufbau nicht möglich: $@";

}



###########################################
# 
sub main() {
   #set variables
   my $result = -1;
   my ($help, $version, $configFile); #Flags for
   
   #Check Commandline params
   $result = GetOptions( "help"       => \$help,       # print help
                         "version"    => \$version,    # print version
                         "configFile=s" => \$configFile  # set config File
                         
                         );

   connectImap();
   
   #react on parameters
   #1. no parameters given
   if (not defined $result || $result != 1 ) {
      return printShortHelp();
   }

   #2. Version?
   if (defined $version) {
      return printVersion();
   }

   #3. Help wanted?
   if (defined $help) {
      return printHelp();
   }
   
   return $result;
}


####################################MAIN PART============================

exit ( main() ); # main entry point


####################################DOCUMENTATION============================

=head1 NAME

GenerateRock.pl -

=head1 SYNOPSIS

ShortTrace.pl [-h] [-v] [-n] [--help] [--version] [--noconstructors]  [files]

=head1 DESCRIPTION

Das Script erwartet als Parameter ein Interface aus *interface/. Zum Beispiel CBiObjMngSystemConst.

Das Script zerlegt die Interface-Klasse in Tokens und erzeugt aus diesen Token Proxy und Adap-Klassen, sowie einen Rock-Namespace.

Die erzeugten Klassen werden in den passenden Unterverzeichnissen abgelegt. Ausgangspunkt zur Ablage der erzeugten Dateien ist der


=head1 LIMITATIONS

=head2 Header Parsing

- Das Skript kann keine Makrodefinitionen erkennen, die Ã¼ber mehrere Zeilen gehen. Loesungsmoeglichkeit: Erkennung auf \

Die Klassenerkennung ist im Augenblick sehr dumm geparst wird nach "class Name { };" mit beliebigen Token dazwischen



=head1 OPTIONS

=over 4

=item -h

=item --help

Aufruf dieses Hilfetexts

=item -v

=item --version

Ausgabe der Versionsnummer und der Autoren

=item -n

=item --noconstructors

Ignores constructor and destructor messages

=item files

One or many files. The script opens those files, shorts them and prints the result to stdout

=cut




=head1 ENVIRONMENT


=head1 BUGS, LIMITATIONS


=head1 AUTHOR

Andrey Behrens

Email: Andrey.Behrens@external.t-mobile.de

Telefon: +49-228-936-36478

=end comment
=cut

