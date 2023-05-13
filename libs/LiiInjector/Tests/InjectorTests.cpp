//
// Created by erik9 on 5/8/2023.
//

#ifndef LIIINJECTOR_INJECTORTESTS_HPP
#define LIIINJECTOR_INJECTORTESTS_HPP
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include "Injector.hpp"
using namespace LiiInjector;

class TestInjectable : public Injectable
{
public:
    int a = 0;
    TestInjectable() = default;
    ~TestInjectable() override = default;
};

class TestInjectableInterface : public Injectable
{
public:
    ~TestInjectableInterface() override = default;
    virtual int GetA() = 0;
};

class TestInjectable2 : public TestInjectableInterface
{
public:
    int a = 0;
    TestInjectable2() = default;
    ~TestInjectable2() override = default;
    int GetA() override
    {
        return a;
    }
};

class TestInjectable3 : public TestInjectableInterface
{
public:
    int a = 0;
    float b = 0;
    std::unique_ptr<TestInjectable2> obj;
    TestInjectable3(int a, float b, std::unique_ptr<TestInjectable2> obj)
    {
        this->a = a;
        this->b = b;
        this ->obj = std::move(obj);
    }
    ~TestInjectable3() override = default;
    int GetA() override
    {
        return a;
    }
};

class TestInjectable4 : public Injectable
{
public:
    std::string a = "";
    long b = 0;
    TestInjectable4(const std::string& a, long b)
    {
        this->a = a;
        this->b = b;
    }

};

TEST_CASE("Multiparam Test with strings and long")
{
    auto injector = Injector{};
    SUBCASE("Without a tag")
    {


        injector.RegisterTransient<TestInjectable4>([](const std::string&, long val) -> Injectable*
        {
            auto instance = new TestInjectable4("test", val);
            return instance;
        });

        try
        {
            std::string str = "test";
            auto instance = injector.ResolveTransient<TestInjectable4, const std::string &, long>("test", 5);
            CHECK(true);
            CHECK(instance->a == "test");
            CHECK(instance->b == 5);
        }
        catch (const std::runtime_error& e)
        {
            INFO(std::string_view(e.what()));
            CHECK(false);
        }
    }
}



TEST_CASE("Singleton registration and resolve")
{
    auto injector = Injector{};
    SUBCASE("without a tag")
    {
        injector.RegisterSingleton<TestInjectable>();
        injector.RegisterSingleton<TestInjectable2>();
        try
        {
            auto* instance = injector.ResolveSingleton<TestInjectable>();
            auto* instance2 = injector.ResolveSingleton<TestInjectable2>();
            CHECK(true);
            CHECK(instance->a == 0);
            CHECK(instance2->a == 0);
        }
        catch (const std::runtime_error& e)
        {
            INFO(std::string_view(e.what()));
            CHECK(false);
        }
    }

    SUBCASE("with a tag")
    {
        injector.RegisterSingletonTag<TestInjectable>("test");
        injector.RegisterSingletonTag<TestInjectable>("tes2");
        try
        {
            auto* instance = injector.ResolveSingletonTag<TestInjectable>("test");
            auto* instance2 = injector.ResolveSingletonTag<TestInjectable>("test");
            CHECK(true);
            CHECK(instance->a == 0);
            CHECK(instance2->a == 0);
        }
        catch (const std::runtime_error& e)
        {
            INFO(std::string_view(e.what()));
            CHECK(true);
        }
    }

    SUBCASE("Factory with a tag")
    {
        injector.RegisterSingletonTag<TestInjectable>([]() -> std::unique_ptr<Injectable>
        {
            auto instance = std::make_unique<TestInjectable>();
            instance->a = 5;
            return instance;
        }, "test");

        injector.RegisterSingletonTag<TestInjectable>([]() -> std::unique_ptr<Injectable>
        {
            auto instance = std::make_unique<TestInjectable>();
            instance->a = 2;
            return instance;
        }, "test2");
        try
        {
            auto* instance = injector.ResolveSingletonTag<TestInjectable>("test");
            auto* instance2 = injector.ResolveSingletonTag<TestInjectable>("test2");
            CHECK(true);
            CHECK(instance->a == 5);
            CHECK(instance2->a == 2);
        }
        catch (const std::runtime_error& e)
        {
            INFO(std::string_view(e.what()));
            CHECK(false);
        }
    }

    SUBCASE("Factory without a tag ")
    {
        injector.RegisterSingleton<TestInjectable>([]() -> std::unique_ptr<Injectable>
        {
           auto instance = std::make_unique<TestInjectable>();
           instance->a = 5;
           return instance;
        });

        try
        {
            auto* instance = injector.ResolveSingleton<TestInjectable>();
            CHECK(true);
            CHECK(instance->a == 5);
        }
        catch (const std::runtime_error& e)
        {
            INFO(std::string_view(e.what()));
            CHECK(false);
        }
    }
}

