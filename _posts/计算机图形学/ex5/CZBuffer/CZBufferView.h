
// CZBufferView.h: CCZBufferView 类的接口
//

#pragma once
#include "Transform3.h"
#include "Revolution.h"

class CCZBufferView : public CView
{
protected: // 仅从序列化创建
	CCZBufferView() noexcept;
	DECLARE_DYNCREATE(CCZBufferView)

// 特性
public:
	CCZBufferDoc* GetDocument() const;

	// 操作
public:
	void DoubleBuffer(CDC* pDC);//双缓冲
	void DrawObject(CDC* pDC);//绘制图形
	void InitializeLightingScene(void);//初始化光照场景
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
	virtual ~CCZBufferView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CRevolution revoUp, revoDown;
	double Alpha, Beta;
	CTransform3 tranUp, tranDown;
	BOOL bPlay;//动画按钮
	int	nLightSourceNumber;//光源数量
	CLighting* pLight;//光照环境
	CMaterial* pMaterial;//物体材质
// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnGraphicAnimation();
	afx_msg void OnUpdateGraphicAnimation(CCmdUI* pCmdUI);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // TestView.cpp 中的调试版本
inline CCZBufferDoc* CCZBufferView::GetDocument() const
   { return reinterpret_cast<CCZBufferDoc*>(m_pDocument); }
#endif

