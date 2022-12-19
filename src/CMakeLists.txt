set(PROJECT_NAME Lii)

################################################################################
# Source groups
################################################################################
set(Enums
    "Enums/EventUpdateFlags.h"
    "Enums/GraphicsScaling.h"
        Enums/FontAlignment.h Enums/Messages.h)
source_group("Lii\\Enums" FILES ${Enums})

set(Lii
    "AddSubject.h"
    "Behavior/DefaultListBoxBehavior.h"
    "DemoApplication.h"
    "api/Draggable.h"
    "DragManager.h"
    "Events/DragSubject.h"
    "Events/DragSubscriber.h"
    "DropAction.h"
    "Events/DropSubject.h"
    "Events/DropSubscriber.h"
    "EventTypes/EventOnAddInfo.h"
    "EventTypes/EventOnDragInfo.h"
    "GenericObj.h"
    "Components/Grid/GridCell.h"
    "Components/Grid/GridSpan.h"
    "Events/OnAddSubscriber.h"
    "TableElement.h"
    "Graphics/TrackbarGraphics.h"
    "AddSubject.cpp"
    "Behavior/DefaultListBoxBehavior.cpp"
    "DemoApplication.cpp"
    "DragManager.cpp"
    "Events/DragSubject.cpp"
    "Events/DragSubscriber.cpp"
    "DropAction.cpp"
    "Events/DropSubject.cpp"
    "Events/DropSubscriber.cpp"
    "EventTypes/EventOnAddInfo.cpp"
    "EventTypes/EventOnDragInfo.cpp"
    "GenericObj.cpp"
    "Components/Grid/GridCell.cpp"
    "Components/Grid/GridSpan.cpp"
    "Main.cpp"
    "Events/OnAddSubscriber.cpp"
    "TableElement.cpp"
    "Graphics/TrackbarGraphics.cpp"
        CoreMediator.cpp CoreMediator.h)
source_group("Lii" FILES ${Lii})




set(Lii_Behavior
    "Behavior/DefaultActivate.h"
    "Behavior/DefaultKeyStateBehavior.h"
    "Behavior/DefaultMouseBehavior.h"
    "Behavior/DefaultMove.h"
    "Behavior/DefaultRender.h"
    "Behavior/DefaultResize.h"
    "Behavior/RadioButtonBehavior.h"
    "Behavior/TextInputBehavior.h"
    "Behavior/Viewport.h"
    "Behavior/DefaultActivate.cpp"
    "Behavior/DefaultKeyStateBehavior.cpp"
    "Behavior/DefaultMouseBehavior.cpp"
    "Behavior/DefaultMove.cpp"
    "Behavior/DefaultRender.cpp"
    "Behavior/DefaultResize.cpp"
    "Components/Grid/Grid.cpp"
    "Components/FileBrowser/FileBrowserFactory.cpp"
    "Components/FileBrowser/LinuxFileBrowser.cpp"
    "Components/FileBrowser/WindowsFileBrowser.cpp"
    "Components/ListBox.cpp"
    "Components/Panel.cpp"
    "Behavior/RadioButtonBehavior.cpp"
    "Behavior/TextInputBehavior.cpp"
    "Behavior/Viewport.cpp"
    Behavior/VerticalScrollbarBehavior.cpp
    Behavior/VerticalScrollbarBehavior.h
        Behavior/TickSubjectBehavior.cpp Behavior/TickSubjectBehavior.h Behavior/StartSubjectBehavior.cpp Behavior/StartSubjectBehavior.h Behavior/DestroySubjectBehavior.cpp Behavior/DestroySubjectBehavior.h)

source_group("Lii\\Behavior" FILES ${Lii_Behavior})