TEST_CASE("Singleton registration and resolve with polymorphism")
{
    auto injector = Injector{};
    SUBCASE("without a tag ")
    {
        injector.RegisterSingleton<TestInjectableInterface>([]() -> std::unique_ptr<Injectable>
        {
            auto instance = std::make_unique<TestInjectable2>();
            instance->a = 5;
            return instance;
        });
        try
        {
            auto* instance = injector.ResolveSingleton<TestInjectableInterface>();
            CHECK(true);
            CHECK(instance->GetA() == 5);
        }
        catch (const std::runtime_error& e)
        {
            INFO(std::string_view(e.what()));
            CHECK(false);
        }
    }

    SUBCASE("Factory with a tag ")
    {
        injector.RegisterSingletonTag<TestInjectableInterface>([]() -> std::unique_ptr<Injectable>
        {
            auto instance = std::make_unique<TestInjectable2>();
            instance->a = 5;
            return instance;
        }, "test1");

        injector.RegisterSingletonTag<TestInjectableInterface>([]() -> std::unique_ptr<Injectable>
        {
            auto instance = std::make_unique<TestInjectable2>();
            instance->a = 2;
            return instance;
        }, "test2");

        try
        {
            auto* instance = injector.ResolveSingletonTag<TestInjectableInterface>("test1");
            auto* instance2 = injector.ResolveSingletonTag<TestInjectableInterface>("test2");
            CHECK(true);
            CHECK(instance->GetA() == 5);
            CHECK(instance2->GetA() == 2);
        }
        catch (const std::runtime_error& e)
        {
            INFO(std::string_view(e.what()));
            CHECK(false);
        }
    }
}

TEST_CASE("Singleton registration and fail with polymorphism")
{
    auto injector = Injector{};
    SUBCASE("Factory without a tag ")
    {
        injector.RegisterSingleton<TestInjectableInterface>([]() -> std::unique_ptr<Injectable>
        {
            auto instance = std::make_unique<TestInjectable>();
            instance->a = 5;
            return instance;
        });
        CHECK_THROWS_WITH_AS(injector.ResolveSingleton<TestInjectableInterface>(), "Singleton type mismatch!", std::runtime_error);
    }

    SUBCASE("Factory with a tag ")
    {
        injector.RegisterSingletonTag<TestInjectableInterface>([]() -> std::unique_ptr<Injectable>
        {
            auto instance = std::make_unique<TestInjectable>();
            instance->a = 5;
            return instance;
        }, "test1");

        injector.RegisterSingletonTag<TestInjectableInterface>([]() -> std::unique_ptr<Injectable>
        {
            auto instance = std::make_unique<TestInjectable>();
            instance->a = 2;
            return instance;
        }, "test2");

        CHECK_THROWS_WITH_AS(injector.ResolveSingletonTag<TestInjectableInterface>("test1"), "Singleton type mismatch!", std::runtime_error);
        CHECK_THROWS_WITH_AS(injector.ResolveSingletonTag<TestInjectableInterface>("test2"), "Singleton type mismatch!", std::runtime_error);
    }
}

TEST_CASE("Singleton Registration exception")
{
    auto injector = Injector{};
    SUBCASE("without a tag resolve failure")
    {
        injector.RegisterSingleton<TestInjectable>();
        CHECK_THROWS_AS(injector.ResolveSingleton<TestInjectable2>(), const std::runtime_error&);
    }

    SUBCASE("with a tag resolve failure")
    {
        injector.RegisterSingletonTag<TestInjectable>("test");
        CHECK_THROWS_AS(injector.ResolveSingletonTag<TestInjectable>("test2"), const std::runtime_error&);
    }
}

