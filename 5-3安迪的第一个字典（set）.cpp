/*
 问题描述：
 输入文本，输出所有不同单词，按字典序输出。
*/

/*
 使用STL-集合-set
 函数和类：
 isalpha()函数：判断是否是字母字符，不是返回0.
 tolower()函数：将字母转换为小写字母。对应函数toupper()
 stringstream类：?????
 insert()函数：
 begin(),end()函数：迭代器数组首元素和尾后元素
*/

#include<iostream>
#include<string>
#include<set>
#include<sstream>
using namespace std;

set<string> dict; //string集合

int main()
{
	string s, buf;
	while (cin >> s)//常见的用输入作为判定条件，检查输入是否合法。
	{
        //for循环将文本“格式化”
		for (int i = 0; i < s.length(); i++)//要注意length()函数返回自定义的unsigned（非负整数）
			if (isalpha(s[i]))
				s[i] = tolower(s[i]);
			else
				s[i] = ' ';

		stringstream ss(s);

		while (ss >> buf)//常见的用输入作为判定条件，检查输入是否合法。
			dict.insert(buf);
	}
	for (auto it = dict.begin(); it != dict.end(); ++it)
		cout << *it << "\n";
	return 0;
}
//未完