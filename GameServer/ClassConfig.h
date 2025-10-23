// ClassConfig.h - COMPLETE MULTI-CONFIG VERSION
#pragma once

#include <string>
#include <map>

struct ClassHexData
{
    int classCode;
    std::string className;
    std::string inventoryHex;
    std::string magicListHex;
    bool isConfigured;
};

class CClassConfigManager
{
public:
    CClassConfigManager();
    ~CClassConfigManager();

    void Initialize();

    // Multi-config support
    bool LoadConfigFile(int configIndex); // Load specific config (1-7)
    bool LoadAllConfigs(); // Load all available configs
    int GetAvailableConfigCount(); // How many configs exist

    // Get data from specific config
    ClassHexData* GetClassData(int classCode, int configIndex = 1);
    const char* GetInventoryHex(int classCode, int configIndex = 1);
    const char* GetMagicListHex(int classCode, int configIndex = 1);
    bool IsClassConfigured(int classCode, int configIndex = 1);

    // Save to specific config
    void SetClassData(int classCode, const char* invHex, const char* magicHex, int configIndex = 1);
    bool SaveConfigFile(int configIndex);

    // Get all classes for UI (from config 1)
    std::map<int, ClassHexData>& GetAllClasses() { return m_ClassData[0]; }

    // Get random config index based on enabled configs
    int GetRandomConfigIndex(int enabledConfigs);

private:
    bool LoadFromFile(const char* filePath, int configIndex);
    bool SaveToFile(const char* filePath, int configIndex);

    char m_ConfigBasePath[260];

    // Store up to 7 configurations (index 0-6 for Config 1-7)
    std::map<int, ClassHexData> m_ClassData[7];
    bool m_ConfigLoaded[7]; // Track which configs are loaded
};

extern CClassConfigManager g_ClassConfigManager;