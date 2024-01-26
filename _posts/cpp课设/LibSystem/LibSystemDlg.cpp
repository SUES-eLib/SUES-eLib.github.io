
// LibSystemDlg.cpp: 实现文件
//

#include "pch.h"
#include "CDlgIndex.h"
#include "CDlgUserIndex.h"
#include "CDataAdapter.h"
#include "CUser.h"
#include "framework.h"
#include "LibSystem.h"
#include "LibSystemDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLibSystemDlg 对话框



CLibSystemDlg::CLibSystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LIBSYSTEM_DIALOG, pParent)
	, m_csName(_T(""))
	, m_csPwd(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLibSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NAME, m_csName);
	DDX_Text(pDX, IDC_PWD, m_csPwd);
}

BEGIN_MESSAGE_MAP(CLibSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CLibSystemDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_PWD, &CLibSystemDlg::OnEnChangePwd)
END_MESSAGE_MAP()


// CLibSystemDlg 消息处理程序

BOOL CLibSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_csName = "admin";
	m_csPwd = "123";
	UpdateData(FALSE);
	GetDlgItem(IDOK)->SetFocus();
	//GetDlgItem(IDOK)->EnableWindow(FALSE);
	LoadUser(_T(".//user.txt"));
	pList = &m_listUser;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLibSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLibSystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLibSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLibSystemDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CheckUser(m_csName);
	if (m_csName.GetBuffer() == m_it->m_sUName 
		&& m_csPwd.GetBuffer() == m_it->m_sPwd)
	{
		if (m_it->m_nAuthority == 1)
		{
			CDialogEx::OnCancel();
			CDlgIndex dlg;
			dlg.DoModal();
			CDialogEx::OnOK();
		}
		else if (m_it->m_nAuthority == 0)
		{
			CDialogEx::OnCancel();
			CDlgUserIndex dlg;
			dlg.DoModal();
			CDialogEx::OnOK();
		}
	}
	else
	{
		AfxMessageBox(_T("Anything wrong!"));
	}
}


void CLibSystemDlg::OnEnChangePwd()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDOK)->EnableWindow(TRUE);
}

void CLibSystemDlg::LoadUser(CString csFullPath)
{
	m_listUser.clear();
	ifstream in(csFullPath, ios::in);
	if (in.is_open())
	{
		int num;
		in >> num;
		for (int i = 0; i < num; i++)
		{
			CUser user = CUser();
			user.Load(in);
			m_listUser.push_back(user);
		}
		in.close();
	}
}

void CLibSystemDlg::CheckUser(CString csUName)
{
	if (pList->size() == 0)
	{
		bFound = false;
		AfxMessageBox(_T("请保证user.txt与工程文件在同一路径下"));
	}
	for (list<CUser>::iterator it = pList->begin(); it != pList->end(); it++)
	{
		if (it->m_sUName == csUName.GetBuffer())
		{
			m_it = it;
			bFound = true;
			break;
		}
	}
	if (bFound == false)
	{
		m_it = pList->begin();
	}
}
