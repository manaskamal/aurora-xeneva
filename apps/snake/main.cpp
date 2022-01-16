#include <daisy.h>
#include <daisy_priwm_window.h>
#include <daisy_window.h>

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



int main (int argc, char* argv[]) {
	daisy_application();
	daisy_window_t *win = daisy_window_create (100,100,500,500,NULL);
	for (int i = 0; i < 500; i++)
		for (int j = 0; j < 500; j++)
			win->backing_store[i * win->ctx->width + j] = BLUE;

	while(1) {
		pri_event_t *e = daisy_get_gifts();
	}
}