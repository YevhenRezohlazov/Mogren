#pragma once

#include "HierarchyItem.h"
#include "Transformation.h"

namespace Common
{
    ///
    /// The Mogren scene item class
    ///
    class SceneItem : public HierarchyItem< SceneItem >
    {
    public:
        ///
        /// Initializes a new instance of the SceneItem class.
        ///
        /// \param parent The parent item.
        SceneItem();

        ///
        /// Gets the scene item transformation.
        ///
        template <typename TTransformation>
        TTransformation& transform();

        ///
        /// Gets the scene item transformation.
        ///
        const Transformation& getTransformation() const;


        ///
        /// Sets the scene item transformation.
        ///
        void setTransformation(std::unique_ptr<Transformation> transformation);

        ///
        /// Returns the global transformation matrix of the scene item
        ///
        const Math::Matrix4x4& getGlobalTransformationMatrix() const;

        ///
        /// Updates the global transformation matrix, if needed
        ///
        virtual bool updateGlobalTransformationMatrix();

        ///
        /// Returns \a true if the scene item and all of its children are excluded from any scene processing
        ///
        bool isEnabled() const;

        ///
        /// If set to \a false, the visual scene item and all of its children are excluded from any scene processing
        ///
        void setEnabled(bool enabled);

    protected:
        ///
        /// Sets mIsTransformationDirty of each scene item child to true
        ///
        void makeChildrenTransformationDirty();

        virtual void onTransformationChanged();

    protected:
        Math::Matrix4x4 mGlobalTransformationMatrix;
        std::unique_ptr<Transformation> mTransformation;
        uint64_t mLastTransformationVersion;
        bool mIsTransformationDirty;
        bool mIsEnabled;
    };

    template<typename TTransformation>
    TTransformation & SceneItem::transform()
    {
        auto result = dynamic_cast<TTransformation*>(mTransformation.get());

        if (result == nullptr)
        {
            mTransformation = std::make_unique<TTransformation>();
            onTransformationChanged();
        }

        return static_cast<TTransformation&>(*mTransformation);
    }
}

