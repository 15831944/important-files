#pragma once

#include "I8BGCache.h"
#include "I8BGImage.h"
#include "I8SkinBitmap.h"

namespace I8SkinCtrl_ns
{
    class CI8LabelWnd : public CWnd
    {
        DECLARE_MESSAGE_MAP()
        DECLARE_DYNAMIC(CI8LabelWnd)
    protected:
        enum Direction_en
        {
            E_DN_LEFT = 0,
            E_DN_TOP,
            E_DN_RIGHT,
            E_DN_BOTTOM,
            E_DN_MAX
        };
    private:
        static LPCTSTR ms_ptClassName; //ע�ᴰ������
        static INT32   ms_iRefCount;   //���ü���
        CI8BGCache m_clBGCache;
        CI8BGImage m_clBGImage;
        CI8SkinBitmap m_aclArrowImage[E_DN_MAX];
        BOOL m_bUpdateRgn;
        CRect m_rtEdge;
        CRect m_rtClient;
        CPoint m_clDesPos; //��Ļ����
        Direction_en m_enDirection;
        CPoint m_clArrowPos;
        BOOL m_bDynamic; //��̬���ڣ��̶��ͻ�����С���Զ����㴰��λ��
        Direction_en m_enDefaultDirection; //Ĭ�Ϸ��򣬶�̬����ר��
        int m_iDesPointInterval; //��Ŀ��������룬��̬����ר��
    public:
        CI8LabelWnd();
        virtual ~CI8LabelWnd();
        void SetDesPoint(const CPoint& clPos);
        void Create(CWnd *pPerantWnd, const CRect& rtRect);
        void CreateDynamic(CWnd *pPerantWnd, const CSize& clClientSize);
        void CreateDynamic(CWnd *pPerantWnd);
        void SetDefaultDirection(Direction_en enDefaultDirection);
        void SetDesPointInterval(int iDesPointInterval);
    protected:
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnSize(UINT nType, int cx, int cy);
        afx_msg BOOL OnEraseBkgnd(CDC* pDC);
        afx_msg void OnPaint();
        virtual void OnDraw(HDC hDC, const CRect& rtClient);
        void LoadSkin(const stdex::tString sName);
        CRect GetDynamicWndRect() const;
    private:
        void UpdateSize();
        void UpdateArrowInfo(const CRect& rtSpaceArea);
        void DrawEgde(HDC hDC);
        virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    };
}


