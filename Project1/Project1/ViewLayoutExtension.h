#pragma once
#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <xutility>
#include <cstring>
enum equalType{
	equalTypeNone,
	equalTypeLeft,
	equalTypeRight,
	equalTypeWidth,
	equalTypeHeight,
	equalTypeTop,
	equalTypeBottom
};
template<typename T>
class  LayoutAbleViewImpl
{
	struct windowLayoutRule
	{
		bool isAbs;
		LayoutAbleViewImpl *windowSource;
		equalType type;
		equalType selfType;
		int offset;
	};


	struct windowLaytouRegistRule
	{
		bool isAbs;
		CWindow *windowSource;
		CWindow *windowDest;
		equalType typeSource;
		equalType typeDest;
		int offset;
		CWindow *parentWindow;
	};
 typedef std::map<CWindow *, std::vector<windowLaytouRegistRule>> regRuleMap;

public:

	BEGIN_MSG_MAP(CDoubleBufferImpl)
	
		MESSAGE_HANDLER(WM_SIZE, OnSize)

	END_MSG_MAP()


	equalType bindType = equalTypeNone;
	CRect windowRect;

	CWindow *tempDest = nullptr;


	LRESULT OnSize(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		
		changeSubSize();
		
		return 0;
	}
	virtual void onLayout() {};

	LayoutAbleViewImpl *  make() { 
		tempRules._Pop_back_n(tempRules.size());
		return this;
	}
	LayoutAbleViewImpl *  regist(CWindow * destWindow) {
		tempRules._Pop_back_n(tempRules.size());
		tempDest = destWindow;
		return this;
	}

	LayoutAbleViewImpl * left() {
		tempRules.push_back(equalTypeLeft);
		return this;
	}
	LayoutAbleViewImpl * right() {
		tempRules.push_back(equalTypeRight);
		return this;
	} 
	LayoutAbleViewImpl * top() {
		tempRules.push_back(equalTypeTop);
		return this;
	}
	LayoutAbleViewImpl *  bottom() {
		tempRules.push_back(equalTypeBottom);
		return this;
	}
	LayoutAbleViewImpl *  width() {
		tempRules.push_back(equalTypeWidth);
		return this;
	}
	LayoutAbleViewImpl *  height() {
		tempRules.push_back(equalTypeHeight);
		return this;
	}


	LayoutAbleViewImpl *  equalTo(LayoutAbleViewImpl * destWindow, int offset) {
		destWindow->registSbuWindow(this);

		for (int i = 0;i< tempRules.size();i++)
		{
			windowLayoutRule rule  = {
				false,
				destWindow,
				destWindow->bindType,
				tempRules[i],
				offset
				};
		
			rulesCache.push_back(rule);

		}
		destWindow->bindType = equalTypeNone;
	
		return this;
	}
	LayoutAbleViewImpl *  bindlTo(CWindow * sourceWindow,equalType sourceType, int offset) {

		CWindow *father = dynamic_cast<CWindow *> (this);
		for (int i = 0; i < tempRules.size(); i++)
		{
			windowLaytouRegistRule rule = {
				false,
				sourceWindow,
				tempDest,
				sourceType,
				tempRules[i],
				offset,
				father
			};
         
			registsCache.push_back(rule);
		}

		return this;
	}

