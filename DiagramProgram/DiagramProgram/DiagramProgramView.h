
// DiagramProgramView.h: CDiagramProgramView 类的接口
//

#pragma once


class CDiagramProgramView : public CView
{
protected: // 仅从序列化创建
	CDiagramProgramView();
	DECLARE_DYNCREATE(CDiagramProgramView)

// 特性
public:
	CDiagramProgramDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CDiagramProgramView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:

};

#ifndef _DEBUG  // DiagramProgramView.cpp 中的调试版本
inline CDiagramProgramDoc* CDiagramProgramView::GetDocument() const
   { return reinterpret_cast<CDiagramProgramDoc*>(m_pDocument); }
#endif

