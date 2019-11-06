#pragma once
#include "TableViewCell.h"
class  TableViewProtocol
{
public:
	virtual int numberOfLines() = 0;
	virtual int heightOfRow(int row) = 0;
	virtual TableViewCell *cellOfRow(int row) = 0;
	virtual ~TableViewProtocol() {};

};