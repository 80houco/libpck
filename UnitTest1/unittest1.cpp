#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\libpck2\pckfile.h"
#include "..\libpck2\pckitem.h"
#include <sstream>
#include "../libpck2/stringhelper.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(Pck���Ĺ���)
	{
		shared_ptr<PckFile> pck;
	public:
		Pck���Ĺ���()
		{
			pck = PckFile::Open("Z:\\gfx.pck");
		}

		TEST_METHOD(����ļ���)
		{
			stringstream ss;
			ss << "�ļ�����" << pck->GetFileCount() << endl;
			Logger::WriteMessage(ss.str().c_str());
		}

		TEST_METHOD(����ļ�����)
		{
			auto& item1 = pck->GetSingleFileItem(0);
			auto& item2 = pck->GetSingleFileItem(item1.GetFileName());
			Assert::IsTrue(&item1 == &item2);
		}

		TEST_METHOD(ͳ����Ϣ)
		{
			stringstream ss;
			size_t s1, s2, s3, s4, s5;
			s1 = pck->GetTotalCipherDataSize();
			s2 = pck->GetTotalDataSize();
			s3 = pck->GetRedundancySize();
			s4 = pck->GetFileSize();
			s5 = pck->GetIndexTableSize();
			ss << "�ļ���С��" << s4 / 1024 / 1024 << " MB" << endl;
			ss << "��������" << s1 / 1024 / 1024 << " MB" << endl;
			ss << "��ѹ��" << s2 / 1024 / 1024 << " MB" << endl;
			ss << "������" << s5 / 1024 << " KB" << endl;
			ss << "�������ݣ�" << s3 / 1024 / 1024 << " MB" << endl;
			ss << "ѹ���ʣ�" << (double)s1 / s2 << endl;
			ss << "�����ʣ�" << (double)s3 / s4 << endl;
			Logger::WriteMessage(ss.str().c_str());
		}

		TEST_METHOD(��ѹ)
		{
			pck->Extract("Z:\\");
		}
	};

	TEST_CLASS(��������)
	{
	public:
#define TESTSTRA "1234�������abcd"
#define TESTSTRW L"1234�������abcd"
		TEST_METHOD(����ת��_A2W)
		{
			auto loc = std::locale("chinese-simplified_china.936");
			std::string s = TESTSTRA;
			Assert::AreEqual(StringHelper::A2W(s, loc).c_str(), TESTSTRW);
		}

		TEST_METHOD(����ת��_W2A)
		{
			auto loc = std::locale("zh-CN");
			std::wstring s = TESTSTRW;
			Assert::AreEqual(StringHelper::W2A(s, loc).c_str(), TESTSTRA);
		}
	};
}