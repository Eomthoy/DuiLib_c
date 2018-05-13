#pragma once
#include "include/cef_v8.h"
#include <vector>
namespace DuiLib
{
	class IOnContextCreatedSolt : public CefBase {
	public:
		//V8���������ص�
		virtual void OnContextCreated(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefRefPtr<CefV8Context> context) = 0;
		//���������ܵ�
		virtual void ConnectionNamePipe(const CefString& pipe_name) = 0;
		//���ú�����
		virtual void SetFunction(const CefString& name) = 0;
	private:
		IMPLEMENT_REFCOUNTING(IOnContextCreatedSolt);
	};

	class CV8ExtensionHandler : public CefV8Handler,
								public IOnContextCreatedSolt
	{
	public:
		CV8ExtensionHandler();
		~CV8ExtensionHandler();

		//js�ص�����
		virtual bool Execute(const CefString& name,
			CefRefPtr<CefV8Value> object,
			const CefV8ValueList& arguments,
			CefRefPtr<CefV8Value>& retval,
			CefString& exception) OVERRIDE;

	public:
		void OnContextCreated(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			CefRefPtr<CefV8Context> context);
		//���ú���
		void SetFunction(const CefString& name);
		//���������ܵ�
		void ConnectionNamePipe(const CefString& pipe_name);

	private:
		HANDLE					handle_name_pipe_;	//�����ܵ����
		CefRefPtr<CefBrowser>   browser_;			//���������
		std::vector<CefString>	function_name_;		//���������б�
		IMPLEMENT_REFCOUNTING(CV8ExtensionHandler);
	};
}

