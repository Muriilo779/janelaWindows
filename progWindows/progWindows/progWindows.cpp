#define WIN32_LEAN_AND_MEAN
#include <windows.h>

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
		MessageBox(NULL, "Erro na cria��o da janela!", "Aplica��o", MB_ICONERROR);
		return 0;
	}

	//criando uma janela baseada na classe "BasicWindow"
	hwnd = CreateWindow ("BasicWindow",			//classe da janela
						"Aplica��o",			//t�tulo da janela
						WS_OVERLAPPEDWINDOW,	//estilo da janela
						CW_USEDEFAULT,			//posi��o x inicial
						CW_USEDEFAULT,			//posi��o y inicial
						CW_USEDEFAULT,			//largura inicial
						CW_USEDEFAULT,			//altura inicial
						NULL,					//identificador da janela pai
						NULL,					//identificador do menu
						hInstance,				//identificador da aplica��o
						NULL);					//par�metros de cria��o
						
	//Mostra janela
	ShowWindow(hwnd, nCmdShow);

	//Envia uma mensagem WM_PAINT para a janela
	UpdateWindow(hwnd);

	//Tratamento de mensagens destinadas a janela da aplica��o
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
	PAINTSTRUCT ps;		//guarda regi�o invalidada da janela
	RECT rect;			//regi�o ret�ngular

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