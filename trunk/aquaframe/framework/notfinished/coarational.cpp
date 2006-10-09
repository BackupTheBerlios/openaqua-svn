#include "coarational.h"


// static
unsigned CoaRational::getShiftFactor(unsigned scale) 
{
   static unsigned shiftFactor[6+1] = { 1,10,100,1000,10000,100000,1000000 };
   CB_ASSERT(scale <= 6);
   return shiftFactor[scale];
}




CoaRational::CoaRational(int num, unsigned den)
{
   mpq_init(q);
   
   // This used to be:
   // mpq_set_si(q, num, den);
   // ...but unfortunately, they're using long (which may or may not be enough).

   bool is_neg;
   unsigned unum;
   
   // Pull out the sign.
   if(num < 0) {
      is_neg = true;
      unum = - num;
   } else {
      is_neg = false;
      unum = num;
   }
   
   // Import 1 word of 8 bytes, in host order for each of num and den.
   mpz_import( mpq_numref(q), 1, 1, 8, 0, 0, reinterpret_cast<void*>(&unum));
   mpz_import( mpq_denref(q), 1, 1, 8, 0, 0, reinterpret_cast<void*>(&den));
   
   mpq_canonicalize(q);
   
   // Put back the sign
   if(is_neg)
      mpq_neg(q,q);
}


CoaRational::CoaRational()
{
   mpq_init(q);
}


CoaRational::CoaRational(const CoaRational& r)
{
   // maybe assert(this != &r) here.
   mpq_init(q);
   mpq_set(q, r.q);
}

CoaRational&
CoaRational::operator =(const CoaRational& r)
{
   if(this != &r)
      mpq_set(q, r.q);
   return *this;
}


CoaRational::~CoaRational()
{
   mpq_clear(q);
}



CoaRational
CoaRational::getRounded(unsigned precision) const
{
   CB_ASSERT(precision <= 6); // ...but would in fact work with any precision.
   unsigned long scale = getShiftFactor(precision);
   
   CoaRational ret(*this);
   
   bool is_neg = ( mpz_sgn(mpq_numref(ret.q)) < 0 );
   
   if(is_neg)
   {
      mpz_neg(mpq_numref(ret.q),mpq_numref(ret.q));
   }
   
   // warn: this code is evil.
   mpq_t qscale;
   mpq_init(qscale);
   mpq_set_ui(qscale, scale, 1);

   // compute ret.q = trunc(ret.q*scale+1/2)/scale

   mpq_mul(ret.q,ret.q,qscale);
   {
      mpq_t q_1_2;
      mpq_init(q_1_2);
      mpq_set_si(q_1_2, 1, 2);
      mpq_add(ret.q,ret.q,q_1_2);
      mpq_clear(q_1_2);
   }
   mpz_tdiv_q(mpq_numref(ret.q), mpq_numref(ret.q), mpq_denref(ret.q));
   mpz_swap(mpq_denref(ret.q), mpq_numref(qscale));
   mpq_canonicalize(ret.q);
   
   mpq_clear(qscale);

   if(is_neg)
   {
      mpz_neg(mpq_numref(ret.q),mpq_numref(ret.q));
   }
   
   return ret;
   
}


CoaRational
CoaRational::getTruncated(unsigned precision) const
   
{
   CB_ASSERT(precision <= 6); // ...but would in fact work with any precision.
   unsigned long scale = getShiftFactor(precision);
   
   CoaRational ret(*this);
   
   bool is_neg = ( mpz_sgn(mpq_numref(ret.q)) < 0 );
   
   if(is_neg)
   {
      mpz_neg(mpq_numref(ret.q),mpq_numref(ret.q));
   }
   
   // warn: this code is evil.
   mpq_t qscale;
   mpq_init(qscale);
   mpq_set_ui(qscale, scale, 1);

   // compute ret.q = trunc(ret.q*scale)/scale

   mpq_mul(ret.q,ret.q,qscale);
   mpz_tdiv_q(mpq_numref(ret.q), mpq_numref(ret.q), mpq_denref(ret.q));
   mpz_swap(mpq_denref(ret.q), mpq_numref(qscale));
   mpq_canonicalize(ret.q);
   
   mpq_clear(qscale);

   if(is_neg)
   {
      mpz_neg(mpq_numref(ret.q),mpq_numref(ret.q));
   }
   
   return ret;
   
}

