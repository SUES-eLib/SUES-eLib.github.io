
// 2DTransView.cpp: CMy2DTransView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "2DTrans.h"
#endif

#include "2DTransDoc.h"
#include "2DTransView.h"
#include "CFence.h"
#include "CP2.h"
#include "CTransform2.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy2DTransView

IMPLEMENT_DYNCREATE(CMy2DTransView, CView)

BEGIN_MESSAGE_MAP(CMy2DTransView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy2DTransView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_GRAPHIC_ANIMATION, &CMy2DTransView::OnGraphicAnimation)
END_MESSAGE_MAP()

// CMy2DTransView 构造/析构

CMy2DTransView::CMy2DTransView() noexcept
{
	// TODO: 在此处添加构造代码
	bPlay = FALSE;
	double a = 30;
	double b = 4.5 * a;
	CenterPoint[0] = CP2(0, 0);
	CenterPoint[1] = CP2(-b, -b);
	CenterPoint[2] = CP2(b, -b);
	CenterPoint[3] = CP2(b, b);
	CenterPoint[4] = CP2(-b, b);
	for (int i = 0; i < 5; i++)
	{
		fence[i].ReadPoint();
		transform[i].SetMatrix(fence[i].P, 12);
		transform[i].Scale(a, a);
		transform[i].Translate(CenterPoint[i].x, CenterPoint[i].y);
	}
}

CMy2DTransView::~CMy2DTransView()
{
}

BOOL CMy2DTransView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy2DTransView 绘图

void CMy2DTransView::DrawObject(CDC* pDC)
{
	if (FALSE == bPlay)
		fence[0].Draw(pDC);
	else
		for (int i = 0; i < 5; i++)
			fence[i].Draw(pDC);
}


void CMy2DTransView::OnDraw(CDC* pDC)
{
	CMy2DTransDoc* pDoc = GetDocument();
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
	DrawObject(pDC);
}


// CMy2DTransView 打印


void CMy2DTransView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy2DTransView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy2DTransView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy2DTransView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMy2DTransView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy2DTransView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMy2DTransView 诊断

#ifdef _DEBUG
void CMy2DTransView::AssertValid() const
{
	CView::AssertValid();
}

void CMy2DTransView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy2DTransDoc* CMy2DTransView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy2DTransDoc)));
	return (CMy2DTransDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy2DTransView 消息处理程序


void CMy2DTransView::OnGraphicAnimation()
{
	// TODO: 在此添加命令处理程序代码
	bPlay = TRUE;
	Invalidate(FALSE);
}
