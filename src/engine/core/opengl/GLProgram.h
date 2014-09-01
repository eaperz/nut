/** 
 * \file GLProgram.h
 * \brief This class create and handle OpenGL programs.
 * 
 * @author: Eder A. Perez.
 */
 
#ifndef GLPROGRAM_H
#define GLPROGRAM_H

#include <string>
#include <GL/glew.h>
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"



namespace nut
{
    class GLSLVariable;

    class GLProgram
    {
        public:

        GLProgram();

        ~GLProgram();

        /**
         * Compile a shader either by code in file or a string containing the code.
         * 
         * @param shader A string containing either the file path to a shader code
         * or the shader code itself.
         * @param type A GLenum that must be one of GL_COMPUTE_SHADER, GL_VERTEX_SHADER,
         * GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, or
         * GL_FRAGMENT_SHADER.
         * @param isFilePath True if @shader is a path to a shader file. False if @shader
         * contains the shader program itself.
         * @return True if compilation was successfull. In case of error, fills the log
         * and returns false.
         */
        bool compileShader(const char* shader, GLenum type, bool isFilePath);
        
        /**
         * Attempt to link the  program.
         * 
         * @return True if program was successfully linked. In case of error, fills the log
         * and returns false.
         */
        bool link();
        
        /**
         * Install the program as part of current rendering state by calling glUseProgram.
         */
        void use()
        {
            glUseProgram(_handle);
        }
        
        /**
         * Return the log of the most recent compile or link action.
         * 
         * @return A string containing the log information.
         */
        const std::string& log()
        {
            return _log;
        }
        
        /**
         * Get the handle to the OpenGL program.
         * 
         * @return The handle to the OpenGL program.
         */
        GLuint getHandle()
        {
            return _handle;
        }
        
        /**
         * Check if program is linked.
         * 
         * @return True if program is linked, false otherwise.
         */
        bool isLinked()
        {
            return _isLinked;
        }
        
        /**
         * Get the location of a uniform variable in this program.
         * 
         * @param name Uniform variable name.
         * @return The location of the uniform variable if it exists. Otherwise,
         * if @name does not correspond to an active uniform variable, if name
         * starts with the reserved prefix "gl_", or if name is associated with an
         * atomic counter or a named uniform block, then returns -1.
         */
        GLint getUniform(const char* name)
        {
            return glGetUniformLocation(_handle, name);
        }

        /**
         * Return a list containing all active uniforms variables.
         * 
         * @param list A list of active uniforms variables.
         */
        void getActiveUniforms(std::vector<GLSLVariable>& list);
        
        /**
         * Return a list containing all active attributes.
         * 
         * @param list A list of active attributes.
         */
        void getActiveAttributes(std::vector<GLSLVariable>& list);

        /**
         * Specify the value of a uniform variable.
         * 
         * @param name Uniform variable name.
         * @param val New value to be used for the variable @name.
         */
        void setUniform(const char* name, float val);
        
        /**
         * Specify the value of a uniform variable.
         * 
         * @param location Uniform variable location.
         * @param val New value to be used for the variable @name.
         */
        void setUniform(GLint location, float val)
        {
            glUniform1f(location, val);
        }
        
        /**
         * Specify the value of a uniform variable.
         * 
         * @param name Uniform variable name.
         * @param val New value to be used for the variable @name.
         */
        void setUniform(const char* name, int val);
        
        /**
         * Specify the value of a uniform variable.
         * 
         * @param location Uniform variable location.
         * @param val New value to be used for the variable @name.
         */
        void setUniform(GLint location, int val)
        {
            glUniform1i(location, val);
        }
        
        /**
         * Specify the value of a uniform variable.
         * 
         * @param name Uniform variable name.
         * @param v New value to be used for the variable @name.
         */
        void setUniform(const char* name, const Vector2D<float>& v);
        
        /**
         * Specify the value of a uniform variable.
         * 
         * @param location Uniform variable location.
         * @param val New value to be used for the variable @name.
         */
        void setUniform(GLint location, const Vector2D<float>& v)
        {
            glUniform2fv(location, 1, &v.x);
        }
        
        /**
         * Specify the value of a uniform variable.
         * 
         * @param name Uniform variable name.
         * @param v New value to be used for the variable @name.
         */
        void setUniform(const char* name, const Vector3D<float>& v);
        
        /**
         * Specify the value of a uniform variable.
         * 
         * @param location Uniform variable location.
         * @param val New value to be used for the variable @name.
         */
        void setUniform(GLint location, const Vector3D<float>& v)
        {
            glUniform3fv(location, 1, &v.x);
        }
        
        /**
         * Specify the value of a uniform variable.
         * 
         * @param name Uniform variable name.
         * @param v New value to be used for the variable @name.
         */
        void setUniform(const char* name, const Vector4D<float>& v);
        
        /**
         * Specify the value of a uniform variable.
         * 
         * @param location Uniform variable location.
         * @param val New value to be used for the variable @name.
         */
        void setUniform(GLint location, const Vector4D<float>& v)
        {
            glUniform4fv(location, 1, &v.x);
        }
        
        /**
         * Specify the value of a uniform variable.
         * 
         * @param name Uniform variable name.
         * @param m New value to be used for the variable @name.
         */
        void setUniform(const char* name, const Matrix3x3<float>& m);
        
        /**
         * Specify the value of a uniform variable.
         * 
         * @param location Uniform variable location.
         * @param val New value to be used for the variable @name.
         */
        void setUniform(GLint location, const Matrix3x3<float>& m)
        {
            glUniformMatrix3fv(location, 1, GL_FALSE, &m[0]);
        }
        
        /**
         * Specify the value of a uniform variable.
         * 
         * @param name Uniform variable name.
         * @param m New value to be used for the variable @name.
         */
        void setUniform(const char* name, const Matrix4x4<float>& m);
        
        /**
         * Specify the value of a uniform variable.
         * 
         * @param location Uniform variable location.
         * @param val New value to be used for the variable @name.
         */
        void setUniform(GLint location, const Matrix4x4<float>& m)
        {
            glUniformMatrix4fv(location, 1, GL_FALSE, &m[0]);
        }



        private:

        GLuint _handle; /**< An OpenGL program handle. */
        bool _isLinked; /**< True if the program was successfully linked. */
        std::string _log; /**< Store the most recent log produced by a compile or link action. */



        /**
         * Check if either a program or a shader was correctly created.
         * 
         * @param obj It can be either a shader or program index.
         * @return True if the status is OK. Otherwise, returns false and fill the log string with information from OpenGL.
         */
        bool _checkStatus(GLuint obj);
    };



    class GLSLVariable
    {
        public:
        
        GLSLVariable() : program(0), location(0), size(0),
                         type(0), name(""), isUniform(false)
        {
        }
        
        GLuint program;
        GLint location;
        GLint size;
        GLenum type;
        std::string name;
        bool isUniform;
    };
}

#endif // GLPROGRAM_H
