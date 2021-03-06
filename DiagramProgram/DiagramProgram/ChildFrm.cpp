
// ChildFrm.cpp: CChildFrame 类的实现
//

#include "stdafx.h"
#include "DiagramProgram.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_COMMAND(ID_CHANGETITLE, &CChildFrame::OnChangetitle)
END_MESSAGE_MAP()

// CChildFrame 构造/析构

CChildFrame::CChildFrame()
{

}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		| FWS_ADDTOTITLE | WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	return TRUE;
}

// CChildFrame 诊断

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame 消息处理程序


BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	if (!m_wndSplitter1.CreateStatic(this, 1, 2))
	{
		return false;
	}

	CRect rect;
	GetClientRect(&rect);
	m_wndSplitter1.CreateView(0, 0, RUNTIME_CLASS(CMaintainProductView), CSize(rect.Width() / 8, rect.Height()), pContext);
	if (m_wndSplitter2.CreateStatic(&m_wndSplitter1, 2, 1, WS_CHILD | WS_VISIBLE, m_wndSplitter1.IdFromRowCol(0, 1)) == NULL)
	{
		return false;
	}
	m_wndSplitter2.CreateView(0, 0, RUNTIME_CLASS(CChartView), CSize(rect.Width() / 8 * 7, rect.Height() / 25 * 24), pContext);
	m_wndSplitter2.CreateView(1, 0, RUNTIME_CLASS(CProductInfoView), CSize(rect.Width() / 8 * 7, rect.Height() / 25), pContext);
	
	m_maintainProductView = (CMaintainProductView *)m_wndSplitter1.GetPane(0, 0);
	m_productInfoView = (CProductInfoView *)m_wndSplitter2.GetPane(0, 0);
	m_chartView = (CChartView *)m_wndSplitter2.GetPane(1, 0);

	return CMDIChildWndEx::OnCreateClient(lpcs, pContext);
}


void CChildFrame::OnChangetitle()
{
	CChangeTitleDlg dlg;
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	dlg.m_diagramTitle = pFrame->m_chart->GetTitle();
	if (dlg.DoModal() == IDOK)
	{
		CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
		pFrame->m_wndOutput.m_operationRecord[pFrame->m_wndOutput.m_operationRecordNum++] = L"曲线图标题：从《" + pFrame->m_chart->GetTitle() + L"》变为《" + dlg.m_diagramTitle + L"》";
		pFrame->m_wndOutput.FillOperationRecordWindow();
		pFrame->m_chart->SetTitle(dlg.m_diagramTitle);
		CDocument *pDoc = GetActiveDocument();
		POSITION pos = pDoc->GetFirstViewPosition();
		while (pos != NULL)
		{
			CView *pView = pDoc->GetNextView(pos);
			pView->OnInitialUpdate();
		}
	}
}
