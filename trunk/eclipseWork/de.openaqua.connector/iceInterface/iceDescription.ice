#
module openaqua {
	module connector { 

		/**
		* Declare the known access methods
		*/	
		enum AccessMethods {HTTP,SOAP,TCP,UDP,BONJOUR, CORBA, RMI};
		
		/**
		* describes a list of known versions for a service
		*/
		sequence<string> VersionSequence; //a list of offered versions
		
		/**
		* Describe a service
		*/ 
		struct ServiceDescription {
			string uniqueName;
			string description;
			AccessMethods accessMethod; //like http, soap, ice, tcp...
			string machine;
			string port;
			VersionSequence versions;
		};
		
		/**
		* A list of services
		*/
		sequence<ServiceDescription> ServiceSequence;
	
	
		/**
		* Get a global unique ID
		*/
		interface uid {
			nonmutating string getUID();
		};


		/**
		*/
		interface Connection {
			idempotent bool login(string uid);
			bool logout();
			idempotent bool registerOffers(ServiceSequence services);
			idempotent bool registerLookups(ServiceSequence services);
		};
	}; 
}; 