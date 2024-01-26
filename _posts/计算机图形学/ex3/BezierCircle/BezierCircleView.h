
// BezierCircleView.h: CBezierCircleView 类的接口
//

#pragma once
#include "CTransform2.h"
#include "CCircle.h"

class CBezierCircleView : public CView
{
protected: // 仅从序列化创建
	CBezierCircleView() noexcept;
	DECLARE_DYNCREATE(CBezierCircleView)

// 特性
public:
	CBezierCircleDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CBezierCircleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CCircle circle;
	CTransform2 transform;
// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // BezierCircleView.cpp 中的调试版本
inline CBezierCircleDoc* CBezierCircleView::GetDocument() const
   { return reinterpret_cast<CBezierCircleDoc*>(m_pDocument); }
#endif

