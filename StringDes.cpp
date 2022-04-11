// StringDes.cpp: implementation of the CStringDes class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StringDes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStringDes::CStringDes()
{

}

CStringDes::~CStringDes()
{

}

/* flag==0 to encrypt,flag==1 to decrypt */
void CStringDes::str_des_crypt(unsigned char MWEN[],unsigned char KEY[],int flag,unsigned char cr_block[]) 
{
	int mwen[64],key[64];
	static int ip[64]={58,50,42,34,26,18,10,2,
		      60,52,44,36,28,20,12,4,
		      62,54,46,38,30,22,14,6,
		      64,56,48,40,32,24,16,8,
		      57,49,41,33,25,17,9,1,
		      59,51,43,35,27,19,11,3,
		      61,53,45,37,29,21,13,5,
		      63,55,47,39,31,23,15,7};

	static int rip[64]={40,8,48,16,56,24,64,32,
		       39,7,47,15,55,23,63,31,
		       38,6,46,14,54,22,62,30,
		       37,5,45,13,53,21,61,29,
		       36,4,44,12,52,20,60,28,
		       35,3,43,11,51,19,59,27,
		       34,2,42,10,50,18,58,26,
		       33,1,41,9,49,17,57,25};
	int trav[64],l0[32],r0[32],l[64];
	int k[16][48];
	int i,j,*fp;

	for(i=0;i<16;i++)
	{
		mwen[i*4]=(int)((MWEN[i]&0x08)>>3);
		mwen[i*4+1]=(int)((MWEN[i]&0x04)>>2);
		mwen[i*4+2]=(int)((MWEN[i]&0x02)>>1);
		mwen[i*4+3]=(int)((MWEN[i]&0x01));

		key[i*4]=(int)((KEY[i]&0x08)>>3);
		key[i*4+1]=(int)((KEY[i]&0x04)>>2);
		key[i*4+2]=(int)((KEY[i]&0x02)>>1);
		key[i*4+3]=(int)((KEY[i]&0x01));
	}

	user_des_getk(k,key,flag);

	for ( i=0; i<64;i++)
	{
		trav[i]=mwen[ip[i]-1];
	}
	for (i=0;i<32;i++)
	{
		l0[i]=trav[i];
		r0[i]=trav[i+32];
	}
	for (i=0;i<16;i++)
	{
		fp=user_des_f(r0,k[i]);
		for (j=0;j<32;j++)
		{
			l[j]=r0[j];
			l[j+32]=l0[j]^*(fp+j);
		}
		for (j=0;j<32;j++)
		{
			l0[j]=l[j];
			r0[j]=l[j+32];
		}
	}
	for (i=0;i<32;i++)
	{
		l[i]=r0[i];
		l[i+32]=l0[i];
	}
	for (i=0;i<64;i++)
	{
		trav[i]=l[rip[i]-1]; 
	} 
	for (i=0;i<16;i++) 
	{
		cr_block[i]=trav[i*4]*8+trav[i*4+1]*4+trav[i*4+2]*2+trav[i*4+3];
	}
	return;
}


/* flag==0 to encrypt,flag==1 to decrypt */
void CStringDes::user_des_getk(int ki[16][48],int keyi[64],int flag)	 
{
	static int mc[2][16]={
			{1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1},
  			{28,27,26,26,26,26,26,26,27,26,26,26,26,26,26,27},
		       };
	static int pc1[56]={57,49,41,33,25,17,9,
		      1,58,50,42,34,26,18,
		      10,2,59,51,43,35,27,
		      19,11,3,60,52,44,36,
		      63,55,47,39,31,23,15,
		      7,62,54,46,38,30,22,
		      14,6,61,53,45,37,29,
		      21,13,5,28,20,12,4};
	static int pc2[48]={14,17,11,24,1,5,
		      3,28,15,6,21,10,
		      23,19,12,4,26,8,
		      16,7,27,20,13,2,
		      41,52,31,37,47,55,
		      30,40,51,45,33,48,
		      44,49,39,56,34,53,
		      46,42,50,36,29,32};
	int i,j,n,tem1,tem2,trav1[56];


	for (i=0;i<56;i++)
	{
		trav1[i]=keyi[pc1[i]-1];
	}
	for (i=0;i<16;i++)
	{
		for (j=0;j<mc[flag][i];j++)
		{
			tem1=trav1[0];
			tem2=trav1[28];
			for (n=0;n<27;n++)
			{
				trav1[n]=trav1[n+1];
				trav1[n+28]=trav1[n+28+1];
			}
			trav1[27]=tem1;
			trav1[55]=tem2;
		}
		for (n=0;n<48;n++)
			ki[i][n]=trav1[pc2[n]-1];
	}
}

