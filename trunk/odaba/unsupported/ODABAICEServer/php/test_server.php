<?php
    // ICE ODABA Interface Test
    // use ./testphp to call from console OR
    // invoke on a webserver
    // make sure you 
    //  - installed the ICE php5 extension
    //  - created INI and Profile
    //  - started the ODABAICEServer
    
    Ice_loadProfile("odaba");
    try{
	    // create the proxy handles 
	    // this are dumb handles with no technical use
	    // you have to call the appropriate Open* functions before you can 
	    // use them.
	    
// not nessesary with generated factory

sleep(rand()%5);
	    $odabaclientp = $ICE->stringToProxy("odabaclient:tcp -p 10000:udp -p 10000");
            $odabaclientp = $odabaclientp->ice_twoway();
            $odabaclient  = $odabaclientp->ice_checkedCast("::Odaba::ODABAClient");

	    // create the proxy that provides us with empty
	    // instances of odaba objects
	    $ofp = $ICE->stringToProxy("objectfactory:tcp -p 10000:udp -p 10000");
            $ofp = $ofp->ice_twoway();
            $of  = $ofp->ice_uncheckedCast("::Odaba::ODABAObjectFactory");


//	    $odabaclient = $of->GetODABAClient();
	    // the dictionary is in short the structure information
	    // you need it to know what is where in the database
	    // technical it is just a database and can be used like it
	    $dictionary  = $of->GetDictionaryHandle();
	    // the database is the storage for the data
	    $database    = $of->GetDatabaseHandle();
	    // the propertyhandle is the tool that enables you to access, read and write
	    // data from a database
	    $property    = $of->GetPropertyHandle();
	    
	    // first exception - the odabaclient can stay dumb unless you want to
	    // connect the ODABAICEServer with a ODABAServer
	    // $odabaclient->Open("inipath","progname","progpath",Odaba_ApplicationTypes::aptCONSOLE);
	    $dictionary->OpenDictionary($odabaclient,"/data/develop/odaba/databases/adk.sys",Odaba_PIACCESSMODES::piaWRITE
		,false   //net
		,-1     //version
		,Odaba_ResourceTypes::resAUTOMATIC //resourcetype
		,false); // sysenv

	    // open the database
	    $database->OpenDatabase($dictionary,"/data/develop/odaba/databases/transparent.dev",Odaba_PIACCESSMODES::piaWRITE
		,false  //net
		,false  //online
		,-1     //version
		,Odaba_ResourceTypes::resAUTOMATIC
		,false);  //sysenv
	
	    // open the propertyhandle 
	    // extents are the eqivalent of tables in relational databases
	    $property->OpenExtent($database,"ODC_ImpClass",Odaba_PIACCESSMODES::piaWRITE
		,false //transient
		,"");  //keyname


	    // do something usefull with the propertyhandle
	    // output the number of items that are available

	    echo $property->GetCount()."\n";
	    
	    // open another propertyhandle
	    $functions = $property->GetPropertyHandle("pfunctions");
	    
	    // loop through data
	    if(rand()%2){
 	    $i=0;
	    while($property->GetAtPosition($i)){
		echo "class ".$property->GetString("sys_ident")."{\n";
		$j=0;
		while($functions->GetAtPosition($j)){
		    echo "  function "
		    .$functions->GetString("ddetype")
		    ." "
		    .$functions->GetString("sys_ident")
		    ."{}\n";
		    $j++;
		}
		echo "};\n";
		$i++;
		
	    }
	    }else{
 	    $i=$property->GetCount()-1;
	    while($property->GetAtPosition($i)){
		echo "class ".$property->GetString("sys_ident")."{\n";
		$j=0;
		while($functions->GetAtPosition($j)){
		    echo "  function "
		    .$functions->GetString("ddetype")
		    ." "
		    .$functions->GetString("sys_ident")
		    ."{}\n";
		    $j++;
		}
		echo "};\n";
		$i--;
		
	    }
	    }
	    /* this can mess your database
	    // write some data
	    echo $property->GetCount()."\n";
	    $property->Add(-1 				 //position
		,"myclassa" 				 //sortkey
		,"myclassb" . $property->GetCount()	 //identkey (sys_ident)
		);
		
	    echo $property->GetCount(),"\n";
	    */
	    // no closes
	    // no uninitialize
	    // just finish
    }
    catch(Ice_LocalException $ex)
    {
        print_r($ex);
    }
    echo "\n----\n";
sleep(5);
?>