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
    "DragManager.h"
    "DropAction.h"
    "EventInfo/EventOnAddInfo.h"
    "EventInfo/EventOnDragInfo.h"
    "GenericObj.h"
    "Components/Grid/GridCell.h"
    "Components/Grid/GridSpan.h"
    "TableElement.h"
    "Graphics/TrackbarGraphics.h"
    "AddSubject.cpp"
    "Behavior/DefaultListBoxBehavior.cpp"
    "DemoApplication.cpp"
    "DragManager.cpp"
        "DropAction.cpp"
        "EventInfo/EventOnDragInfo.cpp"
    "GenericObj.cpp"
    "Components/Grid/GridCell.cpp"
    "Components/Grid/GridSpan.cpp"
    "Main.cpp"
        "TableElement.cpp"
    "Graphics/TrackbarGraphics.cpp"
    CoreMediator.cpp
    CoreMediator.h
        )
source_group("Lii" FILES ${Lii})




set(Lii_Behavior
    "Behavior/DefaultActivate.h"
    "Behavior/DefaultKeyStateBehavior.h"
    "Behavior/DefaultMouseBehavior.h"
    "Behavior/UiMoveBehavior.h"
    "Behavior/DefaultRender.h"
    "Behavior/DefaultResize.h"
    "Behavior/RadioButtonBehavior.h"
    "Behavior/TextInputBehavior.h"
        "Behavior/DefaultActivate.cpp"
    "Behavior/DefaultKeyStateBehavior.cpp"
    "Behavior/DefaultMouseBehavior.cpp"
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
        Behavior/VerticalScrollbarBehavior.cpp
    Behavior/VerticalScrollbarBehavior.h
        Behavior/TickSubjectBehavior.cpp Behavior/TickSubjectBehavior.h Behavior/StartSubjectBehavior.cpp Behavior/StartSubjectBehavior.h Behavior/CoreLifecycleBehavior.cpp Behavior/CoreLifecycleBehavior.h)

source_group("Lii\\Behavior" FILES ${Lii_Behavior})

set(Lii_Renderer
        Renderer/Renderer.h
        Renderer/GdiRenderer.cpp
        Renderer/ShapeRenderer.h
        Renderer/GdiRenderer.h
        Renderer/FontFormat.h
        Renderer/GdiShapeRenderer.cpp
        Renderer/GdiShapeRenderer.h
        Renderer/GdiFontFormat.cpp
        Renderer/GdiFontFormat.h
        Renderer/OpenGLRenderer.cpp
        Renderer/OpenGLRenderer.h
        Renderer/OpenGLShapeRenderer.cpp
        Renderer/OpenGLShapeRenderer.h
        Renderer/DrawData.cpp
        Renderer/DrawData.h
        Renderer/DrawData2D.cpp
        Renderer/DrawData2D.h
        Renderer/RenderingPool.h
        Renderer/GdiRenderingPool.cpp
        Renderer/GdiRenderingPool.h
        Renderer/OpenGLRenderingPool.cpp
        Renderer/OpenGLRenderingPool.h
        Renderer/DefaultAsyncRenderCommandHandler.cpp Renderer/DefaultAsyncRenderCommandHandler.h Renderer/BufferRenderer.h Renderer/RenderingBase.h Renderer/SoftwareRenderer.cpp Renderer/SoftwareRenderer.h Renderer/ConcurrentShapeRenderer.cpp Renderer/ConcurrentShapeRenderer.h Renderer/WindowsBufferRenderer.cpp Renderer/WindowsBufferRenderer.h Renderer/AggShapeRenderer.cpp Renderer/AggShapeRenderer.h Renderer/AggFontFormat.cpp Renderer/AggFontFormat.h)
source_group("Lii\\Renderer" FILES ${Lii_Renderer})

set(Lii_Renderer_WindowsBufferRenderer
        Renderer/WindowsBufferRenderer/BitmapManager.cpp Renderer/WindowsBufferRenderer/BitmapManager.h)
source_group("Lii\\Renderer\\WindowsBufferRenderer" FILES ${Lii_Renderer_WindowsBufferRenderer})


