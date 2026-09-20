#include <afxwin.h>
//CWinApp app;  // 반드시 주석 처리할 것!!!!!!

class MyApp : public CWinApp {
public:
	virtual BOOL InitInstance();
};

class CMainWnd : public CFrameWnd {
public:
	CMainWnd();
};

BOOL MyApp::InitInstance() {
	//AfxMessageBox(L"파생 클래스의 InitInstance() 재정의");

	m_pMainWnd = new CMainWnd();
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

CMainWnd::CMainWnd() {
	Create(NULL, L"GUI 프로그래밍");
}

MyApp app;