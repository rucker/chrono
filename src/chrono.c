/*
* Copyright (c) 2013, 2014, 2015 Rick Ucker
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*/

#include <pebble.h>

#define MY_UUID { 0x76, 0x9F, 0x72, 0xA8, 0x88, 0x51, 0x4A, 0xA1, 0xB8, 0xD9, 0xFB, 0x74, 0xF5, 0x45, 0xE2, 0xA7 }

static const char * CRONO_SCRIPT_TEXT="We've done and seeen a lot up to now. We've traveled to foreign lands and made new friends. We have met challenges. We have leveled up together. We defeated the Dragon Tank! But the world is large and new challenges await.\n\nAre you ready to begin the next quest? Will you travel time and space with me? Will you visit Zeal, the land of dreams and magic with me? Will you battle Magus, come with me to the end of time and back, and find our destinies together?\n\nI love you very much and I want the world to know that we're a team. Let's take on the world together. Let's make it official. Will you be my Lucca?";

Window *window;
GBitmap *bmpCrono;
GBitmap *bmpLucca;
static BitmapLayer *bmpLayerCrono;
static BitmapLayer *bmpLayerLucca;
TextLayer *textLayer;
ScrollLayer *scrollLayer;

void handle_init() {
  GSize text_area_size = GSize(144, 2000);
  window = window_create();
  window_set_fullscreen(window, true);
  window_set_background_color(window, GColorBlack);
  window_stack_push(window, true);

  //Crono
  bmpCrono = gbitmap_create_with_resource(RESOURCE_ID_CRONO);
  bmpLayerCrono = bitmap_layer_create(GRect(0,0,72,70));
  bitmap_layer_set_bitmap(bmpLayerCrono, bmpCrono);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(bmpLayerCrono));

  //Lucca
  bmpLucca = gbitmap_create_with_resource(RESOURCE_ID_LUCCA);
  bmpLayerLucca = bitmap_layer_create(GRect(72,0,72,70));
  bitmap_layer_set_bitmap(bmpLayerLucca, bmpLucca);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(bmpLayerLucca));

  //Text layer
  textLayer = text_layer_create(GRect(0,0,144,88));
  text_layer_set_text_color(textLayer, GColorWhite);
  text_layer_set_background_color(textLayer, GColorBlack);
  text_layer_set_font(textLayer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text(textLayer, CRONO_SCRIPT_TEXT);
  text_layer_set_size(textLayer, text_area_size);

  //Scroll layer
  scrollLayer = scroll_layer_create(GRect(0,70,144,88));
  scroll_layer_set_click_config_onto_window(scrollLayer, window);
  scroll_layer_set_content_size(scrollLayer, text_area_size);
  scroll_layer_add_child(scrollLayer, text_layer_get_layer(textLayer));

  //Calc and set scroll layer size
  GSize used_size = text_layer_get_content_size(textLayer);
  GSize max_size = GSize(used_size.w, used_size.h + 4);
  text_layer_set_size(textLayer, max_size);
  scroll_layer_set_content_size(scrollLayer, max_size);
  layer_add_child(window_get_root_layer(window), scroll_layer_get_layer(scrollLayer));
}

void handle_deinit() {
  text_layer_destroy(textLayer);
  window_destroy(window);
  gbitmap_destroy(bmpCrono);
  gbitmap_destroy(bmpLucca);
  bitmap_layer_destroy(bmpLayerCrono);
  bitmap_layer_destroy(bmpLayerLucca);
}


int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
