#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdint.h>
#include "./ezk_window.h"

typedef struct {
    ezk_win_id id;

    HWND hwnd;
    HINSTANCE hInstance;

    ezk_u32 ev_mask;
    ezk_bool fullscreen;

    RECT windowed_rect;
    DWORD windowed_style;

} ezk_win32_window;

static ezk_win32_window** int_windows = NULL;
static ezk_win_id int_windows_count = 0;

static void realloc_windows(ezk_win_id len) {
    if (int_windows) {
        int_windows = realloc(int_windows, len * sizeof(ezk_win32_window*));
    } else {
        int_windows = malloc(len * sizeof(ezk_win32_window*));
    }
    int_windows_count = len;
}

static ezk_event translate_event(MSG msg) {
    ezk_event ev;

    switch (msg.message) {
        case WM_KEYDOWN:
            ev.type = EZK_EVENT_KEYDOWN;
            ev.key.key = ezk_key_win32_to_ezk((ezk_i32)msg.wParam);
            break;
        case WM_KEYUP:
            ev.type = EZK_EVENT_KEYUP;
            ev.key.key = ezk_key_win32_to_ezk((ezk_i32)msg.wParam);
            break;
        case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
            ev.type = EZK_EVENT_BUTTONDOWN;
            ev.button.button = msg.wParam;
            break;
        case WM_LBUTTONUP:
        case WM_MBUTTONUP:
        case WM_RBUTTONUP:
            ev.type = EZK_EVENT_BUTTONUP;
            ev.button.button = msg.wParam;
            break;
        case WM_MOUSEMOVE:
            ev.type = EZK_EVENT_MOUSEMOVE;
            ev.mousemove.mouse_pos = (ezk_v2_i){ GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam) };
            break;
        case WM_SETFOCUS:
            ev.type = EZK_EVENT_FOCUSIN;
            break;
        case WM_KILLFOCUS:
            ev.type = EZK_EVENT_FOCUSOUT;
            break;
        case WM_CLOSE:
        case WM_DESTROY:
            ev.type = EZK_EVENT_EXIT;
            break;
        case WM_SIZE:
            ev.type = EZK_EVENT_DIMCHANGE;
            ev.dimension.dims = (ezk_v2_i){ LOWORD(msg.lParam), HIWORD(msg.lParam) };
            break;
        default:
            ev.type = EZK_EVENT_UNKNOWN;
            break;
    }

    return ev;
}