TEST_CASE("Transient registration and resolve")
{
    auto injector = Injector{};
    SUBCASE("without a tag")
    {
        injector.RegisterTransient<TestInjectable>();
        injector.RegisterTransient<TestInjectable2>();
        try
        {
            auto instanceA = injector.ResolveTransient<TestInjectable>();
            auto instanceA2 = injector.ResolveTransient<TestInjectable>();
            auto instanceA3 = injector.ResolveTransient<TestInjectable>();

            auto instanceB = injector.ResolveTransient<TestInjectable2>();
            auto instanceB2 = injector.ResolveTransient<TestInjectable2>();
            auto instanceB3 = injector.ResolveTransient<TestInjectable2>();



            instanceA->a = 1;
            instanceA2->a = 2;
            instanceA3->a = 3;

            instanceB->a = 4;
            instanceB2->a = 5;
            instanceB3->a = 6;

            CHECK(true);
            CHECK(instanceA->a == 1);
            CHECK(instanceA2->a == 2);
            CHECK(instanceA3->a == 3);
            CHECK(instanceB->a == 4);
            CHECK(instanceB2->a == 5);
            CHECK(instanceB3->a == 6);
        }
        catch (const std::runtime_error& e)
        {
            INFO(std::string_view(e.what()));
            CHECK(false);
        }
    }

    SUBCASE("With a tag")
    {
        injector.RegisterTransientTag<TestInjectable>("test1");
        injector.RegisterTransientTag<TestInjectable>("test2");
        injector.RegisterTransientTag<TestInjectable2>("test3");
        injector.RegisterTransientTag<TestInjectable2>("test4");
        try
        {
            auto instanceA = injector.ResolveTransientTag<TestInjectable>("test1");
            auto instanceA2 = injector.ResolveTransientTag<TestInjectable>("test1");
            auto instanceA3 = injector.ResolveTransientTag<TestInjectable>("test1");

            auto instanceB = injector.ResolveTransientTag<TestInjectable2>("test3");
            auto instanceB2 = injector.ResolveTransientTag<TestInjectable2>("test3");
            auto instanceB3 = injector.ResolveTransientTag<TestInjectable2>("test3");

            auto instanceC = injector.ResolveTransientTag<TestInjectable>("test2");
            auto instanceC2 = injector.ResolveTransientTag<TestInjectable>("test2");
            auto instanceC3 = injector.ResolveTransientTag<TestInjectable>("test2");

            auto instanceD = injector.ResolveTransientTag<TestInjectable2>("test4");
            auto instanceD2 = injector.ResolveTransientTag<TestInjectable2>("test4");
            auto instanceD3 = injector.ResolveTransientTag<TestInjectable2>("test4");

            instanceA->a = 1;
            instanceA2->a = 2;
            instanceA3->a = 3;

            instanceB->a = 4;
            instanceB2->a = 5;
            instanceB3->a = 6;

            instanceC->a = 7;
            instanceC2->a = 8;
            instanceC3->a = 9;

            instanceD->a = 10;
            instanceD2->a = 11;
            instanceD3->a = 12;

            CHECK(true);
            CHECK(instanceA->a == 1);
            CHECK(instanceA2->a == 2);
            CHECK(instanceA3->a == 3);
            CHECK(instanceB->GetA() == 4);
            CHECK(instanceB2->GetA() == 5);
            CHECK(instanceB3->GetA() == 6);
            CHECK(instanceC->a == 7);
            CHECK(instanceC2->a == 8);
            CHECK(instanceC3->a == 9);
            CHECK(instanceD->GetA() == 10);
            CHECK(instanceD2->GetA() == 11);
            CHECK(instanceD3->GetA() == 12);
        }
        catch (const std::runtime_error& e)
        {
            INFO(std::string_view(e.what()));
            CHECK(false);
        }
    }

    SUBCASE("Factory without a tag")
    {
        injector.RegisterTransient<TestInjectable>([]() -> Injectable *
        {
            auto instance = new TestInjectable();
            instance->a = 1;
            return instance;
        });
        injector.RegisterTransient<TestInjectable2>([]() -> Injectable *
        {
            auto instance = new TestInjectable2();
            instance->a = 2;
            return instance;
        });
        try
        {
            auto instanceA = injector.ResolveTransient<TestInjectable>();
            auto instanceB = injector.ResolveTransient<TestInjectable2>();

            CHECK(true);
            CHECK(instanceA->a == 1);
            CHECK(instanceB->GetA() == 2);
        }
        catch (const std::runtime_error& e)
        {
            INFO(std::string_view(e.what()));
            CHECK(false);
        }
    }

    SUBCASE("Factory with a tag")
    {
        injector.RegisterTransientTag<TestInjectable>([]() -> Injectable *
        {
            auto instance = new TestInjectable();
            instance->a = 1;
            return instance;
        }, "test1");
        injector.RegisterTransientTag<TestInjectable>([]() -> Injectable *
        {
            auto instance = new TestInjectable();
            instance->a = 2;
            return instance;
        }, "test2");
        injector.RegisterTransientTag<TestInjectable2>([]() -> Injectable *
        {
            auto instance = new TestInjectable2();
            instance->a = 3;
            return instance;
        }, "test3");
        injector.RegisterTransientTag<TestInjectable2>([]() -> Injectable *
        {
            auto instance = new TestInjectable2();
            instance->a = 4;
            return instance;
        }, "test4");
        try
        {
            auto instanceA = injector.ResolveTransientTag<TestInjectable>("test1");
            auto instanceB = injector.ResolveTransientTag<TestInjectable>("test2");
            auto instanceC = injector.ResolveTransientTag<TestInjectable2>("test3");
            auto instanceD = injector.ResolveTransientTag<TestInjectable2>("test4");

            CHECK(true);
            CHECK(instanceA->a == 1);
            CHECK(instanceB->a == 2);
            CHECK(instanceC->GetA() == 3);
            CHECK(instanceD->GetA() == 4);
        }
        catch (const std::runtime_error& e)
        {
            INFO(std::string_view(e.what()));
            CHECK(false);
        }
    }
}

