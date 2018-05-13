#pragma once
#include "CefBrowser/CefBrowserDll.h"
#include <share.h>
#include <functional>
#include "DuiLib/UIlib.h"

#define CEF_API __declspec(dllexport)
/***********************************************************
ʹ��˵����
	1.��DuiLib::Create����ǰ����InitCef��ʼ��cef
	2.��MessageLoop()֮��Quit
	3.�̳�ʵ��ISetHandleSolt�ص�,������ʵ��ָ��������Ļص�ʵ��
	4.�̳�ʵ��OnAfterCreate������ResizeBrowser�����
***********************************************************/
//������
const TCHAR CCefBrowserUIClassName[] = L"CefBrowserUI";		
//�ؼ�����
const TCHAR CCefBrowserUIItemInterface[] = L"CefBrowser";	

class ISetHandleSolt {
public:
	//������ص�ʵ��ָ�����ú���
	virtual DuiLib::ILoadHandleSlot* GetILoadHandleSlot(std::wstring browser_name) { return NULL; }
	virtual DuiLib::ILifeSpanHandleSlot* GetILifeSpanHandleSlot(std::wstring browser_name) { return NULL; }
	virtual DuiLib::IDisplayHandleSolt* GetIDisplayHandleSolt(std::wstring browser_name){ return NULL; }
	virtual DuiLib::ILifeSpanFileDialogSolt* GetILifeSpanFileDialogSolt(std::wstring browser_name){ return NULL; }
};

class CEF_API CCefBrowserUI : public DuiLib::CControlUI {
public:
	CCefBrowserUI(HWND parent, ISetHandleSolt* set_handle = NULL);
	~CCefBrowserUI(void);

//DuiLib�ص�����
public:
	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	void DoInit();
	//����λ��
	virtual void SetPos(RECT rc);
	//����������������ʾ���
	virtual void SetInternVisible(bool bVisible = true);
	//�����Ƿ���ʾ
	virtual void SetVisible(bool bVisible = true);

//��̬���ܽӿ�
public:
	//��ʼ��CEF
	static void InitCef(HINSTANCE hInstance, std::wstring cache_path = L"", std::wstring log_file = L"");
	//�˳�CEF
	static void Quit();
	//����cef��Ϣѭ��
	static void StartCefMessageLoop();

//�ؼ�cef����
public:
	//����url
	void LoadURL(std::wstring url);
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
	//��ȡ��ǰUrl
	CefString GetURL();
	//ִ��JS ����Ϊ һ��������js���� �����Ѿ����ڵ�js�������Ӳ���
	void ExectueJS(const CefString &jscode);
	//����Cef���������
	bool CreateCefWindow(CefString url,
		DuiLib::ILifeSpanHandleSlot* life_handle = NULL, 
		DuiLib::ILoadHandleSlot* load_handle = NULL,
		DuiLib::ILifeSpanFileDialogSolt* filedialog_handle = NULL,
		DuiLib::IDisplayHandleSolt* display_handle = NULL);
	//�ر������
	void CloseCefWindow();
	//���ע�ắ��
	void SetFunction(const CefString &name, DuiLib::CustomFunction function);

private:
	//Ĭ�ϵ�ַ
	std::wstring url_;
	//cef���ܽӿڶ���
	DuiLib::CefBrowserDll browser_dll_;
	//����load life �ص������ص�ָ��
	ISetHandleSolt* set_handle_;
	//��������
	HWND parent_hwnd_;
	//���������
	std::wstring browser_name_;
	//�Ƿ񴴽����
	bool is_created_;
};

