#include "TableView.h"
#include "ZXField.h"

TableViewCell * TableView::findCellsFromCache(CString reuseId){

	TableViewCell *newCell = nullptr;


	if (unUsedCells.size() > 0)
	{

		newCell = unUsedCells[unUsedCells.size() - 1];
		unUsedCells.pop_back();
	
	}
	return  newCell;
}

void TableView::realoadData() {
	offset = 0;
	
//设置开始数组
	int offsets = 0;
	cellLocations._Pop_back_n(cellLocations.size());
	for (int i = 0 ; i < usedCells.size();i++)
	{
		unUsedCells.push_back(usedCells[i]);
	}
	usedCells._Pop_back_n(unUsedCells.size());
	cellMaps._Pop_back_n(cellMaps.size());
	for (int i = 0; i < delegate->numberOfLines(); i++)
	{ 
		cellLocations.push_back(offsets);
		cellMaps.push_back({ offsets,nullptr });
		offsets += delegate->heightOfRow(i);
		

	}

	//初始化排列
	

	loadDataWithOffset(0);

}

void TableView::loadDataWithOffset(int offset) {
	int startDrawOffset = 0;
	int startDrawCount = 0;
	int endDrawOffset = 0;
	int endDrawCount = 0;
for (int i = 0;i < delegate->numberOfLines();i++)
{
	
	if (startDrawOffset + delegate->heightOfRow(i) < offset)
	{
		if (cellMaps[i].cell != nullptr)
		{
			unUsedCells.push_back(cellMaps[i].cell);
			cellMaps[i].cell = nullptr;
		}
		

		startDrawOffset += delegate->heightOfRow(i);
		startDrawCount++;
		
	}
	CRect windowRect;
	GetClientRect(windowRect);
	if (endDrawOffset  <= windowRect.Height() + offset)
	{

		endDrawOffset += delegate->heightOfRow(i);
		endDrawCount++;
	

	}
	else
	{
		if (cellMaps[i].cell != nullptr)
		{
			unUsedCells.push_back(cellMaps[i].cell);
			cellMaps[i].cell = nullptr;
		}

	}

}
for (int i = startDrawCount; i < endDrawCount; i++) {
	TableViewCell *cell;
	if (cellMaps[i].cell == nullptr)
	{
		cell = delegate->cellOfRow(i);
		cellMaps[i].cell = cell;
	}
	else
	{
		cell = cellMaps[i].cell;
	}

   
	CRect windwoRect;
	GetClientRect(windwoRect);
	if (cell->IsWindow())
	{
		cell->MoveWindow(rectExtension::ZXRectCreatWith(30, cellMaps[i].location - offset, windwoRect.Width() - 30, delegate->heightOfRow(i)));
	}
	else {
		cell->Create(m_hWnd, rectExtension::ZXRectCreatWith(30, cellMaps[i].location - offset, windwoRect.Width() - 30, delegate->heightOfRow(i)), NULL, WS_VISIBLE | WS_CHILD, NULL, 0U, NULL);
	}

	cell->RedrawWindow();


}
//RedrawWindow();


}
