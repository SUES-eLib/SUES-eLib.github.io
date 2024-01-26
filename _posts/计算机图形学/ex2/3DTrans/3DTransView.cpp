
// 3DTransView.cpp: CMy3DTransView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "3DTrans.h"
#endif

#include "3DTransDoc.h"
#include "3DTransView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy3DTransView

IMPLEMENT_DYNCREATE(CMy3DTransView, CView)

BEGIN_MESSAGE_MAP(CMy3DTransView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy3DTransView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CMy3DTransView 构造/析构

CMy3DTransView::CMy3DTransView() noexcept
{
	// TODO: 在此处添加构造代码
	cube.ReadPoint();
	cube.ReadFacet();
	transform.SetMatrix(cube.GetVertexArrayName(), 8);
	double nEdge = 400;
	transform.Scale(nEdge, nEdge, nEdge);
	transform.Translate(-nEdge / 2, -nEdge / 2, -nEdge / 2);
}

CMy3DTransView::~CMy3DTransView()
{
}

BOOL CMy3DTransView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy3DTransView 绘图

void CMy3DTransView::OnDraw(CDC* pDC)
{
	CMy3DTransDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
	DoubleBuffer(pDC);
}


// CMy3DTransView 打印


void CMy3DTransView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy3DTransView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy3DTransView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy3DTransView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMy3DTransView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy3DTransView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMy3DTransView 诊断

#ifdef _DEBUG
void CMy3DTransView::AssertValid() const
{
	CView::AssertValid();
}

void CMy3DTransView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy3DTransDoc* CMy3DTransView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3DTransDoc)));
	return (CMy3DTransDoc*)m_pDocument;
}

void CMy3DTransView::DrawObject(CDC* pDC)//正交投影
{
	cube.Draw(pDC);
}
void CMy3DTransView::DoubleBuffer(CDC* pDC)//双缓冲绘图
{
	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(rect.Width(), rect.Height());
	pDC->SetViewportExt(rect.Width(), -rect.Height());
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	CDC memDC;//声明内存DC
	memDC.CreateCompatibleDC(pDC);//创建一个与显示DC兼容的内存DC
	CBitmap NewBitmap, * pOldBitmap;
	NewBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());//创建兼容内存位图 
	pOldBitmap = memDC.SelectObject(&NewBitmap);//将兼容位图选入内存DC
	memDC.FillSolidRect(rect, pDC->GetBkColor());//设置客户区背景色
	rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);
	memDC.SetMapMode(MM_ANISOTROPIC);//内存DC自定义坐标系
	memDC.SetWindowExt(rect.Width(), rect.Height());
	memDC.SetViewportExt(rect.Width(), -rect.Height());
	memDC.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	DrawObject(&memDC);//绘制图形
	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, -rect.Width() / 2, -rect.Height() / 2, SRCCOPY); //将内存DC中的位图拷贝到显示DC
	memDC.SelectObject(pOldBitmap);
	NewBitmap.DeleteObject();
	memDC.DeleteDC();
}

#endif //_DEBUG


// CMy3DTransView 消息处理程序



void CMy3DTransView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nChar)
	{
	case VK_UP:
		Alpha = -5;
		transform.RotateX(Alpha);
		break;
	case VK_DOWN:
		Alpha = +5;
		transform.RotateX(Alpha);
		break;
	case VK_LEFT:
		Beta = -5;
		transform.RotateY(Beta);
		break;
	case VK_RIGHT:
		Beta = +5;
		transform.RotateY(Beta);
		break;
	default:
		break;
	}
	Invalidate(FALSE);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
