#pragma once
#include "browser/BrowserClient.h"
#include "include/cef_base.h"
#include <vector>
#include <map>
#include "include/cef_load_handler.h"
#include <Windows.h>
namespace DuiLib
{

#define EXPORT
#ifdef EXPORT
#define CEF_API __declspec(dllexport)  
#else
#define CEF_API __declspec(dllimport)  
#endif

	//IDisplayHandleSolt �ص���
	class IDisplayHandleSolt {
	public:
		//��ַ�ı�
		virtual void OnAddressChange(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			const CefString& url) {}
		//����ı�
		virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
			const CefString& title) {}
		//ҳ��ͼ��ı�
		virtual void OnFaviconURLChange(CefRefPtr<CefBrowser> browser,
			const std::vector<CefString>& icon_urls) {}
		//ҳ��ȫ��ʱ����
		virtual void OnFullscreenModeChange(CefRefPtr<CefBrowser> browser,
			bool fullscreen) {}
		//�������ʾ������ʾ
		virtual void OnTooltip(CefRefPtr<CefBrowser> browser,
			CefString& text) {}
		//���յ�״̬��Ϣʱ
		virtual void OnStatusMessage(CefRefPtr<CefBrowser> browser,
			const CefString& value) {}
		//������ʾ����̨��Ϣ
		virtual void OnConsoleMessage(CefRefPtr<CefBrowser> browser,
			const CefString& message,
			const CefString& source,
			int line) {}
	};

	//CefLoadHandler�ص���
	class ILoadHandleSlot {
	public:
		//���س���
		virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefLoadHandler::ErrorCode errorCode,
			const CefString& errorText,
			const CefString& failedUrl) {}

		//����״̬�ı�
		virtual void OnLoadingStateChange(CefRefPtr<CefBrowser> browser,
			bool isLoading,
			bool canGoBack,
			bool canGoForward) {}

		//���ؿ�ʼ
		virtual void OnLoadStart(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame) {}

		//�������
		virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			int httpStatusCode) {}
	};

	//CefLifeSpanHandler�ص���
	class ILifeSpanHandleSlot {
	public:
		virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) {}
		virtual void DoClose(CefRefPtr<CefBrowser> browser) {}
		virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) {}
	};

	//JS�ļ�ѡ��Ի����������ڻص���
	class ILifeSpanFileDialogSolt {
	public:
		virtual void OnBeforeFileDialog(CefRefPtr<CefBrowser> browser) {}
		virtual void OnAfterFileDialog(CefRefPtr<CefBrowser> browser) {}
	};

	class CEF_API CefBrowserDll{
	public:
		CefBrowserDll();
		~CefBrowserDll();

		//CefBrowser
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
		//CefBrowserHost
		//CefFrameg
		//����url
		void LoadURL(const CefString& url);
		//��ȡ��ǰUrl
		CefString GetURL();
		//��ȡ���������
		CefString GetName(CefRefPtr<CefBrowser> browser);
		//ִ��JS ����Ϊ һ��������js���� �����Ѿ����ڵ�js�������Ӳ���
		void ExectueJS(const CefString &jscode);
		//�Ƿ񴴽����
		bool IsCreated() const;

		//��������
		void Release();
		//cef��ں���
		void CreateCefWindow(HWND hWnd, const CefString& url, 
			ILifeSpanHandleSlot* life_handle = NULL, 
			ILoadHandleSlot* load_handle = NULL,
			IDisplayHandleSolt* display_handle = NULL,
			ILifeSpanFileDialogSolt* filedialog_handle = NULL);
		//�ر�һ�����������
		void CloseCefWindow();
		//���ע�ắ��
		void SetFunction(const CefString &name, CustomFunction function);

	//��̬��ʼ�����ܽӿ�
	public:
		//��ʼ��cef
		static bool InitCef(HINSTANCE hInstance, const CefString& cache_path = "", const CefString& log_file = "");
		//�ر���Ϣѭ��
		static void Quit();
		//������Ϣѭ��
		static void Run();
	//���ýӿ�
	private:
		//���ý���
		void SetFocus(bool enable);
		//��ȡ���ű���
		double GetZoomLevel();

	private:
		//���������
		CefRefPtr<CBrowserClient> client_browser_;
	};
}


