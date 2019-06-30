//
//  render.cpp
//  PLG
//
//  Created by Lukas Zierahn on 02.06.19.
//  Copyright © 2019 Lukas Zierahn. All rights reserved.
//

#include "render.hpp"

#include "ColoredObject.hpp"
#include "TexturedObject.hpp"

void Render::InitGL() {
    // Initialise GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return;
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
        return;
    }
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return;
    }
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
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
}

Render::Render() {
    InitGL();
    
    modelLoader = new ModelLoader(this);
    camera = new Camera(this);
    
    cube = new TexturedObject(this);
    cube->setModelDataByKey("cube_File");
    cube->setTextureByKey("Error");
}

void Render::Draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(mainProgram);
    
    camera->UpdateMatricies();
    cube->Draw();
    
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
        return 0;
    }
    
    GLint Result = GL_FALSE;
    int InfoLogLength;
    
    GLuint shaderId = glCreateShader(type);
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

Render::~Render() {
    glDeleteProgram(mainProgram);
    glDeleteVertexArrays(1, &VertexArrayID);
    
    delete modelLoader;
    delete camera;
    delete cube;
}
