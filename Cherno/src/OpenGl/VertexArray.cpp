#include "VertexArray.h"

#include "Renderer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray() { GLCall(glGenVertexArrays(1, &m_RenderedID)); }

VertexArray::~VertexArray() { GLCall(glDeleteVertexArrays(1, &m_RenderedID)); }

void VertexArray::AddBuffer(const VertexBuffer& vb, const IndexBuffer& ib,
                            const VertexBufferLayout& layout) {
    Bind();
    vb.Bind();
    ib.Bind();
    const auto& elements = layout.GetElements();

    int offset = 0;

    for (unsigned int i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)(uintptr_t)offset));
        offset += element.count * VertexBufferElement::GetTypeSize(element.type);
    }
}

void VertexArray::Bind() const { GLCall(glBindVertexArray(m_RenderedID)); }

void VertexArray::Unbind() const { GLCall(glBindVertexArray(0)); }
