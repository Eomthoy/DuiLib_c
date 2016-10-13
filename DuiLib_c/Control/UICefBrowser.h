#pragma once
#include "Control/UICefBrowser/CefBrowser/CefBrowserDll.h"
#include <share.h>
#include <boost/bind.hpp>
#include "../UIlib.h"

/***********************************************************
ʹ��˵����
	1.��DuiLib::Create����ǰ����InitCef��ʼ��cef
	2.��MessageLoop()֮��Quit
	3.�̳�ʵ��ISetHandleSolt�ص�,������ʵ��ָ��������Ļص�ʵ��
	4.�̳�ʵ��OnAfterCreate������ResizeBrowser�����
***********************************************************/

namespace DuiLib {
	//������
	const TCHAR CCefBrowserUIClassName[] = L"CefBrowserUI";		
	//�ؼ�����
	const TCHAR CCefBrowserUIItemInterface[] = L"CefBrowser";	
	class ISetHandleSolt {
	public:
		//������ص�ʵ��ָ�����ú���
		virtual ILoadHandleSlot* GetILoadHandleSlot(std::wstring browser_name) = 0;
		virtual ILifeSpanHandleSlot* GetILifeSpanHandleSlot(std::wstring browser_name) = 0;
		virtual IDisplayHandleSolt* GetIDisplayHandleSolt(std::wstring browser_name) = 0;
	};

	class UILIB_API CCefBrowserUI : public DuiLib::CControlUI {
	public:
		CCefBrowserUI(HWND parent, ISetHandleSolt* set_handle = NULL);
		~CCefBrowserUI(void);

	//DuiLib�ص�����
	public:
		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		void DoInit();
		//����������������ʾ���
		virtual void SetInternVisible(bool bVisible = true);

	//��̬���ܽӿ�
	public:
		//��ʼ��CEF
		static void InitCef(HINSTANCE hInstance, CefString cache_path = "", CefString log_file = "");
		//�˳�CEF
		static void Quit();
		//����cef��Ϣѭ��
		static void StartCefMessageLoop();

	//�ؼ�cef����
	public:
		//����url
		void LoadURL(std::wstring url);
		//�Ƿ������ǰ����
		bool CanGoForward();
		//��ǰ����
		void GoForward();
		//���¼���
		void Reload();
		//���Ի������
		void ReloadIgnoreCache();
		//ֹͣ����
		void StopLoad();
		//������󵼺�
		bool CanGoBack();
		//��󵼺�
		void GoBack();
		//��ȡ��������
		CefWindowHandle GetHwnd();
		//�������ű���
		void SetZoomLevel(double zoomLevel);
		//��ȡ��ǰUrl
		CefString GetURL();
		//ִ��JS ����Ϊ һ��������js���� �����Ѿ����ڵ�js�������Ӳ���
		void ExectueJS(const CefString &jscode);
		//����Cef���������
		bool CreateCefWindow(CefString url, bool needfocus,
			std::unique_ptr<ILifeSpanHandleSlot> life_handle = NULL, 
			std::unique_ptr<ILoadHandleSlot> load_handle = NULL,
			std::unique_ptr<IDisplayHandleSolt> display_handle = NULL);
		//�ر������
		void CloseCefWindow();
		//���ע�ắ��
		void SetFunction(const CefString &name, CustomFunction function);
	

	//UI��ӿ�
	public:
		//�ػ������
		void ResizeBrowser(DuiLib::CDuiRect rect);
		//�����Ƿ���ʾ
		virtual void SetVisible(bool bVisible = true);

	private:
		//Ĭ�ϵ�ַ
		std::wstring url_;
		//cef���ܽӿڶ���
		CefBrowserDll browser_dll_;
		//����load life �ص������ص�ָ��
		ISetHandleSolt* set_handle_;
		//��������
		HWND parent_hwnd_;
		//���������
		std::wstring browser_name_;
		//�Ƿ񴴽����
		bool is_created_;
	};
}

