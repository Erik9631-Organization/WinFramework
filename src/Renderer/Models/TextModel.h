//
// Created by erik9 on 2/21/2023.
//

#ifndef LII_TEXTMODEL_H
#define LII_TEXTMODEL_H
#include "Movable.h"
#include "Resizable.h"
#include "RenderingModel.h"
#include "MovableModelBehavior.h"
#include "FontAlignment.h"
#include "ModelViewport.h"
#include "FontFormat.h"
#include "api/TextApi.h"
#include <string>

class TextModel : public RenderingModel, public TextApi, public Movable
{
private:
    bool visible = true;
    MovableModelBehavior movableModelBehavior;
    size_t modelId = 0;
    Renderer* renderer = nullptr;
    glm::ivec4 color{255, 255, 255, 255};
    float fontSize = 12.0f;
    FontAlignment fontAlignment = FontAlignment::FontAlignmentNear;
    FontAlignment fontLineAlignment = FontAlignment::FontAlignmentNear;
    bool viewPortSet = false;
    ModelViewport viewPort;
    std::wstring fontFamily = L"Arial";
    std::wstring text;
public:

    TextModel();
    [[nodiscard]] const glm::vec3 & GetPosition() const override;

    [[nodiscard]] const glm::vec3 & GetAbsolutePosition() const override;

    void SetPosition(const glm::vec3 &position, bool emit = true) override;

    void SetTranslate(const glm::vec3 &offset, bool emit = true) override;

    [[nodiscard]] const glm::vec3 & GetTranslate() const override;

    void ReceiveCommand(std::unique_ptr<RenderMessage> message) override;

    void AddOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void RemoveOnMoveSubscriber(MoveSubscriber &subscriber) override;

    float GetZIndex() override;

    void Draw() override;

    void SetRenderer(Renderer *renderer) override;

    void SetModelId(size_t id) override;

    const size_t & GetModelId() override;

    void SetColor(const glm::ivec4 &color) override;

    const glm::ivec4& GetColor() override;

    void SetFontSize(float fontSize) override;

    void SetFontAlignment(FontAlignment alignment) override;

    void SetFontLineAlignment(FontAlignment alignment) override;

    void NotifyOnMoveSubscribers(const EventMoveInfo &e) override;

    void SetText(const std::wstring &text) override;

    void SetFontFamily(const std::wstring &fontFamily) override;

    const std::wstring &GetText() override;

    const std::wstring &GetFontFamily() override;

    FontAlignment GetFontLineAlignment() override;

    FontAlignment GetFontAlignment() override;

    void SetVisible(bool visible) override;

    bool IsVisible() override;

    void SetViewportSize(const glm::vec4 &vec4) override;

    void SetViewportPosition(const glm::vec3 &input) override;

    const glm::vec4 & GetViewportSize() override;

    const glm::vec3 & GetViewportPosition() override;

    void ResetViewport() override;

    void AddViewport2Subscriber(Viewport2Subscriber &subscriber) override;

    void RemoveViewport2Subscriber(Viewport2Subscriber &subscriber) override;

    void NotifyOnViewportSizeChanged(const Viewport2EventInfo &event) override;

    void NotifyOnViewportPositionChanged(const Viewport2EventInfo &event) override;

    bool IsViewportSet() const override;

    void NotifyOnViewportReset(const Viewport2EventInfo &event) override;

};


#endif //LII_TEXTMODEL_H
