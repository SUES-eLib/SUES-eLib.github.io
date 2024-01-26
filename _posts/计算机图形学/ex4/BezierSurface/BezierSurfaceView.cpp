
// BezierSurfaceView.cpp: CBezierSurfaceView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "BezierSurface.h"
#endif

#include "BezierSurfaceDoc.h"
#include "BezierSurfaceView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBezierSurfaceView

IMPLEMENT_DYNCREATE(CBezierSurfaceView, CView)

BEGIN_MESSAGE_MAP(CBezierSurfaceView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CBezierSurfaceView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_32771, &CBezierSurfaceView::GraphicAnimation)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(ID_32771, &CBezierSurfaceView::OnUpdateGraphicAnimation)
END_MESSAGE_MAP()

// CBezierSurfaceView 构造/析构

CBezierSurfaceView::CBezierSurfaceView() noexcept
{
	// TODO: 在此处添加构造代码
	bPlay = FALSE;
	double R = 200;
	double m = 0.5523;
	CP2 P2[7];
	P2[0] = CP2(0, -1);
	P2[1] = CP2(m, -1);
	P2[2] = CP2(1, -m);
	P2[3] = CP2(1, 0);
	P2[4] = CP2(1, m);
	P2[5] = CP2(m, 1);
	P2[6] = CP2(0, 1);
	CP3 DownPoint[4];
	DownPoint[0] = CP3(P2[0].x, P2[0].y, 0.0);
	DownPoint[1] = CP3(P2[1].x, P2[1].y, 0.0);
	DownPoint[2] = CP3(P2[2].x, P2[2].y, 0.0);
	DownPoint[3] = CP3(P2[3].x, P2[3].y, 0.0);
	revoDown.ReadCubicBezierControlPoint(DownPoint);
	tranDown.SetMatrix(revoDown.GetVertexArrayName(), 48);
	tranDown.Scale(R, R, R);
	CP3 UpPoint[4];
	UpPoint[0] = CP3(P2[3].x, P2[3].y, 0.0);
	UpPoint[1] = CP3(P2[4].x, P2[4].y, 0.0);
	UpPoint[2] = CP3(P2[5].x, P2[5].y, 0.0);
	UpPoint[3] = CP3(P2[6].x, P2[6].y, 0.0);
	revoUp.ReadCubicBezierControlPoint(UpPoint);
	tranUp.SetMatrix(revoUp.GetVertexArrayName(), 48);
	tranUp.Scale(R, R, R);
	Alpha = 60;
	tranUp.RotateX(Alpha);
	tranDown.RotateX(Alpha);
	Beta = 30;
	tranUp.RotateY(Beta);
	tranDown.RotateY(Beta);
}

CBezierSurfaceView::~CBezierSurfaceView()
{
}

BOOL CBezierSurfaceView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CBezierSurfaceView 绘图

void CBezierSurfaceView::OnDraw(CDC* pDC)
{
	CBezierSurfaceDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	DoubleBuffer(pDC); 
}

void CBezierSurfaceView::DoubleBuffer(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(rect.Width(), rect.Height());
	pDC->SetViewportExt(rect.Width(), -rect.Height());
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap NewBitmap, * pOldBitmap;
	NewBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height()); 
	pOldBitmap = memDC.SelectObject(&NewBitmap);
	memDC.FillSolidRect(rect, pDC->GetBkColor());
	memDC.SetMapMode(MM_ANISOTROPIC);
	memDC.SetWindowExt(rect.Width(), rect.Height());
	memDC.SetViewportExt(rect.Width(), -rect.Height());
	memDC.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);
	DrawObject(&memDC);
	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, -rect.Width() / 2, -rect.Height() / 2, SRCCOPY);//将内存memDC中的位图拷贝到显示pDC中
	memDC.SelectObject(pOldBitmap);
	NewBitmap.DeleteObject();
}

void CBezierSurfaceView::DrawObject(CDC* pDC)
{
	revoUp.DrawRevolutionSurface(pDC);
	revoDown.DrawRevolutionSurface(pDC);
}

// CBezierSurfaceView 打印


void CBezierSurfaceView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CBezierSurfaceView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CBezierSurfaceView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CBezierSurfaceView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CBezierSurfaceView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CBezierSurfaceView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CBezierSurfaceView 诊断

#ifdef _DEBUG
void CBezierSurfaceView::AssertValid() const
{
	CView::AssertValid();
}

void CBezierSurfaceView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBezierSurfaceDoc* CBezierSurfaceView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBezierSurfaceDoc)));
	return (CBezierSurfaceDoc*)m_pDocument;
}
#endif //_DEBUG


// CBezierSurfaceView 消息处理程序


void CBezierSurfaceView::GraphicAnimation()
{
	// TODO: 在此添加命令处理程序代码
	bPlay = !bPlay;
	if (bPlay)
		SetTimer(1, 150, NULL);
	else
		KillTimer(1);
}


void CBezierSurfaceView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nChar)
	{
	case VK_UP:
		Alpha = +2;
		tranUp.RotateX(Alpha);
		tranDown.RotateX(Alpha);
		break;
	case VK_DOWN:
		Alpha = -2;
		tranUp.RotateX(Alpha);
		tranDown.RotateX(Alpha);
		break;
	case VK_LEFT:
		Beta = -2;
		tranUp.RotateY(Beta);
		tranDown.RotateY(Beta);
		break;
	case VK_RIGHT:
		Beta = 2;
		tranUp.RotateY(Beta);
		tranDown.RotateY(Beta);
		break;
	default:
		break;
	}
	Invalidate(FALSE);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CBezierSurfaceView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	Alpha = 2;	Beta = 2;
	tranUp.RotateX(Alpha);
	tranDown.RotateX(Alpha);
	tranUp.RotateY(Beta);
	tranDown.RotateY(Beta);
	Invalidate(FALSE);
	CView::OnTimer(nIDEvent);
}


void CBezierSurfaceView::OnUpdateGraphicAnimation(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (bPlay)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
