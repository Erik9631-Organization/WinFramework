#pragma once
#include "PropertyParser.h"
#include <functional>
#include <Windows.h>
#include <gdiplus.h>
#include <unordered_map>

class DefaultPropertyParser : PropertyParser
{
private:
	std::unordered_map<std::string, std::function<void(std::string ...)>> parsableMap;

	std::function<void(unsigned char, unsigned char, unsigned char, unsigned char)> setColorFunction;
	void ParseSetColorFunction(std::string ... argument);

	std::function<Gdiplus::Color> getColorFunction;

	std::function<void(Gdiplus::DashStyle)> setBorderStyleFunction;
	std::function<Gdiplus::DashStyle> getBorderStyleFunction;

	std::function<void(float)> setThicknessFunction;
	std::function<float> getThicknessFunction;

	std::function<void(float)> setFontSizeFunction;

public:
	// Inherited via PropertyParser
	virtual void SetProperty(std::string propertyName, std::string values ...) override;
	virtual bool HasProperty(std::string propertyName) override;
	virtual std::any GetProperty(std::string propertyName) override;
	void Set_SetColorFunction(std::function<void(unsigned char, unsigned char, unsigned char, unsigned char)> function);
	void Set_GetColorFunction(std::function<Gdiplus::Color> function);
	void Set_SetBorderStyleFunction(std::function<void(Gdiplus::DashStyle)> setBorderStyleFunction);
	void Set_SetThicknessFunction(std::function<void(float)> function);
	void Set_GetThicknessFunction(std::function<float> function);
	void Set_SetFontSizeFunction(std::function<void(float)> function);
};