int * CStringDes::user_des_f(int fr[32],int fk[48])
{
	static int e[48]={32,1,2,3,4,5,
		    4,5,6,7,8,9,
		    8,9,10,11,12,13,
		    12,13,14,15,16,17,
		    16,17,18,19,20,21,
		    20,21,22,23,24,25,
		    24,25,26,27,28,29,
		    28,29,30,31,32,1};
	static int s[8][4][16]={{{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
			   {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
			   {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
			   {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},
			   {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
			   {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
			   {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
			   {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},
			   {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
			   {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
			   {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
			   {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},
			   {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
			   {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
			   {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
			   {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},
			   {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
			   {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
			   {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
			   {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},
			   {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
			   {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
			   {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
			   {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},
			   {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
			   {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
			   {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
			   {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},
			   {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
			   {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
			   {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
			   {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}};
	static int p[32]={16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,
		    8,24,14,32,27,3,9,19,13,30,6,22,11,4,25
			};

	int i,row,col,temp;
	static int trav2[48],e0[32],ffk[32];

	for (i=0;i<48;i++)
	{
		trav2[i]=fr[e[i]-1];
		trav2[i]=trav2[i]^fk[i];
	}
	for (i=0;i<8;i++)
	{
		row=trav2[i*6]*2+trav2[i*6+5];
		col=trav2[i*6+1]*8+trav2[i*6+2]*4+trav2[i*6+3]*2+trav2[i*6+4];
		temp=s[i][row][col];
		e0[i*4]=temp/8;
		e0[i*4+1]=(temp%8)/4;
		e0[i*4+2]=(temp%4)/2;
		e0[i*4+3]=temp%2;
	}
	for (i=0;i<32;i++)
	{
		ffk[i]=e0[p[i]-1];
	}
	return((int *)ffk);
}

void CStringDes::str_3des_crypt(unsigned char *MWEN, unsigned char *KEY, int flag, unsigned char *cr_block)
{

	unsigned char now_block[16],now_block1[16];

	if ( flag == 0 ) {
		str_des_crypt(MWEN,KEY,0,now_block);
		str_des_crypt(now_block,KEY+16,1,now_block1);
		str_des_crypt(now_block1,KEY,0,now_block);
	}
	else {
		str_des_crypt(MWEN,KEY,1,now_block);
		str_des_crypt(now_block,KEY+16,0,now_block1);
		str_des_crypt(now_block1,KEY,1,now_block);
	}
	memcpy( cr_block, now_block, 16 );
}

void CStringDes::str_3des_crypt_192bit(unsigned char *MWEN, unsigned char *KEY, int flag, unsigned char *cr_block)
{
	unsigned char now_block[17],now_block1[17];
	memset( now_block, 0x00, sizeof(now_block));
	memset( now_block1, 0x00, sizeof(now_block1));
	
	if ( flag == 0 ) {
		str_des_crypt(MWEN,KEY,0,now_block);
		str_des_crypt(now_block,KEY+16,1,now_block1);
		str_des_crypt(now_block1,KEY+32,0,now_block);
	}
	else {
		str_des_crypt(MWEN,KEY+32,1,now_block);
		str_des_crypt(now_block,KEY+16,0,now_block1);
		str_des_crypt(now_block1,KEY,1,now_block);
	}
	memcpy( cr_block, now_block, 16 );
}

void CStringDes::str_str2hex(unsigned char *str, unsigned char *hex)
{
	int	i,len;
	unsigned char ch;
	
	len = strlen( (char *)str );
	for( i=0;i<len;i++ ) 
	{
		ch = str[i];
		if( ch >= '0' && ch <= 0x3f )
			ch -= '0';
		else if( ch >= 'a' && ch <= 'f' )
			ch = ch - 'a' + 10;
		else
			ch = ch - 'A' + 10;
		hex[i] = ch;
	}
	return;
}

void CStringDes::str_hex2str_ABC(unsigned char *hex, unsigned char *str, int length)
{
	int	i;
	unsigned char ch;
	
	for( i=0;i<length;i++ ) 
	{
		if ( hex[i] <=9 )
			ch = hex[i]+'0';
		else
			ch = hex[i]+'A'-10;
		str[i] = ch;
	}
	str[i]=0x0;
	return;
}


void CStringDes::str_c8to16(unsigned char *c8, unsigned char *c16)
{
	int i, j;
	memset(c16, 0x00, 16);
	for(i=0; i<16; i++)  {
		j = i/2;
		if(i%2)
			c16[i] = c8[j]&0x0f;
		else
			c16[i] = (c8[j]&0xf0) >> 4;
	}
}

void CStringDes::str_c16to8(unsigned char *c16, unsigned char *c8)
{
	int i, j;
	memset(c8, 0x00, 8);
	for(i=0;i<16;i++) {
		j = i/2;
		if(i%2)
			c8[j] = c8[j] | c16[i];
		else
			c8[j] = c16[i] << 4;
	}
}

void CStringDes::str_bcdhex2str_ABC(unsigned char *hex, unsigned char *str, int length, int tag)
/* tag:0-℅車??bcd??1-????bcd */
{
	int	i;
	unsigned char ch;
	int check;
	
	if ( length % 2 )
		check=1;
	else
		check=0;
	
	for( i=0;i<length;i++ ) 
	{
		if ( check==0 || tag==0 ) {
			if( i%2 == 0 )
				ch = ( hex[i/2] & 0xf0 ) >> 4;
			else
				ch = hex[i/2] & 0x0f;
		}
		else {  //?∟?????????????豕????
			if( i%2 )
				ch = ( hex[i/2+1] & 0xf0 ) >> 4;
			else
				ch = hex[i/2] & 0x0f;
		}
		if ( ch <= 9 )
			str[i]=ch+'0';
		else
			str[i]=ch+'A'-10;
	}
	str[i]=0x0;
	return;
}

long CStringDes::str_str2bcdhex(unsigned char *str, unsigned char *hex, int tag)
/* tag:0-℅車??bcd??1-????bcd */
{
	int	i,check,len;
	unsigned char ch;
	
	if ( strlen((char *)str) % 2 )
		check=1;
	else
		check=0;
	
	len = strlen( (char *)str );
	for( i=0;i<len;i++ ) 
	{
		ch = str[i];
		if( ch >= '0' && ch <= 0x3f )
			ch -= '0';
		else if( ch >= 'a' && ch <= 'f' )
			ch = ch - 'a' + 10;
		else
			ch = ch - 'A' + 10;
		if ( check==0 || tag==0 ) {
			if( i%2 == 0 )
				hex[i/2] = ch * 16;
			else
				hex[i/2] += ch;
		}
		else {	//?∟?????????????豕????
			if( i%2 )
				hex[i/2+1] = ch * 16;
			else
				if( i )
					hex[i/2] += ch;
				else
					hex[i/2] = ch;
		}
	}
	return( strlen((char *)str)/2 + strlen((char *)str)%2 );
}
unsigned char * CStringDes::str_ltrim( unsigned char *str )     /*    ℅車??????    */
{
	int i;
	i=0;
	while ( *(str+i)==' ' || *(str+i)=='\t' )
		i++;
	strcpy((char *)str,(char *)str+i);
	return( str );
}

unsigned char * CStringDes:: str_rtrim(unsigned char *str )     
/*    ????????    */
{
	int i;
	
	i=strlen( (char *)str )-1;
	while ( ( *(str+i)=='\t' || *(str+i)==' ' ) && i>=0 )
		i--;
	i++;
	*( str+i )='\0';
	return( str );
}

void CStringDes::str_alltrim( char *str )        /*    ????℅車??????    */
{
	unsigned char *string;
	
	string=str_ltrim( (unsigned char *)str );
	string=str_rtrim( (unsigned char *)string );
	strcpy( str,(char *)string );
}