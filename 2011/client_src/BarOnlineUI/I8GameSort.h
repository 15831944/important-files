#pragma once

#include <algorithm>

//��Ϸ����ʽ�������������򣬶�����ֵ��Ϸһ��������ǰ�档
#define SORT_WINDOWS	0	//��windows��Դ������Ĭ�Ϸ�ʽ����
#define SORT_CLICK		1	//����Ϸ���������
#define SORT_FINDPOS    2   //ƥ��λ��

template<class TYPE, int N = SORT_WINDOWS>
struct Pred
{
    bool operator()(const TYPE* p1, const TYPE* p2)
    {
        int nLen1 = p1->Name.GetLength();
        int nLen2 = p2->Name.GetLength();
        int nLen = nLen1 > nLen2 ? nLen1 : nLen2;

        //��ֵ����ǰ
        if (p1->dwI8Play || p2->dwI8Play)
        {
            if (p1->dwI8Play && p2->dwI8Play)
            {
                if (p1->dwI8Play == p2->dwI8Play)
                    return p1->dwSvrClick > p2->dwSvrClick;
                return p1->dwI8Play > p2->dwI8Play;
            }
            if (p1->dwI8Play)
                return true;
            if (p2->dwI8Play)
                return false;
        }
        //��������Դ�����������з�ʽ���š�(����)
        return StrNCmpI(p1->Name, p2->Name, nLen) < 0;
    }
};

template<class TYPE>
struct Pred<TYPE, SORT_CLICK>
{
    bool operator()(const TYPE* p1, const TYPE* p2)
    {
        //��ֵ����ǰ
        if (p1->dwI8Play || p2->dwI8Play)
        {
            if (p1->dwI8Play && p2->dwI8Play)
            {
                if (p1->dwI8Play == p2->dwI8Play)
                    return p1->dwSvrClick > p2->dwSvrClick;
                return p1->dwI8Play > p2->dwI8Play;
            }

            if (p1->dwI8Play)
                return true;
            if (p2->dwI8Play)
                return false;
        }

        //�����������������
        return p1->dwSvrClick > p2->dwSvrClick;
    }
};

template<class TYPE>
struct Pred<TYPE, SORT_FINDPOS>
{
    bool operator()(const TYPE* p1, const TYPE* p2)
    {
        //������λ����������
        if (p1->nFindPos != p2->nFindPos)
        {
            return p1->nFindPos < p2->nFindPos;
        }

        int nLen1 = p1->Name.GetLength();
        int nLen2 = p2->Name.GetLength();
        int nLen = nLen1 > nLen2 ? nLen1 : nLen2;
        return StrNCmpI(p1->Name, p2->Name, nLen) < 0;
    }
};

template <class TYPE, int N>
void SortGameList(std::vector<const TYPE*>& List)
{
    std::sort(List.begin(), List.end(), Pred<TYPE, N>());

    //�������ʱ�鿴�����Ƿ���ȷ
    // 	for (size_t idx=0; idx<GameList.size(); idx++)
    // 	{
    // 		TCHAR szLog[MAX_PATH] = {0};
    // 		_stprintf_s(szLog, TEXT("%s-%d-%d\r\n"), (LPCTSTR)GameList[idx]->Name, 
    // 			GameList[idx]->dwSvrClick, GameList[idx]->dwI8Play);
    // 		OutputDebugString(szLog);
    // 	}
}
