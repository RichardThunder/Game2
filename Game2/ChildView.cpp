
// ChildView.cpp: CChildView 类的实现
//

#include "pch.h"
#include "framework.h"
#include "Game2.h"
#include "ChildView.h"
#include "atlimage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//定时器的名称用宏比较清楚  
#define TIMER_PAINT 1  

#define up 1
#define down 2
#define stright 0//方向

void TransparentPNG(CImage* png)
{
	for (int i = 0; i < png->GetWidth(); i++)
	{
		for (int j = 0; j < png->GetHeight(); j++)
		{
			unsigned char* pucColor = reinterpret_cast<unsigned char*>(png->GetPixelAddress(i, j));
			pucColor[0] = pucColor[0] * pucColor[3] / 255;
			pucColor[1] = pucColor[1] * pucColor[3] / 255;
			pucColor[2] = pucColor[2] * pucColor[3] / 255;
		}
	}
}
// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;
	
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);
	
	//--------游戏数据初始化-------------
	m_bg.Load("D:\\VS\\Game2\\Game2\\bg.png");  
	MyHero.hero.Load("D:\\VS\\Game2\\Game2\\1.png");//m_;//加载小鸟
	TransparentPNG(&MyHero.hero);//去除白色部分

 //初始化英雄状态  
    MyHero.direct=down;  
    MyHero.frame=0;  
	MyHero.x = 100;
	MyHero.y = 100;
	/*m_heroPos.left = 100;
	m_heroPos.right= m_heroPos.left +40;
	m_heroPos.top = 10; 
	m_heroPos.bottom= m_heroPos.top +30;  *///初始位置
	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	CDC* cDC = this->GetDC();   //获得当前窗口的DC     
	GetClientRect(&m_client);   //获得窗口的尺寸 
	
	m_cacheDC.CreateCompatibleDC(NULL);
	m_cacheCBitmap.CreateCompatibleBitmap(cDC, m_client.Width(), m_client.Height());
	m_cacheDC.SelectObject(&m_cacheCBitmap);//创建缓冲区DC


	//---------------------开始绘制---------------------
	//贴背景,现在贴图就是贴在缓冲DC：m_cache中了  
	m_bg.Draw(m_cacheDC, m_client);//绘制背景
	//m_hero.Draw(*cDC, m_heroPos);//绘制小鸟
	MyHero.hero.Draw(m_cacheDC, MyHero.x, MyHero.y, 53, 53, MyHero.frame * 53, MyHero.direct * 53, 53, 53);
	//最后将缓冲DC内容输出到窗口DC中 
	cDC->BitBlt(0, 0, m_client.Width(), m_client.Height(), &m_cacheDC, 0, 0, SRCCOPY);
	//————————————————————绘制结束———————————————————
	  
	ValidateRect(&m_client);//在绘制完图后,使窗口区有效 
	m_cacheDC.DeleteDC();//释放缓冲DC  
	m_cacheCBitmap.DeleteObject();//释放对象
	ReleaseDC(cDC);//释放DC
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//nChar表示按下的键值
	 //nChar表示按下的键值  
	
	/*if (nChar == ' ')
	{
		if (m_heroPos.top > m_client.top)
		{
			MyHero.direct = up;
			m_heroPos.top -= 10;
			m_heroPos.bottom -= 10;
		}
		else NULL;
	}
	else NULL;*/
	if (nChar == ' ')
	{
		if (MyHero.y > m_client.top)
		{
			MyHero.direct = up;
			MyHero.y -= 70;
			//MyHero.y -= 10;
		}
		else NULL;
	}

	//SetTimer(1, 100, NULL);

	OnPaint();
	Sleep(100);
	//SetTimer(1, 100, NULL);
	MyHero.direct = stright;
	OnPaint();
	Sleep(100);
	MyHero.direct = down;
	OnPaint();
}

	

 


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	
	switch (nIDEvent)
	{
	case TIMER_PAINT: 
	{

		/*for(int i=1;;i++)
		{
			MyHero.y += i*i;
		}//MyHero.x+= 10;*/
		MyHero.y+= 5;				//控制人物移动的定时器 
	OnPaint();						//若是重绘定时器，就执行OnPaint函数  
	}
	  break;
	}
	
}
int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	//创建一个毫秒产生一次消息的定时器  
	SetTimer(TIMER_PAINT, 10, NULL);
	return 0;
}