set(Lii_Renderer
        Renderer/RenderingProvider.h
        Renderer/GdiRenderingProvider.cpp
        Renderer/Renderer.cpp
        Renderer/Renderer.h
        Renderer/GdiRenderingProvider.h
        Renderer/FontFormat.cpp
        Renderer/FontFormat.h
        Renderer/GdiRenderer.cpp
        Renderer/GdiRenderer.h
        Renderer/GdiFontFormat.cpp
        Renderer/GdiFontFormat.h
        Renderer/OpenGLRenderingProvider.cpp
        Renderer/OpenGLRenderingProvider.h
        Renderer/OpenGLRenderer.cpp
        Renderer/OpenGLRenderer.h 
        Renderer/DrawData.cpp
        Renderer/DrawData.h
        Renderer/DrawData2D.cpp
        Renderer/DrawData2D.h
        Renderer/RenderingPool.cpp
        Renderer/RenderingPool.h 
        Renderer/GdiRenderingPool.cpp
        Renderer/GdiRenderingPool.h
        Renderer/OpenGLRenderingPool.cpp
        Renderer/OpenGLRenderingPool.h
        Renderer/AsyncRenderer.cpp Renderer/AsyncRenderer.h)
source_group("Lii\\Renderer" FILES ${Lii_Renderer})


set(Lii_Api
        api/Translatable.h
        api/Rotatable.h
        api/Rotatable.h
        api/Transformable.h
        api/RenderSubscriber.h
        api/Activatable.h
        api/Adjustable.h
        api/Collidable.h
        api/MouseInteractable.h
        api/Movable.h
        api/RenderCommander.h
        api/Resizable.h
        api/Viewable.h
        api/Scalable.h
        api/RenderObjectSubscriber.h
        api/RelativeMovement.h
        api/Clonable.h
        api/MemoryMovable.h
        api/Clonable.h
        api/TextureManager.h
        api/MeshManager.h
        api/Texture.h
        api/ShaderManager.h
        api/ResourceManager.h
        api/ShaderManager.h
        api/RendererProxy.h
        api/MeshManager.h api/Light.h api/CoreSubject.h api/PresenterSubscriber.h api/PresentationSubject.h api/Presenter.h api/Core.h api/PresenterSubject.h api/Factory.h api/MountedSubject.h api/MountedSubscriber.h api/AsyncRenderingProvider.h api/RenderingConsumer.h)
source_group("Lii/api" FILES ${Lii_Api})


set(Lii_Components
    "Components/Button.h"
    "Components/Checkbox.h"
    "Components/FileBrowser/FileBrowser.h"
    "Components/FileBrowser/FileBrowserFactory.h"
    "Components/FileBrowser/LinuxFileBrowser.h"
    "Components/FileBrowser/WindowsFileBrowser.h"
    "Components/UiElement.h"
    "Core/Windows/WindowsCore.h"
    "Components/Grid/Grid.h"
    "Components/Label.h"
    "Components/ListBox.h"
    "Components/Panel.h"
    "Components/PasswordField.h"
    "Components/RadioButton.h"
    "Components/Reflectable.h"
    "Components/ReflectionContainer.h"
    "Components/TextInput.h"
    "Components/Window.h"
    "Components/Button.cpp"
    "Components/Checkbox.cpp"
    "Components/UiElement.cpp"
    "Core/Windows/WindowsCore.cpp"
    "Components/Label.cpp"
    "Components/PasswordField.cpp"
    "Components/RadioButton.cpp"
    "Components/Reflectable.cpp"
    "Components/ReflectionContainer.cpp"
    "Components/TextInput.cpp"
    "Components/Window.cpp"
    Components/ScrollBar/ScrollBar.cpp
    Components/ScrollBar/ScrollBar.h
    OnAddHandler.h
        )
source_group("Lii\\Components" FILES ${Lii_Components})

Set(Lii_Core_Windows
        "Core/Windows/WindowsCore.h"
        "Core/Windows/WindowsCore.cpp"
        Core/Windows/CoreArgs.cpp Core/Windows/CoreArgs.h)
source_group("Lii\\Core\\Windows" FILES ${Lii_Core_Windows})

