
// TakeOwnerShipDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TakeOwnerShip.h"
#include "TakeOwnerShipDlg.h"
#include "afxdialogex.h"
#include "atlbase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTakeOwnerShipDlg �Ի���




CTakeOwnerShipDlg::CTakeOwnerShipDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTakeOwnerShipDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTakeOwnerShipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTakeOwnerShipDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD, &CTakeOwnerShipDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DEL, &CTakeOwnerShipDlg::OnBnClickedDel)
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, &CTakeOwnerShipDlg::OnBnClickedButtonAbout)
END_MESSAGE_MAP()


// CTakeOwnerShipDlg ��Ϣ�������

BOOL CTakeOwnerShipDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTakeOwnerShipDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTakeOwnerShipDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTakeOwnerShipDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTakeOwnerShipDlg::OnBnClickedAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRegKey rkAdd;
	rkAdd.Create(HKEY_CLASSES_ROOT,_T("*\\shell\\takeownership"));
	rkAdd.SetValue(_T("����Աȡ������Ȩ"),_T(""));
	rkAdd.SetValue(_T(""),_T("HasLUAShield"));
	rkAdd.SetValue(_T(""),_T("NoWorkingDirectory"));
	rkAdd.Create(HKEY_CLASSES_ROOT,_T("*\\shell\\takeownership\\command"));
	rkAdd.SetValue(_T("cmd.exe /c takeown /f \"%1\" && icacls \"%1\" /grant administrators:F"),_T(""));
	rkAdd.SetValue(_T("cmd.exe /c takeown /f \"%1\" && icacls \"%1\" /grant administrators:F"),_T("IsolatedCommand"));

	rkAdd.Create(HKEY_CLASSES_ROOT,_T("exefile\\shell\\takeownership"));
	rkAdd.SetValue(_T("����Աȡ������Ȩ"),_T(""));
	rkAdd.SetValue(_T(""),_T("HasLUAShield"));
	rkAdd.SetValue(_T(""),_T("NoWorkingDirectory"));
	rkAdd.Create(HKEY_CLASSES_ROOT,_T("exefile\\shell\\takeownership\\command"));
	rkAdd.SetValue(_T("cmd.exe /c takeown /f \"%1\" && icacls \"%1\" /grant administrators:F"),_T(""));
	rkAdd.SetValue(_T("cmd.exe /c takeown /f \"%1\" && icacls \"%1\" /grant administrators:F"),_T("IsolatedCommand"));

	rkAdd.Create(HKEY_CLASSES_ROOT,_T("dllfile\\shell\\takeownership"));
	rkAdd.SetValue(_T("����Աȡ������Ȩ"),_T(""));
	rkAdd.SetValue(_T(""),_T("HasLUAShield"));
	rkAdd.SetValue(_T(""),_T("NoWorkingDirectory"));
	rkAdd.Create(HKEY_CLASSES_ROOT,_T("dllfile\\shell\\takeownership\\command"));
	rkAdd.SetValue(_T("cmd.exe /c takeown /f \"%1\" && icacls \"%1\" /grant administrators:F"),_T(""));
	rkAdd.SetValue(_T("cmd.exe /c takeown /f \"%1\" && icacls \"%1\" /grant administrators:F"),_T("IsolatedCommand"));

	rkAdd.Create(HKEY_CLASSES_ROOT,_T("Directory\\shell\\takeownership"));
	rkAdd.SetValue(_T("����Աȡ������Ȩ"),_T(""));
	rkAdd.SetValue(_T(""),_T("HasLUAShield"));
	rkAdd.SetValue(_T(""),_T("NoWorkingDirectory"));
	rkAdd.Create(HKEY_CLASSES_ROOT,_T("Directory\\shell\\takeownership\\command"));
	rkAdd.SetValue(_T("cmd.exe /c takeown /f \"%1\" /r /d y && icacls \"%1\" /grant administrators:F /t"),_T(""));
	rkAdd.SetValue(_T("cmd.exe /c takeown /f \"%1\" /r /d y && icacls \"%1\" /grant administrators:F /t"),_T("IsolatedCommand"));
	
	MessageBox(_T("��ӳɹ�"),_T("��ʾ"), MB_OK | MB_ICONINFORMATION);
}


void CTakeOwnerShipDlg::OnBnClickedDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRegKey rkDel;
	if(rkDel.Open(HKEY_CLASSES_ROOT,_T("*\\shell\\takeownership"))==ERROR_SUCCESS)
	{
	rkDel.Open(HKEY_CLASSES_ROOT,_T("*\\shell\\takeownership"));
	rkDel.DeleteSubKey(_T("command"));
	rkDel.Open(HKEY_CLASSES_ROOT,_T("*\\shell"));
	rkDel.DeleteSubKey(_T("takeownership"));

	rkDel.Open(HKEY_CLASSES_ROOT,_T("exefile\\shell\\takeownership"));
	rkDel.DeleteSubKey(_T("command"));
	rkDel.Open(HKEY_CLASSES_ROOT,_T("exefile\\shell"));
	rkDel.DeleteSubKey(_T("takeownership"));

	rkDel.Open(HKEY_CLASSES_ROOT,_T("dllfile\\shell\\takeownership"));
	rkDel.DeleteSubKey(_T("command"));
	rkDel.Open(HKEY_CLASSES_ROOT,_T("dllfile\\shell"));
	rkDel.DeleteSubKey(_T("takeownership"));

	rkDel.Open(HKEY_CLASSES_ROOT,_T("Directory\\shell\\takeownership"));
	rkDel.DeleteSubKey(_T("command"));
	rkDel.Open(HKEY_CLASSES_ROOT,_T("Directory\\shell"));
	rkDel.DeleteSubKey(_T("takeownership"));

	MessageBox(_T("ɾ���ɹ�"),_T("��ʾ"), MB_OK | MB_ICONINFORMATION);
	}
	else MessageBox(_T("δ��⵽�Ҽ�����ԱȨ�޲˵���"),_T("��ʾ"),MB_OK | MB_ICONSTOP);
}


void CTakeOwnerShipDlg::OnBnClickedButtonAbout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
}
