#pragma once
#include <vector>
#include <map>
#include "include/cef_load_handler.h"
namespace DuiLib
{
	class CefBrowserBender {
	public:
		CefBrowserBender();
		~CefBrowserBender(void);
	//��̬��ʼ�����ܽӿ�
	public:
		//��ʼ��cef
		static bool InitCef(HINSTANCE hInstance, CefString cache_path = "", CefString log_file = "");
	};
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nCmdShow ) {
	DuiLib::CefBrowserBender::InitCef(hInstance, L"BrowserCache", L"Log\\render.log");
	return 0;
}