set(Lii_Api
        Api/Translatable.h
        Api/Rotatable.h
        Api/Rotatable.h
        Api/Transformable.h
        Api/RenderSubscriber.h
        Api/Activatable.h
        Api/Adjustable.h
        Api/Collidable.h
        Api/MouseInteractable.h
        Api/Movable.h
        Api/RenderCommander.h
        Api/Resizable.h
        Api/Viewable.h
        Api/Scalable.h
        Api/RenderObjectSubscriber.h
        Api/RelativeMovement.h
        Api/Clonable.h
        Api/MemoryMovable.h
        Api/Clonable.h
        Api/TextureManager.h
        Api/MeshManager.h
        Api/Texture.h
        Api/ShaderManager.h
        Api/ResourceManager.h
        Api/ShaderManager.h
        Api/RenderProxy.h
        Api/RenderMessageSender.h
        Api/MeshManager.h
        Api/Light.h
        Api/CoreSubject.h
        Api/PresenterSubscriber.h
        Api/PresentationSubject.h
        Api/Presenter.h
        Api/Core.h
        Api/PresenterSubject.h
        Api/Factory.h
        Api/MountedSubject.h
        Api/MountedSubscriber.h
        Api/AsyncRenderCommandHandler.h
        Api/RenderingConsumer.h
        )
source_group("Lii/api" FILES ${Lii_Api})

set(Lii_Api_Events
        "Api/Events/ActivateSubject.h"
        "Api/Events/ActivateSubscriber.h"
        "Api/Events/CheckboxStateSubject.h"
        "Api/Events/CheckboxStateSubscriber.h"
        "Api/Events/ComboBoxStateSubscriber.h"
        "Api/Events/KeyStateSubject.h"
        "Api/Events/KeyStateSubscriber.h"
        "Api/Events/MouseStateSubject.h"
        "Api/Events/MouseStateSubscriber.h"
        "Api/Events/MoveSubject.h"
        "Api/Events/MoveSubscriber.h"
        "Api/Events/RadioButtonStateSubject.h"
        "Api/Events/RadioButtonStateSubscriber.h"
        "Api/Events/ResizeSubject.h"
        "Api/Events/ResizeSubscriber.h"
        "Api/Events/UpdateSubject.h"
        "Api/Events/UpdateSubscriber.h"
        Api/Events/TimerSubject.h
        Api/Events/OnTickSubscriber.h
        Api/Events/TickSubject.h
        Api/Events/OnStartSubject.h
        "Api/Events/DragSubject.h"
        "Api/Events/DragSubscriber.h"
        "Api/Events/DropSubject.h"
        "Api/Events/DropSubscriber.h"
        "Api/Draggable.h"
        "Api/Events/OnAddSubscriber.h"
        Api/Events/ViewportSubject.h Api/Events/EventSource.h Api/Events/CoreLifecycleSubject.h Api/Events/CoreLifecycleSubscriber.h)
source_group("Lii\\api\\Events" FILES ${Lii_Api_Events})


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

Set(Lii_Components_api
        Components/api/TextInputApi.h)
source_group("Lii\\Components\\api" FILES ${Lii_Components_api})

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
    DataTypes/MultiTree.cpp DataTypes/IRectangle.h DataTypes/Rectangle.h DataTypes/Line.cpp DataTypes/Line.h DataTypes/ILine.cpp DataTypes/ILine.h DataTypes/Buffer.h)
source_group("Lii\\DataTypes" FILES ${Lii_DataTypes})


set(Lii_EventInfo
    "EventInfo/EventCheckboxStateInfo.h"
    "EventInfo/EventComboBoxStateInfo.h"
        "EventInfo/EventKeyStateInfo.h"
    "EventInfo/EventMouseStateInfo.h"
    "EventInfo/EventMoveInfo.h"
    "EventInfo/EventOnActivateInfo.h"
    "EventInfo/EventRadioButtonStateInfo.h"
    "EventInfo/EventResizeInfo.h"
    "EventInfo/EventUpdateInfo.h"
    "EventInfo/RenderEventInfo.h"
    "EventInfo/EventCheckboxStateInfo.cpp"
    "EventInfo/EventComboBoxStateInfo.cpp"
        "EventInfo/EventKeyStateInfo.cpp"
    "EventInfo/EventMouseStateInfo.cpp"
    "EventInfo/EventMoveInfo.cpp"
    "EventInfo/EventOnActivateInfo.cpp"
    "EventInfo/EventRadioButtonStateInfo.cpp"
    "EventInfo/EventResizeInfo.cpp"
    "EventInfo/EventUpdateInfo.cpp"
    "EventInfo/RenderEventInfo.cpp"
    EventInfo/EventOnTimerElapsed.cpp
    EventInfo/EventOnTimerElapsed.h
        EventInfo/EventAttributeInfo.cpp
    EventInfo/EventAttributeInfo.h
        EventInfo/ViewportEventInfo.h
    EventInfo/RenderObjectEventInfo.cpp
    EventInfo/RenderObjectEventInfo.h
        EventInfo/Event.h EventInfo/EventCoreLifecycleInfo.cpp EventInfo/EventCoreLifecycleInfo.h)