TEST_CASE("Transient registration and resolve with multiarguments")
{
    auto injector = Injector{};
    SUBCASE("Multi arguments without a tag")
    {
        injector.RegisterTransient<TestInjectable3>(
                [](int a, float b, std::unique_ptr<TestInjectable2> c) -> Injectable *
                {
                    auto instance = new TestInjectable3(a, b, std::move(c));
                    return instance;
                });

        injector.RegisterTransient<TestInjectable3>([](int a, std::unique_ptr<TestInjectable2> c) -> Injectable *
        {
            auto instance = new TestInjectable3(a, 3.0f, std::move(c));
            return instance;
        });

        try
        {
            auto instance = injector.ResolveTransient<TestInjectable3>(1, 2.0f, std::make_unique<TestInjectable2>());
            auto instance2 = injector.ResolveTransient<TestInjectable3>(1, std::make_unique<TestInjectable2>());
            CHECK(true);
            CHECK(instance->a == 1);
            CHECK(instance->b == 2.0f);
            CHECK(instance->obj->a == 0);
            CHECK(instance2->a == 1);
            CHECK(instance2->b == 3.0f);
            CHECK(instance2->obj->a == 0);
        }
        catch (const std::runtime_error& e)
        {
            INFO(std::string_view(e.what()));
            CHECK(false);
        }

    }

    SUBCASE("Multi arguments with a tag")
    {
        injector.RegisterTransientTag<TestInjectable3>(
                [](int a, float b, std::unique_ptr<TestInjectable2> c) -> Injectable *
                {
                    auto instance = new TestInjectable3(a, b, std::move(c));
                    return instance;
                }, "test1");

        injector.RegisterTransientTag<TestInjectable3>(
                [](int a, float b, std::unique_ptr<TestInjectable2> c) -> Injectable *
                {
                    auto instance = new TestInjectable3(a, b * 3.0f, std::move(c));
                    return instance;
                }, "test2");

        try
        {
            auto instance = injector.ResolveTransientTag<TestInjectable3>("test1", 1, 2.0f,
                    std::make_unique<TestInjectable2>());
            auto instance2 = injector.ResolveTransientTag<TestInjectable3>("test2", 1, 2.0f,
                    std::make_unique<TestInjectable2>());
            CHECK(true);
            CHECK(instance->a == 1);
            CHECK(instance->b == 2.0f);
            CHECK(instance->obj->a == 0);
            CHECK(instance2->a == 1);
            CHECK(instance2->b == 6.0f);
            CHECK(instance2->obj->a == 0);
        }
        catch (const std::runtime_error& e)
        {
            INFO(std::string_view(e.what()));
            CHECK(false);
        }
    }
}

