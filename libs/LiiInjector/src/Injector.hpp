//
// Created by erik9 on 5/8/2023.
//

#ifndef LIIINJECTOR_INJECTOR_HPP
#define LIIINJECTOR_INJECTOR_HPP

#include <string>
#include <memory>
#include <unordered_map>
#include <stdexcept>
#include <typeindex>
#include <functional>
#include "Injectable.h"

namespace LiiInjector
{
    class FunctionWrapperBase
    {
    public:
        virtual ~FunctionWrapperBase() = default;
    };


    template<class ... Args>
    class FunctionWrapper : public FunctionWrapperBase
    {
    private:
        template<typename... Tuples>
        struct tuple_type_cat final
        {
            using type = typename std::function< decltype( std::tuple_cat<Tuples...> ) >::result_type;
        };
    public:
        ~FunctionWrapper() override = default;
        template<class T>
        static std::type_index GetTypeSignature()
        {
            return std::type_index(typeid(tuple_type_cat<std::tuple<T, Args...>>));
        }

        explicit FunctionWrapper(const std::function<Injectable*(Args...)>& factoryFunc) :
                factoryFunc(factoryFunc)
        {

        }
        template<class T>
        std::type_index GenerateTypeSignature()
        {
            typeSignature = GetTypeSignature<T>();
            return typeSignature;
        }
        std::function<Injectable*(Args...)> factoryFunc;
        std::type_index typeSignature = typeid(FunctionWrapper);
    };


    class Injector
    {
    private:
        static Injector* const instance;
        std::unordered_map<std::string, std::unique_ptr<Injectable>> tagSingletons;
        std::unordered_map<std::type_index, std::unique_ptr<Injectable>> singletons;

        std::unordered_map<std::string, std::unique_ptr<FunctionWrapperBase>> transientTag;
        std::unordered_map<std::type_index, std::unique_ptr<FunctionWrapperBase>> transient;
    public:
        static Injector& GetInstance()
        {
            return *instance;
        }

        template<typename T>
        [[maybe_unused]] void RegisterSingletonTag(const std::string& tag)
        {
            static_assert(std::is_base_of<Injectable, T>::value, "T must be a child of Injectable");
            std::unique_ptr<T> singleton = std::unique_ptr<T>(new T());
            auto result = tagSingletons.try_emplace(tag, std::move(singleton));
            if (!result.second)
                throw std::runtime_error("Singleton already registered!");
        }

        template<typename T>
        [[maybe_unused]] void RegisterSingleton()
        {
            static_assert(std::is_base_of<Injectable, T>::value, "T must be a child of Injectable");
            std::unique_ptr<T> singleton = std::unique_ptr<T>(new T());
            auto result = singletons.try_emplace(typeid(T), std::move(singleton));
            if (!result.second)
                throw std::runtime_error("Singleton already registered!");
        }

        template<typename T>
        [[maybe_unused]] void RegisterSingleton(const std::function <std::unique_ptr<Injectable>()>& factoryFunction)
        {
            static_assert(std::is_base_of<Injectable, T>::value, "T must be a child of Injectable");
            auto result = singletons.try_emplace(typeid(T), factoryFunction());
            if (!result.second)
                throw std::runtime_error("Singleton already registered!");
        }

        template<typename T>
        [[maybe_unused]] void RegisterSingletonTag(const std::function <std::unique_ptr<Injectable>()>& function, const std::string& tag)
        {
            static_assert(std::is_base_of<Injectable, T>::value, "T must be a child of Injectable");
            auto result = tagSingletons.try_emplace(tag, function());

            if (!result.second)
                throw std::runtime_error("Singleton already registered!");
        }

        template<class T>
        T* ResolveSingletonTag(const std::string& tag)
        {
            static_assert(std::is_base_of<Injectable, T>::value, "T must be a child of Injectable");
            auto it = tagSingletons.find(tag);
            if (it == tagSingletons.end())
                throw std::runtime_error("Singleton not registered!");
            auto* result = dynamic_cast<T*>(it->second.get());
            if(result == nullptr)
                throw std::runtime_error("Singleton type mismatch!");
            return result;
        }