source_group("Lii\\EventInfo" FILES ${Lii_EventInfo})


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
    Graphics/Border.cpp
    Graphics/Border.h
    Graphics/DefaultRelativeZIndex.h
    Graphics/DefaultRelativeZIndex.cpp)
source_group("Lii\\Graphics" FILES ${Lii_Graphics})

set(Lii_Graphics_RadioButton
    "Graphics/RadioButtonGraphics.h"
    "Graphics/RadioButtonGraphics.cpp" Graphics/RadioButton/RadioCircle.cpp Graphics/RadioButton/RadioCircle.h)
source_group("Lii\\Graphics\\RadioButton" FILES ${Lii_Graphics_RadioButton})

set(Lii_Graphics_Checkbox
        Graphics/Checkbox/CheckboxGraphics.cpp Graphics/Checkbox/CheckboxGraphics.h)
source_group("Lii\\Graphics\\Checkbox" FILES ${Lii_Graphics_Checkbox})

set(Lii_Graphics_api

        Api/Viewport.h Api/Events/ViewportSubscriber.h)
source_group("Lii\\Graphics\\api" FILES ${Lii_Graphics_api})

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
        "Utils/LiiApplication.h"
    "Utils/InputManager.h"
        "Utils/LiiApplication.cpp"
    "Utils/InputManager.cpp"
    Utils/Vector2DScaler.cpp
    Utils/Vector2DScaler.h
        Utils/ScalingUtil2D.cpp
        Utils/ScalingUtil2D.h
        Utils/Timer.cpp
    Utils/Timer.h
        Api/Events/TimerSubscriber.h
        Utils/Hash.cpp Utils/Hash.h
        Utils/AutoId.cpp
        Utils/AutoId.h
        Utils/IdManager.cpp
        Utils/IdManager.h
        Utils/WindowBuilder.cpp
        Utils/WindowBuilder.h
        Utils/RenderingProxyMessageSender.cpp
        Utils/RenderingProxyMessageSender.h
        Utils/Utils.h Utils/Utils.cpp
        Ssd/DisplayPacketSerializer.cpp
        Ssd/DisplayPacketSerializer.h)
source_group("Lii\\Utils" FILES ${Lii_Utils})

set(Lii_OpenGL
        OpenGL/Shader.h 
        OpenGL/GraphicsShader.cpp
        OpenGL/GraphicsShader.h
        Api/ShaderProgram.h
        OpenGL/DefaultShaderProgram.cpp
        OpenGL/DefaultShaderProgram.h
        Api/Mesh.h OpenGL/StaticMesh.cpp
        OpenGL/StaticMesh.h OpenGL/Uniform.h
        OpenGL/UniformProperties.h
        OpenGL/ShapeBuilder.cpp
        OpenGL/ModelBuilder.h
        OpenGL/DefaultTexture.cpp
        OpenGL/StaticTexture.h
        Api/Resource.h
        OpenGL/DefaultVertexAttribute.cpp
        OpenGL/DefaultVertexAttribute.h
        OpenGL/VertexArrayObjectPool.h
        OpenGL/DefaultGpuMemoryAllocator.cpp
        OpenGL/DefaultGpuMemoryAllocator.h
        Api/Taggable.h
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
        Renderer/Proxies/EllipseProxy.cpp
        Renderer/Proxies/EllipseProxy.h Renderer/Proxies/RectangleProxy.cpp Renderer/Proxies/RectangleProxy.h Renderer/Proxies/LineProxy.cpp Renderer/Proxies/LineProxy.h Renderer/Proxies/TextProxy.cpp Renderer/Proxies/TextProxy.h Renderer/Proxies/ModelProxy.cpp Renderer/Proxies/ModelProxy.h)
source_group(Lii/Renderer/Renderers FILES ${Lii_Renderer_Renderers})

set(Lii_Renderer_Messaging

        Renderer/Messaging/RenderMessage.h Renderer/Messaging/Commands.h Renderer/Messaging/MessageGenerateModel.h)
source_group(Lii/Renderer/Messaging FILES ${Lii_Renderer_Messaging})

