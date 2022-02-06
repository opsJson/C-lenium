#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "main.h"
#include "include/hget.h"
#include "include/json-parser.h"

static void driver_open(void) {
    int code;
    char *r;
    json_t *json, *back;
    size_t c1, c2;
    
    r = get("localhost:9515/session", "{\\\"capabilities\\\":{}}", &code, "");

    if (code != 200) {
        free(r);
        return;
    }
    
    json = json_parse(r, &c1);
    back = json;
    json = json_parse(json[0].value, &c2);

    strncpy(DRIVER_SESSION_ID, json[1].value, DRIVER_SESSION_ID_SIZE -1);

    json_free(back, c1);
    json_free(json, c2);
}

void driver_get(char *url) {
    char *_url, *data, *r;
    int code;

    makestr(_url, "localhost:9515/session/%s/url", DRIVER_SESSION_ID);

    makestr(data, "{\\\"url\\\":\\\"%s\\\"}", url);

    r = get(_url, data, &code, "Content-Type: application/json");

    printf("[%s]\n", DRIVER_SESSION_ID);

    free(r);
    free(_url);
    free(data);
}

void driver_forward() {
    char *url, *r;
    int code;

    makestr(url, "localhost:9515/session/%s/forward", DRIVER_SESSION_ID);

    r = get(url, "{}", &code, "Content-Type: application/json");

    free(r);
    free(url);
}

void driver_back() {
    char *url, *r;
    int code;

    makestr(url, "localhost:9515/session/%s/back", DRIVER_SESSION_ID);

    r = get(url, "{}", &code, "Content-Type: application/json");

    free(r);
    free(url);
}

void driver_refresh() {
    char *url, *r;
    int code;

    makestr(url, "localhost:9515/session/%s/refresh", DRIVER_SESSION_ID);

    r = get(url, "{}", &code, "Content-Type: application/json");

    free(r);
    free(url);
}

void driver_close() {
    char *r, *url;
    int code;

    makestr(url, "localhost:9515/session/%s/window", DRIVER_SESSION_ID);

    r = hget_method("DELETE", url, "", &code, "");

    free(r);
    free(url);
}

char *driver_current_url() {
    char *r, *url, *current_url;
    int code;
    json_t *json;
    size_t c;

    makestr(url, "localhost:9515/session/%s/url", DRIVER_SESSION_ID);

    r = hget_method("GET", url, "", &code, "");

    json = json_parse(r, &c);

    makestr(current_url, "%s", json[0].value);

    json_free(json, c);
    free(r);
    free(url);

    return current_url;
}

char *driver_screenshot() {
    char *url, *r;
    int code;

    makestr(url, "localhost:9515/session/%s/screenshot", DRIVER_SESSION_ID);

    r = hget_method("GET", url, "", &code, "");
    
    free(url);

    return r;
}

void driver_print_page() {
    char *url, *r;
    int code;

    makestr(url, "localhost:9515/session/%s/print", DRIVER_SESSION_ID);

    r = get(url, "", &code, "");
    
    free(url);
    free(r);
}

void driver_execute_script(char *javascript) {
    char *url, *data, *r;
    int code;

    makestr(url, "localhost:9515/session/%s/execute/sync", DRIVER_SESSION_ID);

    makestr(data, "{\\\"script\\\":\\\"%s\\\",\\\"args\\\":[]}", javascript);

    r = get(url, data, &code, "");

    free(r);
}

//@segfault
char *driver_getSource() {
    char *url, *r;
    int code;

    makestr(url, "localhost:9515/session/%s/source", DRIVER_SESSION_ID);

    r = hget_method("GET", url, "", &code, "");

    free(url);

    return r;
}

static char *_driver_find_element_by(char *using, char *value) {
    char *url, *data, *r, *element;
    int code;
    json_t *json, *back;
    size_t c1, c2;

    makestr(url, "localhost:9515/session/%s/element", DRIVER_SESSION_ID);

    makestr(data, "{\\\"using\\\":\\\"%s\\\",\\\"value\\\":\\\"%s\\\"}", using, value);

    r = get(url, data, &code, "Content-Type: application/json");

    json = json_parse(r, &c1);
    back = json;
    json = json_parse(json[0].value, &c2);

    makestr(element, "%s", json[0].value);

    json_free(back, c1);
    json_free(json, c2);
    free(r);
    free(url);
    free(data);    

    return element;
}

