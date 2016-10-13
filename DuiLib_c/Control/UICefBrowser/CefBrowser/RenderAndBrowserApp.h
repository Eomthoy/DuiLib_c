#pragma once
#include "include/cef_app.h"
namespace DuiLib {
	class IOnContextCreatedSolt : public CefBase {
	public:
		virtual void OnContextCreated(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefRefPtr<CefV8Context> context) = 0;

	private:
		IMPLEMENT_REFCOUNTING(IOnContextCreatedSolt);
	};

	class CRenderAndBrowserApp : 
		public CefApp,
		public CefRenderProcessHandler,
		public CefBrowserProcessHandler {
	public:
		CRenderAndBrowserApp();

		~CRenderAndBrowserApp(void);

		//Render
		virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE;

		virtual void OnContextCreated(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefRefPtr<CefV8Context> context);

		virtual void OnWebKitInitialized() OVERRIDE;

		virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
			CefProcessId source_process,
			CefRefPtr<CefProcessMessage> message);

		//Browser
		virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler();

		virtual void OnContextInitialized();

		virtual void OnBeforeChildProcessLaunch(
			CefRefPtr<CefCommandLine> command_line);

		virtual void OnRenderProcessThreadCreated(
			CefRefPtr<CefListValue> extra_info);

	public:
		//��ӻص��ӿ�ָ��ʵ��
		void SetIOnContextCreatedSolt(int browser_id, CefRefPtr<IOnContextCreatedSolt> context_solt);
		//ɾ���ص��ӿ�ָ��ʵ��
		void RemoveIOnContextCreatedSolt(int browser_id);

	private:
		//�ص��ӿ�ʵ��ָ��
		std::map<int, CefRefPtr<IOnContextCreatedSolt>> context_solt_map_;
		IMPLEMENT_REFCOUNTING(CRenderAndBrowserApp);
	};
}


