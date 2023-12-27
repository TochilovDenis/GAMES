#include <windows.h>

bool running = true;

struct RenderState {
	void* memory;
	int width, height;

	BITMAPINFO bitmapinfo;
};

RenderState renderState;
static LRESULT CALLBACK windowClick(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;

	switch (uMsg) {
		case WM_CLOSE:
		case WM_DESTROY: {
			running = false;
		} break;
		case WM_SIZE: {
			RECT rect;
			GetClientRect(hWnd, &rect);
			renderState.width = rect.right - rect.left;
			renderState.height = rect.bottom - rect.top;

			int bufferSize = renderState.width * renderState.height * sizeof(unsigned int);

			if (renderState.memory)
				VirtualFree(renderState.memory, 0, MEM_RELEASE);
			renderState.memory = VirtualAlloc(0, bufferSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

			renderState.bitmapinfo.bmiHeader.biSize = sizeof(renderState.bitmapinfo.bmiHeader);
			renderState.bitmapinfo.bmiHeader.biWidth = renderState.width;
			renderState.bitmapinfo.bmiHeader.biHeight = renderState.height;
			renderState.bitmapinfo.bmiHeader.biPlanes = 1;
			renderState.bitmapinfo.bmiHeader.biBitCount = 32;
			renderState.bitmapinfo.bmiHeader.biCompression = BI_RGB;

		} break;
		default: {
			result = DefWindowProc(hWnd, uMsg, wParam, lParam);
		} break;
	}
	return result;
};

// ����� ����� � ���������
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	// ������� Windows Class (����):
	WNDCLASS WindowClass = {};
	WindowClass.style = CS_HREDRAW | CS_VREDRAW ; // ������ ����� ����� ���������������� ����
	WindowClass.lpszClassName = TEXT("Game Window Class"); // �������� ������ ����
	WindowClass.lpfnWndProc = windowClick; // �� ����������� � ������ ������� ���������� ������ �� ����

	// ���������������� ���� �����
	RegisterClass(&WindowClass); // ���������������� ����� � ����� ����������

	// ������� ����
	HWND window = CreateWindow(WindowClass.lpszClassName, TEXT("Game Ping-Pong"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);

	while (running)
	{
		//����
		MSG message;
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		//��������� - ������� ����


		// �����������. ������� StretchDIBits ������������ ��� ����������� ������ �����
		// ��� �������������� �������� � ����������� DIB, JPEG ��� PNG � ���������
		// ������������� ����������.
		StretchDIBits(hdc, 0, 0, renderState.width, renderState.height, 0, 0, renderState.width, renderState.height, renderState.memory, &renderState.bitmapinfo, DIB_RGB_COLORS, SRCCOPY);
	}
};