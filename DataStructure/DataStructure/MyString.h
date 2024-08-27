#pragma once
#include <iostream>
#include <assert.h>


class MyString
{
private:
	wchar_t* str;	//���� ���ڸ� �����ϴ� ���� �迭
	int length;		// ���ڿ��� ����

	//���ڿ� ���� ��� �Լ�
	int my_wcslen(const wchar_t* s)
	{
		int len = 0;
		while (true)
		{
			if (s[len] == L'\0')
			{
				break;
			}
			len++;
		}
		return len;
	}

	//���ڿ� ���� �Լ�
	void my_wcscpy(wchar_t* dest, const wchar_t* source)
	{
		int i = 0;

		while (source[i] != L'\0')
		{
			dest[i] = source[i];
			i++;
		}
		dest[i] = L'\0';
	}

	//���ڿ� ���� �Լ�
	void my_wcscat(wchar_t* dest, const wchar_t* source)
	{
		int dest_len = my_wcslen(dest);
		int i = 0;
		while (source[i] != L'\0')
		{
			dest[dest_len + i] = source[i];
			i++;
		}
		dest[dest_len + i] = L'\0';
	}

	//���ڿ� �� �Լ�
	int my_wcscmp(const wchar_t* s1, const wchar_t* s2)
	{
		int i = 0;
		while (s1[i] != L'\0' && s2[i] != L'\0')
		{
			if (s1[i] != s2[i]) 
			{
				return s1[i] - s2[i];
			}
			i++;
		}
		return s1[i] - s2[i];
	}

public:
	//�⺻ ������ : ���ڿ��� �ʱ�ȭ
	MyString()
		:str(nullptr)
		, length(0)
	{
		str = new wchar_t[1];
		str[0] = L'\0'; //�� ���ڿ��� ��Ÿ���� ���� NULL ���� ���� ����
	}
	
	//���� ���ڿ��� �޾� �ʱ�ȭ �ϴ� ������
	MyString(const wchar_t* other)
	{
		length = my_wcslen(other);					//���޵� ���ڿ��� ���̸� ���
		str = new wchar_t[length + 1];				//���ڿ����� + null���Ṯ�� ũ��� �޸� �Ҵ�
		my_wcscpy(str, other);						//���޵� ���ڿ��� ���� �迭�� ����
	}

	//���������
	MyString(const MyString& other)
	{
		length = other.length;						//������ ���ڿ��� ���̸� ����
		str = new wchar_t[length + 1];				//������ ���̷� �޸� �Ҵ�
		my_wcscpy(str, other.str);					//���ڿ� ����
	}

	//���� ������ �����ε�
	MyString& operator =(const MyString& other)
	{
		if (this == &other)							// �ڱ� �ڽŰ��� ���� ����
		{
			return *this;
		}
		else
		{
			delete[] str;							// ���� �޸� ����
			length = other.length;					// ���ο� ���� ����
			str = new wchar_t[length + 1];			// ���ο� �޸� �Ҵ�
			my_wcscpy(str, other.str);				// ���ڿ� ����
		}
		return *this;
	}

	//�Ҹ���: ���� �޸� ����
	~MyString()
	{
		delete[] str;
	}

	//���� ��ȯ �Լ�
	int size()
	{
		return length;
	}

	//���ڿ� ����(concatenation)
	MyString operator+(const MyString& other)
	{
		MyString result;							//����� ��ȯ�� ���ο� ���ڿ�
		result.length = length + other.length;		//�� ���ڿ��� ���̸� ��ħ
		result.str = new wchar_t[result.length];	//���ο� ũ��� �޸� �Ҵ�

		my_wcscpy(result.str, str);					//ù��° ���ڿ� ����
		my_wcscat(result.str, other.str);			//�ι�° ���ڿ��� �̾� ����

		return result;
	}

	//���ڿ� ��(==������ �����ε�)
	bool operator == (const MyString& other)
	{
		return my_wcscmp(str, other.str) == 0;		//�� ���ڿ��� �����ϸ� 0�� ��ȯ
	}
	//���ڿ� ���(<<������ �����ε�)
	friend std::wostream& operator << (std::wostream& os, const MyString& myStr)
	{
		os << myStr.str; //���� ���ڿ� ���
		return os;
	}



};