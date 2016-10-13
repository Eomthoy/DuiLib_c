#include "CefBrowserDll.h"
#include "RenderAndBrowserApp.h"
#include "BrowserClient.h"
#include "include/cef_runnable.h"
#include <Shlwapi.h>
#include <ShlObj.h>

namespace DuiLib {

	CefRefPtr<CRenderAndBrowserApp> CefBrowserDll::render_app_ = NULL;

	CefBrowserDll::CefBrowserDll() : client_browser_(NULL), browser_id_(-1), need_focus_(false) {

	}

	CefBrowserDll::~CefBrowserDll(void) {
		//�Ƴ�ContextCreated�ص��ӿ�
		render_app_->RemoveIOnContextCreatedSolt(browser_id_);
		//������������
		SendMessage(browser_hwnd_, WM_DESTROY, 0, 0);
		SendMessage(browser_hwnd_, WM_CLOSE, 0, 0);
	}

	//�Ƿ������ǰ����
	bool CefBrowserDll::CanGoForward() {
		if (client_browser_->browser_) {
			return client_browser_->browser_->CanGoForward();

		}
		return false;
	}
	//��ǰ����
	void CefBrowserDll::GoForward() {
		if (client_browser_->browser_) {
			client_browser_->browser_->GoForward();

		}
	}
	//���¼���
	void CefBrowserDll::Reload() {
		if (client_browser_->browser_) {
			client_browser_->browser_->Reload();

		}
	}
	//���Ի������
	void CefBrowserDll::ReloadIgnoreCache() {
		if (client_browser_->browser_) {
			client_browser_->browser_->ReloadIgnoreCache();

		}	
	}
	//ֹͣ����
	void CefBrowserDll::StopLoad() {
		if (client_browser_->browser_) {
			client_browser_->browser_->StopLoad();

		}
	}
	//������󵼺�
	bool CefBrowserDll::CanGoBack() {
		if (client_browser_->browser_) {
			return client_browser_->browser_->CanGoBack();

		}
		return false;
	}
	//��󵼺�
	void CefBrowserDll::GoBack() {
		if (client_browser_->browser_) {
			client_browser_->browser_->GoBack();

		}
	}

	CefWindowHandle CefBrowserDll::GetHwnd() {
		if (client_browser_ == NULL) {
			return NULL;

		}
		if (client_browser_->browser_){
			return client_browser_->browser_->GetHost()->GetWindowHandle();

		}
		return NULL;
	}
	//CefBrowserDllHost
	//���ý���
	void CefBrowserDll::SetFocus(bool enable) {
		if (client_browser_->browser_) {
			client_browser_->browser_->GetHost()->SetFocus(enable);

		}
	}
	//��ȡ���ű���
	double CefBrowserDll::GetZoomLevel() {
		if (client_browser_->browser_) {
			return client_browser_->browser_->GetHost()->GetZoomLevel();

		}
		return -1;
	}
	//�������ű���
	void CefBrowserDll::SetZoomLevel(double zoomLevel) {
		if (client_browser_->browser_) {
			client_browser_->browser_->GetHost()->SetZoomLevel(zoomLevel);

		}
	}

	//CefFrame
	//����url
	void CefBrowserDll::LoadURL(const CefString& url) {
		if (client_browser_->browser_) {
			client_browser_->browser_->GetMainFrame()->LoadURL(url);

		}
	}
	//��ȡ��ǰUrl
	CefString CefBrowserDll::GetURL() {
		if (client_browser_->browser_) {
			return client_browser_->browser_->GetMainFrame()->GetURL();

		}
		return "";
	}

	bool CefBrowserDll::InitCef(HINSTANCE hInstance, CefString cache_path, CefString log_file) {
		//��DPI֧��
		CefEnableHighDPISupport();

		void* sandbox_info = NULL;
		CefMainArgs main_args(hInstance);  

		CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
		command_line->InitFromString(::GetCommandLineW());

		if (!PathIsDirectory(cache_path.ToWString().c_str())) {
			SHCreateDirectory(NULL, cache_path.ToWString().c_str());

		}
		if (!PathIsDirectory(log_file.ToWString().c_str())) {
			SHCreateDirectory(NULL, log_file.ToWString().c_str());

		}

		render_app_ = new CRenderAndBrowserApp();

		//��������
		int exit_code = CefExecuteProcess(main_args, render_app_, sandbox_info);
		if (exit_code >= 0) {
			return false;

		}

		CefSettings settings; 
		CefSettingsTraits::init(&settings); 

		settings.no_sandbox = true;
		settings.single_process = true;
		settings.multi_threaded_message_loop = true;
		settings.log_severity = LOGSEVERITY_DISABLE;
		CefString(&settings.locale).FromWString(L"zh-CN");
		//��������·��
		CefString(&settings.cache_path).FromWString(cache_path);
		//debug��־·��
		CefString(&settings.log_file).FromWString(log_file);
		//��ʼ��cef
		CefInitialize(main_args, settings, render_app_, sandbox_info);  	
		return true;
	}

	bool CefBrowserDll::CreateCefWindow(HWND hWnd, CefString url, 
		std::unique_ptr<ILifeSpanHandleSlot> life_handle, 
		std::unique_ptr<ILoadHandleSlot> load_handle,
		std::unique_ptr<IDisplayHandleSolt> display_handle) {
			CefWindowInfo info;  
			//�����Ӵ���
			RECT rect = { 0, 0, 1, 1 };

			info.SetAsChild(hWnd, rect);
			//info.SetAsPopup(NULL,"test");
			client_browser_ = new CBrowserClient(std::move(life_handle), std::move(load_handle), std::move(display_handle));

			//���ûص��ӿ�
			client_browser_->SetIOnAfterCreateSolt(this);

			CefBrowserSettings b_settings;   

			CefBrowserHost::CreateBrowser(info, client_browser_, url, b_settings, NULL);
			return true;
	}

	void CefBrowserDll::CloseCefWindow() {
		if (client_browser_->browser_) {
			client_browser_->browser_->GetHost()->CloseBrowser(true);
			render_app_->RemoveIOnContextCreatedSolt(browser_id_);

		}
		client_browser_->browser_ = NULL;
	}

	void CefBrowserDll::SetFunction(const CefString &name, CustomFunction function) {
		client_browser_->SetFunction(name, function);

	}

	void CefBrowserDll::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
		browser_id_ = browser->GetIdentifier();
		render_app_->SetIOnContextCreatedSolt(browser->GetIdentifier(), client_browser_->extension_);
		browser_hwnd_ = GetHwnd();
		if (need_focus_) {
			::SetFocus(browser_hwnd_);
			::SetForegroundWindow(browser_hwnd_);
		}	
	}

	void CefBrowserDll::SetNeedFocus(bool needfocus) {
		need_focus_ = needfocus;
	}

	void CefBrowserDll::Quit() {
		CefShutdown();

	}

	void CefBrowserDll::ExectueJS(const CefString &jscode) {
		if (client_browser_->browser_) {
			client_browser_->browser_->GetMainFrame()->ExecuteJavaScript(jscode,
				client_browser_->browser_->GetMainFrame()->GetURL(), 0);

		}
	}

	bool CefBrowserDll::IsCreated() const {
		return client_browser_->IsCreated();

	}

	void CefBrowserDll::Run() {
		CefRunMessageLoop();

	}
}