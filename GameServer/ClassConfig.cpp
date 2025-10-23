// ClassConfig.cpp - COMPLETE MULTI-CONFIG VERSION
#include "stdafx.h"
#include "ClassConfig.h"
#include "Util.h"
#include <fstream>

CClassConfigManager g_ClassConfigManager;

CClassConfigManager::CClassConfigManager()
{
    sprintf_s(m_ConfigBasePath, sizeof(m_ConfigBasePath), "IA\\AccountsInventory\\");
    memset(m_ConfigLoaded, 0, sizeof(m_ConfigLoaded));
}

CClassConfigManager::~CClassConfigManager()
{
}

void CClassConfigManager::Initialize()
{
    // Default hex data
    const char* defaultInv = "0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
    const char* defaultMagic = "0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";

    // Initialize all 7 configs with default data
    for (int config = 0; config < 7; config++)
    {
        ClassHexData dw = { 0, "Dark Wizard (DW)", defaultInv, defaultMagic, false };
        ClassHexData dk = { 16, "Dark Knight (DK)", defaultInv, defaultMagic, false };
        ClassHexData elf = { 32, "Elf (ELF)", defaultInv, defaultMagic, false };
        ClassHexData mg = { 48, "Magic Gladiator (MG)", defaultInv, defaultMagic, false };
        ClassHexData dl = { 64, "Dark Lord (DL)", defaultInv, defaultMagic, false };
        ClassHexData sum = { 80, "Summoner (SUM)", defaultInv, defaultMagic, false };
        ClassHexData rf = { 96, "Rage Fighter (RF)", defaultInv, defaultMagic, false };

        m_ClassData[config][0] = dw;
        m_ClassData[config][16] = dk;
        m_ClassData[config][32] = elf;
        m_ClassData[config][48] = mg;
        m_ClassData[config][64] = dl;
        m_ClassData[config][80] = sum;
        m_ClassData[config][96] = rf;
    }

    // Load all available configs
    LoadAllConfigs();
}

bool CClassConfigManager::LoadAllConfigs()
{
    int loadedCount = 0;

    for (int i = 1; i <= 7; i++)
    {
        if (LoadConfigFile(i))
        {
            loadedCount++;
        }
    }

    if (loadedCount > 0)
    {
        LogAdd(LOG_GREEN, "[ClassConfig] Loaded %d configuration files", loadedCount);
    }
    else
    {
        LogAdd(LOG_BLUE, "[ClassConfig] No config files found, using defaults");
    }

    return (loadedCount > 0);
}

bool CClassConfigManager::LoadConfigFile(int configIndex)
{
    if (configIndex < 1 || configIndex > 7)
    {
        LogAdd(LOG_RED, "[ClassConfig] Invalid config index: %d", configIndex);
        return false;
    }

    char filePath[260];
    if (configIndex == 1)
    {
        sprintf_s(filePath, sizeof(filePath), "%sClassConfig.ini", m_ConfigBasePath);
    }
    else
    {
        sprintf_s(filePath, sizeof(filePath), "%sClassConfig%d.ini", m_ConfigBasePath, configIndex);
    }

    return LoadFromFile(filePath, configIndex - 1); // Array index 0-6
}

bool CClassConfigManager::LoadFromFile(const char* filePath, int configIndex)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        return false;
    }

    std::string line;
    int currentClass = -1;
    bool readingInventory = false;
    bool readingMagic = false;
    std::string currentHex;

    while (std::getline(file, line))
    {
        // Remove whitespace
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        if (!line.empty())
        {
            line.erase(line.find_last_not_of(" \t\r\n") + 1);
        }

        if (line.empty() || line[0] == ';') continue;

        if (line.find("[CLASS_") == 0)
        {
            // Save previous class data if any
            if (currentClass != -1 && !currentHex.empty())
            {
                if (readingInventory)
                {
                    m_ClassData[configIndex][currentClass].inventoryHex = currentHex;
                }
                else if (readingMagic)
                {
                    m_ClassData[configIndex][currentClass].magicListHex = currentHex;
                    m_ClassData[configIndex][currentClass].isConfigured = true;
                }
                currentHex.clear();
            }

            // Parse class code
            size_t start = line.find("_") + 1;
            size_t end = line.find("]");
            if (start != std::string::npos && end != std::string::npos)
            {
                currentClass = atoi(line.substr(start, end - start).c_str());
                readingInventory = false;
                readingMagic = false;
            }
        }
        else if (line == "INVENTORY=")
        {
            readingInventory = true;
            readingMagic = false;
            currentHex.clear();
        }
        else if (line == "MAGICLIST=")
        {
            if (currentClass != -1 && !currentHex.empty())
            {
                m_ClassData[configIndex][currentClass].inventoryHex = currentHex;
            }
            readingInventory = false;
            readingMagic = true;
            currentHex.clear();
        }
        else if (readingInventory || readingMagic)
        {
            currentHex += line;
        }
    }

    // Save last class
    if (currentClass != -1 && !currentHex.empty())
    {
        if (readingMagic)
        {
            m_ClassData[configIndex][currentClass].magicListHex = currentHex;
            m_ClassData[configIndex][currentClass].isConfigured = true;
        }
    }

    file.close();
    m_ConfigLoaded[configIndex] = true;
    LogAdd(LOG_GREEN, "[ClassConfig] Loaded Config %d successfully", configIndex + 1);
    return true;
}

