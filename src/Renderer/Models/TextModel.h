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
    Renderer* renderer;
    glm::ivec4 color{255, 255, 255, 255};
    float fontSize = 12.0f;
    FontAlignment fontAlignment = FontAlignment::FontAlignmentNear;
    FontAlignment fontLineAlignment = FontAlignment::FontAlignmentNear;
    bool viewPortSet = false;
    ModelViewport viewPort;
    std::wstring fontFamily = L"Arial";
    std::wstring text = L"";
public:

    TextModel();
    glm::vec4 GetPosition() override;

    float GetX() override;

    float GetY() override;

    float GetZ() override;

    float GetW() override;

    float GetAbsoluteX() override;

    float GetAbsoluteY() override;

    const glm::vec4 & GetAbsolutePosition() override;

    void SetPosition(glm::vec4 position, bool emit) override;

    void SetPosition(glm::vec4 position) override;

    void SetPosition(float x, float y, float z, float w, bool emit) override;

    void SetPosition(float x, float y, float z, float w) override;

    void SetX(float x, bool emit) override;

    void SetX(float x) override;

    void SetY(float y, bool emit) override;

    void SetY(float y) override;

    void SetZ(float z, bool emit) override;

    void SetZ(float z) override;

    void SetW(float w, bool emit) override;

    void SetW(float w) override;

    void SetTranslate(glm::vec4 offset, bool emit) override;

    void SetTranslate(glm::vec4 offset) override;

    void SetTranslateX(float x, bool emit) override;

    void SetTranslateX(float x) override;

    void SetTranslateY(float y, bool emit) override;

    void SetTranslateY(float y) override;

    glm::vec4 GetTranslate() override;

    float GetTranslateX() override;

    float GetTranslateY() override;

    void ReceiveCommand(std::unique_ptr<RenderMessage> message) override;

    void AddOnMoveSubscriber(MoveSubscriber &subscriber) override;

    void RemoveOnMoveSubscriber(MoveSubscriber &subscriber) override;

    float GetZIndex() override;

    void Draw() override;

    void SetRenderer(Renderer *renderer) override;

    void SetModelId(long long int id) override;

    const size_t & GetModelId() override;

    void SetColor(const glm::ivec4 &color) override;

    const glm::ivec4& GetColor() override;

    void SetFontSize(float fontSize) override;

    void SetFontAlignment(FontAlignment alignment) override;

    void SetFontLineAlignment(FontAlignment alignment) override;

    void NotifyOnMoveSubscribers(EventMoveInfo e) override;

    void SetText(const std::wstring &text) override;

    void SetFontFamily(const std::wstring &fontFamily) override;

    const std::wstring &GetText() override;

    const std::wstring &GetFontFamily() override;

    FontAlignment GetFontLineAlignment() override;

    FontAlignment GetFontAlignment() override;

    void SetVisible(bool visible) override;

    bool IsVisible() override;

};


#endif //LII_TEXTMODEL_H
