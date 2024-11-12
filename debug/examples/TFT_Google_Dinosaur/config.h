#ifndef _CONFIG_H_
#define _CONFIG_H_

#define DEBUG   0



// Game Setting
#define GAME_SPEED          1.0
#define GAME_SPEEDUP_GAP    0.1      
#define GAME_SPEEDUP_SCORE  100



// UART Command / Event
/*
 * ESP32-ATmega328p UART Communication
 * data format: D_T_STRING:
 * D: Tx Side Device, E-ESP32
 *                    A-ATmega328P
 * T: Data Type, C-Command           
 *               E-Event
 * STRING: command name
 *    FORWARD
 *    BACK
 *    LEFT
 *    RIGHT
 */
#define ESP32_CMD_FORWARD   (char *)"E_C_FORWARD\r\n"
#define ESP32_CMD_BACK      (char *)"E_C_BACK\r\n"
#define ESP32_CMD_LEFT      (char *)"E_C_LEFT\r\n"
#define ESP32_CMD_RIGHT     (char *)"E_C_RIGHT\r\n"
#define ESP32_CMD_LSPIN     (char *)"E_C_LSPIN\r\n"
#define ESP32_CMD_RSPIN     (char *)"E_C_RSPIN\r\n"
#define ESP32_CMD_STOP      (char *)"E_C_STOP\r\n"

#define ATM_EVN_BTNA_PRE    (char *)"A_E_BTN_A_PRE\r\n"   // button a pressed event
#define ATM_EVN_BTNA_REL    (char *)"A_E_BTN_A_REL\r\n"   // button a release event
#define ATM_EVN_BTNB_PRE    (char *)"A_E_BTN_B_PRE\r\n"   // button b pressed event
#define ATM_EVN_BTNB_REL    (char *)"A_E_BTN_B_REL\r\n"   // button b release event


typedef void (*func_t) (void);
typedef struct  {
  char    *string;
  int     len;
  func_t  handler;
} CMD_T;

#endif
