#include <windows.h>
#include <time.h>
#include <math.h>

#define szWindowClass	TEXT("First")
#define szTitle			TEXT("First App")

void Drawline(HWND hndl);
void BoxCollision(HWND hndl);
void CircleCollision(HWND hndl);
void BoxCircleCollision(HWND hndl);
bool IsBoxCirCleCollision();

float mouseX;
float mouseY;



LRESULT CALLBACK WndProc( HWND hWnd
                         , UINT message
                         , WPARAM wParam
                         , LPARAM lParam );

int APIENTRY WinMain( HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPSTR lpszCmdParam,
                      int nCmdShow)
{
    WNDCLASSEX wcex;

    wcex.cbSize		= sizeof(WNDCLASSEX);
    wcex.style		= CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc	= (WNDPROC)WndProc;
    wcex.cbClsExtra		= 0;
    wcex.cbWndExtra		= 0;
    wcex.hInstance		= hInstance;
    wcex.hIcon	= LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hIconSm= LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor= LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
    wcex.lpszMenuName	= NULL;
    wcex.lpszClassName	= szWindowClass;

    if( !RegisterClassEx(&wcex) )
        return 0;

    HWND	hWnd = CreateWindowEx( WS_EX_APPWINDOW
        , szWindowClass
        , szTitle
        , WS_OVERLAPPEDWINDOW
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

    ShowWindow(hWnd, nCmdShow);

    MSG			msg;


    while (1)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message==WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
            
        else //Game 처리
        {
            //Drawline(hWnd);
            //BoxCollision(hWnd);
            CircleCollision(hWnd);
            //BoxCircleCollision(hWnd);
        }
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




    switch(message)
    {
    case WM_CREATE:

        break;
    case WM_PAINT:
        {
            hdc = BeginPaint( hWnd, &ps );

            

            EndPaint( hWnd, &ps );
        }
        break;


    case WM_MOUSEMOVE:
    {

       

       mouseX = LOWORD(lParam);
       mouseY = HIWORD(lParam);


       //InvalidateRect(hWnd, NULL, true);

       
       break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;



    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

void Drawline(HWND hndl)
{
    HDC hdc = GetDC(hndl);

    WCHAR strX[256];
    WCHAR strY[256];
    WCHAR d[256];

    memset(strX, 0, sizeof(strX));
    memset(strY, 0, sizeof(strY));
    memset(d, 0, sizeof(d));

    float x = 250;
    float y = 400;
    //float x2 = 200;
    //float y2 = 600;


    MoveToEx(hdc, 500, 0, NULL);
    LineTo(hdc, 200, 600);

    float dist;
    float a, b, c;

    a = y - mouseY;
    b = -(x - mouseX);
    c = -a*mouseX -b*mouseY;

    float d1 = abs(a*mouseX + b*mouseY + c);
    float d2 = sqrt(a*a + b*b);

    dist = d1 / d2;
    //dist = abs(a*mouseX + b*mouseY + c) / sqrt(a*a + b*b);

    wsprintf(strX, L"X= %d", (int)mouseX);
    wsprintf(strY, L"Y= %d", (int)mouseY);
    wsprintf(d, L"Distance= %02f", dist);


    TextOut(hdc, 600, 200, strX, wcslen(strX));
    TextOut(hdc, 600, 220, strY, wcslen(strY));
    TextOut(hdc, 600, 240, d, wcslen(d));




    ReleaseDC(hndl, hdc);
}

void BoxCollision(HWND hndl)
{


}

void CircleCollision(HWND hndl)
{
    HDC hdc = GetDC(hndl);
    HDC	subdc = CreateCompatibleDC(hdc);
    HBITMAP memoryBitmap = CreateCompatibleBitmap(hdc, 800, 600);
    SelectObject(subdc, memoryBitmap);


    Rectangle(subdc, 0, 0, 800, 600);

    HBRUSH fixbrush, movingbrush, collbrush;
    fixbrush = CreateSolidBrush(RGB(200, 20, 20));
    movingbrush = CreateSolidBrush(RGB(20, 200, 20));
    collbrush = CreateSolidBrush(RGB(20, 20, 200));

    SelectObject(subdc, fixbrush);

    int startX = 400 - 50;
    int startY = 300 - 50;
    int endX = 400 + 50;
    int endY = 300 + 50;

    Ellipse(subdc, startX, startY, endX, endY);

    float distance;
    distance = sqrt((mouseX - 400)*(mouseX - 400) + (mouseY - 300)*(mouseY - 300));

    if (distance < 50+30)
    {
        SelectObject(subdc, collbrush);
        Ellipse(subdc, mouseX - 30, mouseY - 30, mouseX + 30, mouseY + 30);
    }
    else
    {
        SelectObject(subdc, movingbrush);
        Ellipse(subdc, mouseX - 30, mouseY - 30, mouseX + 30, mouseY + 30);
    }
    BitBlt(hdc, 0, 0, 800, 600, subdc, 0, 0, SRCCOPY); //hdc 를 subdc로 바꿈

    DeleteDC(subdc);
    DeleteObject(memoryBitmap);
    DeleteObject(fixbrush);
    DeleteObject(movingbrush);
    DeleteObject(collbrush);

}

void BoxCircleCollision(HWND hndl)
{
    HDC hdc = GetDC(hndl);
    HDC	subdc = CreateCompatibleDC(hdc);
    HBITMAP memoryBitmap = CreateCompatibleBitmap(hdc, 800, 600);
    SelectObject(subdc, memoryBitmap);


    Rectangle(subdc, 0, 0, 800, 600);

    HBRUSH fixbrush, movingbrush, collbrush;
    fixbrush = CreateSolidBrush(RGB(200, 20, 20));
    movingbrush = CreateSolidBrush(RGB(20, 200, 20));
    collbrush = CreateSolidBrush(RGB(20, 20, 200));


    bool isColl=false;
    float centerX = 400;
    float centerY = 300;
    float edge = 50;
    float left = centerX-edge;
    float right = centerX+edge;
    float top = centerY-edge;
    float bottom = centerY+edge;
    
    float radius = 30;
    SelectObject(subdc, fixbrush);
    Rectangle(subdc, left, top, right, bottom);

    float distance = sqrt((mouseX - centerX)*(mouseX - centerX) + (mouseY - centerY)*(mouseY - centerY));

    if (centerX - edge < mouseX&&mouseX < centerX + edge)
        isColl = true;
    
    else if (centerY - edge < mouseY&&mouseY < centerY + edge)
        isColl = true;

    //if ()





 
    if (distance - radius > edge){
        if (distance > radius + edge*sqrt(2.0))
        {
            isColl = false;
        }
        isColl = false;
    }
    else
    {
        isColl = true;
    }

    SelectObject(subdc, fixbrush);
    MoveToEx(subdc, (int)centerX, (int)centerY, NULL);
    LineTo(subdc, mouseX, mouseY);


    if (isColl)
    {
        SelectObject(subdc, movingbrush);
        Ellipse(subdc, mouseX - radius, mouseY - radius, mouseX + radius, mouseY + radius);
    }
    else
    {
        SelectObject(subdc, collbrush);
        Ellipse(subdc, mouseX - radius, mouseY - radius, mouseX + radius, mouseY + radius);
    }

    BitBlt(hdc, 0, 0, 800, 600, subdc, 0, 0, SRCCOPY); //hdc 를 subdc로 바꿈





    DeleteDC(subdc);
    DeleteObject(memoryBitmap);
    DeleteObject(fixbrush);
    DeleteObject(movingbrush);
    DeleteObject(collbrush);
}
