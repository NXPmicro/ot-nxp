option(OT_APP_CLI_FREERTOS "Enable ot-cli-freertos example" OFF)
option(OT_APP_CLI_FREERTOS_LOWPOWER "Enable low power addon to ot-cli-freertos" OFF)
option(OT_APP_CLI_FREERTOS_IPERF "Enable iperf addon to ot-cli-freertos" OFF)
option(OT_APP_BR_FREERTOS "Enable border router example" OFF)
option(OT_NXP_LWIP "Enable lwIP stack" OFF)
option(OT_NXP_LWIP_IPERF "Enable iPerf port over lwIP" OFF)
option(OT_NXP_LWIP_ETH "Enable lwIP port over ethernet" OFF)
option(OT_NXP_LWIP_WIFI "Enable lwIP port over wifi" OFF)
option(OT_NXP_EXPORT_TO_BIN "Convert all executables to raw binary" OFF)
option(OT_NXP_EXPORT_TO_SREC "Convert all executables to srec" OFF)

if(OT_APP_CLI_FREERTOS_IPERF OR OT_APP_BR_FREERTOS)
    set(OT_NXP_LWIP ON CACHE BOOL "" FORCE)
    if(OT_APP_CLI_FREERTOS_IPERF)
        set(OT_NXP_LWIP_IPERF ON CACHE BOOL "" FORCE)
    endif()
endif()

message(STATUS OT_APP_CLI_FREERTOS=${OT_APP_CLI_FREERTOS})
message(STATUS OT_APP_CLI_FREERTOS_LOWPOWER=${OT_APP_CLI_FREERTOS_LOWPOWER})
message(STATUS OT_APP_CLI_FREERTOS_IPERF=${OT_APP_CLI_FREERTOS_IPERF})
message(STATUS OT_APP_BR_FREERTOS=${OT_APP_BR_FREERTOS})
message(STATUS OT_NXP_LWIP=${OT_NXP_LWIP})
message(STATUS OT_NXP_LWIP_IPERF=${OT_NXP_LWIP_IPERF})
message(STATUS OT_NXP_LWIP_ETH=${OT_NXP_LWIP_ETH})
message(STATUS OT_NXP_LWIP_WIFI=${OT_NXP_LWIP_WIFI})
message(STATUS OT_NXP_EXPORT_TO_BIN=${OT_NXP_EXPORT_TO_BIN})
message(STATUS OT_NXP_EXPORT_TO_SREC=${OT_NXP_EXPORT_TO_SREC})
