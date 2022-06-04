//
// Created by Erik on 20/02/22.
//

#ifndef LII_MODEL_H
#define LII_MODEL_H
#include <memory>
#include <glm.hpp>
#include "DefaultTexture.h"
#include "ShaderProgram.h"
#include "Transformable.h"
#include "Mesh.h"
#include "Clonable.h"
#include "CameraManagerSubscriber.h"
#include "MemoryMovable.h"
#include "UpdateSubscriber.h"
#include "RenderObject.h"
#include "Material.h"
#include "Identifiable.h"

class Vector3;


class ShaderProgram;

namespace OpenGL
{
    class Model : public Transformable, public Clonable<Model>, public CameraManagerSubscriber, public MemoryMovable<Model>,
                  public UpdateSubscriber, public RenderObject, public Identifiable
    {
    public:
        virtual void CustomCameraEnabled(const bool &state) = 0;
        virtual const bool& IsCustomCameraEnabled() = 0;
        virtual void SetShaderProgram(ShaderProgram *shader) = 0;
        virtual void SetDrawMode(unsigned int drawMode) = 0;
        virtual ShaderProgram & GetShader() const = 0;
        virtual void SetProjectionMatrix(glm::mat4 *projection) = 0;
        virtual void SetViewMatrix(glm::mat4 *view) = 0;
        virtual void SetTexture(Texture *texture) = 0;
        virtual const Texture* GetTexture() const = 0;
        virtual void SetMesh(Mesh *mesh) = 0;
        virtual const Mesh * GetMesh() const = 0;
        virtual const glm::mat4 & GetModelMatrix() const = 0;
        virtual const glm::mat4 & GetBasisMatrix() const = 0;
        virtual const glm::mat4 * GetViewMatrix() const = 0;
        virtual const glm::mat4 * GetProjectionMatrix() const= 0;
        virtual Material& GetMaterial() = 0;
        virtual void SetMaterial(std::unique_ptr<Material> material) = 0;
        virtual void SetCamera(const Camera *camera) = 0;
        virtual const Camera * GetCamera() = 0;
        virtual ~Model() = default;
    };
}


#endif //LII_MODEL_H
