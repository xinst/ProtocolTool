//*************************************************************************
// SingletonTemplate.h 2016-8-4 17:57
// Author: Stonexin
// Purpose: 
//
//*************************************************************************

#ifndef SINGLETONTEMPLATE_H__
#define SINGLETONTEMPLATE_H__

#include <iostream>

template <class T>
class SingletonTpl
{

public:

    SingletonTpl()
    {
        //assert( !m_instance );
        // �������ж�VC++�������汾���汾��ͬ��Ӧ�Ĵ���Ҳ��ͬ
#if defined( _MSC_VER ) && _MSC_VER < 1200
        int offset = (int)(T*)1 - (int)(Singleton <T>*)(T*)1;
        m_pInstance = (T*)((int)this + offset);
#else
        m_pInstance = static_cast< T* >(this);
#endif
    }

    ~SingletonTpl()
    {
       if (m_pInstance)
       {
		   m_pInstance = nullptr;
       }
    }

public:

    static T* GetSingletonPtr()
    {
        if (NULL == m_pInstance)
        {
            m_pInstance = new T;
        }

        return m_pInstance;
    }

    static T& GetSingletonRef()
    {
        return *GetSingletonPtr();
    }

    static T* Instance()
    {
        return GetSingletonPtr();
    }

    static T& InstanceRef()
    {
        return GetSingletonRef();
    }

    static void ReleaseInstance()
    {
        delete m_pInstance;
        m_pInstance = NULL;
    }

private:
    static T* m_pInstance;
};

template <class T>
T* SingletonTpl<T>::m_pInstance = NULL;



#endif // SINGLETONTEMPLATE_H__