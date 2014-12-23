/*
* Copyright (c) 2014 Rick Ucker
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
#
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
#
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*/

#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0x76, 0x9F, 0x72, 0xA8, 0x88, 0x51, 0x4A, 0xA1, 0xB8, 0xD9, 0xFB, 0x74, 0xF5, 0x45, 0xE2, 0xA7 }
PBL_APP_INFO(MY_UUID,
             "Chrono", "Rick Ucker",
             1, 0, /* App version */
             RESOURCE_ID_MASAMUNE_WHITE,
             APP_INFO_STANDARD_APP);

static const char * CRONO_SCRIPT_TEXT="I love you very much and I want the world to know that we're a team. Let's take on the world together. Let's make it official. Will you be my Lucca?";

Window window;
BmpContainer image_container_crono;
BmpContainer image_container_lucca;
TextLayer textLayer;
ScrollLayer scrollLayer;
void handle_init(AppContextRef ctx) {
  GSize text_area_size = GSize(144, 2000);
  window_init(&window, "Main");
  window_set_fullscreen(&window, true);
  window_set_background_color(&window, GColorBlack);
  window_stack_push(&window, true /* Animated */);
  //Crono
  resource_init_current_app(&CHRONO_IMAGE_RESOURCES);
  bmp_init_container(RESOURCE_ID_CRONO_BLACK, &image_container_crono);
  bitmap_layer_set_alignment(&image_container_crono.layer, GAlignCenter);
  layer_set_frame((Layer *)&image_container_crono.layer, GRect(0,0,72,70));
  layer_add_child(&window.layer, (Layer *)&image_container_crono.layer);
  //Lucca
  resource_init_current_app(&CHRONO_IMAGE_RESOURCES);
  bmp_init_container(RESOURCE_ID_LUCCA_BLACK, &image_container_lucca);
  bitmap_layer_set_alignment(&image_container_lucca.layer, GAlignCenter);
  layer_set_frame((Layer *)&image_container_lucca.layer, GRect(72,0,72,70));
  layer_add_child(&window.layer, (Layer *)&image_container_lucca.layer);

  text_layer_init(&textLayer, GRect(0,0,144,88));
  text_layer_set_text_color(&textLayer, GColorWhite);
  text_layer_set_background_color(&textLayer, GColorBlack);
  text_layer_set_font(&textLayer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text(&textLayer, CRONO_SCRIPT_TEXT);
  text_layer_set_size(&textLayer, text_area_size);

  scroll_layer_init(&scrollLayer, GRect(0,70,144,88));
  scroll_layer_set_click_config_onto_window(&scrollLayer, &window);
  scroll_layer_set_content_size(&scrollLayer, text_area_size);
  scroll_layer_add_child(&scrollLayer, &textLayer.layer);

  GSize used_size = text_layer_get_max_used_size(app_get_current_graphics_context(), &textLayer);
  GSize max_size = GSize(used_size.w, used_size.h + 4);
  text_layer_set_size(&textLayer, max_size);
  scroll_layer_set_content_size(&scrollLayer, max_size);
  layer_add_child(&window.layer, &scrollLayer.layer);
}

void handle_deinit(AppContextRef ctx) {
 bmp_deinit_container(&image_container_crono);
 bmp_deinit_container(&image_container_lucca);
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .deinit_handler = &handle_deinit
  };
 app_event_loop(params, &handlers);
}
