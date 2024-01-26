
// DDAView.cpp: CDDAView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DDA.h"
#endif

#include "DDADoc.h"
#include "DDAView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDDAView

IMPLEMENT_DYNCREATE(CDDAView, CView)

BEGIN_MESSAGE_MAP(CDDAView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDDAView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CDDAView 构造/析构

CDDAView::CDDAView() noexcept
{
	// TODO: 在此处添加构造代码

}

CDDAView::~CDDAView()
{
}

BOOL CDDAView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDDAView 绘图

void CDDAView::OnDraw(CDC* /*pDC*/)
{
	CDDADoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CDDAView 打印


void CDDAView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDDAView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDDAView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDDAView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CDDAView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDDAView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDDAView 诊断

#ifdef _DEBUG
void CDDAView::AssertValid() const
{
	CView::AssertValid();
}

void CDDAView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDDADoc* CDDAView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDDADoc)));
	return (CDDADoc*)m_pDocument;
}
#endif //_DEBUG


// CDDAView 消息处理程序


void CDDAView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	line.SetStart(point);
	CView::OnLButtonDown(nFlags, point);
}


void CDDAView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	line.SetEnd(point);
	CDC* pDC = GetDC();
	line.CDDALine(pDC);
	ReleaseDC(pDC);
	CView::OnLButtonUp(nFlags, point);
}