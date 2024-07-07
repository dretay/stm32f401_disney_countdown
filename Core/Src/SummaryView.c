#include "SummaryView.h"

static View view;
static font_t NewWaltDisneyFontRegular_BPen64, MetroMarks_G3KWm144,Braxline_Narrow64, Braxline_Narrow48, Headlines_Bold48;
static coord_t DisplayWidth, DisplayHeight, DisplayWidthMidpoint, DisplayHeightMidpoint;
static u16 DAYS;

static void renderText(font_t* font, char* text, coord_t h_offset, coord_t v_offset,gColor color){

	coord_t text_width = gdispGetStringWidth(text, *font) + 1;
	coord_t text_height = gdispGetFontMetric(*font, fontHeight) + 1;
	gdispDrawStringBox(
		(DisplayWidth/2) - h_offset,
		DisplayHeightMidpoint-v_offset,
		text_width,
		text_height,
		text,
		*font,
		color,
		justifyCenter);

}

static void render()
{
	char values[4] = {0};
	snprintf(values,4,"%d",DAYS);

	gdispClear(White);

	renderText(&Braxline_Narrow64, "DAYS",55,-100,Black);
	renderText(&Braxline_Narrow64, "UNTIL",-60,-100,Black);

	gdispFillCircle((DisplayWidth/2)-120,DisplayHeightMidpoint+130,5,Black);
	gdispFillCircle((DisplayWidth/2)-100,DisplayHeightMidpoint+130,5,Black);
	gdispFillCircle((DisplayWidth/2)-80,DisplayHeightMidpoint+130,5,Black);

	renderText(&Braxline_Narrow48, "OUR",175,-170,Black);
	renderText(&NewWaltDisneyFontRegular_BPen64, "Disney",110,-150,Black);
	renderText(&Headlines_Bold48, "CRUISE",-55,-170,Black);

	gdispDrawThickLine(10,DisplayHeightMidpoint+230,DisplayWidth-10,DisplayHeightMidpoint+230,Black,1,0);
	gdispDrawThickLine(10,DisplayHeightMidpoint+240,DisplayWidth-10,DisplayHeightMidpoint+240,Black,1,0);

	gdispFillCircle((DisplayWidth/2)-100,DisplayHeightMidpoint-170,80,Black);
	gdispFillCircle((DisplayWidth/2)+100,DisplayHeightMidpoint-170,80,Black);
	gdispFillCircle((DisplayWidth/2),DisplayHeightMidpoint-70,120,Black);
	if(DAYS > 99){
		renderText(&MetroMarks_G3KWm144, values ,110,150,White);//3 digit spacing
	}
	else if (DAYS> 9){
		renderText(&MetroMarks_G3KWm144, values ,70,150,White);//2 digit spacing
	}
	else{
		renderText(&MetroMarks_G3KWm144, values ,30,150,White);//1 digit spacing
	}

	gdispGFlush(gdispGetDisplay(0));
}


static View* init(u16 days)
{
	view.render = render;
	DAYS = days;

	//display setup
	gdispSetOrientation(GDISP_ROTATE_90);


	//fonts
	NewWaltDisneyFontRegular_BPen64 = gdispOpenFont("NewWaltDisneyFontRegular_BPen64");
	MetroMarks_G3KWm144 = gdispOpenFont("MetroMarks_G3KWm144");
	Braxline_Narrow64 = gdispOpenFont("Braxline_Narrow64");
	Braxline_Narrow48 = gdispOpenFont("Braxline_Narrow48");
	Headlines_Bold48 = gdispOpenFont("Headlines_Bold48");

	//constants
	DisplayWidth = gdispGetWidth();
	DisplayWidthMidpoint = DisplayWidth / 2;
	DisplayHeight = gdispGetHeight();
	DisplayHeightMidpoint = DisplayHeight / 2;

	return &view;
}

const struct summaryview SummaryView= {
	.init = init,
};
