#pragma once
#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <set>
enum equalType{
	equalTypeNone,
	equalTypeLeft,
	equalTypeRight,
	equalTypeWidth,
	equalTypeHeight,
	equalTypeTop,
	equalTypeBottom
};


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
public:

	equalType bindType = equalTypeNone;
	CRect windowRect;

	virtual void onLayout() {};

	LayoutAbleViewImpl *  make() { 
		tempRules._Pop_back_n(tempRules.size());
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
			windowLayoutRule rule;
			switch (tempRules[i])
			{
			case equalTypeLeft:
				rule = {
				false,
				destWindow,
				destWindow->bindType,
				equalTypeLeft,
				offset
				};
				break;
			case equalTypeRight:
				rule = {
					false,
					destWindow,
					destWindow->bindType,
					equalTypeRight,
					offset
				};
				break;
			case equalTypeTop:
				rule = {
					false,
					destWindow,
					destWindow->bindType,
					equalTypeTop,
					offset
				};
				break;
			case equalTypeBottom:
				rule = {
					false,
					destWindow,
					destWindow->bindType,
					equalTypeBottom,
					offset
				};
				break;
			case equalTypeHeight:
				rule = {
					false,
					destWindow,
					destWindow->bindType,
					equalTypeHeight,
					offset
				};
				break;
			case equalTypeWidth:
				rule = {
					false,
					destWindow,
					destWindow->bindType,
					equalTypeWidth,
					offset
				};
				break;
			default:
				break;
			}
			rules.push_back(rule);

		}
		destWindow->bindType = equalTypeNone;
	
		return this;
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
	
		
	}
	for (auto it = autoLayoutSubWindows.begin();it!=autoLayoutSubWindows.end();it++)
	{
		LayoutAbleViewImpl * window = *it;
		window->changeSize();
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

