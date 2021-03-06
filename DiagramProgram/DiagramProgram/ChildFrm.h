
// ChildFrm.h: CChildFrame 类的接口
//

#pragma once
#include "MaintainProductView.h"
#include "ProductInfoView.h"
#include "ChartView.h"
#include "ChangeTitleDlg.h"

class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// 特性
protected:
	CSplitterWnd m_wndSplitter;
public:

// 操作
public:

// 重写
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CSplitterWnd m_wndSplitter1;
	CSplitterWnd m_wndSplitter2;
public:
	CMaintainProductView * m_maintainProductView;
	CProductInfoView * m_productInfoView;
	CChartView * m_chartView;

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	afx_msg void OnChangetitle();
};