TEST_CASE("Transient registration and resolve with multiarguments and polymorphism")
{
    auto injector = Injector{};
    SUBCASE("Multi arguments without a tag")
    {
        injector.RegisterTransient<TestInjectableInterface>(
                [](int a, float b, std::unique_ptr<TestInjectable2> c) -> Injectable *
                {
                    auto instance = new TestInjectable3(a, b, std::move(c));
                    return instance;
                });

        injector.RegisterTransient<TestInjectableInterface>(
                [](int a, std::unique_ptr<TestInjectable2> c) -> Injectable *
                {
                    auto instance = new TestInjectable3(a, 3.0f, std::move(c));
                    return instance;
                });

        try
        {
            auto instance = injector.ResolveTransient<TestInjectableInterface>(5, 2.0f, std::make_unique<TestInjectable2>());
            auto instance2 = injector.ResolveTransient<TestInjectableInterface>(6, std::make_unique<TestInjectable2>());
            CHECK(true);
            CHECK(instance->GetA() == 5);
            CHECK(instance2->GetA() == 6);
        }
        catch (const std::runtime_error& e)
        {
            INFO(std::string_view(e.what()));
            CHECK(false);
        }

    }

    SUBCASE("Multi arguments with a tag")
    {
        injector.RegisterTransientTag<TestInjectableInterface>(
                [](int a, float b, std::unique_ptr<TestInjectable2> c) -> Injectable *
                {
                    auto instance = new TestInjectable3(a, b, std::move(c));
                    return instance;
                }, "test1");

        injector.RegisterTransientTag<TestInjectableInterface>(
                [](int a, float b, std::unique_ptr<TestInjectable2> c) -> Injectable *
                {
                    auto instance = new TestInjectable3(a, b * 3.0f, std::move(c));
                    return instance;
                }, "test2");

        try
        {
            auto instance = injector.ResolveTransientTag<TestInjectableInterface>("test1", 5, 2.0f,
                    std::make_unique<TestInjectable2>());
            auto instance2 = injector.ResolveTransientTag<TestInjectableInterface>("test2", 6, 2.0f,
                    std::make_unique<TestInjectable2>());
            CHECK(true);
            CHECK(instance->GetA() == 5);
            CHECK(instance2->GetA() == 6);
        }
        catch (const std::runtime_error& e)
        {
            INFO(std::string_view(e.what()));
            CHECK(false);
        }
    }
}

TEST_CASE("Transient registration and resolve with polymorphism")
{
    auto injector = Injector{};

    SUBCASE("without a tag ")
    {
        int counter = 1;
        injector.RegisterTransient<TestInjectableInterface>([&]() -> Injectable *
        {
            auto instance = new TestInjectable2();
            instance->a = counter;
            counter++;
            return instance;
        });

        try
        {
            auto instanceA = injector.ResolveTransient<TestInjectableInterface>();
            auto instanceB = injector.ResolveTransient<TestInjectableInterface>();
            auto instanceC = injector.ResolveTransient<TestInjectableInterface>();

            CHECK(true);
            CHECK(instanceA->GetA() == 1);
            CHECK(instanceB->GetA() == 2);
            CHECK(instanceC->GetA() == 3);

        }
        catch (const std::runtime_error& e)
        {
            INFO(std::string_view(e.what()));
            CHECK(false);
        }

    }

    SUBCASE("With a tag")
    {
        injector.RegisterTransientTag<TestInjectableInterface>([&]() -> Injectable *
        {
            auto instance = new TestInjectable2();
            instance->a = 1;
            return instance;
        }, "test1");
        injector.RegisterTransientTag<TestInjectableInterface>([&]() -> Injectable *
        {
            auto instance = new TestInjectable2();
            instance->a = 2;
            return instance;
        }, "test2");
        injector.RegisterTransientTag<TestInjectableInterface>([&]() -> Injectable *
        {
            auto instance = new TestInjectable2();
            instance->a = 3;
            return instance;
        }, "test3");

        try
        {
            auto instanceA = injector.ResolveTransientTag<TestInjectableInterface>("test1");
            auto instanceB = injector.ResolveTransientTag<TestInjectableInterface>("test2");
            auto instanceC = injector.ResolveTransientTag<TestInjectableInterface>("test3");

            CHECK(true);
            CHECK(instanceA->GetA() == 1);
            CHECK(instanceB->GetA() == 2);
            CHECK(instanceC->GetA() == 3);

        }
        catch (const std::runtime_error& e)
        {
            INFO(std::string_view(e.what()));
            CHECK(false);
        }
    }
}

