set(PROJECT_NAME Graphics)

################################################################################
# Source groups
################################################################################
set(Enums
    "Enums/EventUpdateFlags.h"
    "Enums/GraphicsScaling.h"
    )
source_group("Enums" FILES ${Enums})

set(Lii
    "AddSubject.h"
    "Events/ComboBoxStateSubject.h"
    "Behavior/DefaultListBoxBehavior.h"
    "DemoApplication.h"
    "Components/Draggable.h"
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
    "Mouse.h"
    "OnAddHandler.h"
    "Events/OnAddSubscriber.h"
    "TableElement.h"
    "TrackBarBehavior.h"
    "TrackbarGraphics.h"
    "VerticalTrackbarBehavior.h"
    "AddSubject.cpp"
    "Events/ComboBoxStateSubject.cpp"
    "Behavior/DefaultListBoxBehavior.cpp"
    "DemoApplication.cpp"
    "Components/Draggable.cpp"
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
    "Mouse.cpp"
    "OnAddHandler.cpp"
    "Events/OnAddSubscriber.cpp"
    "TableElement.cpp"
    "TrackBarBehavior.cpp"
    "TrackbarGraphics.cpp"
    "VerticalTrackbarBehavior.cpp"
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
)

source_group("Lii\\Behavior" FILES ${Lii_Behavior})


set(Lii_Components
    "Components/Activatable.h"
    "Components/Adjustable.h"
    "Components/Button.h"
    "Components/Checkbox.h"
    "Components/Collidable.h"
    "Components/Component.h"
    "Components/CoreWindowFrame.h"
    "Components/FileBrowser.h"
    "Components/Grid/Grid.h"
    "Components/Label.h"
    "Components/ListBox.h"
    "MouseInteractable.h"
    "Components/Movable.h"
    "Components/Panel.h"
    "Components/PasswordField.h"
    "Components/RadioButton.h"
    "Components/Reflectable.h"
    "Components/ReflectionContainer.h"
    "Components/Renderable.h"
    "Components/Resizable.h"
    "Components/TextInput.h"
    "Components/TrackBar.h"
    "Components/Viewable.h"
    "Components/WindowFrame.h"
    "Components/Activatable.cpp"
    "Components/Adjustable.cpp"
    "Components/Button.cpp"
    "Components/Checkbox.cpp"
    "Components/Collidable.cpp"
    "Components/Component.cpp"
    "Components/CoreWindowFrame.cpp"
    "Components/Label.cpp"
    "MouseInteractable.cpp"
    "Components/Movable.cpp"
    "Components/PasswordField.cpp"
    "Components/RadioButton.cpp"
    "Components/Reflectable.cpp"
    "Components/ReflectionContainer.cpp"
    "Components/Renderable.cpp"
    "Components/Resizable.cpp"
    "Components/TextInput.cpp"
    "Components/TrackBar.cpp"
    "Components/Viewable.cpp"
    "Components/WindowFrame.cpp"
)
source_group("Lii\\Components" FILES ${Lii_Components})


set(Lii_Components_ComboBox
    "Components/ComboBox/ComboBox.h"
    "Components/ComboBox/ComboElement.h"
    "Components/ComboBox/ComboSelection.h"
    "Components/ComboBox/ComboSelection.cpp"
)
source_group("Lii\\Components\\ComboBox" FILES ${Lii_Components_ComboBox})


set(Lii_DataTypes
    "DataTypes/CastableTree.h"
    "DataTypes/DefaultMultiTree.h"
    "DataTypes/MultiTree.h"
    "DataTypes/CastableTree.cpp"
    "DataTypes/DefaultMultiTree.cpp"
    "DataTypes/MultiTree.cpp"
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
    "Events/RenderableSubscriber.h"
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
)

source_group("Header Files\\Events" FILES ${Lii_Events})


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
        Utils/Vector2DScaler.cpp Utils/Vector2DScaler.h Utils/Vector2d.cpp Utils/Vector2d.h Utils/Graphics2dUtil.cpp Utils/Graphics2dUtil.h)

source_group("Header Files\\Utils" FILES ${Lii_Utils})


set(ALL_FILES
    ${Enums}
    ${Lii}
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
)

################################################################################
# Target
################################################################################

add_executable(${PROJECT_NAME} WIN32 ${ALL_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC
        .
        "Behavior/"
        "Components/"
        "DataTypes/"
        "Events/"
        "EventTypes/"
        "GraphicalStates/"
        "Graphics/"
        "MetaObjects/"
        "Utils/"
        "Enums/"
        )