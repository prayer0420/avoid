#pragma once
#include <iostream>
#include <assert.h>


class MyString
{
private:
	wchar_t* str;	//넓은 문자를 저장하는 동적 배열
	int length;		// 문자열의 길이

	//문자열 길이 계산 함수
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

	//문자열 복사 함수
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

	//문자열 연결 함수
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

	//문자열 비교 함수
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
	//기본 생성자 : 빈문자열로 초기화
	MyString()
		:str(nullptr)
		, length(0)
	{
		str = new wchar_t[1];
		str[0] = L'\0'; //빈 문자열을 나타내기 위해 NULL 종료 문자 설정
	}
	
	//넓은 문자열을 받아 초기화 하는 생성자
	MyString(const wchar_t* other)
	{
		length = my_wcslen(other);					//전달된 문자열의 길이를 계산
		str = new wchar_t[length + 1];				//문자열길이 + null종료문자 크기로 메모리 할당
		my_wcscpy(str, other);						//전달된 문자열을 내부 배열에 복사
	}

	//복사생성자
	MyString(const MyString& other)
	{
		length = other.length;						//복사할 문자열의 길이를 복사
		str = new wchar_t[length + 1];				//동일한 길이로 메모리 할당
		my_wcscpy(str, other.str);					//문자열 복사
	}

	//대입 연산자 오버로드
	MyString& operator =(const MyString& other)
	{
		if (this == &other)							// 자기 자신과의 대입 방지
		{
			return *this;
		}
		else
		{
			delete[] str;							// 기존 메모리 해제
			length = other.length;					// 새로운 길이 설정
			str = new wchar_t[length + 1];			// 새로운 메모리 할당
			my_wcscpy(str, other.str);				// 문자열 복사
		}
		return *this;
	}

	//소멸자: 동적 메모리 해제
	~MyString()
	{
		delete[] str;
	}

	//길이 반환 함수
	int size()
	{
		return length;
	}

	//문자열 연결(concatenation)
	MyString operator+(const MyString& other)
	{
		MyString result;							//결과로 반환할 새로운 문자열
		result.length = length + other.length;		//두 문자열의 길이를 합침
		result.str = new wchar_t[result.length];	//새로운 크기로 메모리 할당

		my_wcscpy(result.str, str);					//첫번째 문자열 복사
		my_wcscat(result.str, other.str);			//두번째 문자열을 이어 붙임

		return result;
	}

	//문자열 비교(==연산자 오버로드)
	bool operator == (const MyString& other)
	{
		return my_wcscmp(str, other.str) == 0;		//두 문자열이 동일하면 0을 반환
	}
	//문자열 출력(<<연산자 오버로드)
	friend std::wostream& operator << (std::wostream& os, const MyString& myStr)
	{
		os << myStr.str; //넓은 문자열 출력
		return os;
	}



};