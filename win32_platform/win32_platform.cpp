/*
wnd - window (окно)
proc - process (процесс)
h - handler ()

UNIT - unsigned integer
param - parameter
l - long
rect -  rectacgle >> определяет прямоугольник по координатам верхнего левого и нижнего правого углов.
alloc - allocate - размечтать память

когда рисуем 
h - horizonatl
v- vertical

defult - по умолчанию
use - использовать
destory - разрушить
close - закрыть

src - sourse - источник
dst - destantion - куда


	  top
left	    right
	 bottom
*/
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

// точка входа в программу
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	// Создаем Windows Class (окна):
	WNDCLASS WindowClass = {};
	WindowClass.style = CS_HREDRAW | CS_VREDRAW ; // задаем когда будет перерысовываться окно
	WindowClass.lpszClassName = TEXT("Game Window Class"); // газвание класса окно
	WindowClass.lpfnWndProc = windowClick; // мы привязываем к классу функцию обработчик кликов по окну

	// Зарегистрировать этот класс
	RegisterClass(&WindowClass); // зарегистрировали класс в нашем приложении

	// Создать окно
	HWND window = CreateWindow(WindowClass.lpszClassName, TEXT("Game Ping-Pong"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);

	while (running)
	{
		//ввод
		MSG message;
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		//симуляция - процесс игры
		
		unsigned int* pixel = (unsigned int*)renderState.memory;
		for (int y = 0; y < renderState.height; y++)
		{
			for (int x = 0; x < renderState.width; x++) {
				*pixel++ = 0xff5500;
			}
		}
		// Задание рисовать РФ флаг 
		/*for (size_t y = 0; y < renderState.height; y++)
		{
			for (size_t x = 0; x < renderState.width; x++)
			{
				if (y * 3 < renderState.height)
					*pixel++ = 0xe4181c;
				else if (y * 3 < 2 * renderState.height)
					*pixel++ = 0x1c3578;
				else
					*pixel++ = 0xffffff;
			}
		}*/

		// Перерисовка. Функция StretchDIBits используется для копирования данных цвета
		//  для прямоугольника пикселей в изображении DIB, JPEG или PNG в указанный
		// прямоугольник назначения.
		StretchDIBits(hdc, 0, 0, renderState.width, renderState.height, 0, 0, renderState.width, renderState.height, renderState.memory, &renderState.bitmapinfo, DIB_RGB_COLORS, SRCCOPY);
	}
};

/*
Этот код представляет собой простую программу на языке C++, 
которая создает окно в Windows с помощью WinAPI.

Вот основные шаги, которые выполняются в этом коде:

1.	Регистрация класса окна: Класс окна определяет поведение окна. В этом случае, 
	класс окна регистрируется с помощью функции RegisterClass, которая принимает 
	структуру WNDCLASS. Эта структура содержит информацию о стилях окна, имени класса,
	процедуре обработки сообщений и других параметрах.
2.  Создание окна: После того, как класс окна зарегистрирован, можно создать окно 
	с помощью функции CreateWindow. Эта функция принимает параметры, такие как имя 
	класса окна, текст окна, стили окна, начальное положение и размер окна, 
	дескриптор родительского окна и другие параметры.
3.  Обработка сообщений: Окно будет получать сообщения от операционной системы и 
	пользовательских действий, таких как клики мыши или нажатия клавиш. Эти сообщения 
	обрабатываются в функции windowClick, которая вызывается каждый раз, когда окно 
	получает сообщение. В этой функции используется оператор switch для обработки
	различных типов сообщений, таких как WM_CLOSE и WM_SIZE.
4.  Цикл обработки сообщений: В главном цикле программы (while (running)) происходит
	чтение и обработка сообщений с помощью функций PeekMessage, TranslateMessage и 
	DispatchMessage. Это обеспечивает взаимодействие между окном и пользователем.
5. Отрисовка: В этом примере кода отсутствует часть отрисовки, но обычно она бы 
	включала в себя вызов функций рисования, таких как StretchDIBits, который 
	используется в данном коде для отрисовки содержимого буфера в окне.

	Этот код является базовым примером создания окна с использованием WinAPI в C++. 
	Он может быть расширен для создания более сложных окон и приложений.
*/