        template<class T>
        T* ResolveSingleton()
        {
            static_assert(std::is_base_of<Injectable, T>::value, "T must be a child of Injectable");
            auto it = singletons.find(typeid(T));
            if (it == singletons.end())
                throw std::runtime_error("Singleton not registered!");
            auto* result = dynamic_cast<T*>(it->second.get());
            if(result == nullptr)
                throw std::runtime_error("Singleton type mismatch!");
            return result;
        }

        template<typename T, typename F>
        void RegisterTransient(const F&& factoryLambda)
        {
            static_assert(std::is_base_of<Injectable, T>::value, "T must be a child of Injectable");
            std::function factoryFunc{factoryLambda};
            auto* functionWrapper = new FunctionWrapper(factoryFunc);
            functionWrapper->template GenerateTypeSignature<T>();
            auto result = transient.try_emplace(functionWrapper->typeSignature, std::unique_ptr<FunctionWrapperBase>(functionWrapper));

            if (!result.second)
                throw std::runtime_error("Type already registered!");
        }

        template<typename T, typename F>
        [[maybe_unused]] void RegisterTransientTag(const F& factoryLambda, const std::string& tag)
        {
            static_assert(std::is_base_of<Injectable, T>::value, "T must be a child of Injectable");
            std::function factoryFunc{factoryLambda};
            auto* functionWrapper = new FunctionWrapper(factoryFunc);
            functionWrapper->template GenerateTypeSignature<T>();
            auto result = transientTag.try_emplace(tag, std::unique_ptr<FunctionWrapperBase>(functionWrapper));

            if (!result.second)
                throw std::runtime_error("Type already registered!");
        }

        template<typename T>
        [[maybe_unused]] void RegisterTransient()
        {
            RegisterTransient<T>([]() -> Injectable *
            { return new T(); });
        }

        template<typename T>
        [[maybe_unused]] void RegisterTransientTag(const std::string& tag)
        {
            RegisterTransientTag<T>([]() -> Injectable *
            { return new T(); }, tag);
        }

        template<typename T>
        std::unique_ptr<T> ResolveTransient()
        {
            static_assert(std::is_base_of<Injectable, T>::value, "T must be a child of Injectable");
            auto it = transient.find(FunctionWrapper<>::template GetTypeSignature<T>());
            if (it == transient.end())
                throw std::runtime_error("Type not registered!");

            auto* functionWrapper = dynamic_cast<FunctionWrapper<>*>(it->second.get());
            if(functionWrapper == nullptr)
                throw std::runtime_error("Factory function mismatch!");

            auto result = dynamic_cast<T*>(functionWrapper->factoryFunc());
            if(result == nullptr)
                throw std::runtime_error("Type mismatch!");
            return std::unique_ptr<T>(result);
        }


        template<typename T, typename ... Args>
        std::unique_ptr<T> ResolveTransient(Args ... args)
        {
            static_assert(std::is_base_of<Injectable, T>::value, "T must be a child of Injectable");
            auto it = transient.find(FunctionWrapper<Args ...>::template GetTypeSignature<T>());
            if (it == transient.end())
                throw std::runtime_error("Type not registered!");

            auto* functionWrapper = dynamic_cast<FunctionWrapper<Args...>*>(it->second.get());
            if(functionWrapper == nullptr)
                throw std::runtime_error("Factory function mismatch!");

            auto result = dynamic_cast<T*>(functionWrapper->factoryFunc(std::move(args) ...));
            if(result == nullptr)
                throw std::runtime_error("Type mismatch!");
            return std::unique_ptr<T>(result);
        }

        template<typename T, typename ... Args>
        std::unique_ptr<T> ResolveTransientTag(const std::string& tag, Args ... args)
        {
            static_assert(std::is_base_of<Injectable, T>::value, "T must be a child of Injectable");
            auto it = transientTag.find(tag);
            if (it == transientTag.end())
                throw std::runtime_error("Type not registered!");

            auto* functionWrapper = dynamic_cast<FunctionWrapper<Args...>*>(it->second.get());
            if(functionWrapper == nullptr)
                throw std::runtime_error("Factory function mismatch!");

            auto result = dynamic_cast<T*>(functionWrapper->factoryFunc(std::move(args) ...));
            if(result == nullptr)
                throw std::runtime_error("Type mismatch!");
            return std::unique_ptr<T>(result);
        }
    };
}

inline LiiInjector::Injector* const LiiInjector::Injector::instance = new LiiInjector::Injector();

#endif //LIIINJECTOR_INJECTOR_HPP
