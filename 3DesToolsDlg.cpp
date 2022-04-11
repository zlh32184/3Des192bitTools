// 3DesToolsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "3DesTools.h"
#include "3DesToolsDlg.h"
#include "StringDes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy3DesToolsDlg dialog

CMy3DesToolsDlg::CMy3DesToolsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy3DesToolsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMy3DesToolsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy3DesToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy3DesToolsDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMy3DesToolsDlg, CDialog)
	//{{AFX_MSG_MAP(CMy3DesToolsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDOK2, OnOk2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy3DesToolsDlg message handlers

BOOL CMy3DesToolsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMy3DesToolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy3DesToolsDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMy3DesToolsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CMy3DesToolsDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN || pMsg->message == WM_KEYUP ){
		switch(pMsg->wParam){
		case VK_ESCAPE:
			return FALSE;
			break;
		default:
			break;
		}
		ShowInput();
	}
// 	else if( pMsg->message == WM_LBUTTONDOWN )
// 	{
// 		ShowInput();
// 	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CMy3DesToolsDlg::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::CalcWindowRect(lpClientRect, nAdjustType);
}
void CMy3DesToolsDlg::ShowInput()
{
	char buff[255],cnt[3];
	CString cStr;
	
	((CEdit *)GetDlgItem(IDC_DATA))->SetLimitText(254);
	((CEdit *)GetDlgItem(IDC_KEY))->SetLimitText(48);
	
	GetDlgItem(IDC_STATUS)->SetWindowText("");

	GetDlgItem(IDC_DATA)->GetWindowText(cStr);
	memset(buff,0x00,sizeof(buff));
	strcpy( buff,cStr.GetBuffer( 254 ) );
	sprintf( cnt,"%2.2d",strlen(buff) );
	GetDlgItem(IDC_S1)->SetWindowText( cnt );	
	if ( strlen(buff) > 254 )
	{
		GetDlgItem(IDC_STATUS)->SetWindowText("Data length must be < 254");
		return;
	}
	
	GetDlgItem(IDC_KEY)->GetWindowText(cStr);
	memset(buff,0x00,sizeof(buff));
	strcpy( buff,cStr.GetBuffer( 254 ) );
	sprintf( cnt,"%2.2d",strlen(buff) );
	GetDlgItem(IDC_S2)->SetWindowText( cnt );	
	if ( strlen(buff) > 0 && strlen(buff)!= 48 )
	{
		GetDlgItem(IDC_STATUS)->SetWindowText("KEY length must be = 48");
		return;
	}



}

void CMy3DesToolsDlg::OnOK() 
{
	// TODO: Add extra validation here
	EncDecFun(0);
	
// 	CDialog::OnOK();
}

void CMy3DesToolsDlg::OnCancel() 
{
	// TODO: Add extra cleanup here

	CDialog::OnCancel();
}

void CMy3DesToolsDlg::EncDecFun(int mode)
{
	char tmp[255];
	char szData[255], szKey[255], szResult[255];
	char inData[255], inKey[255], outBuff[255];
	CString strBuff;
	CStringDes csd;
	int i=0, dataLen=0;

	GetDlgItem(IDC_DATA)->GetWindowText(strBuff);
	memset( szData, 0x00, sizeof (szData));
	strcpy( szData, strBuff.GetBuffer(254));
	csd.str_alltrim(szData);

	if ( strlen(szData)<=0)
	{
		GetDlgItem(IDC_STATUS)->SetWindowText("Data length is null, please input it");
		return;
	}

	GetDlgItem(IDC_KEY)->GetWindowText(strBuff);
	memset( szKey, 0x00, sizeof(szKey));
	strcpy( szKey, strBuff.GetBuffer(254));
	csd.str_alltrim(szKey);
	if ( strlen(szKey)!=48)
	{
		GetDlgItem(IDC_STATUS)->SetWindowText("key length must 48");
		return;
	}
	
	memset( inKey, 0x00, sizeof(inKey));
	csd.str_str2hex( (unsigned char *)szKey, (unsigned char *)inKey );
	memset( outBuff, 0x00, sizeof(outBuff));
	if ( mode )
	{
		dataLen = strlen(szData);
		i=0;
		while( (dataLen-i)/16>0 )
		{
			memset( tmp, 0x00, sizeof(tmp));
			memcpy( tmp, szData+i,16);	
			memset( inData, 0x00, sizeof(inData));
			csd.str_str2hex( (unsigned char *)tmp, (unsigned char *)inData );
			
			memset( outBuff, 0x00, sizeof(outBuff));
			csd.str_3des_crypt_192bit( (unsigned char *)inData, (unsigned char *)inKey, 1, (unsigned char *)outBuff);
			csd.str_c16to8((unsigned char *)outBuff, (unsigned char *)szResult+i/2 );
			i+=16;
		}
// 		memset( szResult, 0x00, sizeof(szResult));	
// 		csd.str_hex2str_ABC((unsigned char *)outBuff, (unsigned char *)szResult, i );
// 		csd.str_str2bcdhex( (unsigned char *)szResult, (unsigned char *)outBuff, 0 );
// 		strcpy( szResult, outBuff );
		
	}
	else
	{
		dataLen = strlen(szData);
		i=0;
		while( (dataLen-i)/8>0 )
		{
			memset( tmp, 0x00, sizeof(tmp));
			memcpy( tmp, szData+i,8);			
			memset( inData, 0x00, sizeof(inData));
			//csd.str_bcdhex2str_ABC( (unsigned char *)tmp, (unsigned char *)inData, 16, 0 );
			csd.str_c8to16( (unsigned char *)tmp, (unsigned char *)inData );
			csd.str_3des_crypt_192bit( (unsigned char *)inData, (unsigned char *)inKey, 0, (unsigned char *)outBuff+(i*2));
			
			i+=8;
		}
		if ( (dataLen-i)%8!=0)
		{
			memset( tmp, 0x00, sizeof(tmp));
			memcpy( tmp, szData+i,8);			
			memset( inData, 0x00, sizeof(inData));
			// csd.str_bcdhex2str_ABC( (unsigned char *)tmp, (unsigned char *)inData, 16, 0 );	
			csd.str_c8to16( (unsigned char *)tmp, (unsigned char *)inData );
			csd.str_3des_crypt_192bit( (unsigned char *)inData, (unsigned char *)inKey, 0, (unsigned char *)outBuff+(i*2));
			
			i+=8;
		}

		memset( szResult, 0x00, sizeof(szResult));
		csd.str_hex2str_ABC( (unsigned char *)outBuff, (unsigned char *)szResult, i*2 );
			
	}
	
	GetDlgItem( IDC_RESULT)->SetWindowText(szResult);


}


void CMy3DesToolsDlg::OnOk2() 
{
	// TODO: Add your control notification handler code here
	EncDecFun(1);
}
