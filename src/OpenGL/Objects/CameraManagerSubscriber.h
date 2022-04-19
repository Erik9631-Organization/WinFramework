//
// Created by Erik on 13/03/22.
//

#ifndef LII_CAMERAMANAGERSUBSCRIBER_H
#define LII_CAMERAMANAGERSUBSCRIBER_H

#include "Camera.h"

namespace OpenGL
{
    class Camera;
    class CameraManagerSubscriber
    {
    public:
        virtual void OnCameraChanged(const Camera &newCamera) = 0;
    };
}


#endif //LII_CAMERAMANAGERSUBSCRIBER_H