	void complete() {
		if (tempDest == nullptr)
		{
			for (int k = 0; k < 3; k++)
			{
				equalType type1;
				equalType type2;
				switch (k)
				{

				case 0:
					type1 = equalTypeLeft;
					type2 = equalTypeTop;
					break;
				case 1:
					type1 = equalTypeWidth;
					type2 = equalTypeHeight;
					break;
				case 2:
					type1 = equalTypeRight;
					type2 = equalTypeBottom;
					break;

				default:
					break;
				}

				for (int i = 0; i < rulesCache.size(); i++)
				{
					windowLayoutRule rule = rulesCache[i];
					if (rule.selfType == type1 || rule.selfType == type2)
					{
						rules.push_back(rule);
					}

				}

			}
			rulesCache._Pop_back_n(rulesCache.size());
		}
		else
		{

			std::vector<windowLaytouRegistRule> tempReg;

			for (int k = 0; k < 3; k++)
			{
				equalType type1;
				equalType type2;
				switch (k)
				{

				case 0:
					type1 = equalTypeLeft;
					type2 = equalTypeTop;
					break;
				case 1:
					type1 = equalTypeWidth;
					type2 = equalTypeHeight;
					break;
				case 2:
					type1 = equalTypeRight;
					type2 = equalTypeBottom;
					break;

				default:
					break;
				}

				for (int i = 0; i < registsCache.size(); i++)
				{
					windowLaytouRegistRule rule = registsCache[i];
					if (rule.typeDest == type1 || rule.typeDest == type2)
					{
						tempReg.push_back(rule);
					}

				}

			}
			layoutSubPool[tempDest] = tempReg;
        	registsCache._Pop_back_n(registsCache.size());
		}


	}

	LayoutAbleViewImpl *  absEqualTo(int num) {
	
		return this;
	}

	void changeSize() {
	CRect destRect;
	
	for (int i = 0; i < rules.size();i++ )
	{
		windowLayoutRule rule = rules[i];
	
		CRect superReact = rule.windowSource->windowRect;


			switch (rule.selfType)
			{
			case equalTypeLeft:
				destRect = leftEqualTo(rule, destRect, superReact, rule.offset);
				break;		
			case equalTypeRight:
				destRect = rightEqualTo(rule, destRect, superReact, rule.offset);
				break;
			case equalTypeTop:
				destRect = topEqualTo(rule, destRect, superReact, rule.offset);
				break;
			case equalTypeBottom:
				destRect = bottomEqualTo(rule, destRect, superReact, rule.offset);
				break;
			case equalTypeWidth:
				destRect = widthEqualTo(rule, destRect, superReact, rule.offset);
				break;
			case equalTypeHeight:
				destRect = heightEqualTo(rule, destRect, superReact, rule.offset);
				break;

			default:
				break;
			}

	}
	if (rules.size() > 0)
	{
		windowRect = destRect;
		onLayout();
		CWindow *pt = dynamic_cast<CWindow *>(this);
		pt->MoveWindow(destRect);
		
	}
	for (auto it = autoLayoutSubWindows.begin();it!=autoLayoutSubWindows.end();it++)
	{
		LayoutAbleViewImpl * window = *it;
		window->changeSize();
	}

	}

	void changeSubSize() {
		CRect destRect;
		
		for (auto it = layoutSubPool.begin(); it != layoutSubPool.end(); it++)
		{

			std::vector<windowLaytouRegistRule> list =(it)->second;

			for (int i = 0; i < list.size(); i++)
			{
				windowLaytouRegistRule rule = list[i];
			
				windowLayoutRule consRule = {
			rule.isAbs,
			nullptr,
			rule.typeSource,
			rule.typeDest,
			rule.offset
				};
				CRect superRect;

				rule.windowSource->GetWindowRect(&superRect);
				//×ø±êÏµ×ª»»
// 				if (rule.parentWindow != rule.windowSource)
// 				{
					rule.parentWindow->ScreenToClient(&superRect);
			//	}
			

				switch (rule.typeDest)
				{
				case equalTypeLeft:
					destRect = leftEqualTo(consRule, destRect, superRect, rule.offset);
					break;
				case equalTypeRight:
					destRect = rightEqualTo(consRule, destRect, superRect, rule.offset);
					break;
				case equalTypeTop:
					destRect = topEqualTo(consRule, destRect, superRect, rule.offset);
					break;
				case equalTypeBottom:
					destRect = bottomEqualTo(consRule, destRect, superRect, rule.offset);
					break;
				case equalTypeWidth:
					destRect = widthEqualTo(consRule, destRect, superRect, rule.offset);
					break;
				case equalTypeHeight:
					destRect = heightEqualTo(consRule, destRect, superRect, rule.offset);
					break;

				default:
					break;
				}
			}
				
			CWindow *window = it->first;
			window->MoveWindow(destRect, 1);

			int i = 0;
		}
		

	}





