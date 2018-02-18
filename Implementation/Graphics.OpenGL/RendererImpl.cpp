#include "RendererImpl.h"
#include "GLInclude.h"
#include "VertexBufferImpl.h"
#include "IndexBufferImpl.h"
#include "RenderTargetImpl.h"
#include "ShaderProgramImpl.h"
#include "ShaderParameterSetImpl.h"

#include <Mogren/Framework/Graphics/NativeInterface/NativeGeometry.h>
#include <Mogren/Framework/Logging/Logger.h>

#include <vector>

namespace Graphics
{
    RendererImpl::RendererImpl()
    {
    }

    void RendererImpl::prepareRender(
        const NativeRenderTarget & renderTarget,
        const Viewport & viewport,
        bool clear, const Color & clearColor)
    {
        auto & impl = static_cast<const RenderTargetImpl&>(renderTarget);
        impl.getGLFrameBuffer().bind();
        glViewport(viewport.mLeft, renderTarget.getHeight() - (viewport.mTop + viewport.mHeight), viewport.mWidth, viewport.mHeight);
        Logging::Logger::writeInfo("RendererImpl::prepareRender");
        if (clear)
        {
            glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
    }

    void RendererImpl::render(
        const NativeGeometry & geometry,
        const NativeShaderProgram & nativeShaderProgram,
        const NativeShaderParameterSet & nativeShaderParameterSet)
    {
        Logging::Logger::writeInfo("RendererImpl::render");
        auto & shaderProgram = static_cast<const ShaderProgramImpl&>(nativeShaderProgram);
        shaderProgram.getGLProgram().use();

        auto & shaderParameterSet = static_cast<const ShaderParameterSetImpl&>(nativeShaderParameterSet);
        shaderParameterSet.applyUniforms();

        auto & indexBuffer = static_cast<const IndexBufferImpl&>(geometry.getIndexBuffer());
        auto & vertexBuffer = static_cast<const VertexBufferImpl&>(geometry.getVertexBuffer());

        indexBuffer.bind();
        vertexBuffer.bind();

        static std::vector<GLuint> enabledAttributes;
        enabledAttributes.clear();

        for (auto attrDesc : vertexBuffer.getVertexStructureDesc().getAttributeDescs())
        {
            const GLint attribLocation = shaderProgram.getAttributeLocation(attrDesc.getAttributeName());

            if (attribLocation == -1)
            {
                continue;
            }

            glEnableVertexAttribArray(attribLocation);
            CHECK_GL_ERROR();
            enabledAttributes.push_back(attribLocation);

            GLint attribSize;
            GLenum attribType;

            switch (attrDesc.getType())
            {
            case Graphics::VertexAttributeType::Byte: attribSize = 1; attribType = GL_BYTE; break;
            case Graphics::VertexAttributeType::ByteVector2: attribSize = 2; attribType = GL_BYTE; break;
            case Graphics::VertexAttributeType::ByteVector3: attribSize = 3; attribType = GL_BYTE; break;
            case Graphics::VertexAttributeType::ByteVector4: attribSize = 4; attribType = GL_BYTE; break;

            case Graphics::VertexAttributeType::UByte: attribSize = 1; attribType = GL_UNSIGNED_BYTE; break;
            case Graphics::VertexAttributeType::UByteVector2: attribSize = 2; attribType = GL_UNSIGNED_BYTE; break;
            case Graphics::VertexAttributeType::UByteVector3: attribSize = 3; attribType = GL_UNSIGNED_BYTE; break;
            case Graphics::VertexAttributeType::UByteVector4: attribSize = 4; attribType = GL_UNSIGNED_BYTE; break;

            case Graphics::VertexAttributeType::Short: attribSize = 1; attribType = GL_SHORT; break;
            case Graphics::VertexAttributeType::ShortVector2: attribSize = 2; attribType = GL_SHORT; break;
            case Graphics::VertexAttributeType::ShortVector3: attribSize = 3; attribType = GL_SHORT; break;
            case Graphics::VertexAttributeType::ShortVector4: attribSize = 4; attribType = GL_SHORT; break;

            case Graphics::VertexAttributeType::UShort: attribSize = 1; attribType = GL_UNSIGNED_SHORT; break;
            case Graphics::VertexAttributeType::UShortVector2: attribSize = 2; attribType = GL_UNSIGNED_SHORT; break;
            case Graphics::VertexAttributeType::UShortVector3: attribSize = 3; attribType = GL_UNSIGNED_SHORT; break;
            case Graphics::VertexAttributeType::UShortVector4: attribSize = 4; attribType = GL_UNSIGNED_SHORT; break;

            case Graphics::VertexAttributeType::Float: attribSize = 1; attribType = GL_FLOAT; break;
            case Graphics::VertexAttributeType::FloatVector2: attribSize = 2; attribType = GL_FLOAT; break;
            case Graphics::VertexAttributeType::FloatVector3: attribSize = 3; attribType = GL_FLOAT; break;
            case Graphics::VertexAttributeType::FloatVector4:
            case Graphics::VertexAttributeType::Color: attribSize = 4; attribType = GL_FLOAT; break;
            default: attribSize = 0; attribType = 0; break;
            }

            glVertexAttribPointer(attribLocation, attribSize, attribType, GL_FALSE, vertexBuffer.getVertexStructureSize(), BUFFER_OFFSET(attrDesc.getOffset()));
            CHECK_GL_ERROR();
        }

        GLenum elemType;

        switch (geometry.getType())
        {
        case GeometryType::LineList:
            elemType = GL_LINES;
            break;
        case GeometryType::LineStrip:
            elemType = GL_LINE_STRIP;
            break;
        case GeometryType::TriangleStrip:
            elemType = GL_TRIANGLE_STRIP;
            break;
        case GeometryType::TriangleFan:
            elemType = GL_TRIANGLE_FAN;
            break;
        default:
            elemType = GL_TRIANGLES;
            break;
        }

        CHECK_GL_ERROR();
        glDrawElements(elemType, geometry.getIndexCount(), GL_UNSIGNED_SHORT, BUFFER_OFFSET(geometry.getIndexOffset() * sizeof(uint16_t)));
        CHECK_GL_ERROR();

        for (auto attribLoc : enabledAttributes)
        {
            glDisableVertexAttribArray(attribLoc);
            CHECK_GL_ERROR();
        }
    }

    void RendererImpl::finishRender()
    {
        Logging::Logger::writeInfo("RendererImpl::finishRender");
    }
}