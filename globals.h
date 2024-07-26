#ifndef globals_h
#define globals_h

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

constexpr const char* GRAY = "\u001b[38;5;242m";
constexpr const char* GRAY_BUT_LIGHTER = "\u001b[38;5;244m";
constexpr const char* LIGHT_GRAY = "\u001b[38;5;247m";
constexpr const char* WHITE = "\u001b[38;5;15m";
constexpr const char* RED = "\u001b[38;5;160m";
constexpr const char* LIME = "\u001b[38;5;10m";
constexpr const char* YELLOW = "\u001b[38;5;11m";
constexpr const char* SILVER = "\u001b[38;5;255m";
constexpr const char* PURPLE = "\u001b[38;5;129m";
constexpr const char* ORANGE = "\u001b[38;5;208m";
constexpr const char* RESET = "\u001b[0m";

int x_pos = 60, y_pos = 20, room_number = 0;
int pause_flag, flag_first_room_button_text, flag_first_room_door_text, flag_second_room_mirror_text, maze_flag;
int room_color[room_amount][height][width];

#endif // globals_h