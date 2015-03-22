#include <windows.h>
#include <time.h>
#include "resource.h"

#define szWindowClass	TEXT("First")
#define szTitle			TEXT("First App")

void MakeCircle(HDC hdc, int startX, int startY);
void MakeRectangle(HDC hdc, int startX, int startY);
HCURSOR LoadAnimatedCursor(HINSTANCE hInstance, UINT nID, LPCTSTR pszResouceType);



LRESULT CALLBACK WndProc( HWND hWnd
						 , UINT message
						 , WPARAM wParam
						 , LPARAM lParam );

int APIENTRY WinMain( HINSTANCE hInstance,
					  HINSTANCE hPrevInstance,
					  LPSTR lpszCmdParam,
					  int nCmdShow)
{
    srand(time(NULL));


	WNDCLASSEX wcex;

	wcex.cbSize		= sizeof(WNDCLASSEX);
    wcex.style      = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon	= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	//wcex.hCursor= LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
    wcex.hCursor = LoadAnimatedCursor(hInstance, IDR_ANI1, L"MyType");
	wcex.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDR_MENU1);
	wcex.lpszClassName	= szWindowClass;
	if( !RegisterClassEx(&wcex) )
		return 0;

	HWND	hWnd = CreateWindowEx( WS_EX_APPWINDOW
		, szWindowClass
		, szTitle
		, WS_OVERLAPPEDWINDOW //OVERLAPPED 라고하면 최소화 닫기 없음
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, 800
		, 600
		, NULL
		, NULL
		, hInstance
		, NULL );

	if( !hWnd )
		return 0;

    WCHAR appTitle[256]; 
    LoadString(hInstance, IDS_TITLE, appTitle, 256);
    SetWindowText(hWnd, appTitle);


	ShowWindow(hWnd, nCmdShow);

	MSG			msg;
	while( GetMessage(&msg, NULL, 0, 0) )
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

// 메시지 처리 함수
LRESULT CALLBACK WndProc( HWND hWnd
						 , UINT message
						 , WPARAM wParam
						 , LPARAM lParam )
{
	HDC	hdc;
	PAINTSTRUCT	ps;

    switch (message)
    {
    case WM_CREATE:

        break;
    case WM_PAINT:
    {
                     hdc = BeginPaint(hWnd, &ps);

//                      HBRUSH myBrush;
//                      HBRUSH oldBrush;
// 
//                      myBrush = CreateSolidBrush(RGB(128, 128, 255));
// 
//                      MoveToEx(hdc, 100, 100, NULL);
//                      LineTo(hdc, 200, 200);
//                      LineTo(hdc, 250, 50);
//                      LineTo(hdc, 100, 100);
// 
//                      oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
//                      Rectangle(hdc, rand() % 100, 200, 500, 400);
//                      myBrush = CreateSolidBrush(RGB(150, 50, 150));
//                      oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
// 
//                      Ellipse(hdc, 600, 20, 700, 100);
// 
//                      DeleteObject(myBrush);
//                      TextOut(hdc, 400, 400, L"Hello", 5);


                     HDC imgDC = CreateCompatibleDC(hdc);
                     HBITMAP hBitmap = LoadBitmap((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDB_BITMAP1));
                     HBITMAP oldBitmap = (HBITMAP)SelectObject(imgDC, hBitmap);

                     BitBlt(hdc, 0, 0, 800, 600, imgDC, 0, 0, SRCCOPY);
                     SelectObject(imgDC, oldBitmap);
                     DeleteObject(hBitmap);
                     DeleteDC(imgDC);



                     EndPaint(hWnd, &ps);
    }

        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;


    case WM_LBUTTONDOWN:
    {
                           hdc = BeginPaint(hWnd, &ps);
                           int num;
                           OutputDebugString(L"왼쪽버튼이 눌림\n");
                           //         int result = MessageBox(hWnd, L"맹박", L"MB bar", MB_CANCELTRYCONTINUE); //NULL 넣으면 MB계속 띄움, hwnd면 한번만!
                           //         if (result == IDCANCEL){
                           //             OutputDebugString(L"Cancel 눌렀다 \n");
                           //         }

                           //todo GetDC로 받아오고 Release로 놓아줄것

                           int x = LOWORD(lParam);
                           int y = HIWORD(lParam);

                           num = rand() % 2;
                           if (num == 0)
                           {
                               MakeCircle(hdc, x, y);
                           }
                           if (num == 1)
                           {
                               MakeRectangle(hdc, x, y);
                           }
                           EndPaint(hWnd, &ps);

                           break;
    }
    case  WM_RBUTTONDOWN:
        OutputDebugString(L"오른쪽버튼이 눌림\n");
        break;

    case WM_LBUTTONDBLCLK:
    {
                             OutputDebugString(L"이벤트 더블클릭\n");
                             break;
    }

    case WM_COMMAND:
    {
                       switch (LOWORD(wParam))
                       {
                       case ID_FILE_EXIT:
                           DestroyWindow(hWnd);
                       }
                       break;
    }

    case WM_MOUSEMOVE:
    {
                         WCHAR strX[256];
                         WCHAR strY[256];
                         
                         memset(strX, 0, sizeof(strX));
                         memset(strY, 0, sizeof(strY));

                         hdc = GetDC(hWnd);
                         int mouseX = LOWORD(lParam);
                         int mouseY = HIWORD(lParam);

                         wsprintf(strX, L"X= %d",mouseX);
                         wsprintf(strY, L"Y= %d", mouseY);


                         TextOut(hdc, 600, 200, strX, wcslen(strX));
                         TextOut(hdc, 600, 220, strY, wcslen(strY));

                         MakeCircle(hdc,mouseX,mouseY);
                         //InvalidateRect(hWnd, NULL, true);

                         ReleaseDC(hWnd,hdc);
                         break;
    }
       
    }


    

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void MakeRectangle(HDC hdc,int startX, int startY)
{
    HBRUSH brush;
    //hdc = BeginPaint(hWnd, &ps);

    brush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
    Rectangle(hdc, startX, startY, startX + rand() % 80, startY + rand() % 100);

}

void MakeCircle(HDC hdc, int startX, int startY)
{
    HBRUSH brush;
    //SelectObject()로 붓을들고
    
    brush = CreateSolidBrush(RGB(200, 20, 20));

    SelectObject(hdc, brush);
    int endX = startX + rand() % 80;
    int endY = startY + rand() % 100;
    //brush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
    Ellipse(hdc, startX, startY, endX ,endY );
    //RECT rect = { startX, startY, endX, endY };


    DeleteObject(brush);
    //DeleteObject() 로 붙을 놓고
   // EndPaint(hWnd, &ps);

}
HCURSOR LoadAnimatedCursor(HINSTANCE hInstance, UINT nID, LPCTSTR pszResouceType)
{
    HCURSOR hCursor = NULL;
    if (hInstance)
    {
        HRSRC hResource = FindResource(hInstance, MAKEINTRESOURCE(nID), pszResouceType);
        DWORD dwResourceSize = SizeofResource(hInstance, hResource);
        if (dwResourceSize > 0)
        {
            HGLOBAL hRsrcGlobal = LoadResource(hInstance, hResource);
            if (hRsrcGlobal)
            {
                LPBYTE pResource = (LPBYTE)LockResource(hRsrcGlobal);
                if (pResource)
                {
                    hCursor = (HCURSOR)CreateIconFromResource(pResource, dwResourceSize, FALSE, 0x00030000);
                    UnlockResource(pResource);
                }
                FreeResource(hRsrcGlobal);
            }
        }
    }
    return hCursor;
}

