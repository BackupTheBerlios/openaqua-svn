#ifndef __CoaRational_h__
#define __CoaRational_h__


#include <QPair>
#include <QString>



class CoaRational
{
private:

   mpq_t    q;

   static unsigned int getShiftFactor(unsigned precision);

   int toScaledInt(unsigned precision) const
      throw(CBcExcBaseTypeRange, CB_THROWS);

public:

   /**
    * - construct 0/1
    */
   CoaRational();

   /**
    * - copy-construct
    */
   CoaRational(const CoaRational& r);

   /**
    * - assignment-operate
    */
   CoaRational& operator=(const CoaRational& r);


   /**
    * - destruct
    */
   ~CoaRational();
   
protected:
   /**
    * - construct num/den.
    */
   CoaRational(int num, unsigned int den);


public:
   /**
    * - Round
    * This function rounds the rational so that q * 10^precision is an integer.
    * Rule:
    * For positive q, set q := floor(q*10^precision + 0.5)/(10^precision).
    * For negative q, invert sign, do as above, invert sign again.
    *
    */
   CoaRational getRounded(unsigned precision) const;
   
   
   /**
    * - Truncate
    * This function truncates the rational so that q * 10^precision is
    * an integer, i.e. the decimal representation is cut off after the
    * precision'th decimal place.
    *
    * Rule:
    * For positive q, set q := floor(q*10^precision)/(10^precision).
    * For negative q, invert sign, do as above, invert sign again.
    *
    */
   CoaRational getTruncated(unsigned precision) const;
   
   /**
    * - Check decimal precision
    * Determine whether the rational can be represented exactly by a
    * decimal with the given precision (i.e. if toScaledInt would work).
    *
    */
   bool isFitting(unsigned precision) const;
   
   
   /**
    * - Construct from other datatypes
    */
   static CoaRational fromInt(int num, unsigned int den=1);

   static CoaRational fromScaledInt(int num, unsigned precision);
   
   static CoaRational fromStringPair(const QPair<QString,QString> & pair);


   /**
    * - Convert to other datatypes
    */
   QString toString() const;
   QPair<QString,QString> toStringPair() const;
   inline double toDouble() const;
   

  

   /**
    * operators
    */
   CoaRational    operator+ (const CoaRational& rhs) const    ;
   CoaRational    operator- (const CoaRational& rhs) const    ;
   CoaRational    operator* (const CoaRational& rhs) const    ;
   CoaRational    operator/ (const CoaRational& rhs) const    ;

   CoaRational    operator- () const      ;
   
   bool           operator> (const CoaRational& rhs) const    ;
   bool           operator< (const CoaRational& rhs) const    ;
   bool           operator>=(const CoaRational& rhs) const    ;
   bool           operator<=(const CoaRational& rhs) const    ;
   bool           operator==(const CoaRational& rhs) const    ;
   bool           operator!=(const CoaRational& rhs) const    ;

};

inline double CoaRational::toDouble() const
{
   return double(0);
}


#endif //
