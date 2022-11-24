//
// Created by erik9 on 11/15/2022.
//

#ifndef LII_WINDOWBUILDER_H
#define LII_WINDOWBUILDER_H
#include <string>
#include <memory>
#include <Window.h>

class WindowBuilder
{
private:
    std::string renderingBackend;
public:
    const std::string &getRenderingBackend() const;
    void setRenderingBackend(const std::string &renderingBackend);

    template<typename ... Args>
    std::unique_ptr<Window> Build(Args ... args)
    {
        auto window = std::make_unique<Window>(std::forward<Args>(args) ...);
    }
};


#endif //LII_WINDOWBUILDER_H
