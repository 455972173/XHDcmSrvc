#include "stdafx.h"
#include "OptFileDef.h"
bool OptConfigFile::ReadConfigFile(string SetupFilePath)
{
	m_ConfigFilePath = SetupFilePath;
	if (!m_IniConfig.ReadConfig(m_ConfigFilePath))
	{
		return false;
	}
	return true;
}