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
	    $sp = $ICE->stringToProxy("session:tcp -p 10000:udp -p 10000");
            $sp = $sp->ice_twoway();
            $s  = $sp->ice_uncheckedCast("::OPI::SessionFactory");
	    $sprx = $s->CreateSessionProxy("php");
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
	    $property    = $of->GetPropertyHandle();
    }
    catch(Ice_LocalException $ex)
    {
        print_r($ex);
    }
    echo "\n----\n";
sleep(5);
?>