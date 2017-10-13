#include "LinuxCoreImpl.h"
#include <GL/glew.h>
#include <GL/freeglut.h>

namespace Common
{
    LinuxCoreImpl* LinuxCoreImpl::mInstance;

    LinuxCoreImpl::LinuxCoreImpl(const Math::Size2DI& screenSize)
        : mScreenSize(screenSize), mMouseButtonPressed(false)
    {
        mInstance = this;
    }

    void LinuxCoreImpl::run()
    {
        int argc = 0;
        char argv[1][1] = { { 0 } };

        glutInit(&argc, reinterpret_cast<char**>(argv));
        glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

        glutInitWindowSize(mScreenSize.width, mScreenSize.height);
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
        glutInitContextVersion (4, 0);
        glutInitContextFlags (GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
        glutCreateWindow("Mogren Windows Demo");
        glutDisplayFunc(glutRender);
        glutMotionFunc(glutMotionCallback);
        glutMouseFunc(glutMouseCallback);
        glutKeyboardUpFunc(glutKeyUpCallback);

        glewInit();
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        if (mInitializationCallback)
        {
            mInitializationCallback();
        }

        glutMainLoop();

        if (mTerminationCallback)
        {
            mTerminationCallback();
        }
    }

    void LinuxCoreImpl::setInitializationCallback(std::function< void() > callback)
    {
        mInitializationCallback = callback;
    }

    void LinuxCoreImpl::setRenderCallback(std::function< void() > callback)
    {
        mRenderCallback = callback;
    }

    void LinuxCoreImpl::callRenderCallback()
    {
        if (mRenderCallback)
        {
            mRenderCallback();
        }
    }

    void LinuxCoreImpl::glutMotionCallback(int x, int y)
    {
        if (mInstance->mMouseButtonPressed)
        {
            mInstance->callTouchInputCallback(Common::TouchAction::Move, Math::Point2DI(x, y), 0);
        }
    }

    void LinuxCoreImpl::glutMouseCallback(int button, int state, int x, int y)
    {
        if (button == GLUT_LEFT_BUTTON)
        {
            switch (state)
            {
            case GLUT_DOWN:
                mInstance->mMouseButtonPressed = true;
                mInstance->callTouchInputCallback(Common::TouchAction::Down, Math::Point2DI(x, y), 0);
                break;
            case GLUT_UP:
                mInstance->mMouseButtonPressed = false;
                mInstance->callTouchInputCallback(Common::TouchAction::Up, Math::Point2DI(x, y), 0);
                break;
            }
        }
    }

    void LinuxCoreImpl::glutRender()
    {
        mInstance->callRenderCallback();

        glutSwapBuffers();
        glutPostRedisplay();
    }

    Math::Size2DI LinuxCoreImpl::getScreenSize() const
    {
        return mScreenSize;
    }

    void LinuxCoreImpl::setTerminationCallback(std::function< void() > callback)
    {
        mTerminationCallback = callback;
    }

    void LinuxCoreImpl::setTouchInputCallback(std::function<void(Common::TouchAction /*action*/, const Math::Point2DI& /*position*/, int /*pointerId*/)> callback)
    {
        mTouchInputCallback = callback;
    }

    void LinuxCoreImpl::callTouchInputCallback(Common::TouchAction action, const Math::Point2DI& position, int pointerId)
    {
        if (mTouchInputCallback)
        {
            mTouchInputCallback(action, position, pointerId);
        }
    }

    void LinuxCoreImpl::setBackButtonCallback(std::function<void() > callback)
    {
        mBackButtonCallback = callback;
    }

    void LinuxCoreImpl::glutKeyUpCallback(unsigned char key, int x, int y)
    {
        if (key == 27 /*escape*/)
        {
            mInstance->callBackButtonCallback();
        }
    }

    void LinuxCoreImpl::callBackButtonCallback()
    {
        if (mBackButtonCallback)
        {
            mBackButtonCallback();
        }
    }

    void LinuxCoreImpl::terminateApp()
    {
        glutLeaveMainLoop();
    }

    void LinuxCoreImpl::setPauseCallback(std::function<void() > callback)
    {
    }

    void LinuxCoreImpl::setResumeCallback(std::function<void() > callback)
    {
    }

    void LinuxCoreImpl::vibrateDevice(float vibrationDuration)
    {
        // do nothing on windows
    }

    std::string LinuxCoreImpl::getLocaleName() const
    {
        return "";
    }
}
