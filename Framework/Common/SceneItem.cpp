#include "SceneItem.h"
#include <assert.h>

namespace Common
{
    SceneItem::SceneItem()
        : mGlobalTransformationMatrix(Math::Matrix4x4::Identity),
        mTransformation(std::make_unique<Transformation>()),
        mLastTransformationVersion(0),
        mIsTransformationDirty(false)
    {
    }

    const Transformation & SceneItem::getTransformation() const
    {
        assert(mTransformation);
        return *mTransformation;
    }

    void SceneItem::setTransformation(std::unique_ptr<Transformation> transformation)
    {
        mTransformation = std::move(transformation);
    }

    const Math::Matrix4x4& SceneItem::getGlobalTransformationMatrix() const
    {
        // needed to keep logical consistency
        SceneItem *_this = const_cast<SceneItem*>(this);
        _this->updateGlobalTransformationMatrix();
        return mGlobalTransformationMatrix;
    }

    bool SceneItem::updateGlobalTransformationMatrix()
    {
        mIsTransformationDirty |= hasParent() && getParent().updateGlobalTransformationMatrix();

        bool needUpdate = mIsTransformationDirty || (mLastTransformationVersion != getTransformation().getVersion());

        if (needUpdate)
        {
            mLastTransformationVersion = getTransformation().getVersion();

            if (hasParent())
            {
                mGlobalTransformationMatrix = getTransformation().getMatrix() * getParent().getGlobalTransformationMatrix();
            }
            else
            {
                mGlobalTransformationMatrix = getTransformation().getMatrix();
            }

            mIsTransformationDirty = false;
            makeChildrenTransformationDirty();
            return true;
        }

        return false;
    }

    void SceneItem::makeChildrenTransformationDirty()
    {
        for (auto &child : getChildren())
        {
            child->mIsTransformationDirty = true;
            child->makeChildrenTransformationDirty();
        }
    }

    void SceneItem::onTransformationChanged()
    {
        mIsTransformationDirty = true;
    }
}