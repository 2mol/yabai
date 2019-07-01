#ifndef APPLICATION_H
#define APPLICATION_H

#define OBSERVER_CALLBACK(name) void name(AXObserverRef observer, AXUIElementRef element, CFStringRef notification, void *context)
typedef OBSERVER_CALLBACK(observer_callback);

#define AX_APPLICATION_WINDOW_CREATED_INDEX       0
#define AX_APPLICATION_WINDOW_FOCUSED_INDEX       1
#define AX_APPLICATION_WINDOW_MAIN_CHANGED_INDEX  2
#define AX_APPLICATION_WINDOW_MOVED_INDEX         3
#define AX_APPLICATION_WINDOW_RESIZED_INDEX       4
#define AX_APPLICATION_WINDOW_TITLE_CHANGED_INDEX 5
#define AX_APPLICATION_WINDOW_MENU_OPENED_INDEX   6

#define AX_APPLICATION_WINDOW_CREATED       (1 << AX_APPLICATION_WINDOW_CREATED_INDEX)
#define AX_APPLICATION_WINDOW_FOCUSED       (1 << AX_APPLICATION_WINDOW_FOCUSED_INDEX)
#define AX_APPLICATION_WINDOW_MAIN_CHANGED  (1 << AX_APPLICATION_WINDOW_MAIN_CHANGED_INDEX)
#define AX_APPLICATION_WINDOW_MOVED         (1 << AX_APPLICATION_WINDOW_MOVED_INDEX)
#define AX_APPLICATION_WINDOW_RESIZED       (1 << AX_APPLICATION_WINDOW_RESIZED_INDEX)
#define AX_APPLICATION_WINDOW_TITLE_CHANGED (1 << AX_APPLICATION_WINDOW_TITLE_CHANGED_INDEX)
#define AX_APPLICATION_ALL                  (AX_APPLICATION_WINDOW_CREATED |\
                                             AX_APPLICATION_WINDOW_FOCUSED |\
                                             AX_APPLICATION_WINDOW_MAIN_CHANGED |\
                                             AX_APPLICATION_WINDOW_MOVED |\
                                             AX_APPLICATION_WINDOW_RESIZED |\
                                             AX_APPLICATION_WINDOW_TITLE_CHANGED)

static CFStringRef ax_application_notification[] =
{
    [AX_APPLICATION_WINDOW_CREATED_INDEX]       = kAXCreatedNotification,
    [AX_APPLICATION_WINDOW_FOCUSED_INDEX]       = kAXFocusedWindowChangedNotification,
    [AX_APPLICATION_WINDOW_MAIN_CHANGED_INDEX]  = kAXMainWindowChangedNotification,
    [AX_APPLICATION_WINDOW_MOVED_INDEX]         = kAXWindowMovedNotification,
    [AX_APPLICATION_WINDOW_RESIZED_INDEX]       = kAXWindowResizedNotification,
    [AX_APPLICATION_WINDOW_TITLE_CHANGED_INDEX] = kAXTitleChangedNotification,
    [AX_APPLICATION_WINDOW_MENU_OPENED_INDEX]   = kAXMenuOpenedNotification
};

struct ax_application
{
    AXUIElementRef ref;
    ProcessSerialNumber psn;
    uint32_t pid;
    char *name;
    AXObserverRef observer_ref;
    uint8_t notification;
    bool is_observing;
    bool is_hidden;
    bool retry;
};

bool application_is_frontmost(struct ax_application *application);
bool application_is_hidden(struct ax_application *application);
uint32_t application_main_window(struct ax_application *application);
uint32_t application_focused_window(struct ax_application *application);
struct ax_window **application_window_list(struct ax_application *application, int *window_count);
bool application_observe(struct ax_application *application);
void application_unobserve(struct ax_application *application);
struct ax_application *application_create(struct process *process);
void application_destroy(struct ax_application *application);

#endif
