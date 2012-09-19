#pragma once

template<class TYPE>
class CI8Trusteeship
{
    private:
        TYPE*          m_pData;      //���йܵ����ݵ�ָ��
        INT32          m_iCount;     //����Ԫ�ظ���
        mutable INT32* m_piRefCount; //���ü���
    public:
        inline CI8Trusteeship(void);
        inline CI8Trusteeship(int iCount);
        inline CI8Trusteeship(IN const CI8Trusteeship& clTrusteeship);
        inline ~CI8Trusteeship(void);
        inline void operator=(IN const CI8Trusteeship& clTrusteeship);
        inline void Apply(void);
        inline void ApplyArray(IN INT32 iCount);
        inline void Extend(IN INT32 iCount);
        inline INT32 GetCount(void) const;
        inline void SetCount(IN INT32 iCount);
        inline const TYPE* GetPointer(void) const;
        inline TYPE* Pointer(void);
        inline void Clear(void);
        inline TYPE& operator[](IN INT32 iIndex);
        inline const TYPE& operator[](IN INT32 iIndex) const;
        inline BOOL IsNull(void) const;
        inline void SetAll(IN const TYPE& Data);
        inline BOOL operator==(IN const CI8Trusteeship& clTrusteeship) const;
        inline BOOL operator!=(IN const CI8Trusteeship& clTrusteeship) const;
        inline void Copy(IN const CI8Trusteeship& clTrusteeship);
};