char *driver_find_element_by_id(char *id) {
    return NULL;
}

char *driver_find_element_by_name(char *name) {
    return NULL;
}

char *driver_find_element_by_xpath(char *xpath) {
    char *element;
    element = _driver_find_element_by("xpath", xpath);

    return element;
}

char *driver_find_element_by_css_selector(char *css_selector) {
    char *element;
    element = _driver_find_element_by("css selector", css_selector);

    return element;
}

char *driver_find_element_by_link_text(char *link_text) {
    char *element;
    element = _driver_find_element_by("link text", link_text);

    return element;
}

char *driver_find_element_by_partial_link_text(char *link_text) {
    char *element;
    element = _driver_find_element_by("partial link text", link_text);

    return element;
}

char *driver_find_element_by_class_name(char class_name) {
    return NULL;
}

char *driver_find_element_by_tag_name(char *tag_name) {
    char *element;
    element = _driver_find_element_by("tag name", tag_name);

    return element;
}

void driver_element_send_keys(char *element, char *keys) {
    char *url, *data, *r;
    int code;

    makestr(url, "localhost:9515/session/%s/element/%s/value", DRIVER_SESSION_ID, element);

    makestr(data, "{\\\"text\\\":\\\"%s\\\"}", keys);

    r = get(url, data, &code, "Content-Type: application/json");

    free(r);
    free(url);
    free(data);
}

void driver_element_clear(char *element, char *keys) {
    char *url, *r;
    int code;

    makestr(url, "localhost:9515/session/%s/element/%s/clear", DRIVER_SESSION_ID, element);

    r = get(url, "{}", &code, "Content-Type: application/json");

    free(r);
    free(url);
}

void driver_element_click(char *element) {
    char *url, *r;
    int code;

    makestr(url, "localhost:9515/session/%s/element/%s/click", DRIVER_SESSION_ID, element);

    r = get(url, "{}", &code, "");

    free(url);
    free(r);
}

char *driver_element_isEnabled(char *element) {
    char *url, *r;
    int code;
    
    makestr(url, "localhost:9515/session/%s/element/%s/enabled", DRIVER_SESSION_ID, element);

    r = hget_method("GET", url, "", &code, "");

    free(url);

    return r;
}

char *driver_element_rect(char *element) {
    char *url, *r;
    int code;
    
    makestr(url, "localhost:9515/session/%s/element/%s/rect", DRIVER_SESSION_ID, element);

    r = hget_method("GET", url, "", &code, "");

    free(url);

    return r;
}

char *driver_element_tagName(char *element) {
    char *url, *r;
    int code;
    
    makestr(url, "localhost:9515/session/%s/element/%s/name", DRIVER_SESSION_ID, element);

    r = hget_method("GET", url, "", &code, "");

    free(url);

    return r;
}

char *driver_element_text(char *element) {
    char *url, *r;
    int code;
    
    makestr(url, "localhost:9515/session/%s/element/%s/text", DRIVER_SESSION_ID, element);

    r = hget_method("GET", url, "", &code, "");

    free(url);

    return r;
}

char *driver_element_cssValue(char *element, char *css_property) {
    char *url, *r;
    int code;
    
    makestr(url, "localhost:9515/session/%s/element/%s/css/%s", DRIVER_SESSION_ID, element, css_property);

    r = hget_method("GET", url, "", &code, "");

    free(url);

    return r;
}

char *driver_element_property(char *element, char *property) {
    char *url, *r;
    int code;
    
    makestr(url, "localhost:9515/session/%s/element/%s/property/%s", DRIVER_SESSION_ID, element, property);

    r = hget_method("GET", url, "", &code, "");

    free(url);

    return r;
}

char *driver_element_attribute(char *element, char *attribute) {
    char *url, *r;
    int code;
    
    makestr(url, "localhost:9515/session/%s/element/%s/attribute/%s", DRIVER_SESSION_ID, element, attribute);

    r = hget_method("GET", url, "", &code, "");

    free(url);

    return r;
}

char *driver_element_isSelected(char *element) {
    char *url, *r;
    int code;
    
    makestr(url, "localhost:9515/session/%s/element/%s/selected", DRIVER_SESSION_ID, element);

    r = hget_method("GET", url, "", &code, "");

    free(url);

    return r;
}

