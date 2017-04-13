#pragma once
#include <assert.h>
#include <memory>

namespace Common
{
    template <typename TInterface>
    class ImplementationHolder
    {
    public:
        explicit ImplementationHolder(std::unique_ptr<TInterface> impl);
        ~ImplementationHolder();

        static TInterface& get();

    private:
        static std::unique_ptr<TInterface> sImpl;
    };

    template<typename TInterface>
    std::unique_ptr<TInterface> ImplementationHolder<TInterface>::sImpl;

    template<typename TInterface>
    inline TInterface& ImplementationHolder<TInterface>::get()
    {
        assert(sImpl);
        return *sImpl;
    }

    template<typename TInterface>
    inline ImplementationHolder<TInterface>::ImplementationHolder(std::unique_ptr<TInterface> impl)
    {
        assert(sImpl == nullptr && "Implementation of an interface is set twice.");
        sImpl = std::move(impl);
    }

    template<typename TInterface>
    inline ImplementationHolder<TInterface>::~ImplementationHolder()
    {
        sImpl.reset();
    }

    template<typename TInterface>
    inline TInterface& getImpl()
    {
        return ImplementationHolder<TInterface>::get();
    }
}

