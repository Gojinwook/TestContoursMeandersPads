
// Master_OneDlg.h : header file
//
#pragma once

#include "Halcon\FWM.h"
#include "Halcon\FLT_All.h"


// CMasterOneDlg dialog
class CMasterOneDlg : public CDialogEx
{
// Construction
public:
	CMasterOneDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MASTER_ONE_DIALOG };
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
	afx_msg void OnBnClickedButScratches();

private:
	FILE* fp_console;

private:
	CString m_folderPath;
	HTuple t_folderPath;
	FWM* m_FWM;

public:
	afx_msg void OnBnClickedButMissingPads();
	afx_msg void OnBnClickedButFwmLoad();
	afx_msg void OnBnClickedButFwmRun();
	afx_msg void OnBnClickedButFwmSave();
	afx_msg void OnBnClickedButFwmLowSlope();
	CButton But_FWM_Low_Slope;
	CButton But_FWM_Run;
	CButton But_FWM_Save;
};
