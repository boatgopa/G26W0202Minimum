#include <afxwin.h>
#include <vector>

// 1. 선(Line) 하나의 정보를 저장하는 구조체
struct DrawLine {
    CPoint start;
    CPoint end;
    COLORREF color;
};

// 2. 애플리케이션 클래스
class CSimplePaintApp : public CWinApp {
public:
    virtual BOOL InitInstance();
};

// 3. 메인 윈도우 클래스
class CMainWnd : public CFrameWnd {
private:
    std::vector<DrawLine> m_lines; // 지금까지 그린 모든 선 모음
    CPoint m_ptPrev;               // 마우스 이동 전 좌표
    BOOL m_bDrawing;               // 현재 드래그(그리기) 중인지 여부
    COLORREF m_currentColor;        // 현재 선택된 펜 색상

public:
    CMainWnd();

    DECLARE_MESSAGE_MAP()

    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnPaint();
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point); // 우클릭: 색상 변경
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags); // C키: 화면 지우기
};

// App 초기화
BOOL CSimplePaintApp::InitInstance() {
    m_pMainWnd = new CMainWnd();
    m_pMainWnd->ShowWindow(m_nCmdShow);
    m_pMainWnd->UpdateWindow();
    return TRUE;
}

// 메시지 맵 등록
BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONUP()
    ON_WM_PAINT()
    ON_WM_RBUTTONDOWN()
    ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// 생성자
CMainWnd::CMainWnd() {
    Create(NULL, _T("MFC 미니 그림판 (좌클릭: 드래그 그리기 / 우클릭: 색상 변경 / 'C'키: 모두 지우기)"));
    m_bDrawing = FALSE;
    m_currentColor = RGB(0, 0, 0); // 기본 색상: 검정색
}

// 마우스 왼쪽 버튼 눌렀을 때 (그리기 시작)
void CMainWnd::OnLButtonDown(UINT nFlags, CPoint point) {
    m_bDrawing = TRUE;
    m_ptPrev = point;
    SetCapture(); // 마우스가 윈도우 밖으로 나가도 이벤트를 받도록 설정
}

// 마우스 이동할 때 (선 그리기)
void CMainWnd::OnMouseMove(UINT nFlags, CPoint point) {
    if (m_bDrawing) {
        // 1. 화면에 실시간으로 선 그리기 (화면 갱신 최소화)
        CClientDC dc(this);
        CPen pen(PS_SOLID, 3, m_currentColor);
        CPen* pOldPen = dc.SelectObject(&pen);

        dc.MoveTo(m_ptPrev);
        dc.LineTo(point);

        dc.SelectObject(pOldPen);

        // 2. 그려진 선 데이터 저장 (WM_PAINT 발생 시 다시 그리기 위함)
        DrawLine line = { m_ptPrev, point, m_currentColor };
        m_lines.push_back(line);

        // 현재 좌표를 이전 좌표로 갱신
        m_ptPrev = point;
    }
}

// 마우스 왼쪽 버튼 뗐을 때 (그리기 종료)
void CMainWnd::OnLButtonUp(UINT nFlags, CPoint point) {
    if (m_bDrawing) {
        m_bDrawing = FALSE;
        ReleaseCapture(); // 마우스 캡처 해제
    }
}

// 창이 가려지거나 최소화 후 다시 켜질 때 복원하는 함수
void CMainWnd::OnPaint() {
    CPaintDC dc(this);

    // 저장된 모든 선들을 다시 그림
    for (const auto& line : m_lines) {
        CPen pen(PS_SOLID, 3, line.color);
        CPen* pOldPen = dc.SelectObject(&pen);

        dc.MoveTo(line.start);
        dc.LineTo(line.end);

        dc.SelectObject(pOldPen);
    }
}

// 마우스 우클릭 시 색상 변경 (검정 -> 빨강 -> 파랑 -> 초록 순환)
void CMainWnd::OnRButtonDown(UINT nFlags, CPoint point) {
    if (m_currentColor == RGB(0, 0, 0)) m_currentColor = RGB(255, 0, 0);       // 빨강
    else if (m_currentColor == RGB(255, 0, 0)) m_currentColor = RGB(0, 0, 255); // 파랑
    else if (m_currentColor == RGB(0, 0, 255)) m_currentColor = RGB(0, 255, 0); // 초록
    else m_currentColor = RGB(0, 0, 0);                                         // 검정
}

// 키보드 키 입력을 받았을 때 ('C' 키 누르면 전체 지우기)
void CMainWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
    if (nChar == 'C' || nChar == 'c') {
        m_lines.clear(); // 선 데이터 초기화
        Invalidate();    // 화면 전체를 새로고침 (OnPaint 호출)
    }
}

// 전역 응용 프로그램 객체
CSimplePaintApp app;