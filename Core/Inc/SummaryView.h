#pragma once

#include "View.h"
#include <stdio.h>
#include "types.h"

struct summaryview
{
	View*(*init)(u16 days);
};
extern const struct summaryview SummaryView;
