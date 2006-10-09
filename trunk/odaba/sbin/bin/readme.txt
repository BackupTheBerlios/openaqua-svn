The installion contains the Solaris 9 Sparc binaries for ODABA2 and the BridgeNA Server.

ODABA2 V8.20, BridgeNA V4.2
----------------------------
The installation file "BridgeNA.SolarisX.42.date.tar.gz" contains the binaries 
that are necessary to run a BridgeNA server on a SolarisX/UltraSPARC platform. 
For installing the following steps must be performed:

	1. Unpack the installation file. 
	2. Run "install" from the unpack directory:
	     install --prefix=$HOME/ODABA2
	   prefix defines the installation directory. For more help run
	     install --help

After successfull installation you can delete the unpack directory. 

PS: If you install BridgeNA without using your standard library path, you have 
to add the libdir to your LD_LIBRARY_PATH.

Starting the BridgeNA server 
-----------------------------
The BridgweNA server "Server" has been provided in .../bin in the 
installation directory. You have to provide two arguments:

   1. the port the server should listen to
   2. the complete path to the ini-file 
   
Run      
   .../Server 6123 (installation path)/ODABA2/share/ODABA/MetaServer.ini  
to start the server1 and 
   .../Server --kill (installation path)/ODABA2/share/ODABA/MetaServer.ini 
to stop the server1. An appropriate ini-file hase been providd as "MetaServer.ini" 
in .../share in the installation directory. The server is starting a deamon that serves a 
number of BridgeNA applications.

To scripts StartServer and KillServer are provided in the .../share/ODABA directory.