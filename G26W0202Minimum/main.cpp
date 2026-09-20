#include <afxwin.h>

class MyApp : public CWinApp {
public:
    virtual BOOL InitInstance();
};

class CMainWnd : public CFrameWnd {
private:
    CPoint m_ptClick = CPoint(-100, -100);

public:
    CMainWnd();

    DECLARE_MESSAGE_MAP()

    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnPaint();
};

BOOL MyApp::InitInstance() {
    m_pMainWnd = new CMainWnd();
    m_pMainWnd->ShowWindow(m_nCmdShow);
    m_pMainWnd->UpdateWindow();

    return TRUE;
}

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)
    ON_WM_LBUTTONDOWN()
    ON_WM_PAINT()
END_MESSAGE_MAP()

CMainWnd::CMainWnd() {
    Create(NULL, L"GUI 프로그래밍 - 원 그리기");
}

void CMainWnd::OnLButtonDown(UINT nFlags, CPoint point) {
    m_ptClick = point;
    Invalidate();
}

void CMainWnd::OnPaint() {
    CPaintDC dc(this);

    dc.Ellipse(m_ptClick.x - 30, m_ptClick.y - 30,
        m_ptClick.x + 30, m_ptClick.y + 30);
}

MyApp app;