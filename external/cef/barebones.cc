#include <gtk/gtk.h>

#include "include/cef_app.h"

#include "bareboneshandler.h"

CefRefPtr<BareBonesHandler> g_handler;

void destroy(void) {
	// Tells CEF to quit its message loop so the application can exit.
	CefQuitMessageLoop();
}

int main(int argc, char* argv[]) {
	CefMainArgs main_args(argc, argv);

	int exitCode = CefExecuteProcess(main_args, NULL);
	if (exitCode >= 0) {
		return exitCode;
	}

	CefSettings settings;
	CefInitialize(main_args, settings, NULL);

	GtkWidget* window;
	GtkWidget* vbox;
	GtkWidget* hbox;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "CEF3 Bare Bones");
	// Set the window to 400x400
	gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);

	g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);

	CefBrowserSettings browserSettings;
	CefWindowInfo info;

	g_handler = new BareBonesHandler();

	info.SetAsChild(hbox);
	CefBrowserHost::CreateBrowserSync(info, g_handler.get(),
			"http://code.google.com", browserSettings);
	CefBrowserHost::CreateBrowserSync(info, g_handler.get(),
			"http://www.github.com", browserSettings);

	info.SetAsChild(vbox);
	CefBrowserHost::CreateBrowserSync(info, g_handler.get(),
			"http://www.google.com", browserSettings);

	gtk_widget_show_all(window);

	CefRunMessageLoop();

	CefShutdown();

	return 0;
}