set(Lii_Components_3d

        Components/3d/ModeledElement.cpp Components/3d/ModeledElement.h Components/3d/Element3d.h Components/3d/Scene.cpp Components/3d/Scene.h Components/3d/PointLight.cpp Components/3d/PointLight.h Components/3d/DirectionalLight.h Components/3d/DirectionalLight.cpp)
source_group("Lii\\Components\\3d" FILES ${Lii_Components_3d})

set(Lii_Components_ComboBox

)
source_group("Lii\\Components\\ComboBox" FILES ${Lii_Components_ComboBox})


set(Lii_DataTypes
        DataTypes/DefaultMultiTree.h
    DataTypes/MultiTree.h
        DataTypes/DefaultMultiTree.cpp
    DataTypes/MultiTree.cpp
    DataTypes/Vector3.cpp
    DataTypes/Vector3.h
    DataTypes/Vector4.cpp
    DataTypes/Vector4.h
    DataTypes/Vector2Int.cpp
    DataTypes/Vector2Int.h
)
source_group("Lii\\DataTypes" FILES ${Lii_DataTypes})


set(Lii_Events
    "Events/ActivateSubject.h"
    "Events/ActivateSubscriber.h"
    "Events/CheckboxStateSubject.h"
    "Events/CheckboxStateSubscriber.h"
    "Events/ComboBoxStateSubscriber.h"
    "Events/KeyStateSubject.h"
    "Events/KeyStateSubscriber.h"
    "Events/MouseStateSubject.h"
    "Events/MouseStateSubscriber.h"
    "Events/MoveSubject.h"
    "Events/MoveSubscriber.h"
    "Events/RadioButtonStateSubject.h"
    "Events/RadioButtonStateSubscriber.h"
    "Events/ResizeSubject.h"
    "Events/ResizeSubscriber.h"
    "Events/UpdateSubject.h"
    "Events/UpdateSubscriber.h"
    "Events/ActivateSubject.cpp"
    "Events/ActivateSubscriber.cpp"
    "Events/CheckboxStateSubject.cpp"
    "Events/CheckboxStateSubscriber.cpp"
    "Events/ComboBoxStateSubscriber.cpp"
    "Events/KeyStateSubject.cpp"
    "Events/KeyStateSubscriber.cpp"
    "Events/MouseStateSubject.cpp"
    "Events/MouseStateSubscriber.cpp"
    "Events/MoveSubject.cpp"
    "Events/MoveSubscriber.cpp"
    "Events/RadioButtonStateSubject.cpp"
    "Events/RadioButtonStateSubscriber.cpp"
        "Events/ResizeSubject.cpp"
    "Events/ResizeSubscriber.cpp"
    "Events/UpdateSubject.cpp"
    Events/TimerSubject.cpp
    Events/TimerSubject.h
    Events/OnTickSubscriber.h
    Events/TickSubject.h
    Events/RenderObjectEventInfo.cpp
    Events/RenderObjectEventInfo.h
    Events/DestroySubject.h
    Events/DestroySubscriber.h
        Events/OnStartSubject.h)

source_group("Lii\\Events" FILES ${Lii_Events})


