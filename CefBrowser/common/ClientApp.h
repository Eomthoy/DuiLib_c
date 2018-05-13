#pragma once
#include "include/cef_app.h"
namespace DuiLib {
	enum ProcessType {
		BrowserProcess,
		RendererProcess,
		OtherProcess,
	};
	class ClientApp : public CefApp
	{
	public:
		ClientApp();
		~ClientApp();
		//��ȡ��������
		static ProcessType GetProcessType(CefRefPtr<CefCommandLine> command_line);

		DISALLOW_COPY_AND_ASSIGN(ClientApp);
	};
}


