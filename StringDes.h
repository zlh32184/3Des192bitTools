// StringDes.h: interface for the CStringDes class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGDES_H__E950AE5E_DC35_46C9_ADFA_B5788B69C720__INCLUDED_)
#define AFX_STRINGDES_H__E950AE5E_DC35_46C9_ADFA_B5788B69C720__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStringDes  
{
public:
	CStringDes();
	virtual ~CStringDes();
	void str_des_crypt(unsigned char MWEN[],unsigned char KEY[],int flag,unsigned char cr_block[]) ;
	void str_3des_crypt(unsigned char *MWEN, unsigned char *KEY, int flag, unsigned char *cr_block);
	void str_3des_crypt_192bit(unsigned char *MWEN, unsigned char *KEY, int flag, unsigned char *cr_block);
	
long str_str2bcdhex(unsigned char *str, unsigned char *hex, int tag);
void str_bcdhex2str_ABC(unsigned char *hex, unsigned char *str, int length, int tag);
void str_hex2str_ABC(unsigned char *hex, unsigned char *str, int length);
void str_str2hex(unsigned char *str, unsigned char *hex);
void str_alltrim( char *str ) ;
unsigned char * str_ltrim( unsigned char *str ) ;    /*    б┴ио??????    */
unsigned char * str_rtrim(unsigned char *str )  ;  


void str_c16to8(unsigned char *c16, unsigned char *c8);
void str_c8to16(unsigned char *c8, unsigned char *c16);



private:
	void user_des_getk(int ki[16][48],int keyi[64],int flag);
	int *user_des_f(int fr[32],int fk[48]);
};

#endif // !defined(AFX_STRINGDES_H__E950AE5E_DC35_46C9_ADFA_B5788B69C720__INCLUDED_)