bool
CoaRational::isFitting(unsigned precision) const
      
{
   bool ret=true;
   
   CB_ASSERT(precision <= 6); // ...but would in fact work with any precision.
   unsigned long scale = getShiftFactor(precision);
   
   // Compute q*scale.
   mpq_t qscale;
   mpq_init(qscale);
   mpq_set_ui(qscale, scale, 1);
   mpq_mul(qscale, qscale, q);
   mpz_tdiv_qr(mpq_numref(qscale), mpq_denref(qscale),
               mpq_numref(qscale), mpq_denref(qscale));

   if(mpz_sgn(mpq_denref(qscale)) != 0)
      ret=false; // there was a remainder in the division
   
   // using sizeinbase instead of fits_slong, since
   // we don't know what type an int really is,
   // just that it's 63 bit + sign.
   if(mpz_sizeinbase(mpq_numref(qscale), 2) > 63)
      ret=false;
   mpq_clear(qscale);
   
   return ret;
}

CoaRational
CoaRational::fromInt(int num, unsigned den /* =1 */ )
   
{
   return CoaRational(num, den);
}


QString
CoaRational::toString() const
   
{
   const int base = 10;
   
   int slen = mpz_sizeinbase (mpq_numref(q), base)
      + mpz_sizeinbase (mpq_denref(q), base) + 3;
   
   char * buf = new char[slen];

   mpq_get_str(buf, base, q);
   
   QString ret(buf);
   delete[] buf;
   return ret;
}


//
// Convert to/from scaled integers
//
CoaRational
CoaRational::fromScaledInt(int num, unsigned precision)
   
{
   return CoaRational(num, getShiftFactor(precision)); // Wow, that was easy...
}


// FIXME: range may be too limited (only signed long?)
int
CoaRational::toScaledInt(unsigned precision) const
   throw(CBcExcBaseTypeRange, CB_THROWS)
{
   mpq_t qres;
   mpq_t qscale;
   
   unsigned long int scale = getShiftFactor(precision);
   
   // Initialize temporary variables
   mpq_init(qres);
   mpq_init(qscale);

   // Store into temporary variables
   mpq_set(qres, this->q);
   mpq_set_ui(qscale, scale, 1);

   // qres = qres * qscale
   mpq_mul(qres, qres, qscale);
   
   // qscale is no longer needed.
   // (we could cannibalize it's parts for temporaries, but won't.)
   mpq_clear(qscale);
   
   // We need an integer temporary now.
   mpz_t zres;
   mpz_t zrem;
   mpz_init(zres);
   mpz_init(zrem);
   
   // Do the divide:
   // zres = floor(qres)
   // note we keep the remainder, for checking.
   mpz_tdiv_qr(zres, zrem, mpq_numref(qres), mpq_denref(qres));
   
   // qres is no longer needed at this point
   mpq_clear(qres);
   
   {
      // Find out if the result fits into int.
      size_t sz = mpz_sizeinbase(zres, 2);
      if(sz > 64) {
         mpz_clear(zres);
         mpz_clear(zrem);
         CB_THROW(CBcExcBaseTypeRange());
      }
      if(sz == 64) {
         // pathological case.
         // since sz is the number of bits in the *absolute* value of zres,
         // we have to check for the case of INT8_MIN.
         mpz_neg(zres, zres);
         if(mpz_popcount(zres) != 1) {
            mpz_clear(zres);
            mpz_clear(zrem);
            CB_THROW(CBcExcBaseTypeRange());
         }
         mpz_neg(zres, zres);
      }
   }
   
   // Check if the conversion was inexact
   if(mpz_sgn(zrem) != 0)
   {
      mpz_clear(zres);
      mpz_clear(zrem);
      CB_DEADBRANCH( "lost precision" );
   }

   // This used to be:
   //signed long int ires = mpz_get_si(zres);
   // ...but sizeof(long)==4 on sunos.

        // TMDcm53739: mpz_export does not write anything (zero words)
   // in case zres is zero. So ires needs to be initialized.
   int ires=0;
   mpz_export(reinterpret_cast<void*>(&ires), NULL,
              1, 8, 0, 0, zres);
   if(mpz_sgn(zres)<0)
      ires = -ires;

   mpz_clear(zres);
   mpz_clear(zrem);
   return ires;
}



