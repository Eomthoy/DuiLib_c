#pragma once
#include "include/cef_client.h"
#include "include/base/cef_lock.h"
#include "V8ExtensionHandler.h"

namespace DuiLib {
	class ILoadHandleSlot;
	class ILifeSpanHandleSlot;
	class IDisplayHandleSolt;

	class IOnAfterCreateSolt : public CefBase {
	public:
		virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) = 0;
	private:
		IMPLEMENT_REFCOUNTING(IOnAfterCreateSolt);
	};

	class CBrowserClient : 
		public CefClient,
		public CefContextMenuHandler,
		public CefRequestHandler,
		public CefDisplayHandler,
		public CefLifeSpanHandler,
		public CefLoadHandler {
	public:

		CBrowserClient(std::unique_ptr<ILifeSpanHandleSlot> life_handle = NULL,
			std::unique_ptr<ILoadHandleSlot> load_handle = NULL,
			std::unique_ptr<IDisplayHandleSolt> display_handle = NULL);

		~CBrowserClient(void);

		virtual CefRefPtr<CefRequestHandler> GetRequestHandler() OVERRIDE;
		virtual CefRefPtr<CefContextMenuHandler> GetContextMenuHandler();
		virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE;
		virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE;
		virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE;

		//�����µĵ�������ĵ���
		virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			const CefString& target_url,
			const CefString& target_frame_name,
			CefLifeSpanHandler::WindowOpenDisposition target_disposition,
			bool user_gesture,
			const CefPopupFeatures& popupFeatures,
			CefWindowInfo& windowInfo,
			CefRefPtr<CefClient>& client,
			CefBrowserSettings& settings,
			bool* no_javascript_access);



		virtual void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefRefPtr<CefContextMenuParams> params,
			CefRefPtr<CefMenuModel> model);

		// CefLifeSpanHandler methods:
		virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
		virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
		virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

		// CefLoadHandler methods:
		//���س���
		virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			ErrorCode errorCode,
			const CefString& errorText,
			const CefString& failedUrl);

		//����״̬�ı�
		virtual void OnLoadingStateChange(CefRefPtr<CefBrowser> browser,
			bool isLoading,
			bool canGoBack,
			bool canGoForward);

		//���ؿ�ʼ
		virtual void OnLoadStart(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame);

		//�������
		virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			int httpStatusCode);

		// CefDisplayHandler methods:
		//��ַ�ı�
		virtual void OnAddressChange(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			const CefString& url);
		//����ı�
		virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
			const CefString& title);
		//ҳ��ͼ��ı�
		virtual void OnFaviconURLChange(CefRefPtr<CefBrowser> browser,
			const std::vector<CefString>& icon_urls);
		//ҳ��ȫ��ʱ����
		virtual void OnFullscreenModeChange(CefRefPtr<CefBrowser> browser,
			bool fullscreen);
		//�������ʾ������ʾ
		virtual bool OnTooltip(CefRefPtr<CefBrowser> browser,
			CefString& text);
		//���յ�״̬��Ϣʱ
		virtual void OnStatusMessage(CefRefPtr<CefBrowser> browser,
			const CefString& value);
		//������ʾ����̨��Ϣ
		virtual bool OnConsoleMessage(CefRefPtr<CefBrowser> browser,
			const CefString& message,
			const CefString& source,
			int line);

		virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
			CefProcessId source_process,
			CefRefPtr<CefProcessMessage> message);

	public:
		//���ע�ắ��
		void SetFunction(const CefString &name, CustomFunction function);
		//���ô���������ص��ӿ�ʵ��
		void SetIOnAfterCreateSolt(IOnAfterCreateSolt* browser_crate_solt);

		//browser�Ƿ�ر�
		bool IsClosing() const;
		//�Ƿ񴴽����
		bool IsCreated() const;

	public:
		//�洢���������
		CefRefPtr<CefBrowser> browser_;
		//��
		base::Lock lock_;
		//V8��չ��
		CefRefPtr<CV8ExtensionHandler> extension_;
	private:
		//CefLoadHandler�ص�ʵ��ָ��
		std::unique_ptr<ILoadHandleSlot> load_handle_;
		//CefLifeSpanHandler�ص�ʵ��ָ��
		std::unique_ptr<ILifeSpanHandleSlot> life_handle_;
		//CefDisplayHandler�ص�ʵ��ָ��
		std::unique_ptr<IDisplayHandleSolt> display_handle_;
		//����������ص��ӿ�
		IOnAfterCreateSolt* browser_create_solt_;

		//�Ƿ�رձ�ʶ
		bool is_closing_; 
		//�Ƿ񴴽����
		bool is_created_;
		//����������Զ����ü���
		IMPLEMENT_REFCOUNTING(CBrowserClient);
	};
}

