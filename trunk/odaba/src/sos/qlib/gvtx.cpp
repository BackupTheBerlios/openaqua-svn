/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    gvtx

\brief    


\date     $Date: 2006/07/28 11:40:59,09 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "gvtx"

#include  <pdefault.h>
#include  <sdttm.hpp>
#include  <igvtu.h>

#include  <igvtx.h>

/******************************************************************************/
/**
\brief  StringLength - 



\return int_len - 

\param  buffer - 
\param  int_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StringLength"

int __cdecl StringLength (char *buffer, int int_len )
{


  return(gvtutle0(buffer,int_len));


}

/******************************************************************************/
/**
\brief  gvtxaas - 



\return ubuffer - 

\param  ubuffer - 
\param  int_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxaas"

uint8 *__cdecl gvtxaas (uint8 *ubuffer, int int_len )
{
  uint8     *parea;
  int32      arealen = 256;
  int 	     i       = 0; 
  int        j       = 0;

 static uint8   area[256] = 
        {  0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07, // 00
           0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
           0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17, // 10
           0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,
           0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27, // 20
           0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
           0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37, // 30
           0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
           0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47, // 40
           0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,
           0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57, // 50
           0x58,0x59,0x5a,0x5b,0x5c,0x5d,0x5e,0x5f,
           0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67, // 60
           0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,
           0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77, // 70
           0x78,0x79,0x7a,0x7b,0x7c,0x7d,0x7e,0x7f,
           0xc7,0xfc,0xe9,0xe2,0xe4,0xe0,0xe5,0xe7, // 80
           0xea,0xeb,0xe8,0xef,0xee,0xec,0xc4,0xc5, 
           0xc9,0xe6,0xc6,0xf4,0xf6,0xf2,0xfb,0xf9, // 90
           0xff,0xd6,0xdc,0xf8,0xa3,0xd8,0xd7,0x1f, 
           0xe1,0xed,0xf3,0xfa,0xf1,0xd1,0xaa,0xba, // a0
           0xbf,0xae,0xac,0xbd,0xbc,0xa1,0xab,0xbb, 
           0x00,0x00,0x00,0x00,0x00,0xc1,0xc2,0xc0, // b0
           0xa9,0x00,0x00,0x00,0x00,0xa2,0xa5,0x00, 
           0x00,0x00,0x00,0x00,0x00,0x00,0xe3,0xc3, // c0
           0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xa4, 
           0xf0,0xd0,0xca,0xcb,0xc8,0x00,0xcd,0xce, // d0
           0xcf,0x00,0x00,0x00,0x00,0xa6,0xcc,0x00, 
           0xd3,0xdf,0xd4,0xd2,0xf5,0xd5,0x00,0xfe, // e0
           0xde,0xda,0xdb,0xd9,0xfd,0xdd,0xaf,0x00, 
           0x00,0xb1,0x3d,0xbe,0xb6,0xa7,0xf7,0xb8, // f0
           0x00,0xa8,0xb7,0xb9,0xb3,0xb2,0x00,0xa0, 
       };  

  parea = area ;
  while ( i <= int_len-1 )
  {   
    j = 0;
    while ( j < arealen )
    {
      if ( (memcmp(ubuffer+i,parea+j,1)) == 0 )
        break;
      j++;
    }     
    if ( j < arealen )
      *(ubuffer+i) = (uint8)j ;
    else
      *(ubuffer+i) = '.';
    i++;
  }
  return(ubuffer);
}

/******************************************************************************/
/**
\brief  gvtxans - 



\return ubuffer - 

\param  ubuffer - 
\param  int_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxans"

uint8 *__cdecl gvtxans (uint8 *ubuffer, int int_len )
{
 int        i = 0;

 static uint8   area[256] = 
        {  0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07, // 00
           0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
           0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17, // 10
           0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,
           0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27, // 20
           0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
           0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37, // 30
           0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
           0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47, // 40
           0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,
           0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57, // 50
           0x58,0x59,0x5a,0x5b,0x5c,0x5d,0x5e,0x5f,
           0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67, // 60
           0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,
           0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77, // 70
           0x78,0x79,0x7a,0x7b,0x7c,0x7d,0x7e,0x7f,
           0xc7,0xfc,0xe9,0xe2,0xe4,0xe0,0xe5,0xe7, // 80
           0xea,0xeb,0xe8,0xef,0xee,0xec,0xc4,0xc5, 
           0xc9,0xe6,0xc6,0xf4,0xf6,0xf2,0xfb,0xf9, // 90
           0xff,0xd6,0xdc,0xf8,0xa3,0xd8,0xd7,0x1f, 
           0xe1,0xed,0xf3,0xfa,0xf1,0xd1,0xaa,0xba, // a0
           0xbf,0xae,0xac,0xbd,0xbc,0xa1,0xab,0xbb, 
           0x00,0x00,0x00,0x00,0x00,0xc1,0xc2,0xc0, // b0
           0xa9,0x00,0x00,0x00,0x00,0xa2,0xa5,0x00, 
           0x00,0x00,0x00,0x00,0x00,0x00,0xe3,0xc3, // c0
           0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xa4, 
           0xf0,0xd0,0xca,0xcb,0xc8,0x00,0xcd,0xce, // d0
           0xcf,0x00,0x00,0x00,0x00,0xa6,0xcc,0x00, 
           0xd3,0xdf,0xd4,0xd2,0xf5,0xd5,0x00,0xfe, // e0
           0xde,0xda,0xdb,0xd9,0xfd,0xdd,0xaf,0x00, 
           0x00,0xb1,0x3d,0xbe,0xb6,0xa7,0xf7,0xb8, // f0
           0x00,0xa8,0xb7,0xb9,0xb3,0xb2,0x00,0xa0, 
       };  
                           
  while ( i <= int_len-1 )
  {
    if ( *(ubuffer+i) == '{' )  
      *(ubuffer+i) = '[';
    else if ( *(ubuffer+i) == '}' )  
      *(ubuffer+i) = ']';
    else if ( *(ubuffer+i) == 92  )    // '\'
      *(ubuffer+i) = '|';
    else  
      *(ubuffer+i) = area[(int) *(ubuffer+i)];
    i++;
  }
  return(ubuffer);

}

/******************************************************************************/
/**
\brief  gvtxasc - 



\return buffer - 

\param  buffer - 
\param  int_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxasc"

char *__cdecl gvtxasc (char *buffer, int int_len )
{

  while ( int_len )
    if ( buffer[--int_len] < ' ' )
      buffer[int_len] = ' ';
  return(buffer);

}

/******************************************************************************/
/**
\brief  gvtxath - 



\return targbuf - 

\param  targbuf - 
\param  buffer - 
\param  int_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxath"

char *__cdecl gvtxath (char *targbuf, char *buffer, int int_len )
{
  static  char *hliste={"0123456789ABCDEF"};
  register      i;

  for (i=0; i < int_len; i++)
  {
    targbuf[(int_len-i)*2-1] = hliste[buffer[int_len-i-1] & 0xf];
    targbuf[(int_len-i-1)*2] = hliste[(buffer[int_len-i-1] & 0xf0)>>4];
  }
  return(targbuf);

}

/******************************************************************************/
/**
\brief  gvtxbcs - 



\return string - String value

\param  string - String value
\param  buffer - 
\param  buflen - 
\param  maxlens - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxbcs"

char *__cdecl gvtxbcs (char *string, char *buffer, int buflen, int16 maxlens )
{
  int       slen = strlen(string);

  gvtxbts(string+slen,buffer,MIN(buflen,maxlens-slen-1));

  return(string);

}

/******************************************************************************/
/**
\brief  gvtxbtc - 



\return string - String value

\param  targarea - 
\param  tlen - 
\param  srcearea - 
\param  slen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxbtc"

char *__cdecl gvtxbtc (char *targarea, int32 tlen, char *srcearea, int32 slen )
{
  char      *target = targarea;
BEGINSEQ
  if ( !targarea || !srcearea || slen <= 0 )         ERROR
  if ( tlen <= 0 )                                   LEAVESEQ
  
  memset(targarea,' ',tlen);
  gvtxstb(targarea,srcearea,MIN(tlen,slen));
  
  while ( --tlen )
  {
    *targarea = *targarea ^ *(targarea+1);
    targarea++;
  }
  *targarea = *targarea ^ 0xFF;
RECOVER
  target = NULL;
ENDSEQ
  return (target);

}

/******************************************************************************/
/**
\brief  gvtxbtoa - 



\return string - String value

\param  val64 - 
\param  buffer - 
\param  radix - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxbtoa"

char *__cdecl gvtxbtoa (int64 val64, char *buffer, uint32 radix )
{

  gvtxxtoa(val64, buffer, radix);

  return (buffer);
}

/******************************************************************************/
/**
\brief  gvtxbtp - 



\return picbuf - 

\param  picbuf - 
\param  val64 - 
\param  int_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxbtp"

char *__cdecl gvtxbtp (char *picbuf, int64 val64, int int_len )
{
   char  buffer[34];
  gvtxbtoa(val64,buffer,10);
  
  gvtxxtp(picbuf,buffer,int_len);
  return(picbuf);

}

/******************************************************************************/
/**
\brief  gvtxbts - 



\return string - String value

\param  string - String value
\param  buffer_c - 
\param  int_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxbts"

char *__cdecl gvtxbts (char *string, const char *buffer_c, int int_len )
{
  int       chklen = 0;

BEGINSEQ
  if ( !buffer_c || !string )                           ERROR
    
  while ( buffer_c[chklen] && ++chklen < int_len ) ;

  while ( (buffer_c[--chklen] == ' ' ||  !buffer_c[chklen] )  &&  
          chklen >= 0 ) ;

  if ( ++chklen  )
    memcpy(string,buffer_c,chklen);

  string[chklen] = '\0';


RECOVER
  if ( string )
    *string = 0;
ENDSEQ
  return (string);

}

/******************************************************************************/
/**
\brief  gvtxbxor - 



\return string - String value

\param  buffer - 
\param  int_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxbxor"

char *__cdecl gvtxbxor (char *buffer, int int_len )
{

  while ( int_len-- )
    buffer[int_len] ^= 0xFF;
  return(buffer);
}

/******************************************************************************/
/**
\brief  gvtxcode - 



\return string - String value

\param  buffer - 
\param  int_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxcode"

char *__cdecl gvtxcode (char *buffer, int int_len )
{

  return(gvtxbxor(buffer,int_len));

}

/******************************************************************************/
/**
\brief  gvtxctb - 



\return string - String value

\param  targarea - 
\param  tlen - 
\param  srcearea - 
\param  slen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxctb"

char *__cdecl gvtxctb (char *targarea, int32 tlen, char *srcearea, int32 slen )
{
  char                *work_buf = targarea;
  logical              wb_alloc = NO;
BEGINSEQ
  if ( !targarea || !srcearea || slen <= 0 )         ERROR
  if ( tlen <= 0 )                                   LEAVESEQ
  
  if ( tlen < slen )
  {
    work_buf = (char *)malloc(slen);
    wb_alloc = YES;
  }
  else
    memset(targarea+slen,' ',tlen-slen);

  memcpy(work_buf,srcearea,slen);
  
  --slen;
  work_buf[slen] = work_buf[slen] ^ 0xFF;
  while ( slen-- )
    work_buf[slen] = work_buf[slen] ^ work_buf[slen+1];

  if ( wb_alloc )
  {
    memcpy(targarea,work_buf,tlen);
    free(work_buf);
  }

RECOVER
  targarea = NULL;
ENDSEQ
  return (targarea);

}

/******************************************************************************/
/**
\brief  gvtxctc - 



\return string - String value

\param  targarea - 
\param  tlen - 
\param  srcearea - 
\param  slen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxctc"

char *__cdecl gvtxctc (char *targarea, int32 tlen, char *srcearea, int32 slen )
{
  char                *work_buf = targarea;
  logical              wb_alloc = NO;
BEGINSEQ
  if ( !targarea || !srcearea || slen <= 0 )         ERROR
  if ( tlen <= 0 )                                   LEAVESEQ
  
  if ( tlen < slen )
  {
    work_buf = (char *)malloc(slen);
    wb_alloc = YES;
  }
  else
    memset(targarea+slen,' ',tlen-slen);
    
  memcpy(work_buf,srcearea,slen);
    
  if ( tlen == slen )                                LEAVESEQ

  gvtxctb(work_buf,slen,work_buf,slen);
  gvtxctb(work_buf,tlen,work_buf,tlen);

  if ( wb_alloc )
  {
    memcpy(targarea,work_buf,tlen);
    free(work_buf);
  }

RECOVER
  targarea = NULL;
ENDSEQ
  return (targarea);

}

/******************************************************************************/
/**
\brief  gvtxcth - 



\return buffer - 

\param  buffer - 
\param  ucharval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxcth"

char *__cdecl gvtxcth (char *buffer, uint8 ucharval )
{
  static char *hliste={"0123456789ABCDEF"};

  buffer += 1;

  *(buffer--) = hliste[ucharval & 0xf];
  *buffer     = hliste[(ucharval & 0xf0)>>4];

  return(buffer);
}

/******************************************************************************/
/**
\brief  gvtxdecode - 



\return string - String value

\param  buffer - 
\param  int_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxdecode"

char *__cdecl gvtxdecode (char *buffer, int int_len )
{

  return(gvtxbxor(buffer,int_len));

}

/******************************************************************************/
/**
\brief  gvtxgst - 



\return string - String value

\param  buffer - 
\param  len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxgst"

char *__cdecl gvtxgst (char *buffer, size_t len )
{
  static     char string[256];
  return ( gvtxbts(string,buffer,MIN(len,sizeof(string)-1)) );

}

/******************************************************************************/
/**
\brief  gvtxhti - 



\return short_val - 

\param  buffer - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxhti"

uint16 __cdecl gvtxhti (char *buffer )
{
  ushort        val = 0;

  val += gvtxhtn(*buffer++) << 12;
  val += gvtxhtn(*buffer++) <<  8;
  val += gvtxhtn(*buffer++) <<  4;
  val += gvtxhtn(*buffer++)      ;

  return(val);

}

/******************************************************************************/
/**
\brief  gvtxhtl - 



\return long_val - 

\param  buffer - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxhtl"

uint32 __cdecl gvtxhtl (char *buffer )
{
  uint32       val = 0;

  val += gvtxhtn(*buffer++) << 28;
  val += gvtxhtn(*buffer++) << 24;
  val += gvtxhtn(*buffer++) << 20;
  val += gvtxhtn(*buffer++) << 16;
  val += gvtxhtn(*buffer++) << 12;
  val += gvtxhtn(*buffer++) <<  8;
  val += gvtxhtn(*buffer++) <<  4;
  val += gvtxhtn(*buffer++)      ;

  return(val);

}

/******************************************************************************/
/**
\brief  gvtxhtn - 



\return int_val - 

\param  ucharval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxhtn"

int __cdecl gvtxhtn (uint8 ucharval )
{
  int    val;

  val = ucharval-'0';
  if ( val < 0 || val > 9 )
  {
    val = 10 + ucharval-'A';
    if ( val < 10 || val > 15 )
      val = AUTO;
  }
  

  return(val);
}

/******************************************************************************/
/**
\brief  gvtxith - 



\return buffer - 

\param  buffer - 
\param  intsval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxith"

char *__cdecl gvtxith (char *buffer, int16 intsval )
{
  static char *hliste={"0123456789ABCDEF"};

  buffer += 3;

  *(buffer--) = hliste[intsval & 0xf];
  *(buffer--) = hliste[(intsval & 0xf0)>>4];
  *(buffer--) = hliste[(intsval & 0xf00)>>8];
  *buffer     = hliste[(intsval & 0xf000)>>12];

  return(buffer);

}

/******************************************************************************/
/**
\brief  gvtxitoa - 



\return string - String value

\param  intsval - 
\param  buffer - 
\param  radix - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxitoa"

char *__cdecl gvtxitoa (int16 intsval, char *buffer, uint32 radix )
{

  gvtxxtoa(intsval, buffer, radix);

  return (buffer);

}

/******************************************************************************/
/**
\brief  gvtxitp - 



\return picbuf - 

\param  picbuf - 
\param  intsval - 
\param  int_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxitp"

char *__cdecl gvtxitp (char *picbuf, int16 intsval, int int_len )
{
   char  buffer[18];

  gvtxitoa (intsval, buffer, 10);
  
  gvtxxtp(picbuf,buffer,int_len);
  return(picbuf);

}

/******************************************************************************/
/**
\brief  gvtxlth - 



\return buffer - 

\param  buffer - 
\param  intval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxlth"

char *__cdecl gvtxlth (char *buffer, int32 intval )
{
  static char *hliste={"0123456789ABCDEF"};

  buffer += 7;

  *(buffer--) = hliste[intval  & 0xf];
  *(buffer--) = hliste[(intval & 0xf0)>>4];
  *(buffer--) = hliste[(intval & 0xf00)>>8];
  *(buffer--) = hliste[(intval & 0xf000)>>12];
  *(buffer--) = hliste[(intval & 0xf0000)>>16];
  *(buffer--) = hliste[(intval & 0xf00000)>>20];
  *(buffer--) = hliste[(intval & 0xf000000)>>24];
  *buffer     = hliste[(intval & 0xf0000000)>>28];

  return(buffer);

}

/******************************************************************************/
/**
\brief  gvtxltoa - 



\return string - String value

\param  intval - 
\param  buffer - 
\param  radix - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxltoa"

char *__cdecl gvtxltoa (int32 intval, char *buffer, uint32 radix )
{

  gvtxxtoa(intval, buffer, radix);

  return (buffer);
}

/******************************************************************************/
/**
\brief  gvtxltp - 



\return picbuf - 

\param  picbuf - 
\param  intval - 
\param  int_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxltp"

char *__cdecl gvtxltp (char *picbuf, int32 intval, int int_len )
{
   char  buffer[34];
  gvtxltoa(intval,buffer,10);
  
  gvtxxtp(picbuf,buffer,int_len);
  return(picbuf);

}

/******************************************************************************/
/**
\brief  gvtxstb - 



\return buffer - 

\param  buffer - 
\param  string_c - 
\param  int_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxstb"

char *__cdecl gvtxstb (char *buffer, const char *string_c, int int_len )
{
  register  i;

BEGINSEQ
  if ( !buffer || !string_c )                           ERROR
    
  for ( i=0;  i < int_len  &&  string_c[i];  i++ )
    buffer[i] = string_c[i];

  for (  ;  i < int_len;  i++ )
    buffer[i] = ' ';

RECOVER
  if ( buffer )
    memset(buffer,' ',int_len);
ENDSEQ
   return(buffer);

}

/******************************************************************************/
/**
\brief  gvtxxtoa - 




\param  val64 - 
\param  buffer - 
\param  radix - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxxtoa"

void __cdecl gvtxxtoa (int64 val64, char *buffer, uint32 radix )
{
  char     *p;                /* pointer to traverse string */
  char     *firstdig;         /* pointer to first digit */
  char     temp;              /* temp char */
  uint64   uval = (uint64)val64;
  unsigned digval;            /* value of digit */

  p = buffer;

  if ( radix == 10 && val64 < 0 ) 
  {
    /* negative, so output '-' and negate */
    *p++ = '-';
    uval = (uint64)(-val64);
  }

  firstdig = p;           /* save pointer to first digit */
  
  do 
  {
    digval = (unsigned) (uval % radix);
    uval /= radix;       /* get next digit */

    /* convert to ascii and store */
    if (digval > 9)
      *p++ = (char) (digval - 10 + 'a');  /* a letter */
    else
      *p++ = (char) (digval + '0');       /* a digit */
  } while (uval > 0);

  /* We now have the digit of the number in the buffer, but in reverse
     order.  Thus we reverse them now. */

  *p-- = '\0';            /* terminate string; p points to last digit */
  
  do 
  {
    temp = *p;
    *p = *firstdig;
    *firstdig = temp;   /* swap *p and *firstdig */
    --p;
    ++firstdig;         /* advance to next two digits */
  } 
  while (firstdig < p); /* repeat until halfway */


}

