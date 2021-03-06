#pragma once

#include "resource.h"
#include <string>


class App
{
public:
    App() {};

    static int RunNewInstance(_In_ HINSTANCE hInstance,
        _In_opt_ HINSTANCE hPrevInstance,
        _In_ LPWSTR    lpCmdLine,
        _In_ int       nCmdShow,
        _In_opt_ const winrt::Windows::Web::UI::Interop::WebViewControlProcess * process = nullptr,
        _In_opt_ const winrt::Windows::Web::UI::Interop::WebViewControlProcessOptions * processOptions = nullptr)
	{
		App* app = new App();
        if (process)
		    app->m_process = *process;
        if (processOptions)
		    app->m_processOptions = *processOptions;
		int result = app->Run(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
		delete app;
		app = nullptr;
		return result;
	}

protected:
	static LRESULT CALLBACK WndProcStatic(_In_ HWND hWnd, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam);
	static INT_PTR CALLBACK About(_In_ HWND hDlg, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam);

	static const size_t s_maxLoadString = 100;
	static const DWORD s_initializeWindowMessage = WM_USER;

	int Run(_In_ HINSTANCE hInstance,
		_In_opt_ HINSTANCE hPrevInstance,
		_In_ LPWSTR    lpCmdLine,
		_In_ int       nCmdShow);
	void MyRegisterClasses(_In_ HINSTANCE hInstance);
	BOOL InitInstance(_In_ HINSTANCE hInstance, _In_ int nCmdShow);
	LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam, _Out_ bool* handled);
	void InitializeWin32WebView();
	void SetScale(_In_ double scale);
	void ResizeWebView();
	void SaveScreenshot();
	void ToggleVisibility();
	void NavigateToUri(_In_ LPCWSTR uri);

    void NavigateWithHeader(const winrt::Windows::Foundation::Uri & uri);
    void AddNavigationStarting();
    std::wstring GetUserAgent();

    winrt::Windows::Web::UI::Interop::WebViewControlProcessOptions CreatePrivateNetworkProcessOptions();

	HINSTANCE m_hInst = nullptr;                                // current instance
	LPWSTR m_cmdline = nullptr;
	INT m_nShow = 0;
	WCHAR m_windowClass[s_maxLoadString];            // the main window class name
	WCHAR m_hostClass[s_maxLoadString] = L"Win32WebViewSampleAppHost"; // the host window class name
	HWND m_mainWindow = nullptr;
	HWND m_hostWindow = nullptr; // HWND of the window containing the webview.
	HWND m_backWindow = nullptr;
	HWND m_addressbarWindow = nullptr;
	HWND m_addressbarGoWindow = nullptr;
	static const DWORD s_addressbarHeight = 32;
	static const DWORD s_addressbarGoWidth = 64;
	static const DWORD s_backWidth = 64;

    winrt::Windows::Web::UI::Interop::WebViewControl m_webViewControl = nullptr;
    winrt::Windows::Web::UI::Interop::WebViewControlProcess m_process = nullptr;
    winrt::Windows::Web::UI::Interop::WebViewControlProcessOptions m_processOptions = nullptr;

    std::wstring m_new_uri;
    winrt::event_token m_nav_start_token;
    std::wstring m_user_agent;

};
