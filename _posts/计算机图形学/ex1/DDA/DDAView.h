
// DDAView.h: CDDAView 类的接口
//

#pragma once
#include "DDALine.h"

class CDDAView : public CView
{
protected: // 仅从序列化创建
	CDDAView() noexcept;
	DECLARE_DYNCREATE(CDDAView)

// 特性
public:
	CDDADoc* GetDocument() const;

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
	virtual ~CDDAView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DDALine line;
};

#ifndef _DEBUG  // DDAView.cpp 中的调试版本
inline CDDADoc* CDDAView::GetDocument() const
   { return reinterpret_cast<CDDADoc*>(m_pDocument); }
#endif

