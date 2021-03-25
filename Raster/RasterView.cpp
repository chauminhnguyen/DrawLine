
// RasterView.cpp : implementation of the CRasterView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Raster.h"
#endif

#include "RasterDoc.h"
#include "RasterView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "LineDDA.h"
#include "Bresenham.h"


// CRasterView

IMPLEMENT_DYNCREATE(CRasterView, CView)

BEGIN_MESSAGE_MAP(CRasterView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CRasterView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CRasterView construction/destruction

CRasterView::CRasterView() noexcept
{
	// TODO: add construction code here

}

CRasterView::~CRasterView()
{
}

BOOL CRasterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);	
}

// CRasterView drawing

void CRasterView::OnDraw(CDC* pDC)
{
	CRasterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	// LineDDA::LineDDA2(pDC, 500, 50, 200, 500, RGB(255, 0, 0));
}


// CRasterView printing


void CRasterView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CRasterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRasterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRasterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CRasterView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CRasterView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CRasterView diagnostics

#ifdef _DEBUG
void CRasterView::AssertValid() const
{
	CView::AssertValid();
}

void CRasterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRasterDoc* CRasterView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRasterDoc)));
	return (CRasterDoc*)m_pDocument;
}
#endif //_DEBUG


// CRasterView message handlers
int x_start = NULL;
int y_start = NULL;
int x_end = NULL;
int y_end = NULL;
bool isDrag = FALSE;

void CRasterView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	x_start = point.x;
	y_start = point.y;
	isDrag = TRUE;

	CView::OnLButtonDown(nFlags, point);
}


void CRasterView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CClientDC* pDC = new CClientDC(this);
	x_end = point.x;
	y_end = point.y;
	if (x_start != NULL && y_start != NULL && x_end != NULL && y_end != NULL && isDrag) {
		Invalidate();
		UpdateWindow();
		//LineDDA::DDA(pDC, x_start, y_start, x_end, y_end, RGB(255, 0, 0));
		Bresenham::LineBresenham(pDC, x_start, y_start, x_end, y_end, RGB(255, 0, 0));
	}
	
	CView::OnMouseMove(nFlags, point);
}


void CRasterView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	isDrag = FALSE;
	
	CView::OnLButtonUp(nFlags, point);
}