set(Lii_EventTypes
    "EventTypes/EventCheckboxStateInfo.h"
    "EventTypes/EventComboBoxStateInfo.h"
    "EventTypes/EventInfo.h"
    "EventTypes/EventKeyStateInfo.h"
    "EventTypes/EventMouseStateInfo.h"
    "EventTypes/EventMoveInfo.h"
    "EventTypes/EventOnActivateInfo.h"
    "EventTypes/EventRadioButtonStateInfo.h"
    "EventTypes/EventResizeInfo.h"
    "EventTypes/EventUpdateInfo.h"
    "EventTypes/RenderEventInfo.h"
    "EventTypes/EventCheckboxStateInfo.cpp"
    "EventTypes/EventComboBoxStateInfo.cpp"
    "EventTypes/EventInfo.cpp"
    "EventTypes/EventKeyStateInfo.cpp"
    "EventTypes/EventMouseStateInfo.cpp"
    "EventTypes/EventMoveInfo.cpp"
    "EventTypes/EventOnActivateInfo.cpp"
    "EventTypes/EventRadioButtonStateInfo.cpp"
    "EventTypes/EventResizeInfo.cpp"
    "EventTypes/EventUpdateInfo.cpp"
    "EventTypes/RenderEventInfo.cpp"
    EventTypes/EventOnTimerElapsed.cpp
    EventTypes/EventOnTimerElapsed.h
    EventTypes/DestroyEventInfo.cpp
    EventTypes/DestroyEventInfo.h
        EventTypes/EventAttributeInfo.cpp EventTypes/EventAttributeInfo.h)

source_group("Lii\\EventTypes" FILES ${Lii_EventTypes})


set(Lii_Graphics
    "Graphics/Background.h"
    "Graphics/CircleBackground.h"
    "Graphics/CircleBorder.h"
    "Graphics/RadioButtonGraphics.h"
    "Graphics/SimpleBorder.h"
    "Graphics/Text.h"
    "Graphics/TestGraphics.h"
    "Graphics/Background.cpp"
    "Graphics/CircleBackground.cpp"
    "Graphics/CircleBorder.cpp"
    "Graphics/RadioButtonGraphics.cpp"
    "Graphics/SimpleBorder.cpp"
    "Graphics/Text.cpp"
    "Graphics/TestGraphics.cpp"
        )
source_group("Lii\\Graphics" FILES ${Lii_Graphics})


set(Lii_GraphicalStates
    "GraphicalStates/DefaultButtonBehavior.h"
    "GraphicalStates/CheckboxBehavior.h"
    "GraphicalStates/DefaultButtonBehavior.cpp"
    "GraphicalStates/CheckboxBehavior.cpp"
)

source_group("Lii\\GraphicalStates" FILES ${Lii_GraphicalStates})


set(Lii_MetaObjects
    "MetaObjects/ClassMethod.h"
    "MetaObjects/Field.h"
    "MetaObjects/Primitive.h"
        "MetaObjects/ClassMethod.cpp"
        "MetaObjects/Field.cpp"
        "MetaObjects/Primitive.cpp"
)

source_group("Lii\\Meta Objects" FILES ${Lii_MetaObjects})


set(Lii_Utils
    "Utils/AccessTools.h"
    "Utils/ApplicationController.h"
    "Utils/InputManager.h"
        "Utils/AccessTools.cpp"
    "Utils/ApplicationController.cpp"
    "Utils/InputManager.cpp"
    Utils/Vector2DScaler.cpp
    Utils/Vector2DScaler.h
        Utils/ScalingUtil.cpp
    Utils/ScalingUtil.h
        Utils/Timer.cpp
    Utils/Timer.h
        Events/TimerSubscriber.cpp
    Events/TimerSubscriber.h
        Utils/Hash.cpp Utils/Hash.h Utils/AutoId.cpp Utils/AutoId.h Utils/IdManager.cpp Utils/IdManager.h Utils/WindowBuilder.cpp Utils/WindowBuilder.h Utils/Managers/RenderingProviderManager.cpp Utils/Managers/RenderingProviderManager.h)
source_group("Lii\\Utils" FILES ${Lii_Utils})

set(Lii_Utils_Managers
        "Utils/Managers/RenderingProviderManager.cpp"
        "Utils/Managers/RenderingProviderManager.h"
        Utils/Managers/CoreManager.cpp Utils/Managers/CoreManager.h)

source_group("Lii\\Utils\\Managers" FILES ${Lii_Utils_Managers})

