#pragma once

#include <stdlib.h>
#include "gfx.h"
#include "View.h"
#include "SummaryView.h"



struct application {
	void(*init)(void);
	void(*run)(void);
};

extern const struct application Application;
