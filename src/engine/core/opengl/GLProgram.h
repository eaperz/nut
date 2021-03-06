/** 
 * \file GLProgram.h
 * \brief This class creates and handle OpenGL programs.
 * 
 * Licensed under the MIT License (MIT)
 * Copyright (c) 2014 Eder de Almeida Perez
 * 
 * @author: Eder A. Perez.
 */
 
#ifndef GLPROGRAM_H
#define GLPROGRAM_H

#include <string>
#include <vector>
#include "glbinding/gl/gl.h"
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "GLSLVariable.h"
#include "GLSLSubroutineUniform.h"



namespace nut
{
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
         * @return True if compilation was successful. In case of error, fills the log
         * and returns false.
         */
        bool compileShader(const char* shader, gl::GLenum type, bool isFilePath);
        
        /**
         * Attempt to link the program. If no successful call to @compileShader
         * method was made previously, @link will fail.
         * 
         * @return True if program was successfully linked. In case of error, fills the log
         * and returns false.
         */
        bool link();

        /**
         * Install the program as part of current rendering state by calling @glUseProgram.
         * Only has effect if program was successfully linked.
         */
        void use() const
        {
            if (_isLinked)
            {
                gl::glUseProgram(_handle);
            }
        }

        /**
         * Return the log of the most recent compile or link action.
         * 
         * @return A string containing the log information.
         */
        const char* log() const
        {
            return _log.c_str();
        }
        
        /**
         * Get the handle to the OpenGL program.
         * 
         * @return The handle to the OpenGL program.
         */
        gl::GLuint getHandle() const
        {
            return _handle;
        }
        
        /**
         * Check if program is linked.
         * 
         * @return True if program is linked, false otherwise.
         */
        bool isLinked() const
        {
            return _isLinked;
        }
        
        /**
         * Get the location of an uniform variable in this program.
         * 
         * @param name Uniform variable name.
         * @return The location of the uniform variable if it exists. Otherwise,
         * if @name does not correspond to an active uniform variable, if name
         * starts with the reserved prefix "gl_", or if name is associated with an
         * atomic counter or a named uniform block, then returns -1.
         */
        gl::GLint getUniform(const char* name) const
        {
            return gl::glGetUniformLocation(_handle, name);
        }

        /**
         * Get the location of an attribute in this program.
         * 
         * @param name Attribute name.
         * @return The location of the attribute if it exists. Otherwise,
         * if @name does not correspond to an active attribute, if name
         * starts with the reserved prefix "gl_", or if name is not an active attribute
         * in the program, then returns -1.
         */
        gl::GLint getAttribute(const char* name) const
        {
            return gl::glGetAttribLocation(_handle, name);
        }

        /**
         * Return a list containing all active uniforms variables.
         * 
         * @param list A list of active uniforms variables.
         */
        void getActiveUniforms(std::vector<GLSLVariable>& list) const;
        
        /**
         * Return a list containing all active attributes.
         * 
         * @param list A list of active attributes.
         */
        void getActiveAttributes(std::vector<GLSLVariable>& list) const;

        /**
         * Return a list containing all active subroutine function's names.
         * 
         * @param list A list of active subroutine function's names. A subroutine
         * function index correspond to its index in the list.
         * @param shaderType A GLenum that must be one of GL_COMPUTE_SHADER,
         * GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER,
         * GL_GEOMETRY_SHADER, or GL_FRAGMENT_SHADER.
         */
        void getActiveSubroutines(std::vector<std::string>& list, gl::GLenum shaderType) const;

        /**
         * Return a list containing all active subroutine uniforms.
         * 
         * @param list A list of active subroutine uniforms.
         * @param shaderType A GLenum that must be one of GL_COMPUTE_SHADER,
         * GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER,
         * GL_GEOMETRY_SHADER, or GL_FRAGMENT_SHADER.
         */
        void getActiveSubroutineUniforms(std::vector<GLSLSubroutineUniform>& list, gl::GLenum shaderType) const;

        /**
         * Specify the value of a uniform variable.
         * 
         * @param name Uniform variable name.
         * @param val New value to be used for the variable @name.
         */
        void setUniform(const char* name, float val) const
        {
            gl::GLint loc = getUniform(name);

            if (loc != -1)
            {
                setUniform(loc, val);
            }
        }
        
        /**
         * Specify the value of a uniform variable.
         * 
         * @param location Uniform variable location.
         * @param val New value to be used for the variable @name.
         */
        void setUniform(gl::GLint location, float val) const
        {
            gl::glProgramUniform1f(_handle, location, val);
        }
        
        /**
         * Specify the value of a uniform variable.
         * 
         * @param name Uniform variable name.
         * @param val New value to be used for the variable @name.
         */
        void setUniform(const char* name, int val) const
        {
            gl::GLint loc = getUniform(name);

            if (loc != -1)
            {
                setUniform(loc, val);
            }
        }
        
        /**
         * Specify the value of a uniform variable.
         * 
         * @param location Uniform variable location.
         * @param val New value to be used for the variable @name.
         */
        void setUniform(gl::GLint location, int val) const
        {
            gl::glProgramUniform1i(_handle, location, val);
        }
        
        /**
         * Specify the value of a uniform variable.
         * 
         * @param name Uniform variable name.
         * @param v New value to be used for the variable @name.
         */
        void setUniform(const char* name, const Vector2D<float>& v) const
        {
            gl::GLint loc = getUniform(name);

            if (loc != -1)
            {
                setUniform(loc, v);
            }
        }
        
