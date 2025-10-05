
// TestContoursDlg.h : header file
//

#pragma once

#include "HalconCpp.h"

using namespace HalconCpp;


// CTestContoursDlg dialog
class CTestContoursDlg : public CDialogEx
{
// Construction
public:
	CTestContoursDlg(CWnd* pParent = nullptr);	// standard constructor

	

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTCONTOURS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support



// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

	HObject m_ho_CG, m_ho_CI, m_ho_Cbj, m_ho_ContoursGrsm, m_ho_MeanderRects, m_ho_RegionG;
	HObject m_ho_ContoursGrsmPi, m_ho_RectanglesPadsIsol, m_ho_ContoursGrsmPc, m_ho_RectanglesPadsCon, m_ho_ContoursWireAngles, m_ho_RectanglesWireAngles;
	HTuple m_hv_ColG, m_hv_RowG, m_hv_ColI, m_hv_RowI, m_hv_DistIG, m_hv_DistIG2;
	HObject m_ho_Im, m_ho_Gi;
	HTuple m_hv_thr, m_hv_ctype, m_hv_meander, m_hw_absmb, m_hw_abssp;
	HTuple  m_hv_pad, m_hv_padc, m_hv_wa;
	bool m_ctype;
	float *medo;
	//float *pmedo = NULL;
	int m_fsz;
	int num; // repeat number
	int disp; // display results
	HObject m_ho_Rectangle5;
	HWindow hWindow;
	

	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnEnChangeEdit11();
};
