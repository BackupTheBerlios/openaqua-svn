<?php
    // ICE ODABA Interface Test
    // use ./testphp to call from console OR
    // invoke on a webserver
    // make sure you 
    //  - installed the ICE php5 extension
    //  - created INI and Profile
    //  - started the OPIICEServer
    
    Ice_loadProfile("opi");
    // Ice_dumpProfile();
    try{
	    // create the proxy handles 
	    // this are dumb handles with no technical use
	    // you have to call the appropriate Open* functions before you can 
	    // use them.
	    
// not nessesary with generated factory

	    // create the proxy that provides us with empty
	    // instances of odaba objects
	    $sp = $ICE->stringToProxy("session:tcp -h 192.168.0.17 -p 10000:udp -h 192.168.0.17 -p 10000 -h 192.168.0.17");
            $sp = $sp->ice_twoway();
            $s  = $sp->ice_uncheckedCast("::OPI::SessionFactory");
	    $sprx = $s->CreateProxy("php".time());
	    $of = $sprx->CreateSession();
	    
	    $odabaclient = $of->GetODABAClient();
	    // the dictionary is in short the structure information
	    // you need it to know what is where in the database
	    // technical it is just a database and can be used like it
	    $dictionary  = $of->GetDictionaryHandle();
	    // the database is the storage for the data
	    $database    = $of->GetDatabaseHandle();
	    // the propertyhandle is the tool that enables you to access, read and write
	    // data from a database
	    $vertraege        = $of->GetPropertyHandle();
	    $gesellschaften   = $of->GetPropertyHandle();

	    // first exception - the odabaclient can stay dumb unless you want to
	    // connect the ODABAICEServer with a ODABAServer
	    // $odabaclient->Open("inipath","progname","progpath",Odaba_ApplicationTypes::aptCONSOLE);
	    $dictionary->OpenDictionary($odabaclient,"/data/data/transparent.dev",OPI_PIACC::piaWRITE
		,false   //net
		,-1     //version
		,OPI_ResourceTypes::resAUTOMATIC //resourcetype
		,false); // sysenv
	    
	    // open the database
	    $database->OpenDatabase($dictionary,"/data/data/transparent.dat",OPI_PIACC::piaWRITE
		,false  //net
		,false  //online
		,-1     //version
		,OPI_ResourceTypes::resAUTOMATIC
		,false);  //sysenv
	
	    // open the propertyhandle 
	    // extents are the eqivalent of tables in relational databases
	    $vertraege->OpenExtent($database,"Action",OPI_PIACC::piaWRITE
		,false //transient
		,"");  //keyname


	    // do something usefull with the propertyhandle
	    // output the number of items that are available

	    echo $vertraege->GetCount()." Vertraege\n";
	    // open another propertyhandle
	    $versicherer = $vertraege->GetPropertyHandle("versicherer");
/*	    $indx = 0;
	    while($vertraege->GetAtPosition($indx)){
	      echo $vertraege->GetString("typ")."\t";
	      echo $vertraege->GetString("sparte")."\t";
	      echo $vertraege->GetString("created")."\n";
	      echo "Versicherer: ";
	      echo $versicherer->GetCount();
	      $versicherer->GetAtPosition(0);
	      echo $versicherer->GetString("name");
	      echo "--\n";
	      $indx++;
	    }
*/
	    $gesellschaften->OpenExtent($database,"s_Gesellschaft",OPI_PIACC::piaWRITE
		,false //transient
		,"");  //keyname


	    // do something usefull with the propertyhandle
	    // output the number of items that are available

	    echo $gesellschaften->GetCount()." Gesellschaften\n";
	    $indx = 0;
	    $vertraege = $gesellschaften->GetPropertyHandle("actions");
	    
	    while($gesellschaften->GetAtPosition($indx)){
	      $count = $vertraege->GetCount();
	      if($count>0){
	        $name = $gesellschaften->GetString("name");
	        $html.="<tr><th>$name</th><td>$count</td></tr>";
	      }
	      $indx++;
	    }
	    //echo "clean\n";
	    $sprx->Destroy();
	    
	    //echo "done\n";
    }
    catch(Ice_LocalException $ex)
    {
        print_r($ex);
    }
    //echo "\n----\n";
?>