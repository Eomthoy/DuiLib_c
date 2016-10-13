#pragma once
#include "BrowserClient.h"
#include "RenderAndBrowserApp.h"
#include <vector>
#include <map>
#include "include/cef_load_handler.h"

namespace DuiLib {
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
			const CefString& url) = 0;
		//����ı�
		virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
			const CefString& title) = 0;
		//ҳ��ͼ��ı�
		virtual void OnFaviconURLChange(CefRefPtr<CefBrowser> browser,
			const std::vector<CefString>& icon_urls) = 0;
		//ҳ��ȫ��ʱ����
		virtual void OnFullscreenModeChange(CefRefPtr<CefBrowser> browser,
			bool fullscreen) = 0;
		//�������ʾ������ʾ
		virtual bool OnTooltip(CefRefPtr<CefBrowser> browser,
			CefString& text) = 0;
		//���յ�״̬��Ϣʱ
		virtual void OnStatusMessage(CefRefPtr<CefBrowser> browser,
			const CefString& value) = 0;
		//������ʾ����̨��Ϣ
		virtual bool OnConsoleMessage(CefRefPtr<CefBrowser> browser,
			const CefString& message,
			const CefString& source,
			int line) = 0;
	};

	//CefLoadHandler�ص���
	class ILoadHandleSlot {
	public:
		//���س���
		virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefLoadHandler::ErrorCode errorCode,
			const CefString& errorText,
			const CefString& failedUrl) = 0;

		//����״̬�ı�
		virtual void OnLoadingStateChange(CefRefPtr<CefBrowser> browser,
			bool isLoading,
			bool canGoBack,
			bool canGoForward) = 0;

		//���ؿ�ʼ
		virtual void OnLoadStart(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame) = 0;

		//�������
		virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			int httpStatusCode) = 0;
	};

	//CefLifeSpanHandler�ص���
	class ILifeSpanHandleSlot {
	public:
		virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) = 0;
		virtual bool DoClose(CefRefPtr<CefBrowser> browser) = 0;
		//virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) = 0;

	};

	class CEF_API CefBrowserDll : public IOnAfterCreateSolt {
	public:
		CefBrowserDll();
		~CefBrowserDll(void);

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
		//cef��ں���
		bool CreateCefWindow(HWND hWnd, CefString url, 
			std::unique_ptr<ILifeSpanHandleSlot> life_handle = NULL, 
			std::unique_ptr<ILoadHandleSlot> load_handle = NULL,
			std::unique_ptr<IDisplayHandleSolt> display_handle = NULL);
		//�ر�һ�����������
		void CloseCefWindow();
		//���ע�ắ��
		void SetFunction(const CefString &name, CustomFunction function);
		//����������ص��ӿ�
		virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser);
		//�����Ƿ���Ҫ����
		void SetNeedFocus(bool dynamic);
	
	//��̬��ʼ�����ܽӿ�
	public:
		//��ʼ��cef
		static bool InitCef(HINSTANCE hInstance, CefString cache_path = "", CefString log_file = "");
		//�˳�Cef
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
		//�����id
		int browser_id_;
		//RenderAppʵ��
		static CefRefPtr<CRenderAndBrowserApp> render_app_;
		//��������
		HWND browser_hwnd_;
		//�Ƿ���Ҫ����
		bool need_focus_;
	};
}