TEST_CASE("Transient registration exception with multiparam")
{
    auto injector = Injector{};

    SUBCASE("Without a tag")
    {
        injector.RegisterTransient<TestInjectable2>(
                [](int a, float b, std::unique_ptr<TestInjectable2> c) -> Injectable *
                {
                    auto instance = new TestInjectable3(a, b, std::move(c));
                    return instance;
                });

        CHECK_THROWS(injector.RegisterTransient<TestInjectable2>(
                [](int a, float b, std::unique_ptr<TestInjectable2> c) -> Injectable *
                {
                    auto instance = new TestInjectable3(a, b, std::move(c));
                    return instance;
                }));
    }

    SUBCASE("With a tag")
    {
        injector.RegisterTransientTag<TestInjectable2>(
                [](int a, float b, std::unique_ptr<TestInjectable2> c) -> Injectable *
                {
                    auto instance = new TestInjectable3(a, b, std::move(c));
                    return instance;
                }, "test1");

        CHECK_THROWS(injector.RegisterTransientTag<TestInjectable2>(
                [](int a, float b, std::unique_ptr<TestInjectable2> c) -> Injectable *
                {
                    auto instance = new TestInjectable3(a, b, std::move(c));
                    return instance;
                }, "test1"));
    }
}

TEST_CASE("Transient registration exception")
{
    auto injector = Injector{};

    SUBCASE("Without a tag")
    {
        injector.RegisterTransient<TestInjectable>([]() -> Injectable *
        {
            auto instance = new TestInjectable();
            instance->a = 1;
            return instance;
        });

        CHECK_THROWS(injector.RegisterTransient<TestInjectable>([]() -> Injectable *
        {
            auto instance = new TestInjectable();
            instance->a = 2;
            return instance;
        }));
    }

    SUBCASE("With a tag")
    {
        injector.RegisterTransientTag<TestInjectable>([]() -> Injectable *
        {
            auto instance = new TestInjectable();
            instance->a = 1;
            return instance;
        }, "test1");

        CHECK_THROWS(injector.RegisterTransientTag<TestInjectable>([]() -> Injectable *
        {
            auto instance = new TestInjectable();
            instance->a = 2;
            return instance;
        }, "test1"));
    }
}

TEST_CASE("Transient registration and fail with polymorphism and multiparams")
{
    auto injector = Injector{};

    SUBCASE("Without a tag")
    {
        injector.RegisterTransient<TestInjectableInterface>(
                [](int a, float b, std::unique_ptr<TestInjectable2> c) -> Injectable *
                {
                    auto instance = new TestInjectable3(a, b, std::move(c));
                    return instance;
                });

        CHECK_THROWS(injector.RegisterTransient<TestInjectableInterface>(
                [](int a, float b, std::unique_ptr<TestInjectable2> c) -> Injectable *
                {
                    auto instance = new TestInjectable3(a, b, std::move(c));
                    return instance;
                }));
    }

    SUBCASE("With a tag")
    {
        injector.RegisterTransientTag<TestInjectableInterface>(
                [](int a, float b, std::unique_ptr<TestInjectable2> c) -> Injectable *
                {
                    auto instance = new TestInjectable3(a, b, std::move(c));
                    return instance;
                }, "test1");

        CHECK_THROWS(injector.RegisterTransientTag<TestInjectableInterface>(
                [](int a, float b, std::unique_ptr<TestInjectable2> c) -> Injectable *
                {
                    auto instance = new TestInjectable3(a, b, std::move(c));
                    return instance;
                }, "test1"));
    }
}

TEST_CASE("Transient registration and fail with polymorphism")
{
    auto injector = Injector{};

    SUBCASE("Without a tag")
    {
        injector.RegisterTransient<TestInjectableInterface>([]() -> Injectable *
        {
            auto instance = new TestInjectable2();
            instance->a = 1;
            return instance;
        });

        CHECK_THROWS(injector.RegisterTransient<TestInjectableInterface>([]() -> Injectable *
        {
            auto instance = new TestInjectable2();
            instance->a = 2;
            return instance;
        }));
    }

    SUBCASE("With a tag")
    {
        injector.RegisterTransientTag<TestInjectableInterface>([]() -> Injectable *
        {
            auto instance = new TestInjectable2();
            instance->a = 1;
            return instance;
        }, "test1");

        CHECK_THROWS(injector.RegisterTransientTag<TestInjectableInterface>([]() -> Injectable *
        {
            auto instance = new TestInjectable2();
            instance->a = 2;
            return instance;
        }, "test1"));
    }
}


#endif //LIIINJECTOR_INJECTORTESTS_HPP
