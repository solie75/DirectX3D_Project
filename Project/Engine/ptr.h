#pragma once

template<typename T>
class Ptr
{
private:
	T* m_Res;

public:
	T* Get() const { return m_Res; }

	void operator = (T* _Res)
	{
		if (nullptr != m_Res)
		{
			m_Res->Release();
		}
		m_Res = _Res;
		if(nullptr != m_Res)
		{
			m_Res->AddRefCount();
		}
	}

	void operator = (const Ptr<T>& _Res)
	{
		if (nullptr != m_Res)
		{
			m_Res->Release();
		}
		m_Res = _Res.m_Res;
		
		if (nullptr != m_Res)
		{
			m_Res->AddRefCount();
		}
	}

	bool operator == (T* _Other)
	{
		return m_Res == _Other;
	}

	bool operator != (T* _Other)
	{
		return m_Res != _Other;
	}

	bool operator == (const Ptr<T>& _Other)
	{
		return m_Res == _Other.m_Res;
	}

	bool operator != (const Ptr<T>& _Other)
	{
		return m_Res != _Other.m_Res;
	}

	Ptr()
		: m_Res(nullptr)
	{};

	Ptr(T* _Res)
		: m_Res(_Res)
	{
		if (nullptr != m_Res)
		{
			m_Res->AddRefCount();
		}
	}

	Ptr(const Ptr<T>& _Other)
		: m_Res(_Other.m_Res)
	{
		if (nullptr != m_Res)
		{
			m_Res->AddRefCount();
		}
	}

	~Ptr()
	{
		if (nullptr != m_Res)
		{
			delete m_Res;
			m_Res = nullptr;
		}
	};
};