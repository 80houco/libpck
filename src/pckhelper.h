#pragma once

#include <string>
#include <vector>
#include <algorithm>

// ���ļ�����Ϊpck�ڵı�׼��ʽ
inline std::string NormalizePckFileName(const std::string& filename)
{
	std::vector<char> buf(filename.begin(), filename.end());
	
	// ������ '/' �滻Ϊ '\'
	std::replace_if(buf.begin(), buf.end(), [](auto i) { return i == '/'; }, '\\');
	
	// �Ѷ�� '\' �滻Ϊ����
	buf.resize(std::distance(buf.begin(), std::unique(buf.begin(), buf.end(), [](auto i, auto j) { return i == j && i == '\\'; })));

	std::string ret(buf.begin(), buf.end());
	ret.erase(0, ret.find_first_not_of(" \r\n\t\\"));
	ret.erase(ret.find_last_not_of(" \r\n\t\\") + 1);

	if (ret.size() > 255)
		throw std::runtime_error("�ļ������ȳ�������");

	return std::move(ret);
}
