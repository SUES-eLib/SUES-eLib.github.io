
// BezierCircleView.cpp: CBezierCircleView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "BezierCircle.h"
#endif

#include "BezierCircleDoc.h"
#include "BezierCircleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBezierCircleView

IMPLEMENT_DYNCREATE(CBezierCircleView, CView)

BEGIN_MESSAGE_MAP(CBezierCircleView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CBezierCircleView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CBezierCircleView 构造/析构

CBezierCircleView::CBezierCircleView() noexcept
{
	// TODO: 在此处添加构造代码
	circle.ReadPoint();
	transform.SetMatrix(circle.GetVertexArrayName(), 12);
	double R = 200;
	transform.Scale(R, R);
}

CBezierCircleView::~CBezierCircleView()
{
}

BOOL CBezierCircleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CBezierCircleView 绘图

void CBezierCircleView::OnDraw(CDC* pDC)
{
	CBezierCircleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(rect.Width(), rect.Height());
	pDC->SetViewportExt(rect.Width(), -rect.Height());
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	circle.Draw(pDC);
}


// CBezierCircleView 打印


void CBezierCircleView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CBezierCircleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CBezierCircleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CBezierCircleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CBezierCircleView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CBezierCircleView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CBezierCircleView 诊断

#ifdef _DEBUG
void CBezierCircleView::AssertValid() const
{
	CView::AssertValid();
}

void CBezierCircleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBezierCircleDoc* CBezierCircleView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBezierCircleDoc)));
	return (CBezierCircleDoc*)m_pDocument;
}
#endif //_DEBUG


// CBezierCircleView 消息处理程序
