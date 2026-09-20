#include <afxwin.h>
//CWinApp app;  // 반드시 주석 처리할 것!!!!!!

class MyApp : public CWinApp {
public:
	virtual BOOL InitInstance();
};

BOOL MyApp::InitInstance() {
	AfxMessageBox(L"파생 클래스의 InitInstance() 재정의");

	return TRUE;
}

MyApp app;