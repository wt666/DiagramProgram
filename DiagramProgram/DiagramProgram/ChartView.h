#pragma once
#include "Chart.h"
#include "MainFrm.h"

// CChartView 视图

class CChartView : public CView
{
	DECLARE_DYNCREATE(CChartView)

protected:
	CChartView();           // 动态创建所使用的受保护的构造函数
	virtual ~CChartView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
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
};


