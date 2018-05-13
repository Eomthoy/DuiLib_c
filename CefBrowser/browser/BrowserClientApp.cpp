#include "BrowserClientApp.h"
namespace DuiLib {
	CefRefPtr<CefBrowserProcessHandler> ClientAppBrowser::GetBrowserProcessHandler() {
		return this;
	}

	void ClientAppBrowser::OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line) {
		//������
		if (process_type.empty()) {
			//����������Ⱦ
			command_line->AppendSwitch("off-screen-rendering-enabled");
			command_line->AppendSwitch("disable-extensions");
			command_line->AppendSwitch("disable-pdf-extension");
			command_line->AppendSwitch("disable-surfaces");
			//����GPU����
			command_line->AppendSwitch("enable-gpu");
			command_line->AppendSwitch("disable-gpu");
			command_line->AppendSwitch("disable-gpu-compositing");
			//���ô������
			command_line->AppendSwitch("no-proxy-server");
			
			//�������е�ҳ�湲��һ�����̣��Խ�ʡ������
			command_line->AppendSwitchWithValue("--renderer-process-limit", "1");
		}
	}
}