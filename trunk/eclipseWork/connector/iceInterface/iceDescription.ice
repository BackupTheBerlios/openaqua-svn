#
module openaqua {
	module connector { 
		interface uid {
			nonmutating string getUID();
		};

/**
				//http://developer.apple.com/networking/bonjour/index.html
				//http://www.zeroc.com//

*/		
			enum AccessMethods {HTTP,SOAP,TCP,UDP,BONJOUR, CORBA, RMI};
		
			sequence<string> VersionSequence; //a list of offered versions
			struct ServiceDescription {
				string uniqueName;
				string description;
				AccessMethods accessMethod; //like http, soap, ice, tcp...
				string machine;
				string port;
				VersionSequence versions;
			};
			sequence<ServiceDescription> ServiceSequence;

		interface Connection {
			bool login(string uid);
			bool logout();
			bool registerOffers(ServiceSequence services);
			bool registerLookups(ServiceSequence services);
		};
	}; 
}; 