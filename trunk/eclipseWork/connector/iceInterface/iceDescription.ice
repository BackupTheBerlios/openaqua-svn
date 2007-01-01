#
module openaqua {
	module connector { 
		interface uid {
			const string getUID();
		}
		
		interface connection {
			enum AccessMethods {
				HTTP,
				SOAP,
				TCP,
				UDP,
				BONJOUR, //http://developer.apple.com/networking/bonjour/index.html
				ICE,  //http://www.zeroc.com//
				CORBA,
				RMI
			};
			
			struct ServiceDescription {
				string uniqueName;
				string description;
				AccessMethods accessMethod; //like http, soap, ice, tcp...
				string machine;
				string port; //might be NULL
				sequence<string> version; //a list of offered versions
			};
			
			sequence<ServiceDescription> ServiceSequence;
			
			
			boolean login(const string uid);
			boolean logout();
			boolean registerOffers();
			boolean registerLookups();
		}
	}; 
}; 