//
//  render.cpp
//  PLG
//
//  Created by Lukas Zierahn on 02.06.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#include "render.hpp"

int Render::InitGL() {
    // Initialise GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return -1;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Open a window and create its OpenGL context
    window = glfwCreateWindow(width, height, "PLG", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to create Window GLFW\n");
        getchar();

        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    
    mainProgram = glCreateProgram();
    GLuint VS_Id = LoadShader("shader/VS.GLSL", GL_VERTEX_SHADER);
    GLuint FS_Id = LoadShader("shader/FS.GLSL", GL_FRAGMENT_SHADER);

    glAttachShader(mainProgram, VS_Id);
    glAttachShader(mainProgram, FS_Id);
    glLinkProgram(mainProgram);
    
    GLint result = GL_FALSE;
    int infoLogLength;
    glGetProgramiv(mainProgram, GL_LINK_STATUS, &result);
    glGetProgramiv(mainProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        vector<char> ProgramErrorMessage(infoLogLength+1);
        glGetProgramInfoLog(mainProgram, infoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }
    
    
    glDetachShader(mainProgram, VS_Id);
    glDetachShader(mainProgram, FS_Id);
    
    glDeleteShader(VS_Id);
    glDeleteShader(FS_Id);
    
    return 0;
}

Render::Render() {
    InitGL();
}

void Render::Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
}

GLuint Render::LoadShader(const char* path, GLenum type) {
    
    string shaderCode;
    ifstream shaderStream(path, ios::in);
    if (shaderStream.is_open()){
        stringstream sstr;
        sstr << shaderStream.rdbuf();
        shaderCode = sstr.str();
        shaderStream.close();
    } else {
        printf("Failed to load shader from path %s\n", path);
        getchar();
        return 0;
    }
    
    GLint Result = GL_FALSE;
    int InfoLogLength;
    
    
    GLuint shaderId = glCreateShader(GL_VERTEX_SHADER);
    char const* sourcePointer = shaderCode.c_str();
    glShaderSource(shaderId, 1, &sourcePointer, NULL);
    glCompileShader(shaderId);
    
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0){
        vector<char> errorMessage(InfoLogLength+1);
        glGetShaderInfoLog(shaderId, InfoLogLength, NULL, &errorMessage[0]);
        printf("%s\n", &errorMessage[0]);
    }
    
    return shaderId;
}
