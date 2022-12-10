//
// Created by erik9 on 12/10/2022.
//

#ifndef LII_ASYNCRENDERER_H
#define LII_ASYNCRENDERER_H
#include <future>
#include <functional>
class EllipseCommander;
class ModelCommander;
class LineCommander;
class Commander;
class TextCommander;

class AsyncRenderer
{
public:
    virtual std::future<EllipseCommander*> RequestEllipseCommander() = 0;
    virtual std::future<ModelCommander*> DrawModel() = 0;
    virtual std::future<LineCommander*>  RequestLineCommander() = 0;
    virtual std::future<TextCommander*> RequestTextCommander() = 0;

    virtual void RequestEllipseCommander(std::function<Commander&> onCreatedAction) = 0;
    virtual void DrawModel(std::function<Commander&> onCreatedAction) = 0;
    virtual void RequestLineCommander(std::function<Commander&> onCreatedAction) = 0;
    virtual void RequestTextCommander(std::function<Commander&> onCreatedAction) = 0;


};
#endif //LII_ASYNCRENDERER_H