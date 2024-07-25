#include <windows.h>
#include <gl/gl.h>
#include <math.h>

#include "renderer.h"
#include "simple.h"
#include "camera.h"

#include "planet.h"

#define window_width LOWORD(lParam)
#define window_height HIWORD(lParam)

#define PLANET_NUM 9


LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

float timer=0.0;

float distance(float x1,float y1,float x2,float y2) {x2-=x1;y2-=y1;return(sqrt(x2*x2+y2*y2));}





int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow) {
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;

    if(!RegisterClassEx(&wcex)) return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,"GLSample","OpenGL Sample",
                          WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,
                          800,600,NULL,NULL,hInstance,NULL);

    ShowWindow(hwnd,nCmdShow);
    EnableOpenGL(hwnd, &hDC, &hRC); //enable OpenGL for the window

    init_cam();

    while(!bQuit) { //program main loop
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            /* handle or dispatch messages */
            if(msg.message==WM_QUIT) {
                bQuit = TRUE;
            }
            else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else { //OpenGL animation code goes here
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glLoadIdentity();

            //DRAW
            glFrustum(-1,1, -1,1, 1,256); //Perspective
				move_camera();
				draw_world();
            SwapBuffers(hDC);


            //UPDATE
				timer+=1.0;

				for(int pp=mercury,n=PLANET_NUM*8;pp<n;pp+=8) {
					float angle=(float)pp+timer/planet[pp+OFFS_PERIOD];
					planet[pp+OFFS_X]=planet[sun+OFFS_X]+sinf(angle)*planet[pp+OFFS_DISTANCE];
					planet[pp+OFFS_Y]=planet[sun+OFFS_Y]+cosf(angle)*planet[pp+OFFS_DISTANCE];
				}

            Sleep(1);
        }
    }

    DisableOpenGL(hwnd, hDC, hRC);	// shutdown OpenGL
    DestroyWindow(hwnd);			// destroy the window explicitly

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CLOSE: PostQuitMessage(0); break;

        case WM_DESTROY: return 0;

        case WM_KEYDOWN: {
            switch (wParam) {case VK_ESCAPE: PostQuitMessage(0); break;}
        }
        break;

		case WM_SIZE:
			glViewport(0,0, window_width,window_height);
		break;

        default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}


void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC) {
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}
void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC) {wglMakeCurrent(NULL, NULL);wglDeleteContext(hRC);ReleaseDC(hwnd, hDC);}



void point_of_well(float x,float y) {
	float dd,zz;

	for(int pp=sun,n=PLANET_NUM*8;pp<n;pp+=8) {
		dd=1.0-distance(x,y,planet[pp+OFFS_X],planet[pp+OFFS_Y])/planet[pp+OFFS_MASS];
		zz+=(dd<0.0 ? 0.0 : dd*dd*-dd*planet[pp+OFFS_MASS]);
	}

	glVertex3f(x,y,zz);
}


void planet_of_well(int thispp) {
	float dd,zz;

	for(int pp=sun,n=PLANET_NUM*8;pp<n;pp+=8) {
		dd=1.0-distance(planet[pp+OFFS_X],planet[pp+OFFS_Y],planet[thispp+OFFS_X],planet[thispp+OFFS_Y])/planet[pp+OFFS_MASS];
		zz+=(dd<0.0 ? 0.0 : dd*dd*-dd*planet[pp+OFFS_MASS]);
	}

	glPushMatrix();
		glBegin(GL_TRIANGLE_FAN);
		glRotatef(122.0,0,0,1);
			glColor3f(1,1,1);
			glVertex3f(planet[thispp+OFFS_X],planet[thispp+OFFS_Y],zz+8);
				for(float i=0,j=M_PI/8,n=M_PI*2+0.01;i<n;i+=j) {
					glVertex3f(planet[thispp+OFFS_X]+sinf(i)*planet[thispp+OFFS_RADIUS],planet[thispp+OFFS_Y],zz+8+cosf(i)*planet[thispp+OFFS_RADIUS]);
				}
		glEnd();
	glPopMatrix();
}


void draw_world() {
	glBegin(GL_LINES);
		glColor3f(0,0,1);
		for(float xx=0.0f;xx<160.0f;xx+=1.0f) {
		for(float yy=0.0f;yy<160.0f;yy+=1.0f) {
			point_of_well(xx,yy);point_of_well(xx+1.0f,yy);
			point_of_well(xx,yy);point_of_well(xx,yy+1.0f);
		}}
	glEnd();

	for(int pp=sun,n=PLANET_NUM*8;pp<n;pp+=8) {planet_of_well(pp);}
}

