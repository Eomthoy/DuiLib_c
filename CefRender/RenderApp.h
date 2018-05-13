#pragma once
#include "V8ExtensionHandler.h"
#include "ClientApp.h"
#include <map>

namespace DuiLib
{
	class IOnContextCreatedSolt;

	class CRenderApp : 
		public ClientApp,
		public CefRenderProcessHandler
	{
	public:
		CRenderApp(const std::vector<CefString> &function_name);

		CRenderApp();

		~CRenderApp(void);

		virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE;

		virtual void OnContextCreated(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefRefPtr<CefV8Context> context);

		virtual void OnWebKitInitialized() OVERRIDE;

		//��Ϣ����
		virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
			CefProcessId source_process,
			CefRefPtr<CefProcessMessage> message);

	private:
		//���ûص�ָ��
		void CRenderApp::SetIOnContextCreatedSolt(int browser_id ,CefRefPtr<IOnContextCreatedSolt> context_solt);

	private:
		//V8��չʵ��ָ��
		std::map<int, CefRefPtr<IOnContextCreatedSolt>> browser_v8extension_map_;

		IMPLEMENT_REFCOUNTING(CRenderApp);
	};
}


