#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(
    const unsigned int &width, 
    const unsigned int &height):
    _width(width), _height(height) 
{
    Initialize();
}


FrameBuffer::~FrameBuffer() {
    glDeleteFramebuffers(1, &_ID);
    glDeleteTextures(1, &_colorAttachment);
    glDeleteRenderbuffers(1, &_depthAttachment);
}

void FrameBuffer::Initialize() {

    if (_ID) {
        glDeleteFramebuffers(1, &_ID);
        glDeleteTextures(1, &_colorAttachment);
        glDeleteRenderbuffers(1, &_depthAttachment);
    }

    glGenFramebuffers(1, &_ID);
    glBindFramebuffer(GL_FRAMEBUFFER, _ID);

    glGenTextures(1, &_colorAttachment);
    glBindTexture(GL_TEXTURE_2D, _colorAttachment);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorAttachment, 0);

    glGenRenderbuffers(1, &_depthAttachment);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthAttachment);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _depthAttachment);


    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


}


void FrameBuffer::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, _ID);
    glViewport(0, 0, _width, _height);
}


void FrameBuffer::Unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void FrameBuffer::Resize(unsigned int nwidth, unsigned int nheight) {
    
    _width = nwidth;
    _height = nheight;
    Initialize();
}

void FrameBuffer::BeginProperty() {
    //static int size[] = { _width, _height };
    ImGui::Text("FrameBuffer Size: ");
    //ImGui::DragInt2("###size", size, 1, 32, 512);

    //if (size[0] != _width || size[1] != _height) {
        //Resize(size[0], size[1]);
    //}
}

GLuint* FrameBuffer::GetColorAttachment() {
    return &_colorAttachment;
}