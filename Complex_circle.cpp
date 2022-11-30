#include "Complex_circle.h"

namespace Graph_lib
{
    void Complex_circle::draw_lines() const
    {
        fl_begin_polygon();
	    if (fill_color().visibility()) {	// fill
	    	fl_color(fill_color().dark_blue);
	    	fl_circle(point(0).x,point(0).y,r);
	    	fl_color(color().as_int());	// reset color
	    }
        fl_end_polygon();

	    if (color().visibility()) {
	    	fl_color(color().dark_blue);
	    	//fl_arc(point(10).x,point(10).y,1,1,100,90);
	    	fl_arc(point(0).x,point(0).y,r+r,r+r,0,360);
	    }
}
}