#pragma once

#include <vector>
#include <string>
#include <cstring>
#include <stdexcept>

class Archive
{
public:
    Archive(bool inIsLoading = false) : isLoading(inIsLoading)
    {
    }

    bool IsLoading() const { return isLoading; }
    bool IsSaving() const { return !isLoading; }

    size_t Tell() const { return position; }
    void Seek(size_t newPos) { position = newPos; }

    size_t TotalSize() const { return data.size(); }

    const std::vector<uint8_t>& GetData() const { return data; }

    void SetData(const std::vector<uint8_t>& inData)
    {
        data = inData;
        position = 0;
    }

    template <typename T>
    Archive& operator<<(T& value)
    {
        SerializeCustomType(value);
        return *this;
    }

    // TODO: Revisit, this code isn't right
    template <typename T>
    void SerializeVector(std::vector<T>& vec)
    {
        int32_t sz = static_cast<int32_t>(vec.size());
        *this << sz;
        for (uint32 i = 0; i < sz; ++i)
        {
            T& value = vec[i];
            *this << value;
        }
    }

    Archive& operator<<(int32_t& value)
    {
        SerializeInternal(value);
        return *this;
    }

    Archive& operator<<(float& value)
    {
        SerializeInternal(value);
        return *this;
    }

    Archive& operator<<(std::string& value)
    {
        if (isLoading)
        {
            int32_t len;
            *this << len;
            if (len > 0)
            {
                value.resize(len);
                Serialize(value.data(), len);
            }
            else
            {
                value.clear();
            }
        }
        else
        {
            int32_t len = static_cast<int32_t>(value.length());
            *this << len;
            if (len > 0)
            {
                Serialize(value.data(), len);
            }
        }
        return *this;
    }

    void Serialize(void* ptr, size_t len)
    {
        if (isLoading)
        {
            if (position + len > data.size())
            {
                throw std::runtime_error("Reading past end of archive");
            }
            std::memcpy(ptr, &data[position], len);
        }
        else
        {
            if (position + len > data.size())
            {
                data.resize(position + len);
            }
            std::memcpy(&data[position], ptr, len);
        }
        position += len;
    }

private:
    std::vector<uint8_t> data;
    size_t position = 0;
    bool isLoading = false;

    template <typename T>
    void SerializeInternal(T& v)
    {
        if (isLoading)
        {
            if (position + sizeof(T) > data.size())
            {
                throw std::runtime_error("Reading past end of archive");
            }
            std::memcpy(&v, &data[position], sizeof(T));
        }
        else
        {
            if (position + sizeof(T) > data.size())
            {
                data.resize(position + sizeof(T));
            }
            std::memcpy(&data[position], &v, sizeof(T));
        }
        position += sizeof(T);
    }

    template <typename T, std::enable_if_t<!std::is_arithmetic_v<T> && !std::is_same_v<T, std::string>, int>  = 0>
    void SerializeCustomType(T& value)
    {
        value.Serialize(*this);
    }

    template <typename T, std::enable_if_t<std::is_arithmetic_v<T> || std::is_same_v<T, std::string>, int>  = 0>
    void SerializeCustomType(T& value)
    {
        *this << value;
    }
};