char *driver_element_getActive() {
    char *url, *r;
    int code;

    makestr(url, "localhost:9515/session/%s/element/active", DRIVER_SESSION_ID);

    r = hget_method("GET", url, "", &code, "");

    free(url);

    return r;
}

void driver_switch_to_window(char *window);
void driver_switch_to_frame(char *frame);
void driver_switch_to_default_content();
void driver_switch_to_alert();

void driver_window_fullscreen() {

}

void driver_window_minimize() {

}

void driver_window_maximize() {

}

void driver_window_rect_set(char *x, char *y) {

}

char *driver_window_rect_get() {
    return NULL;
}

void driver_add_cookie(struct cookies_s *cookies) {
    char *url, *data, *r;
    char time_buf[32];
    int code;

    if (!cookies->name) cookies->name = "";
    if (!cookies->value) cookies->value = "";
    if (!cookies->domain) cookies->domain = "";
    if (!cookies->sameSite) cookies->sameSite = "";
    if (!cookies->path) cookies->path = "/";
    if (!cookies->secure) cookies->secure = "false";
    if (!cookies->httpOnly) cookies->httpOnly = "false";
    if (!cookies->expiry)
    {
        sprintf(time_buf, "%llu", time(0) + 999999999);
        cookies->expiry = time_buf;
    }
    makestr(url, "localhost:9515/session/%s/cookie", DRIVER_SESSION_ID);

    makestr(data, "{\\\"cookie\\\":{\\\"name\\\":\\\"%s\\\","
    "\\\"value\\\":\\\"%s\\\",\\\"path\\\":\\\"%s\\\","
    "\\\"domain\\\":\\\"%s\\\",\\\"secure\\\":%s,"
    "\\\"expiry\\\":%s,\\\"httpOnly\\\":%s,"
    "\\\"sameSite\\\":\\\"%s\\\"}}", cookies->name, cookies->value, cookies->path, cookies->domain,
        cookies->secure, cookies->expiry, cookies->httpOnly, cookies->sameSite);

    r = get(url, data, &code, "");

    free(r);
    free(url);
    free(data);
}
#define driver_add_cookie(...) driver_add_cookie(&(struct cookies_s){__VA_ARGS__})

char *driver_get_all_cookies() {
    char *url, *r;
    int code;

    makestr(url, "localhost:9515/session/%s/cookie", DRIVER_SESSION_ID);

    r = hget_method("GET", url, "", &code, "NULL");
    
    free(url);

    return r;
}

char *driver_get_cookie(char *cookie_name) {
    char *url, *r;
    int code;

    makestr(url, "localhost:9515/session/%s/cookie/%s", DRIVER_SESSION_ID, cookie_name);

    r = hget_method("GET", url, "", &code, "NULL");
    
    free(url);

    return r;
}

void driver_delete_cookie(char *cookie_name) {
    char *url, *r;
    int code;

    makestr(url, "localhost:9515/session/%s/cookie/%s", DRIVER_SESSION_ID, cookie_name);

    r = hget_method("DELETE", url, "", &code, "NULL");
    
    free(url);
    free(r);
}

void driver_delete_all_cookies() {
    char *url, *r;
    int code;

    makestr(url, "localhost:9515/session/%s/cookie", DRIVER_SESSION_ID);

    r = hget_method("DELETE", url, "", &code, "NULL");
    
    free(url);
    free(r);
}

char *driver_alert_get() {
    char *url, *r;
    int code;

    makestr(url, "localhost:9515/session/%s/alert/text", DRIVER_SESSION_ID);

    r = hget_method("GET", url, "", &code, "");

    free(url);

    return r;
}

void driver_alert_accept() {
    char *url, *r;
    int code;

    makestr(url, "localhost:9515/session/%s/alert/accept", DRIVER_SESSION_ID);

    r = get(url, "{}", &code, "");

    free(url);
    free(r);
}

void driver_alert_dismiss() {
    char *url, *r;
    int code;

    makestr(url, "localhost:9515/session/%s/alert/dismiss", DRIVER_SESSION_ID);

    r = get(url, "{}", &code, "");

    free(url);
    free(r);
}

int main(void) {
    driver_open();

    driver_get("https://www.w3.org/TR/webdriver");

    return 0;
}