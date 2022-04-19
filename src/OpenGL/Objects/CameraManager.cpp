//
// Created by Erik on 13/03/22.
//

#include "CameraManager.h"
#include "BasicCamera.h"
using namespace OpenGL;

std::unique_ptr<Camera> OpenGL::CameraManager::activeCamera = std::unique_ptr<Camera>(new BasicCamera);
std::vector<CameraManagerSubscriber*>* OpenGL::CameraManager::cameraSubscribers = new std::vector<CameraManagerSubscriber*>();

void OpenGL::CameraManager::SetActiveCamera(std::unique_ptr<OpenGL::Camera> camera)
{
    activeCamera = std::move(camera);
}

Camera * CameraManager::GetActiveCamera()
{
    return activeCamera.get();
}

void OpenGL::CameraManager::AddSubscriber(CameraManagerSubscriber *subscriber)
{
    cameraSubscribers->push_back(subscriber);
}

void OpenGL::CameraManager::NotifySubscribers()
{
    for(CameraManagerSubscriber* i : *cameraSubscribers)
        i->OnCameraChanged(*activeCamera);
}
