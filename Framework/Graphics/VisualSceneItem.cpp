#include "VisualSceneItem.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Geometry.h"
#include "Camera.h"
#include "NativeInterface/NativeGraphicsInterface.h"
#include "NativeInterface/NativeRenderer.h"
#include <Mogren/Framework/Logging/Logger.h>
#include <Mogren/Framework/Common/ImplementationProvider.h>

namespace Graphics
{
    VisualSceneItem::VisualSceneItem()
    {
    }

    std::shared_ptr<const Shader> VisualSceneItem::getShader() const
    {
        return mShader;
    }

    std::shared_ptr<Shader> VisualSceneItem::getShader()
    {
        return mShader;
    }

    void VisualSceneItem::setShader(const std::shared_ptr<Shader>& shader)
    {
        mShader = shader;
    }

    std::shared_ptr<const Geometry> VisualSceneItem::getGeometry() const
    {
        return mGeometry;
    }

    std::shared_ptr<Geometry> VisualSceneItem::getGeometry()
    {
        return mGeometry;
    }

    void VisualSceneItem::setGeometry(const std::shared_ptr<Geometry>& geometry)
    {
        mGeometry = geometry;
    }

    void VisualSceneItem::render(const Camera & camera)
    {
        if (mGeometry == nullptr || mShader == nullptr)
        {
            Logging::Logger::writeWarning("Can't render visual item without geometry or shader set.");
            return;
        }

        const auto& worldTransform = getGlobalTransformationMatrix();

        // set transformation matrices
        {
            if (getShader()->getWorldTransformParameter())
            {
                getShader()->getWorldTransformParameter()->setValue(worldTransform);
            }

            if (getShader()->getViewTransformParameter())
            {
                getShader()->getViewTransformParameter()->setValue(camera.getViewMatrix());
            }

            if (getShader()->getProjectionTransformParameter())
            {
                getShader()->getProjectionTransformParameter()->setValue(camera.getProjectionMatrix());
            }

            if (getShader()->getViewProjectionTransformParameter())
            {
                getShader()->getViewProjectionTransformParameter()->setValue(camera.getViewProjectionMatrix());
            }

            if (getShader()->getWorldViewTransformParameter())
            {
                getShader()->getWorldViewTransformParameter()->setValue(worldTransform * camera.getViewMatrix());
            }

            if (getShader()->getWorldViewProjectionTransformParameter())
            {
                getShader()->getWorldViewProjectionTransformParameter()->setValue(worldTransform * camera.getViewProjectionMatrix());
            }
        }

        auto& renderer = Common::getImpl<NativeGraphicsInterface>().getRenderer();
        renderer.render(
            getGeometry()->getNativeGeometry(),
            getShader()->getProgram()->getNativeShaderProgram(),
            getShader()->getNativeParameterSet());
    }
}