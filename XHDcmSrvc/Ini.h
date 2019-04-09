//∂¡ŒÔ.ini≈‰÷√Œƒº˛
#ifndef  _INI_H_
#define  _INI_H_
#include <string> 
#include <map> 
using namespace std;
class CIni
{
	public: 
		CIni()
		{
		}
		~CIni()
		{
		}
		bool ReadConfig(const string & filename);
		string ReadString(const char* section, const char* item, const char* default_value);
		int ReadInt(const char* section, const char* item, const int& default_value);
		float ReadFloat(const char* section, const char* item, const float& default_value);
	private: 
		bool IsSpace(char c);
		bool IsCommentChar(char c);
		void Trim(string & str);
		bool AnalyseLine(const string & line, string& section, string & key, string & value);
	private:
		map<string, map<string, string> >settings_;
};






#endif // ! _INI_H_