set(Lii_Renderer_Models
        Renderer/Messaging/RenderMessage.h
        Renderer/Models/RectangleModel.cpp
        Renderer/Models/RectangleModel.h
        Renderer/Models/RenderingModel.h Renderer/Models/LineModel.cpp Renderer/Models/LineModel.h Renderer/Models/TextModel.cpp Renderer/Models/TextModel.h Renderer/Models/EllipseModel.cpp Renderer/Models/EllipseModel.h Renderer/Models/ModelContainer.cpp Renderer/Models/ModelContainer.h)
source_group(Lii/Renderer/Models FILES ${Lii_Renderer_Models})

set(Lii_Renderer_Models_Behavior
        Renderer/Models/Behavior/MovableModelBehavior.cpp
        Renderer/Models/Behavior/MovableModelBehavior.h
        Renderer/Models/Behavior/ResizableModelBehavior.cpp
        Renderer/Models/Behavior/ResizableModelBehavior.h
)
source_group(Lii/Renderer/Models/Behavior FILES ${Lii_Renderer_Models_Behavior})

set(Lii_Renderer_Models_Viewports
        Renderer/Models/Viewports/DefaultViewport.cpp
        Renderer/Models/Viewports/DefaultViewport.h
        Ssd/DisplayPacketSerializer.cpp
        Ssd/DisplayPacketSerializer.h
)
source_group(Lii/Renderer/Models/Viewports FILES ${Lii_Renderer_Models_Viewports})

set(Lii_Ssd
        Ssd/DisplayPacketSerializer.cpp
        Ssd/DisplayPacketSerializer.h
        Ssd/Position.h
        Ssd/Position.cpp
)
source_group(Lii/Ssd FILES ${Lii_Ssd})

set(ALL_FILES
    ${Enums}
    ${Lii}
    ${Lii_Renderer}
    ${Lii_Renderer_WindowsBufferRenderer}
    ${Lii_Behavior}
    ${Lii_Components}
    ${Lii_Components_ComboBox}
    ${Lii_Components_api}
    ${Lii_Core_Windows}
    ${Lii_DataTypes}
    ${Lii_EventInfo}
    ${Lii_Graphics}
    ${Lii_Graphics_RadioButton}
    ${Lii_Graphics_Checkbox}
    ${Lii_Graphics_api}
    ${Lii_GraphicalStates}
    ${Lii_MetaObjects}
    ${Lii_Utils}
    ${Lii_OpenGL}
    ${Lii_Sync}
    ${Lii_Objects}
    ${Lii_Shaders}
    ${Lii_Materials}
    ${Lii_Api}
    ${Lii_Api_Events}
    ${Lii_Managers}
    ${Lii_Components_3d}
    ${Lii_Tests}
    ${Lii_Renderer_Renderers}
    ${Lii_Renderer_Messaging}
    ${Lii_Renderer_Models}
    ${Lii_Renderer_Models_Behavior}
    ${Lii_Renderer_Models_Viewports}
    ${Lii_Ssd}
        Api/CoreSubscriber.h EventInfo/EventRenderingProviderInfo.h EventInfo/EventCursorLockInfo.cpp EventInfo/EventCursorLockInfo.h Api/MountedSubject.h Tests/DemoAppTest.hpp Graphics/Text2.cpp Graphics/Text2.h Renderer/api/TextApi.h Graphics/Checkbox/CheckboxGraphics.cpp Graphics/Checkbox/CheckboxGraphics.h Components/api/TextInputApi.h
        Ssd/DisplayPacketSerializer.cpp
        Ssd/DisplayPacketSerializer.h)


################################################################################
# Target
################################################################################

add_executable(${PROJECT_NAME} ${ALL_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE
        .
        "Behavior/"
        "Api/"
        "Components/"
        "Components/Grid"
        "Components/FileBrowser/"
        "Components/api/"
        "DataTypes/"
        "Api/Events/"
        "EventInfo/"
        "GraphicalStates/"
        "Graphics/"
        "Graphics/api/"
        "MetaObjects/"
        "Utils/"
        "Enums/"
        "Components/ScrollBar"
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
        "Renderer/Models"
        "Renderer/Models/Behavior"
        "Renderer/Models/Viewports"
        "Renderer/WindowsBufferRenderer"
        "Renderer"
        "Renderer/Proxies"
        "Graphics/RadioButton"
        "Graphics/Checkbox"
        "Lii/Ssd"
        )
