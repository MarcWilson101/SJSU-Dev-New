__attribute__((section(".symbol_table"))) const char APP_SYM_TABLE[] =
	"00018920 T abort\n"
	"00011244 T adc0_get_reading\n"
	"000111d0 T adc0_init\n"
	"00011188 T ADC_IRQHandler\n"
	"0001892e T atoi\n"
	"00011528 T CAN_IRQHandler\n"
	"00010674 T c_list_create\n"
	"000106c0 T c_list_find_elm\n"
	"000106ec T c_list_for_each_elm\n"
	"00010688 T c_list_insert_elm_end\n"
	"00014ea4 T clust2sect\n"
	"00010740 T delay_ms\n"
	"00010716 T delay_us\n"
	"0001716c T disk_initialize\n"
	"00017212 T disk_ioctl\n"
	"000171a2 T disk_read\n"
	"00017192 T disk_status\n"
	"000171da T disk_write\n"
	"0001bd18 T div\n"
	"00011420 T eint3_enable_port0\n"
	"000113a0 T EINT3_IRQHandler\n"
	"00015db0 T f_close\n"
	"000164e0 T ff_convert\n"
	"00016540 T ff_cre_syncobj\n"
	"00016554 T ff_del_syncobj\n"
	"00018aa8 T fflush\n"
	"0001657e T ff_rel_grant\n"
	"00016558 T ff_req_grant\n"
	"0001651c T ff_wtoupper\n"
	"00015f22 T f_getfree\n"
	"00017140 T flash_chip_erase\n"
	"00017078 T flash_get_page_count\n"
	"00017098 T flash_get_page_size\n"
	"00016ea0 T flash_initialize\n"
	"00016fd4 T flash_ioctl\n"
	"00017050 T flash_read_permanent_id\n"
	"00016f38 T flash_read_sectors\n"
	"000170a4 T flash_supports_metadata\n"
	"0001700c T flash_write_permanent_id\n"
	"00016f88 T flash_write_sectors\n"
	"00015dd4 T f_lseek\n"
	"00015fec T f_mkfs\n"
	"00015860 T f_mount\n"
	"000158dc T f_open\n"
	"00015a0a T f_read\n"
	"00018ddc T free\n"
	"00015d26 T f_sync\n"
	"00015b7a T f_write\n"
	"00014eba T get_fat\n"
	"000149fc T get_fattime\n"
	"00010000 T g_pfnVectors\n"
	"00010e24 T I2C2_IRQHandler\n"
	"0001a1c8 T iprintf\n"
	"0001a4d0 T iscanf\n"
	"00010732 T is_freertos_running\n"
	"00010148 T isr_default_handler\n"
	"00013660 T isr_hard_fault_handler\n"
	"00010194 T isr_reset\n"
	"000105a8 T logger_init\n"
	"0001326c T lpc_pclk\n"
	"00013238 T lpc_pconp\n"
	"000134b0 T lpc_sys_setup_system_timer\n"
	"00011570 T lpc_timer_enable\n"
	"0001752c T main\n"
	"0001935c T mallinfo\n"
	"00018dcc T malloc\n"
	"00018e10 T memchr\n"
	"00018e2c T memcmp\n"
	"00018e4a T memcpy\n"
	"00018e60 T memmove\n"
	"00018e94 T memset\n"
	"00013d88 T mesh_form_pkt\n"
	"00013d7c T mesh_get_node_address\n"
	"00014030 T mesh_get_num_routing_entries\n"
	"0001431c T mesh_get_pnd_pkt_count\n"
	"00013ed8 T mesh_init\n"
	"00013fd8 T mesh_send\n"
	"00013e80 T mesh_send_formed_pkt\n"
	"0001404c T mesh_service\n"
	"00013d64 T mesh_set_node_address\n"
	"00019064 T mktime\n"
	"0001a65c T nanf\n"
	"00014484 T nordic_clear_all_intr_flags\n"
	"00014554 T nordic_clear_packet_available_flag\n"
	"000144e4 T nordic_clear_packet_sent_flag\n"
	"00014570 T nordic_flush_rx_fifo\n"
	"000144ec T nordic_flush_tx_fifo\n"
	"00014704 T nordic_init\n"
	"00014544 T nordic_is_packet_available\n"
	"00014476 T nordic_is_tx_fifo_empty\n"
	"000144f8 T nordic_mode1_send_single_packet\n"
	"0001460a T nordic_power_down\n"
	"000145f2 T nordic_power_up\n"
	"0001448c T nordic_queue_tx_fifo\n"
	"0001455c T nordic_read_rx_fifo\n"
	"000144b0 T nordic_rx_to_Stanby1\n"
	"000146d4 T nordic_set_addr_width\n"
	"00014644 T nordic_set_air_data_rate\n"
	"00014694 T nordic_set_auto_transmit_options\n"
	"00014620 T nordic_set_channel\n"
	"000145ba T nordic_set_crc\n"
	"0001457c T nordic_set_intr_signals\n"
	"000146c0 T nordic_set_payload_for_pipe\n"
	"00014670 T nordic_set_power_level\n"
	"000146f6 T nordic_set_rx_pipe0_addr\n"
	"000146ea T nordic_set_tx_address\n"
	"000144c0 T nordic_standby1_to_rx\n"
	"00014498 T nordic_standby1_to_tx_mode1\n"
	"00016624 T power_off\n"
	"0001a1c8 T printf\n"
	"00014fe0 T put_fat\n"
	"0001a2b0 T puts\n"
	"00011d88 T pvPortMalloc\n"
	"0001263c T pvTaskIncrementMutexHeldCount\n"
	"00011de8 T pxPortInitialiseStack\n"
	"0001a6b4 T raise\n"
	"0001a310 T rand\n"
	"00016648 T rcvr_datablock\n"
	"000112b8 T RIT_IRQHandler\n"
	"00010e4c T rtc_gettime\n"
	"00010efc T rtc_init\n"
	"00010378 T RTC_IRQHandler\n"
	"00010e94 T rtc_settime\n"
	"00011dc0 T rts_not_full_trace_get\n"
	"0001a4d0 T scanf\n"
	"000167d0 T sd_initialize\n"
	"00016a98 T sd_ioctl\n"
	"0001694c T sd_read\n"
	"0001693c T sd_status\n"
	"000167ac T sd_update_card_status\n"
	"000169e4 T sd_write\n"
	"00016720 T send_cmd\n"
	"0001a500 T setvbuf\n"
	"0001a6ec T siprintf\n"
	"0001a734 T siscanf\n"
	"000110a8 T spi1_lock\n"
	"000110d8 T spi1_unlock\n"
	"0001a6ec T sprintf\n"
	"0001a2c0 T srand\n"
	"0001a734 T sscanf\n"
	"00010fcc T ssp1_dma_init\n"
	"00010fe8 T ssp1_dma_transfer_block\n"
	"0001a812 T strcmp\n"
	"0001a826 T strcpy\n"
	"0001a836 T strlen\n"
	"0001a846 T strncmp\n"
	"0001a86a T strncpy\n"
	"0001b60c T strtol\n"
	"0001e960 T strtoul\n"
	"00012e30 T syscalls_init\n"
	"000136b8 T sys_get_boot_type\n"
	"00013408 T sys_get_cpu_clock\n"
	"00013100 T sys_get_mem_info\n"
	"00013530 T sys_get_mem_info_str\n"
	"00013504 T sys_get_uptime_us\n"
	"00012dfc T sys_set_inchar_func\n"
	"00012df0 T sys_set_outchar_func\n"
	"0001b638 T time\n"
	"00013568 T TIMER1_IRQHandler\n"
	"00010234 T tlm_component_add\n"
	"00010210 T tlm_component_get_by_name\n"
	"000102be T u0_dbg_printf\n"
	"000102a0 T u0_dbg_put\n"
	"0001394c T uart0_getchar\n"
	"000138ec T uart0_init\n"
	"00011318 T UART0_IRQHandler\n"
	"00013964 T uart0_putchar\n"
	"0001397c T uart0_puts\n"
	"00011140 T UART2_IRQHandler\n"
	"00011620 T UART3_IRQHandler\n"
	"000126ee T uxListRemove\n"
	"00012cb0 T uxQueueMessagesWaiting\n"
	"00012cc2 T uxQueueMessagesWaitingFromISR\n"
	"00012d00 T vApplicationMallocFailedHook\n"
	"00012cc8 T vApplicationStackOverflowHook\n"
	"0001268c T vListInitialise\n"
	"000126a2 T vListInitialiseItem\n"
	"000126c0 T vListInsert\n"
	"000126a8 T vListInsertEnd\n"
	"00011e34 T vPortEnterCritical\n"
	"00011e54 T vPortExitCritical\n"
	"00011da6 T vPortFree\n"
	"00011e10 T vPortSVCHandler\n"
	"00012654 T vRunTimeStatIsrEntry\n"
	"0001267c T vRunTimeStatIsrExit\n"
	"0001bb1c T vsniprintf\n"
	"0001bb1c T vsnprintf\n"
	"00012334 T vTaskDelay\n"
	"00012510 T vTaskMissedYield\n"
	"0001241c T vTaskPlaceOnEventList\n"
	"0001253c T vTaskPriorityInherit\n"
	"000124ac T vTaskSetTimeOutState\n"
	"00012134 T vTaskSuspendAll\n"
	"00012364 T vTaskSwitchContext\n"
	"000165f4 T wait_ready\n"
	"00014964 T wireless_init\n"
	"000149b0 T wireless_service\n"
	"000166d4 T xmit_datablock\n"
	"00011e70 T xPortPendSVHandler\n"
	"00011eb4 T xPortSysTickHandler\n"
	"00012a08 T xQueueCreateMutex\n"
	"000128d0 T xQueueGenericCreate\n"
	"00012b14 T xQueueGenericReceive\n"
	"00012864 T xQueueGenericReset\n"
	"00012904 T xQueueGenericSend\n"
	"00012a2c T xQueueGenericSendFromISR\n"
	"00012aac T xQueueGiveFromISR\n"
	"00012c48 T xQueueReceiveFromISR\n"
	"000124c4 T xTaskCheckForTimeOut\n"
	"00011f90 T xTaskCreate\n"
	"0001251c T xTaskGetSchedulerState\n"
	"00012144 T xTaskGetTickCountFromISR\n"
	"00012150 T xTaskIncrementTick\n"
	"000125cc T xTaskPriorityDisinherit\n"
	"0001243c T xTaskRemoveFromEventList\n"
	"0001225c T xTaskResumeAll\n"
	"000136c4 T low_level_init()\n"
	"00011810 T high_level_init()\n"
	"00013354 T sys_clock_configure()\n"
	"00010180 T bss_init(unsigned int, unsigned int)\n"
	"0001016a T data_init(unsigned int, unsigned int, unsigned int)\n"
	"00017350 T LED_Display::setLeftDigit(char)\n"
	"00017368 T LED_Display::setRightDigit(char)\n"
	"00017380 T LED_Display::init()\n"
	"000173b8 T LED_Display::setNumber(char)\n"
	"0001744c T Light_Sensor::getRawValue()\n"
	"00017448 T Light_Sensor::init()\n"
	"0001727a T Acceleration_Sensor::init()\n"
	"000173f2 T LED::init()\n"
	"000173f8 T LED::setAll(unsigned char)\n"
	"00010da4 T I2C2::init(unsigned int)\n"
	"00010e10 T I2C2::I2C2()\n"
	"00010e10 T I2C2::I2C2()\n"
	"000112fc T Uart0::Uart0()\n"
	"000112fc T Uart0::Uart0()\n"
	"00011124 T Uart2::Uart2()\n"
	"00011124 T Uart2::Uart2()\n"
	"00011604 T Uart3::Uart3()\n"
	"00011604 T Uart3::Uart3()\n"
	"00010d6c T CharDev::CharDev()\n"
	"00010d6c T CharDev::CharDev()\n"
	"00010d8c T CharDev::~CharDev()\n"
	"00010d8c T CharDev::~CharDev()\n"
	"000174e8 T Storage::read(char const*, void*, unsigned int, unsigned int)\n"
	"00010874 T UartDev::handleInterrupt()\n"
	"000107e8 T UartDev::flush()\n"
	"00010808 T UartDev::getChar(char*, unsigned int)\n"
	"00010762 T UartDev::putChar(char, unsigned int)\n"
	"00010934 T UartDev::UartDev(unsigned int*)\n"
	"00010934 T UartDev::UartDev(unsigned int*)\n"
	"00010a98 T I2C_Base::readRegisters(unsigned char, unsigned char, unsigned char*, unsigned long)\n"
	"00010ade T I2C_Base::readRegisters(unsigned char, unsigned char*, unsigned long)\n"
	"00010ab2 T I2C_Base::writeRegisters(unsigned char, unsigned char*, unsigned long)\n"
	"00010d30 T I2C_Base::handleInterrupt()\n"
	"00010af6 T I2C_Base::checkDeviceResponse(unsigned char)\n"
	"00010a64 T I2C_Base::writeRegisterThenRead(unsigned char, unsigned char*, unsigned long, unsigned char*, unsigned long)\n"
	"00010b68 T I2C_Base::init(unsigned long, unsigned long)\n"
	"00010a70 T I2C_Base::readReg(unsigned char, unsigned char)\n"
	"0001095c T I2C_Base::transfer(unsigned char, unsigned char*, unsigned long, unsigned char*, unsigned long)\n"
	"00010ac6 T I2C_Base::writeReg(unsigned char, unsigned char, unsigned char)\n"
	"00010b0c T I2C_Base::I2C_Base(LPC_I2C_TypeDef*)\n"
	"00010b0c T I2C_Base::I2C_Base(LPC_I2C_TypeDef*)\n"
	"00017492 T I2C_Temp::getCelsius()\n"
	"000174c4 T I2C_Temp::getFarenheit()\n"
	"00017470 T I2C_Temp::init()\n"
	"00017458 T Switches::getSwitchValues()\n"
	"00017452 T Switches::init()\n"
	"0001729c T IR_Sensor::storeIrCode(unsigned long)\n"
	"000172b8 T IR_Sensor::decodeIrCode()\n"
	"0001731c T IR_Sensor::init()\n"
	"00017c58 T std::type_info::__is_pointer_p() const\n"
	"00017c58 T std::type_info::__is_function_p() const\n"
	"00017c5c T std::type_info::operator==(std::type_info const&) const\n"
	"00017c56 T std::type_info::~type_info()\n"
	"00017c56 T std::type_info::~type_info()\n"
	"00017c90 T std::get_terminate()\n"
	"00017ca0 T std::terminate()\n"
;
