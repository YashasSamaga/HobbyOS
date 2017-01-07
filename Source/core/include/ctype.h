/******************************************************************************/
//	Character Types
//
//	ctype.h
//	Date: January 5th 2017
//
/******************************************************************************/
#ifndef __CTYPE_H
#define __CTYPE_H

/* Constants */
#define CT_UP	0x01	/* upper case */
#define CT_LOW	0x02	/* lower case */
#define CT_DIG	0x04	/* digit */
#define CT_CTL	0x08	/* control */
#define CT_PUN	0x10	/* punctuation */
#define CT_WHT	0x20	/* white space (space/cr/lf/tab) */
#define CT_HEX	0x40	/* hex digit */
#define CT_SP	0x80	/* hard space (0x20) */

unsigned short _ctype[257] = 
{
  0,                      // -1 EOF
  CT_CTL,               // 00 (NUL)
  CT_CTL,               // 01 (SOH)
  CT_CTL,               // 02 (STX)
  CT_CTL,               // 03 (ETX)
  CT_CTL,               // 04 (EOT)
  CT_CTL,               // 05 (ENQ)
  CT_CTL,               // 06 (ACK)
  CT_CTL,               // 07 (BEL)
  CT_CTL,               // 08 (BS)
  CT_SP+CT_CTL,        // 09 (HT)
  CT_SP+CT_CTL,        // 0A (LF)
  CT_SP+CT_CTL,        // 0B (VT)
  CT_SP+CT_CTL,        // 0C (FF)
  CT_SP+CT_CTL,        // 0D (CR)
  CT_CTL,               // 0E (SI)
  CT_CTL,               // 0F (SO)
  CT_CTL,               // 10 (DLE)
  CT_CTL,               // 11 (DC1)
  CT_CTL,               // 12 (DC2)
  CT_CTL,               // 13 (DC3)
  CT_CTL,               // 14 (DC4)
  CT_CTL,               // 15 (NAK)
  CT_CTL,               // 16 (SYN)
  CT_CTL,               // 17 (ETB)
  CT_CTL,               // 18 (CAN)
  CT_CTL,               // 19 (EM)
  CT_CTL,               // 1A (SUB)
  CT_CTL,               // 1B (ESC)
  CT_CTL,               // 1C (FS)
  CT_CTL,               // 1D (GS)
  CT_CTL,               // 1E (RS)
  CT_CTL,               // 1F (US)
  CT_SP+CT_WHT,          // 20 SPACE
  CT_PUN,                 // 21 !
  CT_PUN,                 // 22 "
  CT_PUN,                 // 23 #
  CT_PUN,                 // 24 $
  CT_PUN,                 // 25 %
  CT_PUN,                 // 26 &
  CT_PUN,                 // 27 '
  CT_PUN,                 // 28 (
  CT_PUN,                 // 29 )
  CT_PUN,                 // 2A *
  CT_PUN,                 // 2B +
  CT_PUN,                 // 2C ,
  CT_PUN,                 // 2D -
  CT_PUN,                 // 2E .
  CT_PUN,                 // 2F /
  CT_DIG+CT_HEX,            // 30 0
  CT_DIG+CT_HEX,            // 31 1
  CT_DIG+CT_HEX,            // 32 2
  CT_DIG+CT_HEX,            // 33 3
  CT_DIG+CT_HEX,            // 34 4
  CT_DIG+CT_HEX,            // 35 5
  CT_DIG+CT_HEX,            // 36 6
  CT_DIG+CT_HEX,            // 37 7
  CT_DIG+CT_HEX,            // 38 8
  CT_DIG+CT_HEX,            // 39 9
  CT_PUN,                 // 3A :
  CT_PUN,                 // 3B ;
  CT_PUN,                 // 3C <
  CT_PUN,                 // 3D =
  CT_PUN,                 // 3E >
  CT_PUN,                 // 3F ?
  CT_PUN,                 // 40 @
  CT_UP+CT_HEX,            // 41 A
  CT_UP+CT_HEX,            // 42 B
  CT_UP+CT_HEX,            // 43 C
  CT_UP+CT_HEX,            // 44 D
  CT_UP+CT_HEX,            // 45 E
  CT_UP+CT_HEX,            // 46 F
  CT_UP,                 // 47 G
  CT_UP,                 // 48 H
  CT_UP,                 // 49 I
  CT_UP,                 // 4A J
  CT_UP,                 // 4B K
  CT_UP,                 // 4C L
  CT_UP,                 // 4D M
  CT_UP,                 // 4E N
  CT_UP,                 // 4F O
  CT_UP,                 // 50 P
  CT_UP,                 // 51 Q
  CT_UP,                 // 52 R
  CT_UP,                 // 53 S
  CT_UP,                 // 54 T
  CT_UP,                 // 55 U
  CT_UP,                 // 56 V
  CT_UP,                 // 57 W
  CT_UP,                 // 58 X
  CT_UP,                 // 59 Y
  CT_UP,                 // 5A Z
  CT_PUN,                 // 5B [
  CT_PUN,                 // 5C back slash (actual character not used to prevent multi line comments) 
  CT_PUN,                 // 5D ]
  CT_PUN,                 // 5E ^
  CT_PUN,                 // 5F _
  CT_PUN,                 // 60 `
  CT_LOW+CT_HEX,            // 61 a
  CT_LOW+CT_HEX,            // 62 b
  CT_LOW+CT_HEX,            // 63 c
  CT_LOW+CT_HEX,            // 64 d
  CT_LOW+CT_HEX,            // 65 e
  CT_LOW+CT_HEX,            // 66 f
  CT_LOW,                 // 67 g
  CT_LOW,                 // 68 h
  CT_LOW,                 // 69 i
  CT_LOW,                 // 6A j
  CT_LOW,                 // 6B k
  CT_LOW,                 // 6C l
  CT_LOW,                 // 6D m
  CT_LOW,                 // 6E n
  CT_LOW,                 // 6F o
  CT_LOW,                 // 70 p
  CT_LOW,                 // 71 q
  CT_LOW,                 // 72 r
  CT_LOW,                 // 73 s
  CT_LOW,                 // 74 t
  CT_LOW,                 // 75 u
  CT_LOW,                 // 76 v
  CT_LOW,                 // 77 w
  CT_LOW,                 // 78 x
  CT_LOW,                 // 79 y
  CT_LOW,                 // 7A z
  CT_PUN,                 // 7B {
  CT_PUN,                 // 7C |
  CT_PUN,                 // 7D }
  CT_PUN,                 // 7E ~
  CT_CTL,               // 7F (DEL)
  // and the rest are 0...
};



