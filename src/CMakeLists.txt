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
    "Events/ComboBoxStateSubject.h"
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
    "Events/ComboBoxStateSubject.cpp"
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
        )
source_group("Lii" FILES ${Lii})




set(Lii_Behavior
    "Behavior/DefaultActivate.h"
    "Behavior/DefaultComboBoxBehavior.h"
    "Behavior/DefaultKeyStateBehavior.h"
    "Behavior/DefaultMouseBehavior.h"
    "Behavior/DefaultMove.h"
    "Behavior/DefaultRender.h"
    "Behavior/DefaultResize.h"
    "Behavior/RadioButtonBehavior.h"
    "Behavior/TextInputBehavior.h"
    "Behavior/Viewport.h"
    "Components/ComboBox/ComboBox.cpp"
    "Components/ComboBox/ComboElement.cpp"
    "Behavior/DefaultActivate.cpp"
    "Behavior/DefaultComboBoxBehavior.cpp"
    "Behavior/DefaultKeyStateBehavior.cpp"
    "Behavior/DefaultMouseBehavior.cpp"
    "Behavior/DefaultMove.cpp"
    "Behavior/DefaultRender.cpp"
    "Behavior/DefaultResize.cpp"
    "Components/FileBrowser.cpp"
    "Components/Grid/Grid.cpp"
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
        Renderer/RenderingProvider.cpp
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
)
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
        api/MeshManager.h)
source_group("Lii/api" FILES ${Lii_Api})


set(Lii_Components
    "Components/Button.h"
    "Components/Checkbox.h"
    "Components/UiElement.h"
    "Components/CoreWindow.h"
    "Components/FileBrowser.h"
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
    "Components/CoreWindow.cpp"
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

set(Lii_Components_3d

        Components/3d/ModeledElement.cpp Components/3d/ModeledElement.h Components/3d/Element3d.h Components/3d/Scene.cpp Components/3d/Scene.h)
source_group("Lii\\Components\\3d" FILES ${Lii_Components_3d})

set(Lii_Components_ComboBox
    Components/ComboBox/ComboBox.h
    Components/ComboBox/ComboElement.h
    Components/ComboBox/ComboSelection.h
    Components/ComboBox/ComboSelection.cpp
)
source_group("Lii\\Components\\ComboBox" FILES ${Lii_Components_ComboBox})


set(Lii_DataTypes
    DataTypes/CastableTree.h
    DataTypes/DefaultMultiTree.h
    DataTypes/MultiTree.h
    DataTypes/CastableTree.cpp
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
    "Events/RenderableSubscriber.cpp"
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
)

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
    "Utils/WinWrapper.h"
    "Utils/AccessTools.cpp"
    "Utils/ApplicationController.cpp"
    "Utils/InputManager.cpp"
    Utils/Vector2DScaler.cpp
    Utils/Vector2DScaler.h
    DataTypes/Vector2.cpp DataTypes/Vector2.h
    Utils/ScalingUtil.cpp
    Utils/ScalingUtil.h
    Utils/ValueConverter.cpp
    Utils/ValueConverter.h
    Utils/Timer.cpp
    Utils/Timer.h
    Utils/ValueConverter.cpp
    Events/TimerSubscriber.cpp
    Events/TimerSubscriber.h
        Utils/Hash.cpp Utils/Hash.h Utils/AutoId.cpp Utils/AutoId.h)

source_group("Lii\\Utils" FILES ${Lii_Utils})

set(Lii_OpenGL
        OpenGL/Shader.h 
        OpenGL/GraphicsShader.cpp
        OpenGL/GraphicsShader.h
        api/ShaderProgram.h
        OpenGL/DefaultShaderProgram.cpp
        OpenGL/DefaultShaderProgram.h
        api/Mesh.h OpenGL/DefaultMesh.cpp
        OpenGL/DefaultMesh.h OpenGL/Uniform.h 
        OpenGL/UniformManager.cpp
        OpenGL/UniformProperties.h
        OpenGL/ShapeBuilder.cpp
        OpenGL/ModelBuilder.h
        OpenGL/Texture.cpp
        OpenGL/DefaultTexture.h
        api/Resource.h
        OpenGL/FloatVertexAttribute.cpp
        OpenGL/FloatVertexAttribute.h
        OpenGL/VertexArrayObjectPool.h
        OpenGL/DefaultMeshMemoryManager.cpp
        OpenGL/DefaultMeshMemoryManager.h
        OpenGL/Taggable.h
        OpenGL/MemoryManager.h
        OpenGL/MeshMemoryManager.h
        OpenGL/DefaultMemoryManager.cpp
        OpenGL/DefaultMemoryManager.h
        OpenGL/VertexAttributeGroup.cpp
        OpenGL/VertexAttributeGroup.h
        OpenGL/VertexAttribute.h
        OpenGL/MemoryManager.cpp
        OpenGL/Identifiable.h
        OpenGL/RenderingManager.h
        OpenGL/DefaultRenderingManager.cpp
        OpenGL/DefaultRenderingManager.h
        OpenGL/RenderObject.h
        OpenGL/Hashable.h
        OpenGL/RenderingPriorities.h
        OpenGL/GpuMemoryStrategy.h)
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


set (Lii/Managers
        Managers/GlobalResourceManager.cpp
        Managers/GlobalResourceManager.h)
source_group("Lii/Managers" FILES ${Lii/Managers})




set(ALL_FILES
    ${Enums}
    ${Lii}
    ${Lii_Renderer}
    ${Lii_Behavior}
    ${Lii_Components}
    ${Lii_Components_ComboBox}
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
    ${Lii/Managers}
    ${Lii_Components_3d}
        Events/EntryStateSubscriber.h)

################################################################################
# Target
################################################################################

add_executable(${PROJECT_NAME} WIN32 ${ALL_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE
        .
        "Behavior/"
        "api/"
        "Components/"
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
        )

target_link_libraries(Lii
        stb
        opengl32
        PhysXSDK
        "${CMAKE_SOURCE_DIR}/libs/glew/glew32.lib"
        "${CMAKE_SOURCE_DIR}/libs/glew/glew32s.lib"
        MemoryManagerLib
        )
