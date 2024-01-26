
// 3DTransView.h: CMy3DTransView 类的接口
//

#pragma once
#include"CCube.h"
#include"CTrans3.h"

class CMy3DTransView : public CView
{
protected: // 仅从序列化创建
	CMy3DTransView() noexcept;
	DECLARE_DYNCREATE(CMy3DTransView)

// 特性
public:
	CMy3DTransDoc* GetDocument() const;

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
	virtual ~CMy3DTransView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CCube cube;
	CTrans3 transform;
	void DrawObject(CDC* pDC);
	void DoubleBuffer(CDC* pDC);
	int Alpha;
	int Beta;

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // 3DTransView.cpp 中的调试版本
inline CMy3DTransDoc* CMy3DTransView::GetDocument() const
   { return reinterpret_cast<CMy3DTransDoc*>(m_pDocument); }
#endif

