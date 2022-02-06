#ifndef C_LENIUM_H
#define C_LENIUM_H

struct browser_options {
    
};

struct cookies_s {
    char *name;
    char *value;
    char *path;
    char *domain;
    char *secure;
    char *expiry;
    char *httpOnly;
    char *sameSite;
};

#define DRIVER_SESSION_ID_SIZE 64
char DRIVER_SESSION_ID[DRIVER_SESSION_ID_SIZE] = {0};

void driver_get(char *url);
void driver_forward();
void driver_back();
void driver_refresh();
void driver_close();
char *driver_getUrl();
char *driver_getTitle();
char *driver_getScreenshot();
char *driver_getSource();
void driver_print_page();
void driver_execute_script(char *javascript);

static char *_driver_find_element_by(char *using, char *value);
char *driver_find_element_by_id(char *id);
char *driver_find_element_by_name(char *name);
char *driver_find_element_by_xpath(char *xpath);
char *driver_find_element_by_css_selector(char *css_selector);
char *driver_find_element_by_link_text(char *link_text);
char *driver_find_element_by_partial_link_text(char *link_text);
char *driver_find_element_by_class_name(char class_name);
char *driver_find_element_by_tag_name(char *tag_name);

void driver_element_send_keys(char *element, char *keys);
void driver_element_clear(char *element, char *keys);
void driver_element_click(char *element);
char *driver_element_isEnabled(char *element);
char *driver_element_rect(char *element);
char *driver_element_tagName(char *element);
char *driver_element_text(char *element);
char *driver_element_cssValue(char *element, char *css_property);
char *driver_element_property(char *element, char *property);
char *driver_element_attribute(char *element, char *attribute);
char *driver_element_isSelected(char *element);
char *driver_element_getActive();

void driver_switch_to_window(char *window);
void driver_switch_to_frame(char *frame);
void driver_switch_to_default_content();
void driver_switch_to_alert();

void driver_window_fullscreen();
void driver_window_minimize();
void driver_window_maximize();
void driver_window_rect_set(char *x, char *y, char *width, char *height);
char *driver_window_rect_get();

void driver_add_cookie();
char *driver_get_all_cookies();
char *driver_get_cookie(char *cookie_name);
void driver_delete_cookie(char *cookie_name);
void driver_delete_all_cookies();

char *driver_alert_get();
void driver_alert_accept();
void driver_alert_dismiss();

void driver_wait_implicitly(int seconds);
void driver_wait_until_title_is(char *title, int max_time);
void driver_wait_until_title_contains(char *key, int max_time);
void driver_wait_until_presence_of_element_located(char *locator, int max_time);
void driver_wait_until_presence_of_all_elements_located(char *locator, int max_time);
void driver_wait_until_visibility_of_element_located(char *locator, int max_time);
void driver_wait_until_visibility_of(char *element, int max_time);
void driver_wait_until_text_to_be_present_in_element(int max_time);
void driver_wait_until_text_to_be_present_in_element_value(int max_time);
void driver_wait_until_frame_to_be_available_and_switch_to_it(int max_time);
void driver_wait_until_invisibility_of_element_located(char *locator, int max_time);
void driver_wait_until_element_to_be_clickable(int max_time);
void driver_wait_until_staleness_of(char *staleness, int max_time);
void driver_wait_until_element_to_be_selected(int max_time);
void driver_wait_until_element_located_to_be_selected(int max_time);
void driver_wait_until_element_selection_state_to_be(char *state, int max_time);
void driver_wait_until_element_located_selection_state_to_be(char *state, int max_time);
void driver_wait_until_alert_is_present(int max_time);

#endif