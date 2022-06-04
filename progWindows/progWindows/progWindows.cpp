#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>

LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	
	HWND		hwnd; // identificador da janela
	MSG			msg;  // mensagem
	WNDCLASS	wndclass; // classe da janela

	// definindo uma classe de janela chamada "BasicWindow"
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WinProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = "BasicWindow";

	//registrar a classe "BasicWIndow"
	if (!RegisterClass(&wndclass)) {
		MessageBox(NULL, "Erro na criação da janela!", "Aplicação", MB_ICONERROR);
		return 0;
	}
	int windowWidth = 960;
	int windowHeight = 540;

	//Conta utilizada para centralizar a janela
	int windowPosX = GetSystemMetrics(SM_CXSCREEN) / 2 - windowWidth / 2;
	int windowPosY = GetSystemMetrics(SM_CYSCREEN) / 2 - windowHeight / 2;
	
	//criando uma janela baseada na classe "BasicWindow"
	hwnd = CreateWindowEx (NULL,							//estilos extras
						"BasicWindow",						//classe da janela
						"Aplicação",						//título da janela
						WS_OVERLAPPED | WS_SYSMENU,			//estilo da janela
						windowPosX,							//posição x inicial
						windowPosY,							//posição y inicial
						windowWidth,						//largura inicial
						windowHeight,						//altura inicial
						NULL,								//identificador da janela pai
						NULL,								//identificador do menu
						hInstance,							//identificador da aplicação
						NULL);								//parâmetros de criação
						
	// o retangulo com o tamanho da área cliente desejada
	RECT  winRect = { 0, 0, windowWidth, windowHeight };

	//ajuste o tamanho da janela
	AdjustWindowRectEx(&winRect, GetWindowStyle(hwnd), GetMenu(hwnd) != NULL, GetWindowExStyle(hwnd));

	//usado para centralizar janela na tela
	windowPosX = (GetSystemMetrics(SM_CXSCREEN) / 2) - ((winRect.right - winRect.left) / 2);
	windowPosY = (GetSystemMetrics(SM_CYSCREEN) / 2) - ((winRect.bottom - winRect.top) / 2);

	//redimensiona janela com uma chamada a movewindow
	MoveWindow(
		hwnd,							//indentificador da janela
		windowPosX,						//posição x
		windowPosY,						//posição y
		winRect.right - winRect.left,	//largura
		winRect.bottom - winRect.top,	//altura
		TRUE							//repintar
		);
	//Mostra janela
	ShowWindow(hwnd, nCmdShow);

	//Envia uma mensagem WM_PAINT para a janela
	UpdateWindow(hwnd);

	//Tratamento de mensagens destinadas a janela da aplicação
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//fim do programa
	return int(msg.wParam);
}

//procedimento da janela 
LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;			//representa o dispostivo grafico
	PAINTSTRUCT ps;		//guarda região invalidada da janela
	RECT rect;			//região retângular

	switch (message){
		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);

			GetClientRect(hwnd, &rect);
			DrawText(hdc, "Oi janela!", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			EndPaint(hwnd, &ps);
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}

	return DefWindowProc(hwnd, message, wParam, lParam);
}