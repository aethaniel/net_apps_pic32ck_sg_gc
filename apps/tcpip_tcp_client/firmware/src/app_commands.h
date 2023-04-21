/*******************************************************************************
  Application Header

  File Name:
    app_commands.h

  Summary:
 code for the console commands for the simple tcp client demo

  Description:
    code for the console commands for the simple tcp client demo
 *******************************************************************************/

#ifndef APP_COMMANDS_H
#define	APP_COMMANDS_H
#include <stdbool.h>
#ifdef	__cplusplus
extern "C" {
#endif

#define MAX_URL_SIZE 255
bool APP_Commands_Init(void);
extern char APP_URL_Buffer[MAX_URL_SIZE];


#ifdef	__cplusplus
}
#endif

#endif	/* APP_COMMANDS_H */

