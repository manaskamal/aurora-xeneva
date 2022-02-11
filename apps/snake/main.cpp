#include <daisy.h>
#include <daisy_priwm_window.h>
#include <daisy_window.h>
#include <daisy_widget_panel.h>
#include <daisy_widget_button.h>

#include <sys\_file.h>
#include <acrylic.h>
#include <sys\_ipc.h>
#include <sys\_time.h>
#include <sys\_xeneva.h>
#include <sys\_thread.h>
#include <sys\_process.h>
#include <sys\_wait.h>
#include <sys\_sleep.h>
#include <string.h>
#include <color.h>
#include <sys\_term.h>

//uint32_t colors[23] = {0xFF9EA09F, 0xFFA8A8A8, 0xFFB5B7B7, 0xFFC0C5C3, 0xFFCACFCE,0xD3D5D4,0xD3D5D4,0xD3D5D4,0xD3D5D4,0xD3D5D4
//,0xD3D5D4,0xD3D5D4,0xD3D5D4,0xD3D5D4,0xD3D5D4,0xD3D5D4,0xD3D5D4,0xD3D5D4,0xD3D5D4,0xD3D5D4,0xD3D5D4,0xD3D5D4,0xD3D5D4};

int main (int argc, char* argv[]) {
	daisy_application();
	daisy_window_t *win = daisy_window_create (100,100,500,300,NULL);
	daisy_win_info_t *info = daisy_get_window_info(win);
	daisy_window_set_title (win, "Snake");
	
	daisy_widget_panel_t *panel = daisy_widget_create_panel(win,0x4DD9D9D9/*LIGHTSILVER*/);
	daisy_window_add_widget (win,(daisy_widget_t*)panel);

	daisy_widget_button_t *button = daisy_widget_create_button (win, "Click Me");
	daisy_widget_button_set_dimension (button,40,40,100,30);
	daisy_widget_panel_add(panel,(daisy_widget_t*)button);

	daisy_window_show(win);
	while(1) {
		pri_event_t *e = daisy_get_gifts();
		daisy_window_service_event(win,e);
		sys_wait();
	}
}