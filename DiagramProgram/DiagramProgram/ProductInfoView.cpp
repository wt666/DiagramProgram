// ProductInfoView.cpp: 实现文件
//

#include "stdafx.h"
#include "DiagramProgram.h"
#include "ProductInfoView.h"


// CProductInfoView

IMPLEMENT_DYNCREATE(CProductInfoView, CListView)

CProductInfoView::CProductInfoView()
{
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	m_chart = pFrame->m_chart;
}

CProductInfoView::~CProductInfoView()
{
}

BEGIN_MESSAGE_MAP(CProductInfoView, CListView)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CProductInfoView::OnNMDblclk)
END_MESSAGE_MAP()


// CProductInfoView 诊断

#ifdef _DEBUG
void CProductInfoView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CProductInfoView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CProductInfoView 消息处理程序


void CProductInfoView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	CListCtrl &m_listCtrl = GetListCtrl();
	LONG lStyle;
	lStyle = GetWindowLong(m_listCtrl.m_hWnd, GWL_STYLE);
	lStyle &= ~LVS_TYPEMASK;
	lStyle |= LVS_REPORT;
	SetWindowLong(m_listCtrl.m_hWnd, GWL_STYLE, lStyle);

	m_listCtrl.DeleteAllItems();
	for (int i = 0; i <= m_chart->m_monthNum; i++)
	{
		m_listCtrl.DeleteColumn(0);
	}

	DWORD extStyle = m_listCtrl.GetExtendedStyle();
	extStyle |= LVS_EX_FULLROWSELECT;
	extStyle |= LVS_EX_GRIDLINES;
	m_listCtrl.SetExtendedStyle(extStyle);
	m_listCtrl.InsertColumn(0, L"产品", LVCFMT_CENTER, 50);
	if (m_chart->m_product.empty() != 1)
	{
		int i;
		CString s;
		for (i = 0; i < m_chart->m_monthNum; i++)
		{
			s.Format(L"%d年%d月", m_chart->m_product[0]->m_monthYield[i].year, m_chart->m_product[0]->m_monthYield[i].month);
			m_listCtrl.InsertColumn(i + 1, s, LVCFMT_CENTER, 80);
		}
		int num;
		CString numstr;
		int j;
		for (i = 0; i < m_chart->m_product.size(); i++)
		{
			m_listCtrl.InsertItem(i, m_chart->m_product[i]->GetName());
			for (j = 0; j < m_chart->m_monthNum; j++)
			{
				num = m_chart->m_product[i]->m_monthYield[j].yield;
				numstr.Format(L"%d", num);
				m_listCtrl.SetItemText(i, j + 1, numstr);
			}
			m_listCtrl.SetItemData(i, (DWORD_PTR)&m_chart->m_product[i]);
		}
	}
}


void CProductInfoView::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (pNMItemActivate->iItem <= m_chart->m_product.size())
	{
		CChangeProductInfoDlg dlg(pNMItemActivate->iItem);
		if (dlg.DoModal() == IDOK)
		{
			int key = 1;
			int i;
			CString name;
			name = m_chart->m_product[pNMItemActivate->iItem]->GetName();
			if (name == dlg.m_productName && m_chart->m_product[pNMItemActivate->iItem]->GetColor() == dlg.m_color && m_chart->m_product[pNMItemActivate->iItem]->GetShape() == dlg.m_shape)
			{
				for (i = 0; i < m_chart->m_monthNum; i++)
				{
					if (m_chart->m_product[pNMItemActivate->iItem]->m_monthYield[i].yield != dlg.m_yield[i])
						break;
				}
				if (i == m_chart->m_monthNum)
					key = 0;
			}
			if (key == 1)
			{
				CString change = L"修改了产品：" + dlg.m_productName;
				if (name != dlg.m_productName)
				{
					change = change + L"（原名：" + name + L"）";
					m_chart->m_product[pNMItemActivate->iItem]->SetName(dlg.m_productName);
				}
				if (m_chart->m_product[pNMItemActivate->iItem]->GetShape() != dlg.m_shape)
				{
					int shape1, shape2;
					shape1 = m_chart->m_product[pNMItemActivate->iItem]->GetShape();
					change = change + L"    曲线图例：从";
					if (shape1 == 1)
						change += L"◇";
					else if (shape1 == 2)
						change += L"□";
					else if (shape1 == 3)
						change += L"△";
					else if (shape1 == 4)
						change += L"×";
					else
						change += L"○";
					shape2 = dlg.m_shape;
					change += L"变为";
					if (shape2 == 1)
						change += L"◇";
					else if (shape2 == 2)
						change += L"□";
					else if (shape2 == 3)
						change += L"△";
					else if (shape2 == 4)
						change += L"×";
					else
						change += L"○";
					m_chart->m_product[pNMItemActivate->iItem]->SetShape(dlg.m_shape);
				}
				if (m_chart->m_product[pNMItemActivate->iItem]->GetColor() != dlg.m_color)
				{
					CString r1, r2, g1, g2, b1, b2;
					r1.Format(L"%d", GetRValue(m_chart->m_product[pNMItemActivate->iItem]->GetColor()));
					r2.Format(L"%d", GetRValue(dlg.m_color));
					g1.Format(L"%d", GetGValue(m_chart->m_product[pNMItemActivate->iItem]->GetColor()));
					g2.Format(L"%d", GetGValue(dlg.m_color));
					b1.Format(L"%d", GetBValue(m_chart->m_product[pNMItemActivate->iItem]->GetColor()));
					b2.Format(L"%d", GetBValue(dlg.m_color));
					change = change + L"    曲线颜色：从RGB（" + r1 + L"，" + g1 + L"，" + b1 + L"）变为RGB（" + r2 + L"，" + g2 + L"，" + b2 + L"）";
					m_chart->m_product[pNMItemActivate->iItem]->SetColor(dlg.m_color);
				}
				for (i = 0; i < m_chart->m_monthNum; i++)
				{
					if (m_chart->m_product[pNMItemActivate->iItem]->m_monthYield[i].yield != dlg.m_yield[i])
						break;
				}
				if (i != m_chart->m_monthNum)
				{
					change = change + L"    月产量：从（";
					CString yield;
					for (i = 0; i < m_chart->m_monthNum; i++)
					{
						yield.Format(L"%d", m_chart->m_product[pNMItemActivate->iItem]->m_monthYield[i].yield);
						if (i < m_chart->m_monthNum - 1)
							change += yield + L"，";
						else
							change += yield + L"）变为（";
					}
					for (i = 0; i < m_chart->m_monthNum; i++)
					{
						yield.Format(L"%d", dlg.m_yield[i]);
						if (i < m_chart->m_monthNum - 1)
							change += yield + L"，";
						else
							change += yield + L"）";
						m_chart->m_product[pNMItemActivate->iItem]->ChangeMonthYield(i, m_chart->m_product[pNMItemActivate->iItem]->m_monthYield[i].year, m_chart->m_product[pNMItemActivate->iItem]->m_monthYield[i].month, dlg.m_yield[i]);
					}
				}
				CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
				pFrame->m_wndOutput.m_operationRecord[pFrame->m_wndOutput.m_operationRecordNum++] = change;
				pFrame->m_wndOutput.FillOperationRecordWindow();
			}
			CDocument *pDoc = GetDocument();
			POSITION pos = pDoc->GetFirstViewPosition();
			while (pos != NULL)
			{
				CView *pView = pDoc->GetNextView(pos);
				pView->OnInitialUpdate();
			}
		}
	}
	*pResult = 0;
}
