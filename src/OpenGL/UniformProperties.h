#ifndef LII_UniformProperties_H
#define LII_UniformProperties_H
#include <string>
#include <glew.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <vector>
#include "Core/Windows/WindowsCore.h"
#include <iostream>

namespace OpenGL
{
    class UniformProperties
    {
    private:
        const unsigned int& shaderProgramId;
        template<typename type>
        void SetPropertyCount(const unsigned int uniformShaderId, const type& arg1) const
        {
            if constexpr(std::is_same<const type&, const float&>::value)
                glUniform1f(uniformShaderId, arg1);
            if constexpr(std::is_same<const type&, const int&>::value)
                glUniform1i(uniformShaderId, arg1);
            if constexpr(std::is_same<const type&, const unsigned int&>::value)
                glUniform1ui(uniformShaderId, arg1);


            //Single values
            if constexpr(std::is_same<const type&, const glm::ivec1&>::value)
                glUniform1iv(uniformShaderId, 1 ,glm::value_ptr(arg1));
            if constexpr(std::is_same<const type&, const glm::ivec2&>::value)
                glUniform2iv(uniformShaderId, 1 ,glm::value_ptr(arg1));
            if constexpr(std::is_same<const type&, const glm::ivec3&>::value)
                glUniform3iv(uniformShaderId, 1 ,glm::value_ptr(arg1));
            if constexpr(std::is_same<const type&, const glm::ivec4&>::value)
                glUniform4iv(uniformShaderId, 1 ,glm::value_ptr(arg1));

            if constexpr(std::is_same<const type&, const glm::vec1&>::value)
                glUniform1fv(uniformShaderId, 1 ,glm::value_ptr(arg1));
            if constexpr(std::is_same<const type&, const glm::vec2&>::value)
                glUniform2fv(uniformShaderId, 1 ,glm::value_ptr(arg1));
            if constexpr(std::is_same<const type&, const glm::vec3&>::value)
                glUniform3fv(uniformShaderId, 1 ,glm::value_ptr(arg1));
            if constexpr(std::is_same<const type&, const glm::vec4&>::value)
                glUniform4fv(uniformShaderId, 1 ,glm::value_ptr(arg1));

            if constexpr(std::is_same<const type&, const glm::uvec1&>::value)
                glUniform1uiv(uniformShaderId, 1 ,glm::value_ptr(arg1));
            if constexpr(std::is_same<const type&, const glm::uvec2&>::value)
                glUniform2uiv(uniformShaderId, 1 ,glm::value_ptr(arg1));
            if constexpr(std::is_same<const type&, const glm::uvec3&>::value)
                glUniform3uiv(uniformShaderId, 1 ,glm::value_ptr(arg1));
            if constexpr(std::is_same<const type&, const glm::uvec4&>::value)
                glUniform4uiv(uniformShaderId, 1 ,glm::value_ptr(arg1));



            if constexpr(std::is_same<const type&, const glm::mat2&>::value)
                glUniformMatrix2fv(uniformShaderId, 1, GL_FALSE, glm::value_ptr(arg1));
            if constexpr(std::is_same<const type&, const glm::mat3&>::value)
                glUniformMatrix3fv(uniformShaderId, 1, GL_FALSE, glm::value_ptr(arg1));
            if constexpr(std::is_same<const type&, const glm::mat4&>::value)
                glUniformMatrix4fv(uniformShaderId, 1, GL_FALSE, glm::value_ptr(arg1));
            if constexpr(std::is_same<const type&, const glm::mat2x3&>::value)
                glUniformMatrix2x3fv(uniformShaderId, 1, GL_FALSE, glm::value_ptr(arg1));
            if constexpr(std::is_same<const type&, const glm::mat3x2&>::value)
                glUniformMatrix3x2fv(uniformShaderId, 1, GL_FALSE, glm::value_ptr(arg1));
            if constexpr(std::is_same<const type&, const glm::mat2x4&>::value)
                glUniformMatrix2x4fv(uniformShaderId, 1, GL_FALSE, glm::value_ptr(arg1));
            if constexpr(std::is_same<const type&, const glm::mat4x2&>::value)
                glUniformMatrix4x2fv(uniformShaderId, 1, GL_FALSE, glm::value_ptr(arg1));
            if constexpr(std::is_same<const type&, const glm::mat3x4&>::value)
                glUniformMatrix3x4fv(uniformShaderId, 1, GL_FALSE, glm::value_ptr(arg1));
            if constexpr(std::is_same<const type&, const glm::mat4x3&>::value)
                glUniformMatrix4x3fv(uniformShaderId, 1, GL_FALSE, glm::value_ptr(arg1));


            //Vector types
            if constexpr(std::is_same<const type&, const std::vector<glm::ivec1>&>::value)
                glUniform1iv(uniformShaderId, arg1.viewPortPosition() , ToData<glm::ivec1>(arg1));
            if constexpr(std::is_same<const type&, const std::vector<glm::ivec2>&>::value)
                glUniform2iv(uniformShaderId, arg1.viewPortPosition() , ToData<glm::ivec2>(arg1));
            if constexpr(std::is_same<const type&, const std::vector<glm::ivec3>&>::value)
                glUniform3iv(uniformShaderId, arg1.viewPortPosition() , ToData<glm::ivec3>(arg1));
            if constexpr(std::is_same<const type&, const std::vector<glm::ivec4>&>::value)
                glUniform4iv(uniformShaderId, arg1.viewPortPosition() , ToData<glm::ivec4>(arg1));

            if constexpr(std::is_same<const type&, const std::vector<glm::fvec1>&>::value)
                glUniform1fv(uniformShaderId, arg1.viewPortPosition() , ToData<glm::fvec1>(arg1));
            if constexpr(std::is_same<const type&, const std::vector<glm::fvec2>&>::value)
                glUniform2fv(uniformShaderId, arg1.viewPortPosition() , ToData<glm::fvec2>(arg1));
            if constexpr(std::is_same<const type&, const std::vector<glm::fvec3>&>::value)
                glUniform3fv(uniformShaderId, arg1.viewPortPosition() , ToData<glm::fvec3>(arg1));
            if constexpr(std::is_same<const type&, const std::vector<glm::fvec4>&>::value)
                glUniform4fv(uniformShaderId, arg1.viewPortPosition() , ToData<glm::fvec4>(arg1));

            if constexpr(std::is_same<const type&, const std::vector<glm::uvec1>&>::value)
                glUniform1uiv(uniformShaderId, arg1.viewPortPosition() , ToData<glm::uvec1>(arg1));
            if constexpr(std::is_same<const type&, const std::vector<glm::uvec2>&>::value)
                glUniform2uiv(uniformShaderId, arg1.viewPortPosition() , ToData<glm::uvec2>(arg1));
            if constexpr(std::is_same<const type&, const std::vector<glm::uvec3>&>::value)
                glUniform3uiv(uniformShaderId, arg1.viewPortPosition() , ToData<glm::uvec3>(arg1));
            if constexpr(std::is_same<const type&, const std::vector<glm::uvec4>&>::value)
                glUniform4uiv(uniformShaderId, arg1.viewPortPosition() , ToData<glm::uvec4>(arg1));



            if constexpr(std::is_same<const type&, const std::vector<glm::mat2>&>::value)
                glUniformMatrix2fv(uniformShaderId, arg1.viewPortPosition(), GL_FALSE, ToData<glm::mat2>(arg1));
            if constexpr(std::is_same<const type&, const std::vector<glm::mat3>&>::value)
                glUniformMatrix3fv(uniformShaderId, arg1.viewPortPosition(), GL_FALSE, ToData<glm::mat3>(arg1));
            if constexpr(std::is_same<const type&, const std::vector<glm::mat4>&>::value)
                glUniformMatrix4fv(uniformShaderId, arg1.viewPortPosition(), GL_FALSE, ToData<glm::mat4>(arg1));
            if constexpr(std::is_same<const type&, const std::vector<glm::mat2x3>&>::value)
                glUniformMatrix2x3fv(uniformShaderId, arg1.viewPortPosition(), GL_FALSE, ToData<glm::mat2x3>(arg1));
            if constexpr(std::is_same<const type&, const std::vector<glm::mat3x2>&>::value)
                glUniformMatrix3x2fv(uniformShaderId, arg1.viewPortPosition(), GL_FALSE, ToData<glm::mat3x2>(arg1));
            if constexpr(std::is_same<const type&, const std::vector<glm::mat2x4>&>::value)
                glUniformMatrix2x4fv(uniformShaderId, arg1.viewPortPosition(), GL_FALSE, ToData<glm::mat2x4>(arg1));
            if constexpr(std::is_same<const type&, const std::vector<glm::mat4x2>&>::value)
                glUniformMatrix4x2fv(uniformShaderId, arg1.viewPortPosition(), GL_FALSE, ToData<glm::mat4x2>(arg1));
            if constexpr(std::is_same<const type&, const std::vector<glm::mat3x4>&>::value)
                glUniformMatrix3x4fv(uniformShaderId, arg1.viewPortPosition(), GL_FALSE, ToData<glm::mat3x4>(arg1));
            if constexpr(std::is_same<const type&, const std::vector<glm::mat4x3>&>::value)
                glUniformMatrix4x3fv(uniformShaderId, arg1.viewPortPosition(), GL_FALSE, ToData<glm::mat4x3>(arg1));
        }

