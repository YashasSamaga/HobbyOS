/******************************************************************************/
//	Generic String Library
//
//	Standard String Library Routines Implementation
//
//	string.c
//	Date: January 5th 2017
//
/******************************************************************************/
void itoa(unsigned i, unsigned base, char *buf) 
{
	int pos = 0, opos = 0, top = 0;

	static char tbuf[32];
	static char bchars[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
   
	if (i == 0 || base > 16) 
	{
		buf[0] = '0';
		buf[1] = '\0';
		return;
	}

	while (i != 0) 
	{
		tbuf[pos] = bchars[i % base];
		pos++;
		i /= base;
	}
	top=pos--;
	
	for (opos=0; opos<top; pos--,opos++) 
      buf[opos] = tbuf[pos];

   buf[opos] = 0;
}
void itoa_s(int i, unsigned base, char *buf) 
{
   if (base > 16) return;
   if (i < 0) 
   {
      *buf++ = '-';
      i *= -1;
   }
   itoa(i,base,buf);
}