set(Lii_Utils_Factories
        Utils/Factories/GdiRenderingProviderFactory.cpp
        Utils/Factories/GdiRenderingProviderFactory.h
        Utils/Factories/OpenGLRenderingProviderFactory.cpp
        Utils/Factories/OpenGLRenderingProviderFactory.h
        Utils/Factories/CoreFactory.cpp Utils/Factories/CoreFactory.h)
source_group("Lii\\Utils\\Factory" FILES ${Lii_Utils_Factories}

)


set(Lii_OpenGL
        OpenGL/Shader.h 
        OpenGL/GraphicsShader.cpp
        OpenGL/GraphicsShader.h
        api/ShaderProgram.h
        OpenGL/DefaultShaderProgram.cpp
        OpenGL/DefaultShaderProgram.h
        api/Mesh.h OpenGL/StaticMesh.cpp
        OpenGL/StaticMesh.h OpenGL/Uniform.h
        OpenGL/UniformProperties.h
        OpenGL/ShapeBuilder.cpp
        OpenGL/ModelBuilder.h
        OpenGL/DefaultTexture.cpp
        OpenGL/StaticTexture.h
        api/Resource.h
        OpenGL/DefaultVertexAttribute.cpp
        OpenGL/DefaultVertexAttribute.h
        OpenGL/VertexArrayObjectPool.h
        OpenGL/DefaultGpuMemoryAllocator.cpp
        OpenGL/DefaultGpuMemoryAllocator.h
        api/Taggable.h
        OpenGL/GpuMemoryAllocator.h
        OpenGL/MemoryAllocatorManager.cpp
        OpenGL/MemoryAllocatorManager.h
        OpenGL/VertexAttributeGroup.cpp
        OpenGL/VertexAttributeGroup.h
        OpenGL/VertexAttribute.h
        OpenGL/Identifiable.h
        OpenGL/RenderingManager.h
        OpenGL/DefaultRenderingManager.cpp
        OpenGL/DefaultRenderingManager.h
        OpenGL/RenderObject.h
        OpenGL/Hashable.h
        OpenGL/RenderingPriorities.h
        OpenGL/GpuMemoryStrategy.h OpenGL/RenderObjectSubject.h OpenGL/GpuMemoryStrategySubscriber.h)
source_group("Lii\\OpenGL" FILES ${Lii_OpenGL})

set(Lii_Sync
        Sync/UiTreeDataSyncer.cpp
        Sync/UiTreeDataSyncer.h
        Sync/Element3dDataSyncer.cpp Sync/Element3dDataSyncer.h)
source_group("Lii\\Sync" FILES ${Lii_Sync})

set(Lii_Objects
        OpenGL/Objects/Model.h 
        OpenGL/Objects/DefaultModel.cpp
        OpenGL/Objects/DefaultModel.h 
        OpenGL/Objects/Camera.h 
        OpenGL/Objects/BasicCamera.h 
        OpenGL/Objects/BasicCamera.cpp 
        OpenGL/Objects/CameraManager.cpp 
        OpenGL/Objects/CameraManager.h 
        OpenGL/Objects/CameraManagerSubscriber.h
    )

source_group("Lii/OpenGL/Objects" FILES ${Lii_Objects})

set(Lii_Shaders
        "Shaders/default.frag"
        "Shaders/default.vert"
)
source_group("Lii/Shaders" FILES ${Lii_Shaders})

set (Lii_Materials
        Materials/Material.cpp
        Materials/Material.h
)
source_group("Lii/Materials" FILES ${Lii_Materials})


set (Lii_Managers
        Managers/GlobalResourceManager.cpp
        Managers/GlobalResourceManager.h)
source_group("Lii/Managers" FILES ${Lii/Managers})

set(Lii_Tests
        Tests/OnMountedTest.hpp
)
source_group("Lii/Tests" FILES ${Lii_Tests})

