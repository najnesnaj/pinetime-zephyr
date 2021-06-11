SECTIONS
 {
 initlevel :
 {
  __init_start = .;
  __init_PRE_KERNEL_1_start = .; KEEP(*(SORT(.z_init_PRE_KERNEL_1[0-9]_*))); KEEP(*(SORT(.z_init_PRE_KERNEL_1[1-9][0-9]_*)));
  __init_PRE_KERNEL_2_start = .; KEEP(*(SORT(.z_init_PRE_KERNEL_2[0-9]_*))); KEEP(*(SORT(.z_init_PRE_KERNEL_2[1-9][0-9]_*)));
  __init_POST_KERNEL_start = .; KEEP(*(SORT(.z_init_POST_KERNEL[0-9]_*))); KEEP(*(SORT(.z_init_POST_KERNEL[1-9][0-9]_*)));
  __init_APPLICATION_start = .; KEEP(*(SORT(.z_init_APPLICATION[0-9]_*))); KEEP(*(SORT(.z_init_APPLICATION[1-9][0-9]_*)));
  __init_SMP_start = .; KEEP(*(SORT(.z_init_SMP[0-9]_*))); KEEP(*(SORT(.z_init_SMP[1-9][0-9]_*)));
  __init_end = .;
 }
 initlevel_error :
 {
  KEEP(*(SORT(.z_init_[_A-Z0-9]*)))
 }
 ASSERT(SIZEOF(initlevel_error) == 0, "Undefined initialization levels used.")
 app_shmem_regions :
 {
  __app_shmem_regions_start = .;
  KEEP(*(SORT(.app_regions.*)));
  __app_shmem_regions_end = .;
 }
 bt_l2cap_fixed_chan_area : SUBALIGN(4) { _bt_l2cap_fixed_chan_list_start = .; KEEP(*(SORT_BY_NAME(._bt_l2cap_fixed_chan.static.*))); _bt_l2cap_fixed_chan_list_end = .; }
 bt_gatt_service_static_area : SUBALIGN(4) { _bt_gatt_service_static_list_start = .; KEEP(*(SORT_BY_NAME(._bt_gatt_service_static.static.*))); _bt_gatt_service_static_list_end = .; }
 settings_handler_static_area : SUBALIGN(4) { _settings_handler_static_list_start = .; KEEP(*(SORT_BY_NAME(._settings_handler_static.static.*))); _settings_handler_static_list_end = .; }
 k_p4wq_initparam_area : SUBALIGN(4) { _k_p4wq_initparam_list_start = .; KEEP(*(SORT_BY_NAME(._k_p4wq_initparam.static.*))); _k_p4wq_initparam_list_end = .; }
 log_strings_sections :
 {
  __log_strings_start = .;
  KEEP(*(SORT(.log_strings*)));
  __log_strings_end = .;
 }
 log_const_sections :
 {
  __log_const_start = .;
  KEEP(*(SORT(.log_const_*)));
  __log_const_end = .;
 }
 log_backends_sections :
 {
  __log_backends_start = .;
  KEEP(*("._log_backend.*"));
  __log_backends_end = .;
 }
 shell_area : SUBALIGN(4) { _shell_list_start = .; KEEP(*(SORT_BY_NAME(._shell.static.*))); _shell_list_end = .; }
 shell_root_cmds_sections :
 {
  __shell_root_cmds_start = .;
  KEEP(*(SORT(.shell_root_cmd_*)));
  __shell_root_cmds_end = .;
 }
 font_entry_sections :
 {
  __font_entry_start = .;
  KEEP(*(SORT_BY_NAME("._cfb_font.*")))
  __font_entry_end = .;
 }
 tracing_backend_area : SUBALIGN(4) { _tracing_backend_list_start = .; KEEP(*(SORT_BY_NAME(._tracing_backend.static.*))); _tracing_backend_list_end = .; }
 zephyr_dbg_info :
 {
  KEEP(*(".dbg_thread_info"));
 }
 device_handles :
 {
  __device_handles_start = .;
  KEEP(*(SORT(.__device_handles_pass1*)));
  __device_handles_end = .;
 }
 devices :
 {
  __device_start = .;
  __device_PRE_KERNEL_1_start = .; KEEP(*(SORT(.z_device_PRE_KERNEL_1[0-9]_*))); KEEP(*(SORT(.z_device_PRE_KERNEL_1[1-9][0-9]_*)));
  __device_PRE_KERNEL_2_start = .; KEEP(*(SORT(.z_device_PRE_KERNEL_2[0-9]_*))); KEEP(*(SORT(.z_device_PRE_KERNEL_2[1-9][0-9]_*)));
  __device_POST_KERNEL_start = .; KEEP(*(SORT(.z_device_POST_KERNEL[0-9]_*))); KEEP(*(SORT(.z_device_POST_KERNEL[1-9][0-9]_*)));
  __device_APPLICATION_start = .; KEEP(*(SORT(.z_device_APPLICATION[0-9]_*))); KEEP(*(SORT(.z_device_APPLICATION[1-9][0-9]_*)));
  __device_SMP_start = .; KEEP(*(SORT(.z_device_SMP[0-9]_*))); KEEP(*(SORT(.z_device_SMP[1-9][0-9]_*)));
  __device_end = .;
 }
 initshell :
 {
  __shell_module_start = .;
  KEEP(*(".shell_module_*"));
  __shell_module_end = .;
  __shell_cmd_start = .;
  KEEP(*(".shell_cmd_*"));
  __shell_cmd_end = .;
 }
 log_dynamic_sections :
 {
  __log_dynamic_start = .;
  KEEP(*(SORT(.log_dynamic_*)));
  __log_dynamic_end = .;
 }
 _static_thread_data_area : SUBALIGN(4) { __static_thread_data_list_start = .; KEEP(*(SORT_BY_NAME(.__static_thread_data.static.*))); __static_thread_data_list_end = .; }
 k_timer_area : SUBALIGN(4) { _k_timer_list_start = .; *(SORT_BY_NAME(._k_timer.static.*)); _k_timer_list_end = .; }
 k_mem_slab_area : SUBALIGN(4) { _k_mem_slab_list_start = .; *(SORT_BY_NAME(._k_mem_slab.static.*)); _k_mem_slab_list_end = .; }
 k_mem_pool_area : SUBALIGN(4) { _k_mem_pool_list_start = .; *(SORT_BY_NAME(._k_mem_pool.static.*)); _k_mem_pool_list_end = .; }
 k_heap_area : SUBALIGN(4) { _k_heap_list_start = .; *(SORT_BY_NAME(._k_heap.static.*)); _k_heap_list_end = .; }
 k_mutex_area : SUBALIGN(4) { _k_mutex_list_start = .; *(SORT_BY_NAME(._k_mutex.static.*)); _k_mutex_list_end = .; }
 k_stack_area : SUBALIGN(4) { _k_stack_list_start = .; *(SORT_BY_NAME(._k_stack.static.*)); _k_stack_list_end = .; }
 k_msgq_area : SUBALIGN(4) { _k_msgq_list_start = .; *(SORT_BY_NAME(._k_msgq.static.*)); _k_msgq_list_end = .; }
 k_mbox_area : SUBALIGN(4) { _k_mbox_list_start = .; *(SORT_BY_NAME(._k_mbox.static.*)); _k_mbox_list_end = .; }
 k_pipe_area : SUBALIGN(4) { _k_pipe_list_start = .; *(SORT_BY_NAME(._k_pipe.static.*)); _k_pipe_list_end = .; }
 k_sem_area : SUBALIGN(4) { _k_sem_list_start = .; *(SORT_BY_NAME(._k_sem.static.*)); _k_sem_list_end = .; }
 k_queue_area : SUBALIGN(4) { _k_queue_list_start = .; *(SORT_BY_NAME(._k_queue.static.*)); _k_queue_list_end = .; }
 k_condvar_area : SUBALIGN(4) { _k_condvar_list_start = .; *(SORT_BY_NAME(._k_condvar.static.*)); _k_condvar_list_end = .; }
 _net_buf_pool_area : SUBALIGN(4)
 {
  _net_buf_pool_list = .;
  KEEP(*(SORT_BY_NAME("._net_buf_pool.static.*")))
 }
native_pre_tasks :
{
 __native_tasks_start = .;
 __native_PRE_BOOT_1_tasks_start = .; KEEP(*(SORT(.native_PRE_BOOT_1[0-9]_task))); KEEP(*(SORT(.native_PRE_BOOT_1[1-9][0-9]_task))); KEEP(*(SORT(.native_PRE_BOOT_1[1-9][0-9][0-9]_task)));
 __native_PRE_BOOT_2_tasks_start = .; KEEP(*(SORT(.native_PRE_BOOT_2[0-9]_task))); KEEP(*(SORT(.native_PRE_BOOT_2[1-9][0-9]_task))); KEEP(*(SORT(.native_PRE_BOOT_2[1-9][0-9][0-9]_task)));
 __native_PRE_BOOT_3_tasks_start = .; KEEP(*(SORT(.native_PRE_BOOT_3[0-9]_task))); KEEP(*(SORT(.native_PRE_BOOT_3[1-9][0-9]_task))); KEEP(*(SORT(.native_PRE_BOOT_3[1-9][0-9][0-9]_task)));
 __native_FIRST_SLEEP_tasks_start = .; KEEP(*(SORT(.native_FIRST_SLEEP[0-9]_task))); KEEP(*(SORT(.native_FIRST_SLEEP[1-9][0-9]_task))); KEEP(*(SORT(.native_FIRST_SLEEP[1-9][0-9][0-9]_task)));
 __native_ON_EXIT_tasks_start = .; KEEP(*(SORT(.native_ON_EXIT[0-9]_task))); KEEP(*(SORT(.native_ON_EXIT[1-9][0-9]_task))); KEEP(*(SORT(.native_ON_EXIT[1-9][0-9][0-9]_task)));
 __native_tasks_end = .;
}
 __data_ram_end = .;
 } INSERT AFTER .data;
