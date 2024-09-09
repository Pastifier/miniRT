/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:49:01 by melshafi          #+#    #+#             */
/*   Updated: 2024/09/09 13:49:02 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
 #define KEYS_H

 #ifdef __MACH__
  // Alphabet Keys
  #define KEY_A 0
  #define KEY_B 11
  #define KEY_C 8
  #define KEY_D 2
  #define KEY_E 14
  #define KEY_F 3
  #define KEY_G 5
  #define KEY_H 4
  #define KEY_I 34
  #define KEY_J 38
  #define KEY_K 40
  #define KEY_L 37
  #define KEY_M 46
  #define KEY_N 45
  #define KEY_O 31
  #define KEY_P 35
  #define KEY_Q 12
  #define KEY_R 15
  #define KEY_S 1
  #define KEY_T 17
  #define KEY_U 32
  #define KEY_V 9
  #define KEY_W 13
  #define KEY_X 7
  #define KEY_Y 16
  #define KEY_Z 6

  // Number Keys (Top Row)
  #define KEY_1 18
  #define KEY_2 19
  #define KEY_3 20
  #define KEY_4 21
  #define KEY_5 23
  #define KEY_6 22
  #define KEY_7 26
  #define KEY_8 28
  #define KEY_9 25
  #define KEY_0 29

  // Function Keys
  #define KEY_F1 122
  #define KEY_F2 120
  #define KEY_F3 99
  #define KEY_F4 118
  #define KEY_F5 96
  #define KEY_F6 97
  #define KEY_F7 98
  #define KEY_F8 100
  #define KEY_F9 101
  #define KEY_F10 109
  #define KEY_F11 103
  #define KEY_F12 111

  // Arrow Keys
  #define KEY_UP 126
  #define KEY_DOWN 125
  #define KEY_LEFT 123
  #define KEY_RIGHT 124

  // Special Keys
  #define KEY_ESC 53
  #define KEY_TAB 48
  #define KEY_CAPSLOCK 57
  #define KEY_SHIFT 56
  #define KEY_CTRL 59
  #define KEY_ALT 58
  #define KEY_CMD 55
  #define KEY_SPACE 49
  #define KEY_ENTER 36
  #define KEY_BACKSPACE 51
  #define KEY_DELETE 117
  #define KEY_HOME 115
  #define KEY_END 119
  #define KEY_PAGEUP 116
  #define KEY_PAGEDOWN 121

  // Punctuation and Symbols
  #define KEY_MINUS 27
  #define KEY_EQUALS 24
  #define KEY_LEFTBRACKET 33
  #define KEY_RIGHTBRACKET 30
  #define KEY_BACKSLASH 42
  #define KEY_SEMICOLON 41
  #define KEY_APOSTROPHE 39
  #define KEY_COMMA 43
  #define KEY_PERIOD 47
  #define KEY_SLASH 44
  #define KEY_GRAVE 50

  // Numeric Keypad
  #define KEY_NUMPAD_0 82
  #define KEY_NUMPAD_1 83
  #define KEY_NUMPAD_2 84
  #define KEY_NUMPAD_3 85
  #define KEY_NUMPAD_4 86
  #define KEY_NUMPAD_5 87
  #define KEY_NUMPAD_6 88
  #define KEY_NUMPAD_7 89
  #define KEY_NUMPAD_8 91
  #define KEY_NUMPAD_9 92
  #define KEY_NUMPAD_PLUS 69
  #define KEY_NUMPAD_MINUS 78
  #define KEY_NUMPAD_MULTIPLY 67
  #define KEY_NUMPAD_DIVIDE 75
  #define KEY_NUMPAD_ENTER 76
  #define KEY_NUMPAD_DECIMAL 65
  #define KEY_NUMPAD_EQUAL 81

 #endif // __MACH__

 #ifdef __linux__ || __unix__

  // Alphabet Keys
  #define KEY_A 97
  #define KEY_B 98
  #define KEY_C 99
  #define KEY_D 100
  #define KEY_E 101
  #define KEY_F 102
  #define KEY_G 103
  #define KEY_H 104
  #define KEY_I 105
  #define KEY_J 106
  #define KEY_K 107
  #define KEY_L 108
  #define KEY_M 109
  #define KEY_N 110
  #define KEY_O 111
  #define KEY_P 112
  #define KEY_Q 113
  #define KEY_R 114
  #define KEY_S 115
  #define KEY_T 116
  #define KEY_U 117
  #define KEY_V 118
  #define KEY_W 119
  #define KEY_X 120
  #define KEY_Y 121
  #define KEY_Z 122

  // Number Keys (Top Row)
  #define KEY_1 49
  #define KEY_2 50
  #define KEY_3 51
  #define KEY_4 52
  #define KEY_5 53
  #define KEY_6 54
  #define KEY_7 55
  #define KEY_8 56
  #define KEY_9 57
  #define KEY_0 48

  // Number Pad Keys
  #define KEY_NUMPAD_1 65457
  #define KEY_NUMPAD_2 65458
  #define KEY_NUMPAD_3 65459
  #define KEY_NUMPAD_4 65460
  #define KEY_NUMPAD_5 65461
  #define KEY_NUMPAD_6 65462
  #define KEY_NUMPAD_7 65463
  #define KEY_NUMPAD_8 65464
  #define KEY_NUMPAD_9 65465
  #define KEY_NUMPAD_0 65456

  // Function Keys
  #define KEY_F1 65470
  #define KEY_F2 65471
  #define KEY_F3 65472
  #define KEY_F4 65473
  #define KEY_F5 65474
  #define KEY_F6 65475
  #define KEY_F7 65476
  #define KEY_F8 65477
  #define KEY_F9 65478
  #define KEY_F10 65479
  #define KEY_F11 65480
  #define KEY_F12 65481

  // Arrow Keys
  #define KEY_UP 65362
  #define KEY_DOWN 65364
  #define KEY_LEFT 65361
  #define KEY_RIGHT 65363

  // Special Keys
  #define KEY_ESCAPE 65307
  #define KEY_TAB 65289
  #define KEY_CAPSLOCK 65509
  #define KEY_SHIFT_L 65505
  #define KEY_SHIFT_R 65506
  #define KEY_CTRL_L 65507
  #define KEY_CTRL_R 65508
  #define KEY_ALT_L 65513
  #define KEY_ALT_R 65514
  #define KEY_SPACE 32
  #define KEY_ENTER 65293
  #define KEY_BACKSPACE 65288
  #define KEY_DELETE 65535
  #define KEY_HOME 65360
  #define KEY_END 65367
  #define KEY_PAGE_UP 65365
  #define KEY_PAGE_DOWN 65366
  #define KEY_INSERT 65379
  #define KEY_PRINT_SCREEN 65377
  #define KEY_PAUSE 65299

  // Miscellaneous Keys
  #define KEY_COMMA 44
  #define KEY_PERIOD 46
  #define KEY_SLASH 47
  #define KEY_BACKSLASH 92
  #define KEY_SEMICOLON 59
  #define KEY_APOSTROPHE 39
  #define KEY_LBRACKET 91
  #define KEY_RBRACKET 93
  #define KEY_MINUS 45
  #define KEY_EQUALS 61
  #define KEY_GRAVE 96 // Tilde/backtick key

 #endif // __linux__

#endif // !KEYS_H
