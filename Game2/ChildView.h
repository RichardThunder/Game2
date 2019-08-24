﻿
// ChildView.h: CChildView 类的接口
//


#pragma once


// CChildView 窗口

class CChildView : public CWnd
{
// 构造
public:
	CChildView();
	CRect m_client;//保存客户区大小
	CRect m_heroPos;    //保存英雄的位置  
	CImage m_bg;//背景图
	CImage m_hero;//英雄
	CDC m_cacheDC;//缓冲DC
	CBitmap m_cacheCBitmap;//缓冲位图

// 特性
public:
	struct shero
	{
		CImage hero;     //保存英雄的图像  
		int x;             //保存英雄的位置  
		int y;
		int direct;        //英雄的方向  
		int frame;         //运动到第几张图片  
	}MyHero;
// 操作
public:

// 重写
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildView();

	// 生成的消息映射函数
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
};

