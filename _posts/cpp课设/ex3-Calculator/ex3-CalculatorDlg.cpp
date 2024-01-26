
// ex3-CalculatorDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ex3-Calculator.h"
#include "ex3-CalculatorDlg.h"
#include "afxdialogex.h"
#include "cstring"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int OP_TYPE_ADD = 1;
const int OP_TYPE_SUB = 2;
const int OP_TYPE_MUL = 3;
const int OP_TYPE_DIV = 4;
const int OP_TYPE_NONE = 0;
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


// Cex3CalculatorDlg 对话框



Cex3CalculatorDlg::Cex3CalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EX3CALCULATOR_DIALOG, pParent)
	, m_csRes(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cex3CalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RES, m_csRes);
}

BEGIN_MESSAGE_MAP(Cex3CalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cex3CalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Cex3CalculatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Cex3CalculatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Cex3CalculatorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &Cex3CalculatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &Cex3CalculatorDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &Cex3CalculatorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &Cex3CalculatorDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &Cex3CalculatorDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON0, &Cex3CalculatorDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &Cex3CalculatorDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_SUB, &Cex3CalculatorDlg::OnBnClickedButtonSub)
	ON_BN_CLICKED(IDC_BUTTON_MUL, &Cex3CalculatorDlg::OnBnClickedButtonMul)
	ON_BN_CLICKED(IDC_BUTTON_DIV, &Cex3CalculatorDlg::OnBnClickedButtonDiv)
	ON_BN_CLICKED(IDC_BUTTON_CALC, &Cex3CalculatorDlg::OnBnClickedButtonCalc)
	ON_BN_CLICKED(IDC_BUTTON_DOT, &Cex3CalculatorDlg::OnBnClickedButtonDot)
END_MESSAGE_MAP()


// Cex3CalculatorDlg 消息处理程序

BOOL Cex3CalculatorDlg::OnInitDialog()
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
	m_nOpType = OP_TYPE_NONE;
	m_bNew = true;
	m_csRes = _T("0");
	GetDlgItem(IDC_BUTTON_CALC)->EnableWindow(FALSE);
	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cex3CalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cex3CalculatorDlg::OnPaint()
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
HCURSOR Cex3CalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cex3CalculatorDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	PressDigit(1);
}


void Cex3CalculatorDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	PressDigit(2);
}


void Cex3CalculatorDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	PressDigit(3);
}


void Cex3CalculatorDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	PressDigit(4);
}


void Cex3CalculatorDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	PressDigit(5);
}


void Cex3CalculatorDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	PressDigit(6);
}


void Cex3CalculatorDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	PressDigit(7);
}


void Cex3CalculatorDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	PressDigit(8);
}


void Cex3CalculatorDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	PressDigit(9);
}


void Cex3CalculatorDlg::OnBnClickedButton0()
{
	// TODO: 在此添加控件通知处理程序代码
	PressDigit(0);
}

void Cex3CalculatorDlg::OnBnClickedButtonDot()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bNew)
	{
		m_bNew = false;
		m_csRes = _T("0");
	}
	else
		UpdateData(TRUE);

	CString str;
	str=_T(".");
	m_csRes += str;
	GetDlgItem(IDC_BUTTON_DOT)->EnableWindow(FALSE);
	UpdateData(FALSE);
}

void Cex3CalculatorDlg::PressDigit(int nDigit)
{
	if (m_bNew) 
	{
		m_bNew = false;
		m_csRes = _T("0");
	}
	else
		UpdateData(TRUE);
	
	CString str;
	str.Format(_T("%d"), nDigit);
	if (m_csRes == CString(_T("0")))
		m_csRes = _T("");
	m_csRes += str;

	UpdateData(FALSE);
}
void Cex3CalculatorDlg::PressOp(int nType)
{
	m_nOpType = nType;
	m_csOpA = m_csRes;
	m_csRes = _T("0");
	UpdateData(FALSE);
	
	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON7)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON9)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON0)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_DOT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CALC)->EnableWindow(TRUE);

	GetDlgItem(IDC_BUTTON_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SUB)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_MUL)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DIV)->EnableWindow(FALSE);
}

void Cex3CalculatorDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	PressOp(OP_TYPE_ADD);
}


void Cex3CalculatorDlg::OnBnClickedButtonSub()
{
	// TODO: 在此添加控件通知处理程序代码
	PressOp(OP_TYPE_SUB);
}


void Cex3CalculatorDlg::OnBnClickedButtonMul()
{
	// TODO: 在此添加控件通知处理程序代码
	PressOp(OP_TYPE_MUL);
}


void Cex3CalculatorDlg::OnBnClickedButtonDiv()
{
	// TODO: 在此添加控件通知处理程序代码
	PressOp(OP_TYPE_DIV);
}


void Cex3CalculatorDlg::OnBnClickedButtonCalc()
{
	// TODO: 在此添加控件通知处理程序代码
	m_csOpB = m_csRes;
	float nOpA = _tstof(m_csOpA);
	float nOpB = _tstof(m_csOpB);
	float nRes;
	switch (m_nOpType)
	{
	case OP_TYPE_ADD:
		nRes = nOpA + nOpB;
		break;
	case OP_TYPE_SUB:
		nRes = nOpA - nOpB;
		break;
	case OP_TYPE_MUL:
		nRes = nOpA * nOpB;
		break;
	case OP_TYPE_DIV:
		nRes = nOpA / nOpB;
		break;
	}
	m_csRes.Format(_T("%g"), nRes);
	UpdateData(FALSE);
	m_nOpType = OP_TYPE_NONE;
	m_bNew = true;
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON7)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON9)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON0)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DOT)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON_ADD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SUB)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MUL)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_DIV)->EnableWindow(TRUE);
}
