#include "stdafx.h"
#include "CppUnitTest.h"
#include <sstream>
#include "../include/pckfile.h"
#include "../include/pckitem.h"
#include "../include/pckfile_c.h"
#include "../include/stringhelper.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(Pck���Ĺ���)
	{
		shared_ptr<PckFile> pck;
	public:
		Pck���Ĺ���()
		{
			pck = PckFile::Open("E:\\����3\\element\\gfx.pck");
			//pck = PckFile::Open("Z:\\configs.pck");
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

		TEST_METHOD(����ļ�����_���淶���ļ�����ʽ)
		{
			auto& item1 = pck->GetSingleFileItem("//gfx\\\\//version.sw");
			Logger::WriteMessage(item1.GetFileName());
		}

		TEST_METHOD(ͳ����Ϣ)
		{
			stringstream ss;
			size_t s1, s2, s3, s4, s5;
			s1 = pck->GetTotalCompressDataSize();
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

	TEST_CLASS(�½�PCK)
	{
		shared_ptr<PckFile> pck;
	public:
		�½�PCK()
		{
			pck = PckFile::Create("Z:\\test.pck", true);
		}

		TEST_METHOD(����ļ�)
		{
			pck->AddItem("D:\\User\\Desktop\\����.txt", "test\\����.txt");
		}
	};

	TEST_CLASS(�޸�PCK)
	{
		shared_ptr<PckFile> pck;
	public:
		�޸�PCK()
		{
			pck = PckFile::Open("Z:\\configs.pck", false);
		}

		TEST_METHOD(����ļ�)
		{
			stringstream ss;
			ss << "����ļ�ǰ��" << endl;
			ss << "�ļ�����" << pck->GetFileCount() << endl;
			ss << "�ļ���С��" << pck->GetFileSize() << endl;
			ss << "��������" << pck->GetTotalCompressDataSize() << endl;
			ss << "���ࣺ" << pck->GetRedundancySize() << endl;
			ss << "������" << pck->GetIndexTableSize() << endl;

			pck->AddItem("D:\\User\\Desktop\\����.txt", "test\\����.txt");

			ss << "����ļ���" << endl;
			ss << "�ļ�����" << pck->GetFileCount() << endl;
			ss << "�ļ���С��" << pck->GetFileSize() << endl;
			ss << "��������" << pck->GetTotalCompressDataSize() << endl;
			ss << "���ࣺ" << pck->GetRedundancySize() << endl;
			ss << "������" << pck->GetIndexTableSize() << endl;

			Logger::WriteMessage(ss.str().c_str());
			auto data = pck->GetSingleFileItem("test\\����.txt").GetData();
			auto pstr = (char*)data.data();
			Logger::WriteMessage(pstr);
		}

		TEST_METHOD(ɾ���ļ�)
		{
			pck->DeleteItem((*pck)[0]);
		}
	};

	TEST_CLASS(����PCK)
	{
	public:
		TEST_METHOD(�ؽ�)
		{
			//PckFile::ReBuild("E:\\����3\\element\\gfx.pck", "Z:\\new.pck", true);
			Pck_ReBuild("E:\\����3\\element\\gfx.pck", "Z:\\new.pck", true);
		}

		TEST_METHOD(��Ŀ¼����)
		{
			PckFile::CreateFromDirectory("Z:\\test.pck", "Z:\\npm", false, true, [](auto i, auto t) {
				stringstream ss;
				ss << i << " / " << t << endl;
				Logger::WriteMessage(ss.str().c_str());
				return true;
			});
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