/******************************************************************************/
/**
\brief  gvtxxtp - 



\return picbuf - 

\param  picbuf - 
\param  string - String value
\param  int_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtxxtp"

char *__cdecl gvtxxtp (char *picbuf, char *string, int int_len )
{
   char  sign='+';
   int   firstdig=0;
   int   i,k;

  if ( string[0] == '-' )
  {
    firstdig = 1;
    sign     = '-';
  }

  for (i = strlen(string), k=int_len; i > firstdig  &&  k > 0; k-- )
  {
    switch ( picbuf[k-1] )
    {
      case 'S':  picbuf[k-1] = sign;
	         break;
      case '-':  if ( sign == '+' )
	           picbuf[k-1] = ' ';
                 break;
      case '9':  picbuf[k-1] = string[i-1];
	         i--;
                 break;
      case 'Z':  picbuf[k-1] = string[i-1];
	         i--;
                 break;
    }
  }

  if ( i > firstdig ) 
    memset(picbuf,'*',int_len);

  for ( ;k > 0;k-- )
  {
    switch ( picbuf[k-1] )
    {
      case 'S':  picbuf[k-1] = sign;
	         break;
      case '-':  if ( sign == '+' )
	           picbuf[k-1] = ' ';
                 break;
      case '9':  picbuf[k-1] = '0';
	         break;
      case 'Z':  picbuf[k-1] = ' ';
	         break;
      case '.':  if ( k>1  &&  picbuf[k-2] == 'Z')  
                   picbuf[k-1] = ' ';
     	         break;
    }
  }

  return(picbuf);

}

