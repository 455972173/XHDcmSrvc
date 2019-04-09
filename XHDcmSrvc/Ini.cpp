#include "stdafx.h"
#include "Ini.h" 
#include <fstream> 
#include <stdlib.h> 
bool CIni::IsSpace(char c)
{
	if (' ' == c || '\t' == c)
	{
		return true;
	}
	return false;
}
bool CIni::IsCommentChar(char c)
{
	switch (c)
	{
	case '#':
		return true;
	default:
		return false;
	}
}
void CIni::Trim(string & str)
{
	if (str.empty())
	{
		return;
	}
	int i, start_pos, end_pos;
	for (i = 0; i < str.size(); ++i)
	{
		if (!IsSpace(str[i]))
		{
			break;
		}
	}
	if (i == str.size())
	{
		str = "";
		return;
	}
	start_pos = i;
	for (i = str.size() - 1; i >= 0; --i)
	{
		if (!IsSpace(str[i]))
		{
			break;
		}
	}
	end_pos = i;
	str = str.substr(start_pos, end_pos - start_pos + 1);
}
bool CIni::AnalyseLine(const string & line, string& section, string & key, string & value)
{
	if (line.empty())
	{
		return false;
	}
	int start_pos = 0, end_pos = line.size() - 1, pos, s_startpos, s_endpos;
	if ((pos = line.find("#")) != -1)
	{
		if (0 == pos)
		{
			return false;
		}
		end_pos = pos - 1;
	}
	if (((s_startpos = line.find("[")) != -1) && ((s_endpos = line.find("]"))) != -1)
	{
		section = line.substr(s_startpos + 1, s_endpos - 1);
		return true;
	}
	string new_line = line.substr(start_pos, start_pos + 1 - end_pos);
	if ((pos = new_line.find('=')) == -1)
	{
		return false;
	}
	key = new_line.substr(0, pos);
	value = new_line.substr(pos + 1, end_pos + 1 - (pos + 1));
	Trim(key);
	if (key.empty())
	{
		return false;
	} Trim(value);
	if ((pos = value.find("\r")) > 0)
	{
		value.replace(pos, 1, "");
	}
	if ((pos = value.find("\n")) > 0)
	{
		value.replace(pos, 1, "");
	}
	return true;
}
bool CIni::ReadConfig(const string & filename)
{
	settings_.clear();
	ifstream infile(filename.c_str());
	if (!infile)
	{
		return false;
	}
	string line, key, value, section;
	map<string, string> k_v;
	map<string, map<string, string> >::iterator it;
	while (getline(infile, line))
	{
		if (AnalyseLine(line, section, key, value))
		{
			it = settings_.find(section);
			if (it != settings_.end())
			{
				k_v[key] = value;
				it->second = k_v;
			}
			else
			{
				k_v.clear();
				settings_.insert(make_pair(section, k_v));
			}
		}
		key.clear();
		value.clear();
	}
	infile.close();
	return true;
}
string CIni::ReadString(const char* section, const char* item, const char* default_value)
{
	string tmp_s(section);
	string tmp_i(item);
	string def(default_value);
	map<string, string> k_v;
	map<string, string>::iterator it_item;
	map<string, map<string, string> >::iterator it;
	it = settings_.find(tmp_s);
	if (it == settings_.end())
	{
		return def;
	}
	k_v = it->second;
	it_item = k_v.find(tmp_i);
	if (it_item == k_v.end())
	{
		return def;
	}
	return it_item->second;
}
int CIni::ReadInt(const char* section, const char* item, const int& default_value)
{
	string tmp_s(section);
	string tmp_i(item);
	map<string, string> k_v;
	map<string, string>::iterator it_item;
	map<string, map<string, string> >::iterator it;
	it = settings_.find(tmp_s);
	if (it == settings_.end())
	{
		return default_value;
	}
	k_v = it->second;
	it_item = k_v.find(tmp_i);
	if (it_item == k_v.end())
	{
		return default_value;
	}
	return atoi(it_item->second.c_str());
}
float CIni::ReadFloat(const char* section, const char* item, const float& default_value)
{
	string tmp_s(section);
	string tmp_i(item);
	map<string, string> k_v;
	map<string, string>::iterator it_item;
	map<string, map<string, string> >::iterator it;
	it = settings_.find(tmp_s);
	if (it == settings_.end())
	{
		return default_value;
	}
	k_v = it->second;
	it_item = k_v.find(tmp_i);
	if (it_item == k_v.end())
	{
		return default_value;
	}
	return atof(it_item->second.c_str());
}