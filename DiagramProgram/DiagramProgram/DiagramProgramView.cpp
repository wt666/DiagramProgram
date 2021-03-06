
// DiagramProgramView.cpp: CDiagramProgramView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DiagramProgram.h"
#endif

#include "DiagramProgramDoc.h"
#include "DiagramProgramView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDiagramProgramView

IMPLEMENT_DYNCREATE(CDiagramProgramView, CView)

BEGIN_MESSAGE_MAP(CDiagramProgramView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CDiagramProgramView 构造/析构

CDiagramProgramView::CDiagramProgramView()
{

}

CDiagramProgramView::~CDiagramProgramView()
{
}

BOOL CDiagramProgramView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDiagramProgramView 绘图

void CDiagramProgramView::OnDraw(CDC* /*pDC*/)
{
	CDiagramProgramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

void CDiagramProgramView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDiagramProgramView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDiagramProgramView 诊断

#ifdef _DEBUG
void CDiagramProgramView::AssertValid() const
{
	CView::AssertValid();
}

void CDiagramProgramView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDiagramProgramDoc* CDiagramProgramView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDiagramProgramDoc)));
	return (CDiagramProgramDoc*)m_pDocument;
}
#endif //_DEBUG


// CDiagramProgramView 消息处理程序