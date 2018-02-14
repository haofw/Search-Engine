#include <iostream> 
#include <fstream> 
#include <string> 

using namespace std;
void checkName(string& line)
{
	int l = line.length();
	for (int k = 0; k < l; k++)
	{
		if (line[k] < 65 || (line[k]>90 && line[k] < 97) || line[k]>122)
		{
			for (int j = k; j < l; j++)
				line[j] = line[j + 1];
			l--;
			k--; //此行有误，两个非法值在一起就算不出来了
		}
	}
}
int main()
{
	string line = "this@ is. a.test.string!";
	checkName(line);
	
	cout << line << endl;
	return 0;
}
