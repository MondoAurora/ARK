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

#include <MiND/DustMindUtils.h>

using namespace DustUnitMindGeneric;
using namespace DustUnitMindGeometry;
using namespace std;

float theta = 0.0f;

void setColor(DustEntity col)
{
    if ( col )
    {
        glColor3f(
            DustData::getReal(col, DustRefColorComp,  0.0f, DustTagColorRed),
            DustData::getReal(col, DustRefColorComp,  0.0f, DustTagColorGreen),
            DustData::getReal(col, DustRefColorComp,  0.0f, DustTagColorBlue)
        );
    }
}

void drawPoint(DustEntity e)
{
    DustEntity col = DustData::getRef(e, DustRefColoredColor);
    setColor(col);

    glVertex2f(
        DustData::getReal(e, DustRefGeoInfoData, 0.0f, DustTagCartesianX),
        DustData::getReal(e, DustRefGeoInfoData, 0.0f, DustTagCartesianY)
    );
}

void enterInclusion(DustEntity incl)
{
    glPushMatrix();

    int ic = DustData::getMemberCount(incl, DustRefCollectionMembers);
    for ( int ii = 0; ii < ic; ++ii)
    {
        DustEntity eAction = DustData::getRef(incl, DustRefCollectionMembers, DUST_ENTITY_INVALID, ii);

        DustEntity eCmd = DustUtils::getSingleTag(eAction, DustTagGeoRole, DUST_ENTITY_INVALID);

        if ( eCmd ) {
            double x = DustData::getReal(eAction, DustRefGeoInfoData, 0.0f, DustTagCartesianX);
            double y = DustData::getReal(eAction, DustRefGeoInfoData, 0.0f, DustTagCartesianY);
            double z = DustData::getReal(eAction, DustRefGeoInfoData, 0.0f, DustTagCartesianZ);

           if ( DustTagGeoRolePlace == eCmd ) {
                glTranslated(x, y, z);
           } else if ( DustTagGeoRoleRotate == eCmd ) {
                glRotated(theta, x, y, z);
           } else if ( DustTagGeoRoleScale == eCmd ) {
                glScaled(x, y, z);
           }
        }
    }
}

void leaveInclusion(DustEntity incl)
{
    glPopMatrix();
}

void updateGraphics()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    DustRef r;
    DustEntity self = r;

    int ic = DustData::getMemberCount(self, DustRefCollectionMembers);

    for ( int ii = 0; ii < ic; ++ii)
    {
        DustEntity eInc = DustData::getRef(self, DustRefCollectionMembers, DUST_ENTITY_INVALID, ii);
        enterInclusion(eInc);

        DustEntity path = DustData::getRef(eInc, DustRefLinkTarget);

        glBegin(DustUtils::tag(path, DUST_ACCESS_GET, DustGenTagClosed) ? GL_LINE_LOOP : GL_LINE_STRIP);
        int len = DustData::getMemberCount(path, DustRefCollectionMembers);
        for ( int i = 0; i < len; ++i )
        {
            drawPoint(DustData::getRef(path, DustRefCollectionMembers, DUST_ENTITY_INVALID, i));
        }
        glEnd();

        leaveInclusion(eInc);
    }

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

        HDC hDC = (HDC) DustData::getInteger(self, DustIntHDC);

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