	void registSbuWindow(LayoutAbleViewImpl * window) {

		autoLayoutSubWindows.insert(window);
	}

	LayoutAbleViewImpl *  layout_left() {
		bindType = equalTypeLeft;
		return this;
	}
	LayoutAbleViewImpl *  layout_right() {
		bindType = equalTypeRight;
		return this;
	}
	LayoutAbleViewImpl *  layout_top() {
		bindType = equalTypeTop;
		return this;
	}
	LayoutAbleViewImpl *  layout_bottom() {
		bindType = equalTypeBottom;
		return this;
	}
	LayoutAbleViewImpl *  layout_width() {
		bindType = equalTypeWidth;
		return this;
	}
	
	LayoutAbleViewImpl *  layout_height() {
		bindType = equalTypeHeight;
		return this;
	}

private:
	std::set<LayoutAbleViewImpl *> autoLayoutSubWindows;
	std::vector<equalType> tempRules;
	std::vector<windowLayoutRule> rules;
	std::vector<windowLayoutRule> rulesCache;
	std::vector<windowLaytouRegistRule> registsCache;
	regRuleMap layoutSubPool;

	CRect leftEqualTo(windowLayoutRule rule,CRect rectSelf,CRect rectSource,int offset) {
	
	if (rule.type == equalTypeNone || rule.type == equalTypeLeft)
	{ 
		rectSelf.left = rectSource.left + offset;

	}
	else if(rule.type == equalTypeRight)
	{
		rectSelf.left = rectSource.right  + offset;
	}
	
	return rectSelf;

	}


	CRect rightEqualTo(windowLayoutRule rule, CRect rectSelf, CRect rectSource, int offset) {

		if (rule.type == equalTypeNone || rule.type == equalTypeRight)
		{
			rectSelf.right = rectSource.right + offset;

		}
		else if (rule.type == equalTypeLeft)
		{
			rectSelf.right = rectSource.left + offset;
		}

		return rectSelf;

	}

	CRect topEqualTo(windowLayoutRule rule, CRect rectSelf, CRect rectSource, int offset) {

		if (rule.type == equalTypeNone || rule.type == equalTypeTop)
		{
			rectSelf.top = rectSource.top + offset;

		}
		else if (rule.type == equalTypeBottom)
		{
			rectSelf.top = rectSource.bottom + offset;
		}
		return rectSelf;
	}

	CRect bottomEqualTo(windowLayoutRule rule, CRect rectSelf, CRect rectSource, int offset) {

		if (rule.type == equalTypeNone || rule.type == equalTypeBottom)
		{
			rectSelf.bottom = rectSource.bottom + offset;

		}
		else if (rule.type == equalTypeTop)
		{
			rectSelf.bottom = rectSource.top + offset;
		}

		return rectSelf;

	}

	CRect widthEqualTo(windowLayoutRule rule, CRect rectSelf, CRect rectSource, int offset) {

		if (rule.type == equalTypeNone || rule.type == equalTypeWidth)
		{
			rectSelf.right = rectSelf.left + rectSource.Width() + offset;

		}else if (rule.type == equalTypeHeight)
		{
			rectSelf.right = rectSelf.left + rectSource.Height() + offset;
		}

		return rectSelf;

	}

	CRect heightEqualTo(windowLayoutRule rule, CRect rectSelf, CRect rectSource, int offset) {

		if (rule.type == equalTypeNone || rule.type == equalTypeHeight)
		{
			rectSelf.bottom = rectSelf.top + rectSource.Height() + offset;

		}
		else if (rule.type == equalTypeWidth)
		{
			rectSelf.bottom = rectSelf.top + rectSource.Width() + offset;
		}

		return rectSelf;

	}

};


