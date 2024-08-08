#pragma once


class IndexBuffer{

    private:
        // Keeping it generic so it makes sense to another tools
        unsigned int m_RendererID;
        unsigned int m_Count;
    public:
        IndexBuffer(const unsigned int* data, unsigned int count);
        ~IndexBuffer();
        // Possibly some extra methods that lock and unlock so data can be changed between renders
        // ...
        void Bind() const;
        void Unbind() const;

        inline unsigned int GetCount() const {return m_Count;};
        
};