        template<typename type>
        const float* ToData(const std::vector<type>& data)
        {
            //So far works only for sizeof 1
            float* dataArray = glm::value_ptr(data[0]);
            return dataArray;
//            for(int i = 0; i < data.viewPortPosition(); i++)
//            {
//                dataArray[i] = glm::value_ptr(data[i]);
//            }
        }

        template<typename type>
        void SetPropertyCount(const unsigned int uniformShaderId, const type& arg1, const type& arg2) const
        {
            if constexpr(std::is_same<const type&, float>::value)
                 glUniform2f(uniformShaderId, arg1, arg2);
            if constexpr(std::is_same<const type&, int>::value)
                glUniform2i(uniformShaderId, arg1, arg2);
            if constexpr(std::is_same<const type&, unsigned int>::value)
                glUniform2ui(uniformShaderId, arg1, arg2);
        }
        template<typename type>
        void SetPropertyCount(const unsigned int uniformShaderId, const type& arg1, const type& arg2, const type& arg3) const
        {
            if constexpr(std::is_same<const type&, float>::value)
                glUniform3f(uniformShaderId, arg1, arg2, arg3);
            if constexpr(std::is_same<const type&, int>::value)
                glUniform3i(uniformShaderId, arg1, arg2, arg3);
            if constexpr(std::is_same<const type&, unsigned int>::value)
                glUniform3ui(uniformShaderId, arg1, arg2, arg3);
        }
        template<typename type>
        void SetPropertyCount(const unsigned int uniformShaderId, const type& arg1, const type& arg2, const type& arg3, const type& arg4) const
        {
            if constexpr(std::is_same<const type&, float>::value)
                glUniform4f(uniformShaderId, arg1, arg2, arg3, arg4);
            if constexpr(std::is_same<const type&, int>::value)
                glUniform4i(uniformShaderId, arg1, arg2, arg3, arg4);
            if constexpr(std::is_same<const type&, unsigned int>::value)
                glUniform4ui(uniformShaderId, arg1, arg2, arg3, arg4);
        }


    public:
        UniformProperties(const unsigned int& shaderProgramId) : shaderProgramId(shaderProgramId)
        {

        }

        template<typename ... type >
        void SetProperty(const std::string& propertyName, const type& ... args ) const
        {
            unsigned int uniformLocation = glGetUniformLocation(shaderProgramId, propertyName.c_str());
            unsigned int error;
            if( (error = glGetError()) != GL_NO_ERROR)
            {
               std::cout << "UniformProperties error: " << error << std::endl;
               return;
            }

            SetPropertyCount(uniformLocation, args ...);
        }

    };
}

#endif //LII_UniformProperties_H
