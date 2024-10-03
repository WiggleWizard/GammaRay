#pragma once

#include <array>
#include <random>
#include <sstream>
#include <iomanip>
#include <string>

class UUID
{

public:
    // Default constructor generates a new UUID
    UUID()
    {
        Generate();
    }

    // Copy constructor
    UUID(const UUID& other) : data(other.data)
    {
    }

    // Copy assignment operator
    UUID& operator=(const UUID& other)
    {
        if (this != &other)
        {
            data = other.data;
        }
        return *this;
    }

    // Generate a new UUID for this object
    void regenerate()
    {
        Generate();
    }

    std::string ToString() const
    {
        std::stringstream ss;
        ss << std::hex << std::setfill('0');
        for (size_t i = 0; i < 16; ++i)
        {
            if (i == 4 || i == 6 || i == 8 || i == 10)
            {
                ss << '-';
            }
            ss << std::setw(2) << static_cast<int>(data[i]);
        }
        return ss.str();
    }

    const std::array<uint8_t, 16>& getBytes() const
    {
        return data;
    }

    bool operator==(const UUID& other) const
    {
        return data == other.data;
    }

    bool operator!=(const UUID& other) const
    {
        return !(*this == other);
    }
    
private:
    void Generate()
    {
        for (int i = 0; i < 16; ++i)
        {
            data[i] = static_cast<uint8_t>(dis(gen));
        }

        // Set version to 4
        data[6] = (data[6] & 0x0F) | 0x40;

        // Set variant to RFC4122
        data[8] = (data[8] & 0x3F) | 0x80;
    }
    
    std::array<uint8_t, 16> data;
    static inline std::random_device rd;
    static inline std::mt19937 gen;
    static inline std::uniform_int_distribution<> dis;
};
