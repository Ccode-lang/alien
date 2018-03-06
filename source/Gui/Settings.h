#pragma once

#include <QColor>
#include <QFont>
#include <QPalette>

//visual editor
const QColor BACKGROUND_COLOR(0x00, 0x00, 0x00);
const QColor UNIVERSE_COLOR(0x00, 0x00, 0x1b);
const QColor CELL_COLOR(0x6F, 0x90, 0xFF, 0xA0);
const QColor CELL_CLUSTER_PEN_FOCUS_COLOR(0xFF, 0xFF, 0xFF, 0xFF);
const QColor LINE_ACTIVE_COLOR(0xFF, 0xFF, 0xFF, 0xB0);
const QColor LINE_INACTIVE_COLOR(0xB0, 0xB0, 0xB0, 0xB0);
const QColor TOKEN_COLOR(0xB0, 0xB0, 0xFF, 0xFF);
const QColor TOKEN_FOCUS_COLOR(0xE0, 0xE0, 0xFF, 0xFF);
const QColor ENERGY_COLOR(0xB0, 0x10, 0x0, 0xFF);
const QColor ENERGY_FOCUS_COLOR(0xE0, 0x30, 0x20, 0xFF);
const QColor ENERGY_PEN_FOCUS_COLOR(0xFF, 0xFF, 0xFF, 0xFF);
const QColor MARKER_COLOR(0x0, 0xC0, 0xFF, 0x30);

//text editor
const QColor HEX_EDIT_COLOR1(0x80, 0xA0, 0xFF);//(0x30,0x30,0xBB);
const QColor HEX_EDIT_COLOR2(0x80, 0xA0, 0xFF);//(0x30,0x30,0x99);
const QColor CELL_EDIT_CAPTION_COLOR1(0xD0, 0xD0, 0xD0);
const QColor CELL_EDIT_TEXT_COLOR1(0xD0, 0xD0, 0xD0);
const QColor CELL_EDIT_TEXT_COLOR2(0xB0, 0xB0, 0xB0);
const QColor CELL_EDIT_DATA_COLOR1(0x80, 0xA0, 0xFF);
const QColor CELL_EDIT_DATA_COLOR2(0x60, 0x80, 0xC0);
const QColor CELL_EDIT_CURSOR_COLOR(0x6F, 0x90, 0xFF, 0x90);
const QColor CELL_EDIT_METADATA_COLOR(0xA0, 0xFF, 0x80);
const QColor CELL_EDIT_METADATA_CURSOR_COLOR(0xA0, 0xFF, 0x80, 0x90);
const QString resourceInfoOn("://Icons/info_on.png");
const QString resourceInfoOff("://Icons/info_off.png");

class GuiSettings
{
public:
    static QFont getGlobalFont ();
	static QFont getCellFont();
	static QPalette getPaletteForTabWidget();
	static QPalette getPaletteForTab();

	static const QString ButtonStyleSheet;
	static const QString TableStyleSheet;
	static const QString ScrollbarStyleSheet;
	static const QColor ButtonTextColor;
	static const QColor ButtonTextHighlightColor;
	static const QString StandardFont;
};