/* Basic macros */
#define isalnum(c)	((_ctype + 1)[(unsigned)(c)] & (CT_UP | CT_LOW | CT_DIG))
#define isalpha(c)	((_ctype + 1)[(unsigned)(c)] & (CT_UP | CT_LOW))
#define iscntrl(c)	((_ctype + 1)[(unsigned)(c)] & (CT_CTL))
#define isdigit(c)	((_ctype + 1)[(unsigned)(c)] & (CT_DIG))
#define isgraph(c)	((_ctype + 1)[(unsigned)(c)] & (CT_PUN | CT_UP | CT_LOW | CT_DIG))
#define islower(c)	((_ctype + 1)[(unsigned)(c)] & (CT_LOW))
#define isprint(c)	((_ctype + 1)[(unsigned)(c)] & (CT_PUN | CT_UP | CT_LOW | CT_DIG | CT_SP))
#define ispunct(c)	((_ctype + 1)[(unsigned)(c)] & (CT_PUN))
#define isspace(c)	((_ctype + 1)[(unsigned)(c)] & (CT_WHT))
#define isupper(c)	((_ctype + 1)[(unsigned)(c)] & (CT_UP))
#define isxdigit(c)	((_ctype + 1)[(unsigned)(c)] & (CT_DIG | CT_HEX))
#define isascii(c)	((unsigned)(c) <= 0x7F)
#define toascii(c)	((unsigned)(c) & 0x7F)
#define tolower(c)	(isupper(c) ? c + 'a' - 'A' : c)
#define toupper(c)	(islower(c) ? c + 'A' - 'a' : c)

#endif // __CTYPE_H
