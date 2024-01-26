
// ex1View.cpp: Cex1View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ex1.h"
#endif

#include "ex1Doc.h"
#include "ex1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cex1View

IMPLEMENT_DYNCREATE(Cex1View, CView)

BEGIN_MESSAGE_MAP(Cex1View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cex1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// Cex1View 构造/析构

Cex1View::Cex1View() noexcept
{
	// TODO: 在此处添加构造代码

}

Cex1View::~Cex1View()
{
}

BOOL Cex1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// Cex1View 绘图

void Cex1View::OnDraw(CDC* /*pDC*/)
{
	Cex1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// Cex1View 打印


void Cex1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Cex1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void Cex1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void Cex1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void Cex1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cex1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Cex1View 诊断

#ifdef _DEBUG
void Cex1View::AssertValid() const
{
	CView::AssertValid();
}

void Cex1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cex1Doc* Cex1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cex1Doc)));
	return (Cex1Doc*)m_pDocument;
}
#endif //_DEBUG


// Cex1View 消息处理程序


void Cex1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	P0 = point;
	CView::OnLButtonDown(nFlags, point);
}


void Cex1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	P1 = point;
	CDC* pDC = GetDC();

	CPen pen(PS_SOLID, 6, RGB(100, 20, 80));
	pDC->SelectObject(&pen);
	pDC->MoveTo(P0);
	pDC->LineTo(P1);
	DeleteObject(&pen);
	ReleaseDC(pDC);

	//CBrush brush;
	//brush.CreateSolidBrush(RGB(120, 50, 60));
	//pDC->Rectangle(CRect(P0, P1));
	//pDC->FillRect(CRect(P0, P1),&brush);
	//DeleteObject(&brush);
	//ReleaseDC(pDC);
	CView::OnLButtonUp(nFlags, point);
}
