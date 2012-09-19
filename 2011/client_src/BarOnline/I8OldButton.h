#pragma once

#include "UI/I8SkinCtrl/I8SkinCommonFunction.h"

#define DEFAULT_FONT_NAME	TEXT("����")

namespace I8SkinCtrl_ns
{
    class CI8OldButton : public CButton
    {
        friend class CDockStatusBar;
        DECLARE_DYNAMIC(CI8OldButton)
        enum  BEX_Status
        {
            BEX_NORMAL,
            BEX_HOVER,
            BEX_PRESSED
        };
        enum  BDRAW_Status
        {
            BDRAW_NORMAL,
            BDRAW_ALPHA
        };
        enum BTYPE
        {
            BTYPE_NORMAL,
            BTYPE_NBTITLE,
            BTYPE_NBCONTENT,
            BTYPE_QUIKRUN
        };
    public:
        enum BTEXT_STYLE
        {
            BTEXT_LEFT,
            BTEXT_CENTER,
            BTEXT_RIGHT
        };
    public:
        CI8OldButton();
        virtual ~CI8OldButton();

        void  SetImage(DWORD backImage = 0, DWORD hoverImage = 0, DWORD selectImage = 0);
        void  SetImage(LPCTSTR backImage = NULL, LPCTSTR hoverImage = NULL, LPCTSTR selectImage = NULL, 
            LPCTSTR activeImage = NULL, LPCTSTR disableImage = NULL, BOOL bAlphaMode = FALSE);
        void  SetImage2(LPCTSTR backImage = NULL, LPCTSTR backImage2 = NULL, LPCTSTR backImage3 = NULL, 
            LPCTSTR selectImage = NULL, LPCTSTR selectImage2 = NULL, LPCTSTR selectImage3 = NULL);
        void  SetImage3(COLORREF backColor, COLORREF hoverColor, COLORREF selectColor, COLORREF activeColor);

        //����ͼ�꣨���������£�
        void SetIconImage(LPCTSTR iconImage, LPCTSTR iconSelImage = NULL);
        void SetIconImage(HICON hIcon, HICON hSelIcon = NULL);

        //���ð�ť���壬��С���Լ���ɫ������
        void  SetTextStyle(CString font = DEFAULT_FONT_NAME, int nSize = 12, 
            COLORREF clrText = RGB(0, 0, 0), COLORREF clrHover = RGB(0, 0, 0), COLORREF clrSel = RGB(0, 0, 0), COLORREF clrActive = RGB(0, 0, 0),
            BTEXT_STYLE nStyle = BTEXT_LEFT, BOOL bBold = FALSE, BOOL bUnderline = FALSE, BOOL bItalic = FALSE, BOOL bStrikeOut = FALSE,
            BTYPE bType = BTYPE_NORMAL, BOOL bSelBold = FALSE);
        void  SetActive(BOOL bActive);
        BOOL  GetActive()		{ return m_bActive; }
        void  SetCursor(HCURSOR hCursor)	{ m_hCursor = hCursor; }
        inline BOOL IsHasIcon() const{return m_piconImage != NULL;};
    protected:
        virtual void PreSubclassWindow();
        virtual BOOL PreTranslateMessage(MSG* pMsg);
        virtual void DrawItem(LPDRAWITEMSTRUCT lpDis);
        afx_msg BOOL OnEraseBkgnd(CDC* pDC);
        afx_msg void OnMouseMove( UINT nFlags, CPoint point);
        afx_msg void OnMouseHover(UINT nFlags, CPoint point);
        afx_msg void OnMouseLeave();
        afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
        afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
        afx_msg void OnTimer(UINT_PTR nIDEvent);
        DECLARE_MESSAGE_MAP()

    protected:
        void         DrawFadeEffect();                            //���ƽ���Ч��

    private:
        BEX_Status m_Status;
        COLORREF m_bgBack, m_bgHover, m_bgPressed, m_bgActive;
        CBitmap *m_pbkImage, *m_pbkImage2, *m_pbkImage3;				//Ĭ�ϱ�����Ĭ�ϱ����У����죩��Ĭ�ϱ�����
        CBitmap *m_phoverImage, *m_phoverImage2, *m_phoverImage3;	//��꾭������꾭���У����죩����꾭����
        CBitmap *m_pselectImage, *m_pselectImage2, *m_pselectImage3;	//��갴������갴���У����죩����갴����
        CBitmap *m_pActiveImage, *m_piconImage, *m_piconSelImage;	//��ť��ߵ�ͼ�꣨Ĭ�ϣ�����)
        CBitmap *m_pdisableImage;
        CString m_szFont;													//��ť������
        int m_nFontSize;
        COLORREF m_clrText, m_clrHover, m_clrSel, m_clrActive;
        BTEXT_STYLE m_nBTStyle;
        BOOL m_bBold, m_bUnderline, m_bItalic, m_bStrictOut;
        BOOL m_bActive;
        BOOL m_bSelBold;
        HCURSOR m_hCursor;
        BOOL m_bAlphaMode;
        BDRAW_Status m_DrawStatus;
        BTYPE m_bType;
        BLENDFUNCTION m_bf;
        CBitmap* m_pSourceBitmap;
        CToolTipCtrl m_toolTip;
        CString  m_strTooltip;                                    //���ɵ�ַTOOLTIP�����ڽ���ڵ������޷���Ӧ�ı���
        HICON m_hIconNormal;
    };
}