set(Lii_Renderer_Renderers
        Renderer/Renderers/EllipseProxy.cpp
        Renderer/Renderers/EllipseProxy.h Renderer/Renderers/RectangleProxy.cpp Renderer/Renderers/RectangleProxy.h Renderer/Renderers/LineProxy.cpp Renderer/Renderers/LineProxy.h Renderer/Renderers/TextProxy.cpp Renderer/Renderers/TextProxy.h)
source_group(Lii/Renderer/Renderers FILES ${Lii_Renderer_Renderers})

set(Lii_Renderer_Messaging

        Renderer/Messaging/RenderMessage.h Renderer/Messaging/MessageIds.h)
source_group(Lii/Renderer/Messaging FILES ${Lii_Renderer_Messaging})

set(Lii_Renderer_Models
        Renderer/Messaging/RenderMessage.h
        Renderer/Models/RectangleModel.cpp Renderer/Models/RectangleModel.h Renderer/Models/Model.h)
source_group(Lii/Renderer/Models FILES ${Lii_Renderer_Models})

set(Lii_Renderer_Models_Behavior
        Renderer/Models/Behavior/MovableModelBehavior.cpp Renderer/Models/Behavior/MovableModelBehavior.h Renderer/Models/Behavior/ResizableModelBehavior.cpp Renderer/Models/Behavior/ResizableModelBehavior.h)
source_group(Lii/Renderer/Models/Behavior FILES ${Lii_Renderer_Models_Behavior})


set(ALL_FILES
    ${Enums}
    ${Lii}
    ${Lii_Renderer}
    ${Lii_Behavior}
    ${Lii_Components}
    ${Lii_Components_ComboBox}
    ${Lii_Core_Windows}
    ${Lii_DataTypes}
    ${Lii_Events}
    ${Lii_EventTypes}
    ${Lii_Graphics}
    ${Lii_GraphicalStates}
    ${Lii_MetaObjects}
    ${Lii_Utils}
    ${Lii_OpenGL}
    ${Lii_Sync}
    ${Lii_Objects}
    ${Lii_Shaders}
    ${Lii_Materials}
    ${Lii_Api}
    ${Lii_Managers}
    ${Lii_Components_3d}
    ${Lii_Utils_Managers}
    ${Lii_Utils_Factories}
    ${Lii_Tests}
    ${Lii_Renderer_Renderers}
    ${Lii_Renderer_Messaging}
    ${Lii_Renderer_Models}
    ${Lii_Renderer_Models_Behavior}
        api/CoreSubscriber.h EventTypes/EventRenderingProviderInfo.cpp EventTypes/EventRenderingProviderInfo.h EventTypes/EventCursorLockInfo.cpp EventTypes/EventCursorLockInfo.h api/MountedSubject.h Tests/DemoAppTest.hpp)

################################################################################
# Target
################################################################################

add_executable(${PROJECT_NAME} ${ALL_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE
        .
        "Behavior/"
        "api/"
        "Components/"
        "Components/Grid"
        "Components/FileBrowser/"
        "DataTypes/"
        "Events/"
        "EventTypes/"
        "GraphicalStates/"
        "Graphics/"
        "MetaObjects/"
        "Utils/"
        "Enums/"
        "Components/ScrollBar"
        "Renderer"
        "Renderer/Renderers"
        "OpenGL/"
        "Sync/"
        "OpenGL/Objects"
        "Materials/"
        "../libs/glew/include/gl"
        "../libs/glm"
        "../libs/stb"
        "Managers/"
        "Components/3d"
        "../libs/PhysX-4.1/physx/include/"
        "Core/Windows"
        "Utils/Managers"
        "Utils/Factories"
        "Tests"
        "Renderer/Messaging"
        "Renderer/Models/Behavior"
        )

target_link_libraries(${PROJECT_NAME}
        stb
        opengl32
        PhysXSDK
        catch2Lib
        "${CMAKE_SOURCE_DIR}/libs/glew/glew32.lib"
        "${CMAKE_SOURCE_DIR}/libs/glew/glew32s.lib"
        MemoryManagerLib
        )