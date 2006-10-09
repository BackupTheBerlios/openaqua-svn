#ifndef __IXmlContext_h__
#define __IXmlContext_h__


//Forward Declaration
class QString;


class IXmlContext
{
   public:
      virtual ~IXmlContext(){};
      virtual const QString& getDocumentRoot() const = 0;

   private:
};

#endif //__IXmlDocument_h__
