/*******************************************************************************
  Sample Application

  File Name:
    app_commands.c

  Summary:
    commands for the tcp client demo app.

  Description:
    
 *******************************************************************************/

#include "app_commands.h"
#include "app.h"
#include "tcpip/tcpip.h"

#if defined(SMSC_9303_CMD_PROCESSOR) && (SMSC_9303_CMD_PROCESSOR != 0)
int32_t DRV_ETHPHY_SMSC9303_InitCmdProcessor();
#endif

#if defined(TCPIP_STACK_COMMAND_ENABLE)



static void _APP_Commands_OpenURL(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);
static void _APP_Commands_ChangeIP(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv);

static const SYS_CMD_DESCRIPTOR    appCmdTbl[]=
{
    {"openurl",     _APP_Commands_OpenURL,              ": Connect to a url and do a GET"},
    {"ChangeIP",    _APP_Commands_ChangeIP,             ": Change the IP Address"},
};

bool APP_Commands_Init()
{
    if (!SYS_CMD_ADDGRP(appCmdTbl, sizeof(appCmdTbl)/sizeof(*appCmdTbl), "app", ": app commands"))
    {
        SYS_ERROR(SYS_ERROR_ERROR, "Failed to create TCPIP Commands\r\n");
        return false;
    }
    memset(APP_URL_Buffer, 0, MAX_URL_SIZE);
#if defined(SMSC_9303_CMD_PROCESSOR) && (SMSC_9303_CMD_PROCESSOR != 0)
    DRV_ETHPHY_SMSC9303_InitCmdProcessor();
#endif
    return true;
}

char APP_URL_Buffer[MAX_URL_SIZE];

void _APP_Commands_OpenURL(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    const void* cmdIoParam = pCmdIO->cmdIoParam;


    if (argc != 2)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Usage: openurl <url>\r\n");
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Ex: openurl http://www.google.com/\r\n");
        return;
    }

    strncpy(APP_URL_Buffer, argv[1], MAX_URL_SIZE);
}

void _APP_Commands_ChangeIP(SYS_CMD_DEVICE_NODE* pCmdIO, int argc, char** argv)
{
    TCPIP_NET_HANDLE    netH;
    IPV4_ADDR ipAddress;
    ipAddress.Val = 0xB677A8C0;
    netH = TCPIP_STACK_IndexToNet(0);
    TCPIP_STACK_NetAddressSet(netH, &ipAddress, NULL, 0);
}

#endif
