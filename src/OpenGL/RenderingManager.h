//
// Created by Erik on 09/04/22.
//

#ifndef LII_RENDERINGMANAGER_H
#define LII_RENDERINGMANAGER_H
#include "Model.h"
#include <map>

namespace OpenGL
{
    class RenderingManager
    {
    public:
        virtual void Render() = 0;
        virtual void Render(const Model& model) = 0;
        virtual void AddModel(const Model &model) = 0;
        virtual void RemoveModel(Model& model) = 0;
        virtual void Move(const Model& model) = 0;
        virtual bool HasModel(const Model &model) const = 0;
        ~RenderingManager() = default;
    };
}


#endif //LII_RENDERINGMANAGER_H
