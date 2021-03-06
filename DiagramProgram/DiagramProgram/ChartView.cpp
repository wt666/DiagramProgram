// ChartView.cpp: 实现文件
//

#include "stdafx.h"
#include "DiagramProgram.h"
#include "ChartView.h"


// CChartView

IMPLEMENT_DYNCREATE(CChartView, CView)

CChartView::CChartView()
{
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	m_chart = pFrame->m_chart;
}

CChartView::~CChartView()
{
}

BEGIN_MESSAGE_MAP(CChartView, CView)

END_MESSAGE_MAP()


// CChartView 绘图

void CChartView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	
	// 双缓冲绘图
	CRect rc;
	GetClientRect(rc);
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());
	memDC.SelectObject(&bitmap);
	memDC.FillSolidRect(rc, RGB(255, 255, 255));
	m_chart->Draw(&memDC);
	pDC->BitBlt(rc.left, rc.top, rc.Width(), rc.Height(), &memDC, 0, 0, SRCCOPY);
	bitmap.DeleteObject();
	memDC.DeleteDC();

}


// CChartView 诊断

#ifdef _DEBUG
void CChartView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CChartView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CChartView 消息处理程序
