__attribute__((section(".symbol_table"))) const char APP_SYM_TABLE[] =
	"00018ae8 T abort\n"
	"00011170 T adc0_get_reading\n"
	"000110fc T adc0_init\n"
	"000110b4 T ADC_IRQHandler\n"
	"00018af6 T atoi\n"
	"00011454 T CAN_IRQHandler\n"
	"00010674 T c_list_create\n"
	"000106c0 T c_list_find_elm\n"
	"000106ec T c_list_for_each_elm\n"
	"00010688 T c_list_insert_elm_end\n"
	"00014dd4 T clust2sect\n"
	"00010740 T delay_ms\n"
	"00010716 T delay_us\n"
	"0001709c T disk_initialize\n"
	"00017142 T disk_ioctl\n"
	"000170d2 T disk_read\n"
	"000170c2 T disk_status\n"
	"0001710a T disk_write\n"
	"0001bee0 T div\n"
	"0001134c T eint3_enable_port0\n"
	"000112cc T EINT3_IRQHandler\n"
	"00015ce0 T f_close\n"
	"00016410 T ff_convert\n"
	"00016470 T ff_cre_syncobj\n"
	"00016484 T ff_del_syncobj\n"
	"00018c70 T fflush\n"
	"000164ae T ff_rel_grant\n"
	"00016488 T ff_req_grant\n"
	"0001644c T ff_wtoupper\n"
	"00015e52 T f_getfree\n"
	"00017070 T flash_chip_erase\n"
	"00016fa8 T flash_get_page_count\n"
	"00016fc8 T flash_get_page_size\n"
	"00016dd0 T flash_initialize\n"
	"00016f04 T flash_ioctl\n"
	"00016f80 T flash_read_permanent_id\n"
	"00016e68 T flash_read_sectors\n"
	"00016fd4 T flash_supports_metadata\n"
	"00016f3c T flash_write_permanent_id\n"
	"00016eb8 T flash_write_sectors\n"
	"00015d04 T f_lseek\n"
	"00015f1c T f_mkfs\n"
	"00015790 T f_mount\n"
	"0001580c T f_open\n"
	"0001593a T f_read\n"
	"00018fa4 T free\n"
	"00015c56 T f_sync\n"
	"00015aaa T f_write\n"
	"00014dea T get_fat\n"
	"0001492c T get_fattime\n"
	"00010000 T g_pfnVectors\n"
	"00010d50 T I2C2_IRQHandler\n"
	"0001a390 T iprintf\n"
	"0001a698 T iscanf\n"
	"00010732 T is_freertos_running\n"
	"00010148 T isr_default_handler\n"
	"00013590 T isr_hard_fault_handler\n"
	"00010194 T isr_reset\n"
	"000105a8 T logger_init\n"
	"0001319c T lpc_pclk\n"
	"00013168 T lpc_pconp\n"
	"000133e0 T lpc_sys_setup_system_timer\n"
	"0001149c T lpc_timer_enable\n"
	"00017744 T main\n"
	"00019524 T mallinfo\n"
	"00018f94 T malloc\n"
	"00018fd8 T memchr\n"
	"00018ff4 T memcmp\n"
	"00019012 T memcpy\n"
	"00019028 T memmove\n"
	"0001905c T memset\n"
	"00013cb8 T mesh_form_pkt\n"
	"00013cac T mesh_get_node_address\n"
	"00013f60 T mesh_get_num_routing_entries\n"
	"0001424c T mesh_get_pnd_pkt_count\n"
	"00013e08 T mesh_init\n"
	"00013f08 T mesh_send\n"
	"00013db0 T mesh_send_formed_pkt\n"
	"00013f7c T mesh_service\n"
	"00013c94 T mesh_set_node_address\n"
	"0001922c T mktime\n"
	"0001a824 T nanf\n"
	"000143b4 T nordic_clear_all_intr_flags\n"
	"00014484 T nordic_clear_packet_available_flag\n"
	"00014414 T nordic_clear_packet_sent_flag\n"
	"000144a0 T nordic_flush_rx_fifo\n"
	"0001441c T nordic_flush_tx_fifo\n"
	"00014634 T nordic_init\n"
	"00014474 T nordic_is_packet_available\n"
	"000143a6 T nordic_is_tx_fifo_empty\n"
	"00014428 T nordic_mode1_send_single_packet\n"
	"0001453a T nordic_power_down\n"
	"00014522 T nordic_power_up\n"
	"000143bc T nordic_queue_tx_fifo\n"
	"0001448c T nordic_read_rx_fifo\n"
	"000143e0 T nordic_rx_to_Stanby1\n"
	"00014604 T nordic_set_addr_width\n"
	"00014574 T nordic_set_air_data_rate\n"
	"000145c4 T nordic_set_auto_transmit_options\n"
	"00014550 T nordic_set_channel\n"
	"000144ea T nordic_set_crc\n"
	"000144ac T nordic_set_intr_signals\n"
	"000145f0 T nordic_set_payload_for_pipe\n"
	"000145a0 T nordic_set_power_level\n"
	"00014626 T nordic_set_rx_pipe0_addr\n"
	"0001461a T nordic_set_tx_address\n"
	"000143f0 T nordic_standby1_to_rx\n"
	"000143c8 T nordic_standby1_to_tx_mode1\n"
	"00016554 T power_off\n"
	"0001a390 T printf\n"
	"00014f10 T put_fat\n"
	"0001a478 T puts\n"
	"00011cb4 T pvPortMalloc\n"
	"0001256c T pvTaskIncrementMutexHeldCount\n"
	"00011d14 T pxPortInitialiseStack\n"
	"0001a87c T raise\n"
	"0001a4d8 T rand\n"
	"00016578 T rcvr_datablock\n"
	"000111e4 T RIT_IRQHandler\n"
	"00010d78 T rtc_gettime\n"
	"00010e28 T rtc_init\n"
	"00010378 T RTC_IRQHandler\n"
	"00010dc0 T rtc_settime\n"
	"00011cec T rts_not_full_trace_get\n"
	"0001a698 T scanf\n"
	"00016700 T sd_initialize\n"
	"000169c8 T sd_ioctl\n"
	"0001687c T sd_read\n"
	"0001686c T sd_status\n"
	"000166dc T sd_update_card_status\n"
	"00016914 T sd_write\n"
	"00016650 T send_cmd\n"
	"0001a6c8 T setvbuf\n"
	"0001a8b4 T siprintf\n"
	"0001a8fc T siscanf\n"
	"00010fd4 T spi1_lock\n"
	"00011004 T spi1_unlock\n"
	"0001a8b4 T sprintf\n"
	"0001a488 T srand\n"
	"0001a8fc T sscanf\n"
	"00010ef8 T ssp1_dma_init\n"
	"00010f14 T ssp1_dma_transfer_block\n"
	"0001a9da T strcmp\n"
	"0001a9ee T strcpy\n"
	"0001a9fe T strlen\n"
	"0001aa0e T strncmp\n"
	"0001aa32 T strncpy\n"
	"0001b7d4 T strtol\n"
	"0001eb28 T strtoul\n"
	"00012d60 T syscalls_init\n"
	"000135e8 T sys_get_boot_type\n"
	"00013338 T sys_get_cpu_clock\n"
	"00013030 T sys_get_mem_info\n"
	"00013460 T sys_get_mem_info_str\n"
	"00013434 T sys_get_uptime_us\n"
	"00012d2c T sys_set_inchar_func\n"
	"00012d20 T sys_set_outchar_func\n"
	"0001b800 T time\n"
	"00013498 T TIMER1_IRQHandler\n"
	"00010234 T tlm_component_add\n"
	"00010210 T tlm_component_get_by_name\n"
	"000102be T u0_dbg_printf\n"
	"000102a0 T u0_dbg_put\n"
	"0001387c T uart0_getchar\n"
	"0001381c T uart0_init\n"
	"00011244 T UART0_IRQHandler\n"
	"00013894 T uart0_putchar\n"
	"000138ac T uart0_puts\n"
	"0001106c T UART2_IRQHandler\n"
	"0001154c T UART3_IRQHandler\n"
	"0001261e T uxListRemove\n"
	"00012be0 T uxQueueMessagesWaiting\n"
	"00012bf2 T uxQueueMessagesWaitingFromISR\n"
	"00012c30 T vApplicationMallocFailedHook\n"
	"00012bf8 T vApplicationStackOverflowHook\n"
	"000125bc T vListInitialise\n"
	"000125d2 T vListInitialiseItem\n"
	"000125f0 T vListInsert\n"
	"000125d8 T vListInsertEnd\n"
	"00011d64 T vPortEnterCritical\n"
	"00011d84 T vPortExitCritical\n"
	"00011cd2 T vPortFree\n"
	"00011d40 T vPortSVCHandler\n"
	"00012584 T vRunTimeStatIsrEntry\n"
	"000125ac T vRunTimeStatIsrExit\n"
	"0001bce4 T vsniprintf\n"
	"0001bce4 T vsnprintf\n"
	"00012264 T vTaskDelay\n"
	"00012440 T vTaskMissedYield\n"
	"0001234c T vTaskPlaceOnEventList\n"
	"0001246c T vTaskPriorityInherit\n"
	"000123dc T vTaskSetTimeOutState\n"
	"00012064 T vTaskSuspendAll\n"
	"00012294 T vTaskSwitchContext\n"
	"00016524 T wait_ready\n"
	"00014894 T wireless_init\n"
	"000148e0 T wireless_service\n"
	"00016604 T xmit_datablock\n"
	"00011da0 T xPortPendSVHandler\n"
	"00011de4 T xPortSysTickHandler\n"
	"00012938 T xQueueCreateMutex\n"
	"00012800 T xQueueGenericCreate\n"
	"00012a44 T xQueueGenericReceive\n"
	"00012794 T xQueueGenericReset\n"
	"00012834 T xQueueGenericSend\n"
	"0001295c T xQueueGenericSendFromISR\n"
	"000129dc T xQueueGiveFromISR\n"
	"00012b78 T xQueueReceiveFromISR\n"
	"000123f4 T xTaskCheckForTimeOut\n"
	"00011ec0 T xTaskCreate\n"
	"0001244c T xTaskGetSchedulerState\n"
	"00012074 T xTaskGetTickCountFromISR\n"
	"00012080 T xTaskIncrementTick\n"
	"000124fc T xTaskPriorityDisinherit\n"
	"0001236c T xTaskRemoveFromEventList\n"
	"0001218c T xTaskResumeAll\n"
	"000135f4 T low_level_init()\n"
	"0001173c T high_level_init()\n"
	"00013284 T sys_clock_configure()\n"
	"00010180 T bss_init(unsigned int, unsigned int)\n"
	"0001016a T data_init(unsigned int, unsigned int, unsigned int)\n"
	"00017280 T LED_Display::setLeftDigit(char)\n"
	"00017298 T LED_Display::setRightDigit(char)\n"
	"000172b0 T LED_Display::init()\n"
	"000172e8 T LED_Display::setNumber(char)\n"
	"0001737c T Light_Sensor::getRawValue()\n"
	"00017378 T Light_Sensor::init()\n"
	"000171aa T Acceleration_Sensor::init()\n"
	"00017322 T LED::init()\n"
	"00017328 T LED::setAll(unsigned char)\n"
	"00010ccc T I2C2::init(unsigned int)\n"
	"00010d3c T I2C2::I2C2()\n"
	"00010d3c T I2C2::I2C2()\n"
	"00011228 T Uart0::Uart0()\n"
	"00011228 T Uart0::Uart0()\n"
	"00011050 T Uart2::Uart2()\n"
	"00011050 T Uart2::Uart2()\n"
	"00011530 T Uart3::Uart3()\n"
	"00011530 T Uart3::Uart3()\n"
	"00010c94 T CharDev::CharDev()\n"
	"00010c94 T CharDev::CharDev()\n"
	"00010cb4 T CharDev::~CharDev()\n"
	"00010cb4 T CharDev::~CharDev()\n"
	"00017418 T Storage::read(char const*, void*, unsigned int, unsigned int)\n"
	"00010874 T UartDev::handleInterrupt()\n"
	"000107e8 T UartDev::flush()\n"
	"00010808 T UartDev::getChar(char*, unsigned int)\n"
	"00010762 T UartDev::putChar(char, unsigned int)\n"
	"00010934 T UartDev::UartDev(unsigned int*)\n"
	"00010934 T UartDev::UartDev(unsigned int*)\n"
	"00010c1a T I2C_Base::setAckFlag()\n"
	"00010bfc T I2C_Base::clearSIFlag()\n"
	"00010c24 T I2C_Base::setNackFlag()\n"
	"00010c06 T I2C_Base::setSTARTFlag()\n"
	"00010a98 T I2C_Base::readRegisters(unsigned char, unsigned char, unsigned char*, unsigned long)\n"
	"00010ade T I2C_Base::readRegisters(unsigned char, unsigned char*, unsigned long)\n"
	"00010c10 T I2C_Base::clearSTARTFlag()\n"
	"00010ab2 T I2C_Base::writeRegisters(unsigned char, unsigned char*, unsigned long)\n"
	"00010c58 T I2C_Base::handleInterrupt()\n"
	"0001745c T I2C_Base::i2cStateMachine()\n"
	"00010af6 T I2C_Base::checkDeviceResponse(unsigned char)\n"
	"00010a64 T I2C_Base::writeRegisterThenRead(unsigned char, unsigned char*, unsigned long, unsigned char*, unsigned long)\n"
	"00010b68 T I2C_Base::init(unsigned long, unsigned long)\n"
	"00010a70 T I2C_Base::readReg(unsigned char, unsigned char)\n"
	"00010c2e T I2C_Base::setStop()\n"
	"0001095c T I2C_Base::transfer(unsigned char, unsigned char*, unsigned long, unsigned char*, unsigned long)\n"
	"00010ac6 T I2C_Base::writeReg(unsigned char, unsigned char, unsigned char)\n"
	"00010b0c T I2C_Base::I2C_Base(LPC_I2C_TypeDef*)\n"
	"00010b0c T I2C_Base::I2C_Base(LPC_I2C_TypeDef*)\n"
	"000173c2 T I2C_Temp::getCelsius()\n"
	"000173f4 T I2C_Temp::getFarenheit()\n"
	"000173a0 T I2C_Temp::init()\n"
	"00017388 T Switches::getSwitchValues()\n"
	"00017382 T Switches::init()\n"
	"000171cc T IR_Sensor::storeIrCode(unsigned long)\n"
	"000171e8 T IR_Sensor::decodeIrCode()\n"
	"0001724c T IR_Sensor::init()\n"
	"00017e20 T std::type_info::__is_pointer_p() const\n"
	"00017e20 T std::type_info::__is_function_p() const\n"
	"00017e24 T std::type_info::operator==(std::type_info const&) const\n"
	"00017e1e T std::type_info::~type_info()\n"
	"00017e1e T std::type_info::~type_info()\n"
	"00017e58 T std::get_terminate()\n"
	"00017e68 T std::terminate()\n"
;
