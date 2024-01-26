
// BresenhamView.cpp: CBresenhamView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Bresenham.h"
#endif

#include "BresenhamDoc.h"
#include "BresenhamView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBresenhamView

IMPLEMENT_DYNCREATE(CBresenhamView, CView)

BEGIN_MESSAGE_MAP(CBresenhamView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CBresenhamView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CBresenhamView 构造/析构

CBresenhamView::CBresenhamView() noexcept
{
	// TODO: 在此处添加构造代码

}

CBresenhamView::~CBresenhamView()
{
}

BOOL CBresenhamView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CBresenhamView 绘图

void CBresenhamView::OnDraw(CDC* /*pDC*/)
{
	CBresenhamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CBresenhamView 打印


void CBresenhamView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CBresenhamView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CBresenhamView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CBresenhamView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CBresenhamView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CBresenhamView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CBresenhamView 诊断

#ifdef _DEBUG
void CBresenhamView::AssertValid() const
{
	CView::AssertValid();
}

void CBresenhamView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBresenhamDoc* CBresenhamView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBresenhamDoc)));
	return (CBresenhamDoc*)m_pDocument;
}
#endif //_DEBUG


// CBresenhamView 消息处理程序


void CBresenhamView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	line.SetStart(point);
	CView::OnLButtonDown(nFlags, point);
}


void CBresenhamView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	line.SetEnd(point);
	CDC* pDC = GetDC();
	line.BresenhamLine(pDC);
	ReleaseDC(pDC);
	CView::OnLButtonUp(nFlags, point);
}
