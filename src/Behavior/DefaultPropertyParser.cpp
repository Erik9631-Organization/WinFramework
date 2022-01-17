#include "DefaultPropertyParser.h"

void DefaultPropertyParser::ParseSetColorFunction(std::string ... argument)
{

}

void DefaultPropertyParser::SetProperty(std::string propertyName, std::string values ...)
{
    //Look up in the table whether propertyName has a parsableFunction assigned
    //If yes, then call the parsable function and pass the values ... inside
}

bool DefaultPropertyParser::HasProperty(std::string propertyName)
{
    return false;
}

std::any DefaultPropertyParser::GetProperty(std::string propertyName)
{
    return std::any();
}
//
//Parse the argument
//Call the proper real 

void DefaultPropertyParser::Set_SetColorFunction(std::function<void(unsigned char, unsigned char, unsigned char, unsigned char)> function)
{
}

void DefaultPropertyParser::Set_GetColorFunction(std::function<Gdiplus::Color> function)
{
}

void DefaultPropertyParser::Set_SetBorderStyleFunction(std::function<void(Gdiplus::DashStyle)> setBorderStyleFunction)
{
}

void DefaultPropertyParser::Set_SetThicknessFunction(std::function<void(float)> function)
{
}

void DefaultPropertyParser::Set_GetThicknessFunction(std::function<float> function)
{
}

void DefaultPropertyParser::Set_SetFontSizeFunction(std::function<void(float)> function)
{
}