ezk_time get_time() {
    FILETIME ft;
    GetSystemTimePreciseAsFileTime(&ft);  // 100‑ns precision :contentReference[oaicite:2]{index=2}

    ULARGE_INTEGER uli;
    uli.LowPart = ft.dwLowDateTime;
    uli.HighPart = ft.dwHighDateTime;

    uint64_t usec_total = uli.QuadPart / 10;  // convert to microseconds
    ezk_time out;
    out.seconds = (time_t)(usec_total / 1000000ULL);
    out.nanoseconds = (uint32_t)(usec_total % 1000000ULL) * 1000;
    return out;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
    default:
	  return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

void ezk_internal_set_fullscreen(ezk_win_id id, ezk_bool fs) {
    ezk_win32_window* win = int_windows[id];

    if (fs == win->fullscreen) return;

    HWND hwnd = win->hwnd;
    HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY);
    MONITORINFO mi = { .cbSize = sizeof(mi) };
    GetMonitorInfo(hMonitor, &mi);

    if (fs) {
        GetWindowRect(hwnd, &win->windowed_rect);
        win->windowed_style = GetWindowLong(hwnd, GWL_STYLE);

        SetWindowLong(hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
        SetWindowPos(hwnd, HWND_TOP,
                     mi.rcMonitor.left, mi.rcMonitor.top,
                     mi.rcMonitor.right - mi.rcMonitor.left,
                     mi.rcMonitor.bottom - mi.rcMonitor.top,
                     SWP_FRAMECHANGED);
    } else {
        SetWindowLong(hwnd, GWL_STYLE, win->windowed_style);
        SetWindowPos(hwnd, HWND_TOP,
                     win->windowed_rect.left, win->windowed_rect.top,
                     win->windowed_rect.right - win->windowed_rect.left,
                     win->windowed_rect.bottom - win->windowed_rect.top,
                     SWP_FRAMECHANGED);
    }

    win->fullscreen = fs;
}

void ezk_internal_set_dims(ezk_win_id id, ezk_v2_i dims) {
    ezk_win32_window* win = int_windows[id];
    SetWindowPos(win->hwnd, NULL, 0, 0, dims.x, dims.y, SWP_NOMOVE | SWP_NOZORDER);
}

void ezk_internal_set_pos(ezk_win_id id, ezk_v2_i pos) {
    ezk_win32_window* win = int_windows[id];
    SetWindowPos(win->hwnd, NULL, pos.x, pos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void ezk_internal_set_name(ezk_win_id id, ezk_string name) {
    ezk_win32_window* win = int_windows[id];
    SetWindowText(win->hwnd, name);
}

void ezk_internal_create_window(ezk_window* window, ezk_win_desc desc) {
    if (window->id >= int_windows_count) {
        realloc_windows(window->id + 1);
    }

    int_windows[window->id] = malloc(sizeof(ezk_win32_window));
    ezk_win32_window* win = int_windows[window->id];

    win->id = window->id;
    win->fullscreen = desc.fullscreen;
    win->hInstance = GetModuleHandle(NULL);

    const char* class_name = "EZK_WIN_CLASS";

    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = win->hInstance;
    wc.lpszClassName = class_name;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClassEx(&wc)) {
        fprintf(stderr, "RegisterClassEx failed\n");
        exit(1);
    }


    DWORD style = WS_OVERLAPPEDWINDOW;

    RECT rect = { 0, 0, desc.dims.x, desc.dims.y };
    AdjustWindowRect(&rect, style, FALSE);

    HWND hwnd = CreateWindowEx(
        0, class_name, desc.name, style,
        desc.pos.x, desc.pos.y,
        rect.right - rect.left, rect.bottom - rect.top,
        NULL, NULL, win->hInstance, NULL
    );

    if (!hwnd) {
        fprintf(stderr, "CreateWindowEx failed.\n");
        exit(1);
    }

    win->hwnd = hwnd;

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    if (desc.fullscreen) {
        ezk_internal_set_fullscreen(window->id, true);
    }
}

void ezk_internal_delete_window(ezk_win_id id) {
    ezk_win32_window* win = int_windows[id];
    DestroyWindow(win->hwnd);
    free(win);
}

static ezk_bool is_next_event(MSG* msg) {
    return PeekMessage(msg, NULL, 0, 0, PM_REMOVE);
}

static ezk_event get_next_event(ezk_win32_window* win, MSG* msg) {
    TranslateMessage(msg);
    DispatchMessage(msg);

    ezk_event ev = translate_event(*msg);
    ev.any.win_id = win->id;
    ev.any.time = get_time();
    return ev;
}

ezk_event* ezk_internal_update_evqueue(ezk_win_id id) {
    ezk_win32_window* win = int_windows[id];

    // Start with space for at least one event plus terminator
    ezk_u32 ev_index = 0;
    ezk_event* ev_queue = malloc(2 * sizeof(ezk_event));
    MSG msg;

    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        // Process and store the event
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        // Debug print before translation
        if (msg.message == WM_KEYDOWN) {
            printf("Raw Windows key code: %lu\n", msg.wParam);
        }

        ev_queue[ev_index] = translate_event(msg);
        ev_queue[ev_index].any.win_id = win->id;
        ev_queue[ev_index].any.time = get_time();
        ev_queue[ev_index].any.index = ev_index;

        // Debug print after translation
        if (ev_queue[ev_index].type == EZK_EVENT_KEYDOWN) {
            printf("Translated key code: %d\n", ev_queue[ev_index].key.key);
        }

        // Resize array for next event
        ev_index++;
        ev_queue = realloc(ev_queue, sizeof(ezk_event) * (ev_index + 1));
    }

    // Add terminating event
    ezk_event term = {0};
    term.type = EZK_EVENT_NONE;
    ev_queue[ev_index] = term;

    return ev_queue;
}
