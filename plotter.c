#include <gtk/gtk.h>
#include <math.h>

const int windowWidth  = 500;
const int windowHeight = 500;
const double xO = 250, yO = 0;
const double xScale = 1, yScale = 10;
const float colors[][3] = {
	{1.0, 1.0, 1.0},
	{1.0, 0.5, 0.5},
	{0.5, 1.0, 0.5},
	{0.5, 0.5, 1.0},
	{1.0, 1.0, 0.0},
	{1.0, 0.0, 1.0},
	{0.0, 1.0, 1.0},
};

static double function(int x) {
	//return sin(sqrt(x)) * cos(sqrt(x));
	return log(x+sqrt(1+x*x));
}

static double coordConvert(double function(int), double x) {
	return windowHeight/2 - (function(x + xO - windowWidth/2) - yO) * yScale;
}

static gboolean draw_cb(GtkWidget *widget, cairo_t *cr, gpointer data) {
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_paint(cr);

	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_set_line_width(cr, 2);
	cairo_move_to(cr, -100, windowHeight/2);
	for (int x = 0; x < windowWidth; x++) {
		cairo_line_to(cr, x, coordConvert(function, x));
//		if (x % 10 == 9) {
//			cairo_set_source_rgb(cr,
//					colors[(x/10)%7][0],
//					colors[(x/10)%7][1],
//					colors[(x/10)%7][2]);
//			cairo_stroke(cr);
//		}
	}
	cairo_stroke(cr);

	return FALSE;
}

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);

	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	GtkWidget *da = gtk_drawing_area_new();
	gtk_widget_set_size_request(da, windowWidth, windowHeight);
	g_signal_connect(da, "draw", G_CALLBACK(draw_cb),  NULL);

	gtk_container_add(GTK_CONTAINER(window), da);
	gtk_widget_show(da);
	gtk_widget_show(window);

	gtk_main();

	return 0;
}

