#include <daisy.h>
#include <daisy_priwm_window.h>
#include <daisy_window.h>
#include <daisy_widget_panel.h>
#include <daisy_widget_button.h>
#include <daisy_widget_label.h>
#include <daisy_widget_slider.h>
#include <daisy_widget_onoff.h>
#include <daisy_scroll_view.h>
#include <daisy_widget_scrollbar.h>
#include <daisy_widget_list.h>

#include <sys\_file.h>
#include <acrylic.h>
#include <sys\_ipc.h>
#include <sys\_time.h>
#include <sys\_xeneva.h>
#include <sys\_thread.h>
#include <sys\_process.h>
#include <sys\_wait.h>
#include <sys\_sleep.h>
#include <sys\mmap.h>
#include <string.h>
#include <color.h>
#include <sys\_term.h>
#include <xnsnd.h>

//uint32_t colors[23] = {0xFF9EA09F, 0xFFA8A8A8, 0xFFB5B7B7, 0xFFC0C5C3, 0xFFCACFCE,0xD3D5D4,0xD3D5D4,0xD3D5D4,0xD3D5D4,0xD3D5D4
//,0xD3D5D4,0xD3D5D4,0xD3D5D4,0xD3D5D4,0xD3D5D4,0xD3D5D4,0xD3D5D4,0xD3D5D4,0xD3D5D4,0xD3D5D4,0xD3D5D4,0xD3D5D4,0xD3D5D4};

int main (int argc, char* argv[]) {
	daisy_application();

	daisy_window_t *win = daisy_window_create (100,200,500,300,DAISY_WIN_NORMAL,"Audio Player");
	daisy_win_info_t *info = daisy_get_window_info(win);
	
	daisy_widget_panel_t *panel = daisy_widget_create_panel(win,0x4DD9D9D9/*LIGHTSILVER*/);
	daisy_window_add_widget (win,(daisy_widget_t*)panel);
	daisy_window_set_back_color(win,panel->color);


	daisy_scroll_view_t *sv = daisy_widget_create_scroll_view();
	daisy_sv_set_dimension(sv,0,23,info->width,info->height - 23);
	daisy_widget_panel_add(panel,(daisy_widget_t*)sv);

	daisy_widget_scrollbar_t *scrollbar = daisy_widget_create_scrollbar(DAISY_SCROLLBAR_VERTICAL);
	daisy_widget_scrollbar_add_view(scrollbar,sv);
	daisy_widget_panel_add(panel,(daisy_widget_t*)scrollbar);

	daisy_widget_list_t *list = daisy_widget_create_list(sv);
	daisy_widget_list_set_dimension(list,sv->base.x, sv->base.y, sv->base.width,sv->base.height);
	daisy_widget_list_add_element(list,win,daisy_widget_list_create_element("Hello"));
	daisy_widget_list_add_element(list,win,daisy_widget_list_create_element("Hello"));
	daisy_widget_list_add_element(list,win,daisy_widget_list_create_element("Hello"));
	daisy_widget_list_add_element(list,win,daisy_widget_list_create_element("Hello"));
	daisy_widget_list_add_element(list,win,daisy_widget_list_create_element("Hello"));
	daisy_widget_list_add_element(list,win,daisy_widget_list_create_element("Hello"));
	daisy_widget_list_add_element(list,win,daisy_widget_list_create_element("Hello"));
	daisy_widget_list_add_element(list,win,daisy_widget_list_create_element("Hello"));
	daisy_widget_list_add_element(list,win,daisy_widget_list_create_element("Hello"));
	daisy_widget_list_add_element(list,win,daisy_widget_list_create_element("Hello"));
	daisy_widget_list_add_element(list,win,daisy_widget_list_create_element("Hello"));
	daisy_widget_list_add_element(list,win,daisy_widget_list_create_element("Hello"));
	daisy_widget_list_add_element(list,win,daisy_widget_list_create_element("Hello"));
	daisy_widget_list_add_element(list,win,daisy_widget_list_create_element("Hello"));
	daisy_widget_list_add_element(list,win,daisy_widget_list_create_element("Hello"));
	daisy_widget_list_add_element(list,win,daisy_widget_list_create_element("Hello"));
	daisy_widget_list_add_element(list,win,daisy_widget_list_create_element("Hello"));
	daisy_widget_list_add_element(list,win,daisy_widget_list_create_element("Hello"));
	daisy_widget_list_add_element(list,win,daisy_widget_list_create_element("Hello"));
	daisy_widget_list_add_element(list,win,daisy_widget_list_create_element("Hello"));
	daisy_widget_list_add_element(list,win,daisy_widget_list_create_element("Hello"));
	daisy_widget_list_add_element(list,win,daisy_widget_list_create_element("Hello"));
	daisy_widget_list_add_element(list,win,daisy_widget_list_create_element("Hello"));
	daisy_widget_list_add_element(list,win,daisy_widget_list_create_element("Hello"));
	daisy_sv_add_component(sv,(daisy_widget_t*)list);
	
	daisy_window_show(win);

	int pri_event_fd = daisy_get_event_fd();
	pri_event_t e;
	while(1) {
		/*pri_event_t *e = daisy_get_gifts(true);
		daisy_window_service_event(win,e);*/
		ioquery (pri_event_fd,PRI_LOOP_GET_EVENT,&e);
		if (e.type != 0) {
			if (e.type == DAISY_CURSOR_MOVED) {
				daisy_window_handle_mouse(win,e.dword, e.dword2, e.dword3);
				memset(&e, 0, sizeof(pri_event_t));
			}
		}
		sys_wait();
	}
}