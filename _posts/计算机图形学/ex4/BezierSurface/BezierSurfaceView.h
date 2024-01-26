
// BezierSurfaceView.h: CBezierSurfaceView 类的接口
//

#pragma once
#include"CTrans3.h"
#include"CRevolution.h"

class CBezierSurfaceView : public CView
{
protected: // 仅从序列化创建
	CBezierSurfaceView() noexcept;
	DECLARE_DYNCREATE(CBezierSurfaceView)

// 特性
public:
	CBezierSurfaceDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CBezierSurfaceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	bool bPlay;
	CRevolution revoDown, revoUp;
	double Alpha, Beta;
	CTrans3 tranUp, tranDown;
	void DoubleBuffer(CDC* pDC);
	void DrawObject(CDC* pDC);
// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void GraphicAnimation();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnUpdateGraphicAnimation(CCmdUI* pCmdUI);
};

#ifndef _DEBUG  // BezierSurfaceView.cpp 中的调试版本
inline CBezierSurfaceDoc* CBezierSurfaceView::GetDocument() const
   { return reinterpret_cast<CBezierSurfaceDoc*>(m_pDocument); }
#endif

