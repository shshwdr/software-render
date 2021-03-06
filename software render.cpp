// software render.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include "tgaimage.h"
#include "model.h"

using namespace std;

static const int windowWidth = 600;
static const int windowHeight = 450;
static const LPCTSTR title = (LPCTSTR)"CS's playground";
HDC hdc = NULL;
HDC screenHDC = NULL;

void Update();
void InitWindow();

//test only
void TestTGAImage();

int main()
{
	TestTGAImage();
	//InitWindow();

	//Update();
    return 0;
}


LRESULT OnEvent(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void InitWindow() {
	WNDCLASS windowClass = { CS_BYTEALIGNCLIENT, (WNDPROC)OnEvent, 0, 0, 0, NULL, NULL, NULL, NULL, title };
	if (!RegisterClass(&windowClass))
		MessageBox(NULL, (LPCTSTR)"Could not register class", (LPCTSTR)"Error", MB_OK);
	HWND windowHandle = CreateWindow(title,
		title,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0,
		0,
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN),
		NULL,
		NULL,
		NULL,
		NULL);
	SetWindowPos(windowHandle, NULL, 0, 0, windowWidth, windowHeight, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));
	ShowWindow(windowHandle, SW_NORMAL);
	hdc = GetDC((windowHandle));
	screenHDC = CreateCompatibleDC(hdc);
	BITMAPINFO bitmapInfo = { { sizeof(BITMAPINFOHEADER),windowWidth, windowHeight, 1, 32, BI_RGB, windowWidth * windowHeight * 4, 0, 0, 0, 0 } };
	LPVOID ptr;
	//创建设备无关的位图
	HBITMAP bitmapHandler = CreateDIBSection(screenHDC, &bitmapInfo, DIB_RGB_COLORS, &ptr, 0, 0);
	if (bitmapHandler == NULL)
		return;

	HBITMAP screenObject = (HBITMAP)SelectObject(screenHDC, bitmapHandler);
	ShowWindow(windowHandle, SW_NORMAL);
	UpdateWindow(windowHandle);
}

void Update()
{
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{

	}
}

//test only

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
	bool steep = false;
	if (abs(x0 - x1) < abs(y0 - y1)) {
		swap(x0, y0);
		swap(x1, y1);
		steep = true;
	}
	if (x0 > x1) {
		swap(x0, x1);
		swap(y0, y1);
	}
	int dx = x1 - x0;
	int dx2 = dx * 2;
	int dy = y1 - y0;

	//derror was dy/dx, and compare error with 0.5
	//but we can multiply 2dx for all of them, so there is no float in calculation

	int derror2 = abs(dy) * 2;
	int error2 = 0;
	int y = y0;
	int yStep = (y1 > y0) ? 1 : -1;
	for (int x = x0;x <= x1;x++) {
		if (steep) {
			image.set(y, x, color);
		}
		else {
			image.set(x, y, color);
		}
		error2 += derror2;
		if (error2 > dx) {
			error2 -= dx2;
			y += yStep;
		}
	}
}
void TestTGAImage() {
	int width = 800;
	int height = 800;
	TGAImage image(width, height, TGAImage::RGB);
	const TGAColor red = TGAColor(255, 0, 0, 255);
	Model *model = new Model("african_haed.obj");

	for (int i = 0;i < model->nfaces();i++) {
		vector<int> face = model->face(i);
		for (int j = 0;j < 3;j++) {
			Vec3f a = model->vert(face[j]);
			Vec3f b = model->vert(face[(j + 1) % 3]);
			int x0 = (a.x+1)*width / 2.;
			int y0 = (a.y+1)*height / 2.;
			int x1 = (b.x + 1)*width / 2.;
			int y1 = (b.y + 1)*height / 2.;
			line(x0, y0, x1, y1, image, red);
		}
	}

	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
}