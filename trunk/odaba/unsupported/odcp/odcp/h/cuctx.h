class   CTX_Administration;
class   CTX_Application;
class   CTX_Control;
class   CTX_Document;
class   CTX_Project;

typedef CTX_Administration *(*CreateAdminCtxPtr)(long);
typedef CTX_Application    *(*CreateApplCtxPtr)(long);
typedef CTX_Control        *(*CreateCtlCtxPtr)(long);
typedef CTX_Document       *(*CreateDocCtxPtr)(long);
typedef CTX_Project        *(*CreatePrjCtxPtr)(long);