        /**
         * Specify the value of a uniform variable.
         * 
         * @param location Uniform variable location.
         * @param val New value to be used for the variable @name.
         */
        void setUniform(gl::GLint location, const Vector2D<float>& v) const
        {
            gl::glProgramUniform2fv(_handle, location, 1, &v.x);
        }
        
        /**
         * Specify the value of a uniform variable.
         * 
         * @param name Uniform variable name.
         * @param v New value to be used for the variable @name.
         */
        void setUniform(const char* name, const Vector3D<float>& v) const
        {
            gl::GLint loc = getUniform(name);

            if (loc != -1)
            {
                setUniform(loc, v);
            }
        }
        
        /**
         * Specify the value of a uniform variable.
         * 
         * @param location Uniform variable location.
         * @param val New value to be used for the variable @name.
         */
        void setUniform(gl::GLint location, const Vector3D<float>& v) const
        {
            gl::glProgramUniform3fv(_handle, location, 1, &v.x);
        }
        
        /**
         * Specify the value of a uniform variable.
         * 
         * @param name Uniform variable name.
         * @param v New value to be used for the variable @name.
         */
        void setUniform(const char* name, const Vector4D<float>& v) const
        {
            gl::GLint loc = getUniform(name);

            if (loc != -1)
            {
                setUniform(loc, v);
            }
        }
        
        /**
         * Specify the value of a uniform variable.
         * 
         * @param location Uniform variable location.
         * @param val New value to be used for the variable @name.
         */
        void setUniform(gl::GLint location, const Vector4D<float>& v) const
        {
            gl::glProgramUniform4fv(_handle, location, 1, &v.x);
        }
        
        /**
         * Specify the value of a uniform variable.
         * 
         * @param name Uniform variable name.
         * @param m New value to be used for the variable @name.
         */
        void setUniform(const char* name, Matrix3x3<float>& m) const
        {
            gl::GLint loc = getUniform(name);

            if (loc != -1)
            {
                setUniform(loc, m);
            }
        }
        
        /**
         * Specify the value of a uniform variable.
         * 
         * @param location Uniform variable location.
         * @param val New value to be used for the variable @name.
         */
        void setUniform(gl::GLint location, Matrix3x3<float>& m) const
        {
            gl::glProgramUniformMatrix3fv(_handle, location, 1, gl::GL_FALSE, &m[0]);
        }
        
        /**
         * Specify the value of a uniform variable.
         * 
         * @param name Uniform variable name.
         * @param m New value to be used for the variable @name.
         */
        void setUniform(const char* name, Matrix4x4<float>& m) const
        {
            gl::GLint loc = getUniform(name);

            if (loc != -1)
            {
                setUniform(loc, m);
            }
        }
        
        /**
         * Specify the value of a uniform variable.
         * 
         * @param location Uniform variable location.
         * @param val New value to be used for the variable @name.
         */
        void setUniform(gl::GLint location, Matrix4x4<float>& m) const
        {
            gl::glProgramUniformMatrix4fv(_handle, location, 1, gl::GL_FALSE, &m[0]);
        }

        /**
         * Specify the value of a uniform variable.
         * 
         * @param name Uniform variable name.
         * @param m New value to be used for the variable @name.
         */
        void setUniform(const char* name, GLMatrix<float>& m) const
        {
            gl::GLint loc = getUniform(name);

            if (loc != -1)
            {
                setUniform(loc, m);
            }
        }
        
        /**
         * Specify the value of a uniform variable.
         * 
         * @param location Uniform variable location.
         * @param val New value to be used for the variable @name.
         */
        void setUniform(gl::GLint location, GLMatrix<float>& m) const
        {
            gl::glProgramUniformMatrix4fv(_handle, location, 1, gl::GL_FALSE, &m[0]);
        }
        
        /**
         * Activate all uniform subroutines of a shader stage at once.
         * 
         * @param shaderType A GLenum that must be one of GL_COMPUTE_SHADER,
         * GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER,
         * GL_GEOMETRY_SHADER, or GL_FRAGMENT_SHADER.
         * @param count Number of elements of @indices. It must be the same value
         * returned by glGetProgramStageiv with GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS
         * parameter
         * @param indices A list of subroutine function's indices where the i-th
         * element corresponds to a subroutine function index being assigned to the subroutine
         * uniform location i.
         */
        void setSubroutineUniforms(gl::GLenum shaderType, gl::GLint count, const gl::GLuint* indices)
        {
            gl::GLint currentProgram;
            gl::GLint subroutineUniformLocationsCount;
            
            gl::glGetIntegerv(gl::GL_CURRENT_PROGRAM, &currentProgram);
            
            if (currentProgram != static_cast<int>(_handle))
            {
                gl::glUseProgram(_handle);
            }

            gl::glGetProgramStageiv(_handle, shaderType, gl::GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS, &subroutineUniformLocationsCount);
            
            if (count == subroutineUniformLocationsCount)
            {
                gl::glUniformSubroutinesuiv(shaderType, count, indices);
            }
            
            if (currentProgram != static_cast<int>(_handle))
            {
                gl::glUseProgram(currentProgram);
            }
        }



        private:

        gl::GLuint _handle; /**< An OpenGL program handle. */
        bool _isLinked; /**< True if the program was successfully linked. */
        std::string _log; /**< Store the most recent log produced by a compile or link action. */



        /**
         * Check if either a program or a shader was correctly created.
         * 
         * @param obj It can be either a shader or program index.
         * @return True if the status is OK. Otherwise, returns false and fill the log string with information from OpenGL.
         */
        bool _checkStatus(gl::GLuint obj);
    };
}

#endif // GLPROGRAM_H
