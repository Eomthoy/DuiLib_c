#pragma once
#include "include/cef_client.h"
#include "include/cef_load_handler.h"
#include "include/cef_base.h"
#include "include/base/cef_lock.h"
#include <map>
#include <functional>
#include <share.h>
#include "include/cef_v8.h"

namespace DuiLib
{
	typedef std::function<CefRefPtr<CefValue> (CefRefPtr<CefListValue>)> CustomFunction;
	class ILoadHandleSlot;
	class ILifeSpanHandleSlot;
	class IDisplayHandleSolt;
	class ILifeSpanFileDialogSolt;

	class CBrowserClient : 
		public CefClient,
		public CefContextMenuHandler,
		public CefDragHandler,
		public CefRequestHandler,
		public CefDisplayHandler,
		public CefDialogHandler,
		public CefLifeSpanHandler,
		public CefKeyboardHandler,
		public CefLoadHandler {
	public:
		CBrowserClient();
		~CBrowserClient(void);

		virtual CefRefPtr<CefRequestHandler> GetRequestHandler() OVERRIDE;
		virtual CefRefPtr<CefContextMenuHandler> GetContextMenuHandler();
		virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE;
		virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE;
		virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE;
		virtual CefRefPtr<CefDragHandler> GetDragHandler() OVERRIDE;
		virtual CefRefPtr<CefDialogHandler> GetDialogHandler() OVERRIDE;
		virtual CefRefPtr<CefKeyboardHandler> GetKeyboardHandler() OVERRIDE;

		//���ΰ�����Ӧ
		virtual bool OnPreKeyEvent(CefRefPtr<CefBrowser> browser,
			const CefKeyEvent& event,
			CefEventHandle os_event,
			bool* is_keyboard_shortcut);

		//�Զ����ļ�ѡ��Ի���
		virtual bool OnFileDialog(CefRefPtr<CefBrowser> browser,
			FileDialogMode mode,
			const CefString& title,
			const CefString& default_file_path,
			const std::vector<CefString>& accept_filters,
			int selected_accept_filter,
			CefRefPtr<CefFileDialogCallback> callback);

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

		//�Ҽ������˵�
		virtual void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefRefPtr<CefContextMenuParams> params,
			CefRefPtr<CefMenuModel> model);

		//����ǰ�Ĺ���
		virtual bool OnBeforeBrowse(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefRefPtr<CefRequest> request,
			bool is_redirect); 

		//��ֹ������ק�ļ�
		virtual bool OnDragEnter(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefDragData> dragData,
			DragOperationsMask mask);

		//������Ϣ
		virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
			CefProcessId source_process,
			CefRefPtr<CefProcessMessage> message);

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

	public:
		//���ļ�ѡ��Ի���
		std::wstring OpenPictureFile();
		//cef��ں���
		void CreateCefWindow(HWND hWnd, const CefString& url, 
			ILifeSpanHandleSlot* life_handle = NULL, 
			ILoadHandleSlot* load_handle = NULL,
			IDisplayHandleSolt* display_handle = NULL,
			ILifeSpanFileDialogSolt* filedialog_handle = NULL);
		//��ȡ���������
		CefRefPtr<CefBrowser> GetBrowser();
		//�Ƿ񴴽����
		bool IsCreated() const;
		//��Ӻ���
		void SetFunction(const CefString &name, CustomFunction function);
		//�ر������
		void CloseBrowser();
		//loaded
		bool browser_loaded_;

	private:
		//�洢���������
		CefRefPtr<CefBrowser> browser_;
		//��
		base::Lock lock_;
		//�����ܵ����
		HANDLE	handle_name_pipe_;
		//CefLoadHandler�ص�ʵ��ָ��
		ILoadHandleSlot* load_handle_;
		//CefLifeSpanHandler�ص�ʵ��ָ��
		ILifeSpanHandleSlot* life_handle_;
		//CefDisplayHandler�ص�ʵ��ָ��
		IDisplayHandleSolt* display_handle_;
		//ILifeSpanFileDialogSolt�ص�ָ��ʵ��
		ILifeSpanFileDialogSolt* filedialog_handle_;
		//����map
		std::map<CefString, CustomFunction> function_map_;
		//�Ƿ񴴽����
		bool is_created_;
		//����������Զ����ü���
		IMPLEMENT_REFCOUNTING(CBrowserClient);
	};
}