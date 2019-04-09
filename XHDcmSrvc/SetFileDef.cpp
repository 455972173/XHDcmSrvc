#include "stdafx.h"
#include"SetFileDef.h"
bool ConfigFile::ReadConfigFile()
{
	fstream CurFile;
	CurFile.open(m_ConfigFilePath);
	if (!CurFile)
	{
		cout << m_ConfigFilePath << "²»´æÔÚ" << endl;
		return false;
	}
}