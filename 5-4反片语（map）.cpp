/*
 问题描述：
 输入一些单词，找到所有满足条件的单词：该单词不能通过字母重排，得到其他单词，不分大小写
 输出时保留输入大小写。按字典序重排。
*/


/*
 函数：
 sort()函数:按字典序排序，参数：前后两个指针。
 length()函数:无参数，输出字符串长度。
 push_back()函数：尾后插入一个元素。参数：该元素。
 count()函数：algorithm头文件，其功能类似于find。这个函数使用一对迭代器和一个值做参数，返回这个值出现次数的统计结果。
 size()函数：和length()函数功能相同,但可以用在vector等容器中。sizeof()求对象所占内存大小。
*/




#include<iostream>
#include<string>
#include<cctype>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

map<string, int> cnt;
vector<string> words;//保存原单词

//函数将单词s进行“标准化”
string repr(const string &s)
{
	string ans = s;

	for (int i = 0; i < ans.length(); i++)//转换为小写字母
		ans[i] = tolower(ans[i]);

	sort(ans.begin(), ans.end());//排序string的元素

	return ans;
}

int main()
{
	int n = 0;
	string s;

	while (cin >> s)
	{
		if (s[0] == '#')//退出循环条件
			break;
		words.push_back(s);//将原单词在words中储存
		string r = repr(s);//将s“标准化”并传给r
		if (!cnt.count(r))//判断是否有r字符串并计数
			cnt[r] = 0;//没有则定义为0；
		cnt[r]++;//有则加1
	}

	vector<string> ans;

	for (int i = 0; i < words.size(); i++)//用for循环将words中符合条件的元素传给ans
		if (cnt[repr(words[i])] == 1)
			ans.push_back(words[i]);

	sort(ans.begin(), ans.end());//sort()函数排序ans内元素

	for (int i = 0; i < ans.size(); i++)//用for循环依次输出
		cout << ans[i] << "\n";

	return 0;
}