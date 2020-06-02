#include <iostream>
#include <string>

#include <DustModule.h>

#include <vendors/dust/DustgenUnitTest01.h>

#ifdef _WIN32
#include <windows.h>
#else
// linux version
#endif


#include <gl/gl.h>

float theta = 0.0f;

GLAPI void APIENTRY glVertex2fX( GLfloat x, GLfloat y ){
    glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(x,y);
    glColor3f(1.0f, 0.0f, 0.0f);
}


void updateGraphics()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glRotatef(theta, 0.0f, 0.5f, 1.0f);

    glBegin(GL_LINE_LOOP);

    glColor3f(1.0f, 0.0f, 0.0f);

    glVertex2fX(0.0, 1.0);
    glVertex2f(0.5, 0.0);
    glVertex2fX(0.5, 0.2);
    glVertex2f(0.2, -0.2);
    glVertex2f(-0.2, -0.2);
    glVertex2fX(-0.5, 0.2);
    glVertex2f(-0.5, 0.0);

    glEnd();

    glPopMatrix();

    theta += 1.0f;
}


using namespace std;
using namespace DustUnitDustTest01;

class GLPainter : public DustNativeLogic
{
    HGLRC hRC;

public:
    GLPainter() : hRC(0) {}

    virtual DustResultType DustActionExecute()
    {
        DustRef self;

        HDC hDC = (HDC) DustData::getRef(self, DustIntHDC);

        if ( ! hDC )
        {
            wglMakeCurrent(NULL, NULL);
            wglDeleteContext(hRC);
        }
        else if ( !hRC )
        {
            hRC = wglCreateContext(hDC);
            wglMakeCurrent(hDC, hRC);
        }
        else
        {
            updateGraphics();
        }

        return DUST_RESULT_ACCEPT;
    }
};

DECLARE_FACTORY(GLPainter, DustAgentTestOpenGL)

class OpenGlModule : public DustModule
{
public:
    virtual ~OpenGlModule()
    {
    }

    virtual DustResultType DustResourceInit()
    {
        cout << "OpenGlModule::DustResourceInit" << endl;
        registerFactory(&FactGLPainter);
        return DUST_RESULT_ACCEPT;
    }
    virtual DustResultType DustResourceRelease()
    {
        cout << "OpenGlModule::DustResourceRelease" << endl;
        return DUST_RESULT_ACCEPT;
    }
};

OpenGlModule module;

extern "C" DustModule* getModule()
{
    return &module;
}
