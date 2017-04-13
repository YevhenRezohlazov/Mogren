#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <algorithm>
#include <assert.h>

namespace Common
{
    ///
    /// Base class for item of any hierarchy.
    ///
    template <typename TItem>
    class HierarchyItem
    {
    protected:
        HierarchyItem();

    public:
        HierarchyItem(HierarchyItem&) = delete;
        HierarchyItem& operator=(HierarchyItem&) = delete;

        bool hasParent() const;

        TItem& getParent();
        const TItem& getParent() const;

        ///
        /// Gets the hierarchy child items vector.
        ///
        const std::vector< std::shared_ptr< TItem > >& getChildren() const;

        ///
        /// Adds the child to children collection.
        ///
        /// \param child The child to be added.
        virtual void addChild(const std::shared_ptr< TItem > & child);

        ///
        /// Removes the child from children collection.
        ///
        /// \param child The child to be removed.
        virtual void removeChild(const std::shared_ptr< TItem > & child);

        virtual ~HierarchyItem();

    private:
        void setParent(TItem * parent);

    private:
        ///
        /// The parent hierarchy item.
        ///
        TItem * mParent;

    protected:

        ///
        /// The hierarchy child items
        ///
        std::vector< std::shared_ptr< TItem > > mChildren;
    };

    template<typename TItem>
    HierarchyItem<TItem>::HierarchyItem()
        : mParent(nullptr), mChildren()
    {
    }

    template<typename TItem>
    inline bool HierarchyItem<TItem>::hasParent() const
    {
        return mParent != nullptr;
    }

    template<typename TItem>
    inline TItem & HierarchyItem<TItem>::getParent()
    {
        assert(mParent != nullptr);
        return *mParent;
    }

    template<typename TItem>
    inline const TItem & HierarchyItem<TItem>::getParent() const
    {
        assert(mParent != nullptr);
        return *mParent;
    }

    ///
    /// Gets the hierarchy child items vector.
    ///
    template<typename TItem>
    inline const std::vector<std::shared_ptr<TItem>>& HierarchyItem<TItem>::getChildren() const
    {
        return mChildren;
    }

    ///
    /// Adds the child to children collection.
    ///
    /// \param child The child to be added.
    template<typename TItem>
    inline void HierarchyItem<TItem>::addChild(const std::shared_ptr<TItem>& child)
    {
        assert(child != nullptr);

        if (child->hasParent())
        {
            child->getParent().removeChild(child);
        }

        mChildren.push_back(child);
        child->setParent(static_cast<TItem*>(this));
    }

    ///
    /// Removes the child from children collection.
    ///
    /// \param child The child to be removed.
    template<typename TItem>
    inline void HierarchyItem<TItem>::removeChild(const std::shared_ptr<TItem>& child)
    {
        assert(child != nullptr);
        auto childIter = std::find(mChildren.cbegin(), mChildren.cend(), child);
        if (childIter != mChildren.cend())
        {
            mChildren.erase(childIter);
            child->setParent(nullptr);
        }
    }

    template<typename TItem>
    inline HierarchyItem<TItem>::~HierarchyItem()
    {
        for (auto & child : mChildren)
        {
            child->setParent(nullptr);
        }
    }

    template<typename TItem>
    inline void HierarchyItem<TItem>::setParent(TItem * parent)
    {
        mParent = parent;
    }
}
