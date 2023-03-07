#pragma once

#include <glad/glad.h>

class VBO {
  unsigned int ID;

public:
  VBO() { glGenBuffers(1, &ID); }

  void Bind() { glBindBuffer(GL_ARRAY_BUFFER, ID); }

  void Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

  void Data(unsigned int size, const void *data, int type = GL_STATIC_DRAW) {
    Bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, type);
  }

  ~VBO() { glDeleteBuffers(1, &ID); }
};

class EBO {
  unsigned int ID;

public:
  EBO() { glGenBuffers(1, &ID); }

  void Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); }

  void Data(unsigned int size, const void *data, int type = GL_STATIC_DRAW) {
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, type);
  }

  void Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

  ~EBO() { glDeleteBuffers(1, &ID); }
};

class VAO {
  unsigned int ID;

public:
  VAO() { glGenVertexArrays(1, &ID); }

  void Bind() { glBindVertexArray(ID); }

  void Unbind() { glBindVertexArray(0); }

  ~VAO() { glDeleteVertexArrays(1, &ID); }

  void Layout(int layout, int type_size, int type, int stride, int offset,
              int normalize = GL_FALSE) {
    glVertexAttribPointer(layout, type_size, type, normalize, stride,
                          (void *)offset);
    glEnableVertexAttribArray(layout);
  }
};