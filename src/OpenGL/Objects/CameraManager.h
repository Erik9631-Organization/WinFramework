//
// Created by Erik on 13/03/22.
//

#ifndef LII_CAMERAMANAGER_H
#define LII_CAMERAMANAGER_H
#include "Camera.h"
#include <memory>
#include <vector>
#include "CameraManagerSubscriber.h"

namespace OpenGL
{
    class BasicCamera;
    class CameraManager
    {
    public:
        static void SetActiveCamera(std::unique_ptr<Camera> camera);
        static Camera * GetActiveCamera();
        static void AddSubscriber(CameraManagerSubscriber *subscriber);
        static void NotifySubscribers();
    private:
        static std::vector<CameraManagerSubscriber*>* cameraSubscribers;
        static std::unique_ptr<Camera> activeCamera;
    };
}


#endif //LII_CAMERAMANAGER_H
