#pragma once

#include <Mogren/Framework/Common/SceneItem.h>
#include <memory>

namespace Graphics
{
    class Shader;
    class Geometry;
    class Camera;
    ///
    /// Visual scene item class
    ///
    class VisualSceneItem : public Common::SceneItem
    {
    public:
        ///
        /// Creates a new instance of the VisualSceneItem class.
        /// \param parentItem The parent scene item
        ///
        VisualSceneItem();
        
        ///
        /// Gets the shader used to draw the item
        ///
        std::shared_ptr<const Shader> getShader() const;
        std::shared_ptr<Shader> getShader();

        ///
        /// Sets the shader used to draw the item
        ///
        void setShader(const std::shared_ptr<Shader> &shader);

        ///
        /// Gets the geometry of the item
        ///
        std::shared_ptr<const Geometry> getGeometry() const;
        std::shared_ptr<Geometry> getGeometry();

        ///
        /// Sets the geometry of the item
        ///
        void setGeometry(const std::shared_ptr<Geometry> & geometry);

        ///
        /// Returns \a true if the visual scene item and all of its children are visible.
        ///
        bool isVisible() const;

        ///
        /// If set to \a false, the visual scene item and all of its children are not visible.
        ///
        void setVisible(bool visible);

        ///
        /// Renders the visual scene item
        ///
        virtual void render(const Camera & camera);

        virtual ~VisualSceneItem() = default;

    private:
        std::shared_ptr<Shader> mShader;
        std::shared_ptr<Geometry> mGeometry;

        bool mIsVisible;
    };
}