CoaRational CoaRational::fromStringPair(const QPair<QString,QString> & pair)
{
   const int base=10;
   
   CoaRational ret;
   
   if(mpz_set_str(mpq_numref(ret.q), pair.first.c_str(), base) < 0)
   {
      CB_THROW(CBcExcBaseTypeFormat()); // num not parseable as integer
   }
   
   if(mpz_set_str(mpq_denref(ret.q), pair.second.c_str(), base) < 0)
   {
      CB_THROW(CBcExcBaseTypeFormat()); // den not parseable as integer
   }
   
   // FIXME: more tests? i.e. den strictly positive?
   // (following line might bomb, otherwise)
   mpq_canonicalize(ret.q);
   
   return ret;
}

QPair<QString,QString> CoaRational::toStringPair() const
{
   const int base = 10;
   int num_len = mpz_sizeinbase(mpq_numref(q), base) + 2;   // sign + zero term
   int den_len = mpz_sizeinbase(mpq_denref(q), base) + 1;   // den can't be <0
   char * num_buf = new char[num_len];
   char * den_buf = new char[den_len];
   mpz_get_str(num_buf, base, mpq_numref(q));
   mpz_get_str(den_buf, base, mpq_denref(q));
   
   QString num(num_buf);
   QString den(den_buf);
   
   delete[] num_buf;
   delete[] den_buf;
   
   return QPair<QString,QString>(num, den);
}



//
// operators
//
CoaRational CoaRational::operator+(const CoaRational& rhs) const
{
   CoaRational tmp;
   mpq_add(tmp.q, this->q, rhs.q);
   return tmp;
}

CoaRational CoaRational::operator-(const CoaRational& rhs) const
{
   CoaRational tmp;
   mpq_sub(tmp.q, this->q, rhs.q);
   return tmp;
}


CoaRational CoaRational::operator*(const CoaRational& rhs) const
   
{
   CoaRational tmp;
   mpq_mul(tmp.q, this->q, rhs.q);
   return tmp;
}

CoaRational CoaRational::operator/(const CoaRational& rhs) const
{
   CoaRational tmp;
   mpq_div(tmp.q, this->q, rhs.q);
   return tmp;
}
   
CoaRational CoaRational::operator-() const
{
   CoaRational tmp;
   mpq_neg(tmp.q, this->q);
   return tmp;
}

bool CoaRational::operator>(const CoaRational& rhs) const
{
   return mpq_cmp(this->q, rhs.q) > 0;
}

bool CoaRational::operator<(const CoaRational& rhs) const
{
   return mpq_cmp(this->q, rhs.q) < 0;
}

bool CoaRational::operator>=(const CoaRational& rhs) const
{
   return !this->operator<(rhs);
}

bool CoaRational::operator<=(const CoaRational& rhs) const
{
   return !this->operator>(rhs);
}

bool CoaRational::operator==(const CoaRational& rhs) const
{
   return mpq_equal(this->q, rhs.q) != 0;
}

bool CoaRational::operator!=(const CoaRational& rhs) const  
{
   return !this->operator==(rhs);
}


