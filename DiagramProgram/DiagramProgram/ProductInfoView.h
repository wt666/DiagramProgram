#pragma once
#include "Chart.h"
#include "MainFrm.h"
#include "ChangeProductInfoDlg.h"

// CProductInfoView 视图

class CProductInfoView : public CListView
{
	DECLARE_DYNCREATE(CProductInfoView)

protected:
	CProductInfoView();           // 动态创建所使用的受保护的构造函数
	virtual ~CProductInfoView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	CChart * m_chart;

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
};


