#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

void MyDrawLine(Graphics &graphics)
{
	Pen      pen(Color(255, 0, 0, 255));
	graphics.DrawLine(&pen, 0, 0, 200, 100);
	graphics.DrawLine(&pen, 0, 0, 300, 100);
}

void MyWriteFont(Graphics &graphics)
{
	SolidBrush  brush(Color(0, 255, 255));
	FontFamily  fontFamily(L"Times New Roman");
	Font        font(&fontFamily, 24, FontStyleBold, UnitPixel);
	PointF      pointF(10.0f, 20.0f);

	graphics.DrawString(L"Hello World!", -1, &font, pointF, &brush);

	Font        font1(&fontFamily, 24, FontStyleStrikeout, UnitPixel);
	PointF      pointF1(60.0f, 60.0f);

	graphics.DrawString(L"Hello World!", -1, &font1, pointF1, &brush);
}

void MyDrawRectangle(Graphics &graphics)
{
	Pen blackPen(Color(255, 0, 0, 0), 10);
	Pen greenPen(Color(255, 0, 255, 0), 5);
	greenPen.SetAlignment(PenAlignmentCenter);
	graphics.DrawRectangle(&blackPen, 10, 10, 100, 50);
	graphics.DrawRectangle(&greenPen, 10, 10, 100, 50);

	greenPen.SetAlignment(PenAlignmentInset);
	graphics.DrawRectangle(&blackPen, 80, 80, 100, 50);
	graphics.DrawRectangle(&greenPen, 80, 80, 100, 50);
}

void MyDrawLineWithLineCap(Graphics &graphics)
{
	Pen pen(Color(255, 0, 0, 255), 8);
	pen.SetStartCap(LineCapArrowAnchor);
	pen.SetEndCap(LineCapRoundAnchor);
	graphics.DrawLine(&pen, 20, 175, 300, 175);
}

void MyDrawLineJoin(Graphics &graphics)
{
	GraphicsPath path;
	Pen penJoin(Color(255, 0, 0, 255), 8);

	path.StartFigure();
	path.AddLine(Point(50, 200), Point(100, 200));
	path.AddLine(Point(100, 200), Point(100, 250));

	penJoin.SetLineJoin(LineJoinMiter);
	graphics.DrawPath(&penJoin, &path);
}

void MyDrawElliseWithBrush(Graphics &graphics)
{
	SolidBrush solidBrush(Color(255, 255, 0, 0));
	graphics.FillEllipse(&solidBrush, 0, 0, 100, 60);
}

void MyDrawTexture(Graphics &graphics)
{
	Image         image(L"Texture2.jpg");
	TextureBrush  tBrush(&image);
	Pen           texturedPen(&tBrush, 30);

	//graphics.DrawImage(&image, 0, 0, image.GetWidth(), image.GetHeight());
	graphics.DrawEllipse(&texturedPen, 100, 20, 200, 100);
}

void MyDrawShapWithHatchBrush(Graphics &graphics)
{
	HatchBrush hBrush(HatchStyleZigZag, Color(255, 255, 0, 0),
		Color(255, 128, 255, 255));
	graphics.FillEllipse(&hBrush, 0, 0, 100, 60);
}

void MyDrawShapWithImageTexture(Graphics &graphics)
{
	Image image(L"Texture2.jpg");
	TextureBrush tBrush(&image);
	tBrush.SetTransform(&Matrix(75.0 / 640.0, 0.0f, 0.0f,
		75.0 / 480.0, 0.0f, 0.0f));
	graphics.FillEllipse(&tBrush, Rect(0, 150, 150, 250));
	graphics.FillRectangle(&tBrush, Rect(200, 250, 150, 100));
}

void MyDrawShapWithGradientColor(Graphics &graphics)
{
	LinearGradientBrush linGrBrush(
		Point(0, 10),
		Point(200, 10),
		Color(255, 255, 0, 0),   // opaque red
		Color(255, 0, 0, 255));  // opaque blue

	Pen pen(&linGrBrush);

	graphics.DrawLine(&pen, 0, 10, 200, 10);
	graphics.FillEllipse(&linGrBrush, 0, 30, 200, 100);
	graphics.FillRectangle(&linGrBrush, 0, 155, 500, 30);
}

void MyDrawBitmap(Graphics &graphics)
{
	Image image(L"my.bmp");
	graphics.DrawImage(&image, 60, 10);
}

VOID OnPaint(HDC hdc)
{
	Graphics graphics(hdc);

	//MyDrawLine(graphics);
	//MyWriteFont(graphics);
	//MyDrawRectangle(graphics);
	//MyDrawLineWithLineCap(graphics);
	//MyDrawLineJoin(graphics);
	//MyDrawTexture(graphics);
	//MyDrawElliseWithBrush(graphics);
	//MyDrawShapWithHatchBrush(graphics);
	//MyDrawShapWithImageTexture(graphics);
	//MyDrawShapWithGradientColor(graphics);
	MyDrawBitmap(graphics);
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	HWND                hWnd;
	MSG                 msg;
	WNDCLASS            wndClass;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = TEXT("GettingStarted");

	RegisterClass(&wndClass);

	hWnd = CreateWindow(
		TEXT("GettingStarted"),   // window class name
		TEXT("Getting Started"),  // window caption
		WS_OVERLAPPEDWINDOW,      // window style
		CW_USEDEFAULT,            // initial x position
		CW_USEDEFAULT,            // initial y position
		CW_USEDEFAULT,            // initial x size
		CW_USEDEFAULT,            // initial y size
		NULL,                     // parent window handle
		NULL,                     // window menu handle
		hInstance,                // program instance handle
		NULL);                    // creation parameters

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	GdiplusShutdown(gdiplusToken);
	return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC          hdc;
	PAINTSTRUCT  ps;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		OnPaint(hdc);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
} // WndProc