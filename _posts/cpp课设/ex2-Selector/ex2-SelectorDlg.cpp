
// ex2-SelectorDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ex2-Selector.h"
#include "ex2-SelectorDlg.h"
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


// Cex2SelectorDlg 对话框



Cex2SelectorDlg::Cex2SelectorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EX2SELECTOR_DIALOG, pParent)
	, m_nSelA(0)
	, m_nSelB(0)
	, m_bChkA(FALSE)
	, m_bChkB(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cex2SelectorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_nSelA);
	DDX_Radio(pDX, IDC_RADIO4, m_nSelB);
	DDX_Check(pDX, IDC_CHECK1, m_bChkA);
	DDX_Check(pDX, IDC_CHECK2, m_bChkB);
}

BEGIN_MESSAGE_MAP(Cex2SelectorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &Cex2SelectorDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK1, &Cex2SelectorDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &Cex2SelectorDlg::OnBnClickedCheck2)
END_MESSAGE_MAP()


// Cex2SelectorDlg 消息处理程序

BOOL Cex2SelectorDlg::OnInitDialog()
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
	m_bChkA = TRUE;
	GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE); 
	GetDlgItem(IDC_RADIO3)->EnableWindow(TRUE);

	m_bChkB = FALSE;
	GetDlgItem(IDC_RADIO4)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO5)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO6)->EnableWindow(FALSE);

	m_nSelA = 0;
	m_nSelB = 0;
	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cex2SelectorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cex2SelectorDlg::OnPaint()
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
HCURSOR Cex2SelectorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cex2SelectorDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString csGroupA[] = { _T("美国"),_T("日本") ,_T("韩国") };
	CString csGroupB[] = { _T("英国"),_T("巴西") ,_T("法国") };

	UpdateData(TRUE);
	CString csMsg;
	if (m_bChkA == TRUE)
		csMsg = csGroupA[m_nSelA] + _T("\n");
	if (m_bChkB == TRUE)
		csMsg += csGroupB[m_nSelB];
	MessageBox(csMsg);
	CDialogEx::OnOK();
}


void Cex2SelectorDlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	GetDlgItem(IDC_RADIO1)->EnableWindow(m_bChkA);
	GetDlgItem(IDC_RADIO2)->EnableWindow(m_bChkA);
	GetDlgItem(IDC_RADIO3)->EnableWindow(m_bChkA);
}


void Cex2SelectorDlg::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码 
	UpdateData(TRUE);
	GetDlgItem(IDC_RADIO4)->EnableWindow(m_bChkB);
	GetDlgItem(IDC_RADIO5)->EnableWindow(m_bChkB);
	GetDlgItem(IDC_RADIO6)->EnableWindow(m_bChkB);
}