bool CClassConfigManager::SaveConfigFile(int configIndex)
{
    if (configIndex < 1 || configIndex > 7)
    {
        LogAdd(LOG_RED, "[ClassConfig] Invalid config index: %d", configIndex);
        return false;
    }

    char filePath[260];
    if (configIndex == 1)
    {
        sprintf_s(filePath, sizeof(filePath), "%sClassConfig.ini", m_ConfigBasePath);
    }
    else
    {
        sprintf_s(filePath, sizeof(filePath), "%sClassConfig%d.ini", m_ConfigBasePath, configIndex);
    }

    return SaveToFile(filePath, configIndex - 1);
}

bool CClassConfigManager::SaveToFile(const char* filePath, int configIndex)
{
    std::ofstream file(filePath);
    if (!file.is_open())
    {
        LogAdd(LOG_RED, "[ClassConfig] Cannot save config file: %s", filePath);
        return false;
    }

    file << "; Class Configuration File #" << (configIndex + 1) << "\n";
    file << "; Format: [CLASS_X] where X is class code\n";
    file << "; INVENTORY= followed by hex data\n";
    file << "; MAGICLIST= followed by hex data\n\n";

    for (std::map<int, ClassHexData>::iterator it = m_ClassData[configIndex].begin();
        it != m_ClassData[configIndex].end(); ++it)
    {
        ClassHexData& data = it->second;

        file << "[CLASS_" << data.classCode << "] ; " << data.className << "\n";
        file << "INVENTORY=\n";
        file << data.inventoryHex << "\n\n";
        file << "MAGICLIST=\n";
        file << data.magicListHex << "\n\n";
    }

    file.close();
    m_ConfigLoaded[configIndex] = true;
    LogAdd(LOG_GREEN, "[ClassConfig] Saved Config %d successfully", configIndex + 1);
    return true;
}

int CClassConfigManager::GetAvailableConfigCount()
{
    int count = 0;
    for (int i = 0; i < 7; i++)
    {
        if (m_ConfigLoaded[i])
        {
            count++;
        }
    }
    return count;
}

ClassHexData* CClassConfigManager::GetClassData(int classCode, int configIndex)
{
    if (configIndex < 1 || configIndex > 7)
    {
        return NULL;
    }

    int arrayIndex = configIndex - 1;
    std::map<int, ClassHexData>::iterator it = m_ClassData[arrayIndex].find(classCode);
    if (it != m_ClassData[arrayIndex].end())
    {
        return &it->second;
    }
    return NULL;
}

void CClassConfigManager::SetClassData(int classCode, const char* invHex, const char* magicHex, int configIndex)
{
    if (configIndex < 1 || configIndex > 7)
    {
        return;
    }

    int arrayIndex = configIndex - 1;
    std::map<int, ClassHexData>::iterator it = m_ClassData[arrayIndex].find(classCode);
    if (it != m_ClassData[arrayIndex].end())
    {
        it->second.inventoryHex = invHex;
        it->second.magicListHex = magicHex;
        it->second.isConfigured = true;
        SaveConfigFile(configIndex);
    }
}

bool CClassConfigManager::IsClassConfigured(int classCode, int configIndex)
{
    if (configIndex < 1 || configIndex > 7)
    {
        return false;
    }

    int arrayIndex = configIndex - 1;
    std::map<int, ClassHexData>::iterator it = m_ClassData[arrayIndex].find(classCode);
    if (it != m_ClassData[arrayIndex].end())
    {
        return it->second.isConfigured;
    }
    return false;
}

const char* CClassConfigManager::GetInventoryHex(int classCode, int configIndex)
{
    if (configIndex < 1 || configIndex > 7)
    {
        return "";
    }

    int arrayIndex = configIndex - 1;
    std::map<int, ClassHexData>::iterator it = m_ClassData[arrayIndex].find(classCode);
    if (it != m_ClassData[arrayIndex].end())
    {
        return it->second.inventoryHex.c_str();
    }
    return "";
}

const char* CClassConfigManager::GetMagicListHex(int classCode, int configIndex)
{
    if (configIndex < 1 || configIndex > 7)
    {
        return "";
    }

    int arrayIndex = configIndex - 1;
    std::map<int, ClassHexData>::iterator it = m_ClassData[arrayIndex].find(classCode);
    if (it != m_ClassData[arrayIndex].end())
    {
        return it->second.magicListHex.c_str();
    }
    return "";
}

int CClassConfigManager::GetRandomConfigIndex(int enabledConfigs)
{
    // enabledConfigs is a bitmask: 1=Config1, 2=Config2, 4=Config3, etc.
    int availableConfigs[7];
    int count = 0;

    for (int i = 0; i < 7; i++)
    {
        if ((enabledConfigs & (1 << i)) && m_ConfigLoaded[i])
        {
            availableConfigs[count++] = i + 1; // Store as 1-7
        }
    }

    if (count == 0)
    {
        return 1; // Default to config 1
    }

    // Return random config from enabled ones
    return availableConfigs[GetLargeRand() % count];
}