template <class TYPE>
CI8Trusteeship<TYPE>::CI8Trusteeship(void)
    : m_pData(NULL)
    , m_iCount(0)
    , m_piRefCount(NULL)
{
}
template <class TYPE>
CI8Trusteeship<TYPE>::CI8Trusteeship(int iCount)
    : m_pData(NULL)
    , m_iCount(0)
    , m_piRefCount(NULL)
{
    ApplyArray(iCount);
}
template <class TYPE>
CI8Trusteeship<TYPE>::CI8Trusteeship(
    IN const CI8Trusteeship& clTrusteeship //�й�
)
    : m_pData(NULL)
    , m_iCount(0)
    , m_piRefCount(NULL)
{
    operator=(clTrusteeship);
}
template <class TYPE>
CI8Trusteeship<TYPE>::~CI8Trusteeship(void)
{
    Clear();
}
template <class TYPE>
void
CI8Trusteeship<TYPE>::operator=(
    IN const CI8Trusteeship& clTrusteeship //�й�
)
{
    if (this != &clTrusteeship)
    {
        Clear();
        if (clTrusteeship.m_pData != NULL)
        {
            if (clTrusteeship.m_piRefCount == NULL)
            {
                clTrusteeship.m_piRefCount = new INT32;
                *clTrusteeship.m_piRefCount = 1;
            }
            m_piRefCount = clTrusteeship.m_piRefCount;
            m_pData = clTrusteeship.m_pData;
            m_iCount = clTrusteeship.m_iCount;
            ++(*clTrusteeship.m_piRefCount);
        }
    }
}
template <class TYPE>
void
CI8Trusteeship<TYPE>::Apply(void)
{
    Clear();
    m_pData = new TYPE[1];
    m_iCount = 1;
}
template <class TYPE>
void
CI8Trusteeship<TYPE>::ApplyArray(
    IN INT32 iCount //����Ԫ�ظ���
)
{
    if (iCount < 0)
    {
        assert(0 && "����Ĵ�С��������Ϊ�������");
    }
    Clear();
    m_pData = new TYPE[iCount];
    m_iCount = iCount;
}
template <class TYPE>
void
CI8Trusteeship<TYPE>::Extend(
    IN INT32 iCount //����Ԫ�ظ���
)
{
    if (m_piRefCount != NULL && (*m_piRefCount) > 1)
    {
        assert(0 && "�ڴ��ڱ��ദʹ��ʱ���޷���չ��С�ġ�");
    }
    if (iCount <= 0)
    {
        assert(0 && "����Ĵ�С��������Ϊ�������");
    }
    if (IsNull())
    {
        ApplyArray(iCount);
    }
    else
    {
        if (m_iCount != iCount)
        {
            TYPE *pData = new TYPE[iCount];
            TYPE *pDesData = pData,
                *pSrcData = m_pData;
            INT32 iCopyCount = m_iCount < iCount ? m_iCount : iCount;
            for (INT32 i = 0; i < iCopyCount; ++i)
            {
                *pDesData = *pSrcData;
                ++pDesData;
                ++pSrcData;
            }
            Clear();
            m_pData = pData;
            m_iCount = iCount;
        }
    }
}
template <class TYPE>
INT32  //�й�����Ԫ�ظ���
CI8Trusteeship<TYPE>::GetCount(void) const
{
    if (IsNull())
    {
        return 0;
    }
    else
    {
        return m_iCount;
    }
}
template <class TYPE>
void
CI8Trusteeship<TYPE>::SetCount(
    IN INT32 iCount //����Ԫ�ظ���
)
{
    if (iCount <= 0)
    {
        assert(0 && "����Ĵ�С��������Ϊ�������");
    }
    if (IsNull())
    {
        ApplyArray(iCount);
    }
    else
    {
        if (m_iCount != iCount)
        {
            ApplyArray(iCount);
        }
    }
}
template <class TYPE>
const TYPE* //�й�����ָ��
CI8Trusteeship<TYPE>::GetPointer(void) const
{
    if (IsNull())
    {
        assert(0 && "�ڴ�δ�����롣");
    }
    return m_pData;
}
template <class TYPE>
TYPE*  //�й�����ָ��
CI8Trusteeship<TYPE>::Pointer(void)
{
    if (IsNull())
    {
        assert(0 && "�ڴ�δ�����롣");
    }
    return m_pData;
}
template <class TYPE>
void
CI8Trusteeship<TYPE>::Clear(void)
{
    if (m_pData != NULL)
    {
        if (m_piRefCount != NULL)
        {
            if (*m_piRefCount == 1)
            {
                delete[] m_pData;
                m_pData = NULL;
                delete m_piRefCount;
                m_piRefCount = NULL;
            }
            else
            {
                if (*m_piRefCount <= 0)
                {
                    assert(0 && "�ڴ��ڱ��ദʹ��ʱ���޷���չ��С�ġ�");
                }
                else
                {
                    --(*m_piRefCount);
                    m_pData = NULL;
                    m_piRefCount = NULL;
                }
            }
        }
        else
        {
            delete[] m_pData;
            m_pData = NULL;
        }
        m_iCount = 0;
    }
    else
    {
        if (m_piRefCount != NULL)
        {
            assert(0 && "�����ݲ����������ü�����");
        }
    }
}
template <class TYPE>
TYPE&               //ָ�����ݵ�����
CI8Trusteeship<TYPE>::operator[](
    IN INT32 iIndex //����
)
{
    if (IsNull())
    {
        assert(0 && "�ڴ�δ�����롣");
    }
    if ((iIndex >= m_iCount) || (iIndex < 0))
    {
        assert(0 && "���������������");
    }
    return m_pData[iIndex];
}
template <class TYPE>
const TYPE&         //ָ�����ݵ�����
CI8Trusteeship<TYPE>::operator[](
    IN INT32 iIndex //����
) const
{
    if (IsNull())
    {
        assert(0 && "�ڴ�δ�����롣");
    }
    if ((iIndex >= m_iCount) || (iIndex < 0))
    {
        assert(0 && "���������������");
    }
    return m_pData[iIndex];
}
template <class TYPE>
BOOL   //û�����ݱ�����
CI8Trusteeship<TYPE>::IsNull(void) const
{
    return m_pData == NULL;
}
template <class TYPE>
void
CI8Trusteeship<TYPE>::SetAll(
    IN const TYPE& Data //ֵ
)
{
    if (IsNull())
    {
        assert(0 && "�ڴ�δ�����롣");
    }
    for(INT32 i = 0; i < m_iCount; ++i)
    {
        m_pData[i] = Data;
    }
}
template <class TYPE>
BOOL                                       //����������ͬ
CI8Trusteeship<TYPE>::operator==(
    IN const CI8Trusteeship& clTrusteeship //�й�
) const
{
    if (IsNull())
    {
        if(clTrusteeship.IsNull())
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        if(clTrusteeship.IsNull())
        {
            return FALSE;
        }
        else
        {
            if (m_iCount == clTrusteeship.m_iCount)
            {
                for (INT32 i = 0; i < m_iCount; ++i)
                {
                    if (m_pData[i] != clTrusteeship.m_pData[i])
                    {
                        return FALSE;
                    }
                }
                return TRUE;
            }
            else
            {
                return FALSE;
            }
        }
    }
}
template <class TYPE>
BOOL                                       //�������ݲ���ͬ
CI8Trusteeship<TYPE>::operator!=(
    IN const CI8Trusteeship& clTrusteeship //�й�
) const
{
    return !operator==(clTrusteeship);
}
template <class TYPE>
void
CI8Trusteeship<TYPE>::Copy(
    IN const CI8Trusteeship& clTrusteeship //�й�
)
{
    if (clTrusteeship.IsNull())
    {
        Clear();
    }
    else
    {
        SetCount(clTrusteeship.GetCount());
        for (INT32 i = 0; i < m_iCount; ++i)
        {
            m_pData[i] = clTrusteeship.m_pData[i];
        }
    }
}