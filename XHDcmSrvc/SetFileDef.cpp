#include "stdafx.h"
#include"SetFileDef.h"

bool ConfigFile::ReadConfigFile(string SetupFilePath)
{
	m_ConfigFilePath = SetupFilePath;
	if (!m_IniConfig.ReadConfig(m_ConfigFilePath))
	{
		return false;
	}
	return true;
}