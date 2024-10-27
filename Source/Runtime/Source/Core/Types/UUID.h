#pragma once

#include <array>
#include <random>
#include <sstream>
#include <iomanip>
#include <string>
#include <functional>

class UUID
{
public:
    // Default constructor generates a new UUID
    UUID()
    {
        Generate();
    }

    // Constructor from string
    explicit UUID(const std::string& uuidString) { FromString(uuidString); }

    // Constructor from raw bytes
    explicit UUID(const std::array<uint8_t, 16>& bytes) : data(bytes)
    {
    }

    static UUID CreateInvalid()
    {
        UUID uuid;
        uuid.Invalidate();
        return uuid;
    }

    bool IsValid() const
    {
        return isValid;
    }

    void Invalidate()
    {
        isValid = false;
    }

    // Generate a new UUID for this object
    void Regenerate() { Generate(); }

    std::string ToString() const
    {
        if (!isValid)
            return "INVALID_UUID";

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

    const std::array<uint8_t, 16>& GetBytes() const { return data; }

    bool operator==(const UUID& other) const
    {
        return isValid == other.isValid && (isValid ? data == other.data : true);
    }

    bool operator!=(const UUID& other) const { return !(*this == other); }
    bool operator<(const UUID& other) const
    {
        if (isValid != other.isValid) return isValid < other.isValid;
        return isValid ? data < other.data : false;
    }

    // Parse UUID from string
    void FromString(const std::string& uuidString)
    {
        if (uuidString == "INVALID_UUID")
        {
            Invalidate();
            return;
        }

        std::stringstream ss(uuidString);
        std::array<uint32_t, 5> segments;
        char dash;

        if (!(ss >> std::hex >> segments[0] >> dash >> segments[1] >> dash >> segments[2] >> dash >> segments[3] >> dash >> segments[4]))
        {
            Invalidate();
            return;
        }

        data[0] = (segments[0] >> 24) & 0xFF;
        data[1] = (segments[0] >> 16) & 0xFF;
        data[2] = (segments[0] >> 8) & 0xFF;
        data[3] = segments[0] & 0xFF;
        data[4] = (segments[1] >> 8) & 0xFF;
        data[5] = segments[1] & 0xFF;
        data[6] = (segments[2] >> 8) & 0xFF;
        data[7] = segments[2] & 0xFF;
        data[8] = (segments[3] >> 8) & 0xFF;
        data[9] = segments[3] & 0xFF;
        data[10] = (segments[4] >> 24) & 0xFF;
        data[11] = (segments[4] >> 16) & 0xFF;
        data[12] = (segments[4] >> 8) & 0xFF;
        data[13] = segments[4] & 0xFF;
        
        // Handle the last two bytes separately
        uint32_t lastTwoBytes;
        ss >> lastTwoBytes;
        data[14] = (lastTwoBytes >> 8) & 0xFF;
        data[15] = lastTwoBytes & 0xFF;

        isValid = true;
    }

private:
    void Generate()
    {
        static thread_local std::random_device rd;
        static thread_local std::mt19937 gen(rd());
        static thread_local std::uniform_int_distribution<> dis(0, 255);

        for (int i = 0; i < 16; ++i)
        {
            data[i] = static_cast<uint8_t>(dis(gen));
        }

        // Set version to 4
        data[6] = (data[6] & 0x0F) | 0x40;

        // Set variant to RFC4122
        data[8] = (data[8] & 0x3F) | 0x80;

        isValid = true;
    }

    std::array<uint8_t, 16> data;
    bool isValid = false;
};

// Hash function for UUID
namespace std
{
    template <>
    struct hash<UUID>
    {
        size_t operator()(const UUID& uuid) const
        {
            if (!uuid.IsValid())
                return 0;
            
            const auto& bytes = uuid.GetBytes();
            return std::hash<std::string_view>{}(std::string_view(reinterpret_cast<const char*>(bytes.data()), bytes.size()));
        }
    };
}
