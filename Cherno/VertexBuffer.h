#pragma once


class VertexBuffer{

    private:
        // Keeping it generic so it makes sense to another tools
        unsigned int m_RendererID;
    public:
        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();
        // Possibly some extra methods that lock and unlock so data can be changed between renders
        // ...
        void Bind() const;
        void Unbind() const;

        
};