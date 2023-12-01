``c:\Users\frankw\.platformio\packages\tool-openocd\bin\openocd -f c:/Users/frankw/.platformio/packages/tool-openocd/scripts/board/ti_ek-tm4c123gxl.cfg -c help``

```
adapter
      adapter command group (command valid any time)
  adapter assert |deassert [srst|trst [assert|deassert srst|trst]]
        Controls SRST and TRST lines.
  adapter deassert |assert [srst|trst [deassert|assert srst|trst]]
        Controls SRST and TRST lines.
  adapter driver driver_name
        Select a debug adapter driver (configuration command)
  adapter list
        List all built-in debug adapter drivers (command valid any time)
  adapter name
        Returns the name of the currently selected adapter (driver)
        (command valid any time)
  adapter speed [khz]
        With an argument, change to the specified maximum jtag speed.  For
        JTAG, 0 KHz signifies adaptive clocking. With or without argument,
        display current setting. (command valid any time)
  adapter srst
        srst adapter command group (command valid any time)
    adapter srst delay [milliseconds]
          delay after deasserting SRST in ms (command valid any time)
    adapter srst pulse_width [milliseconds]
          SRST assertion pulse width in ms (command valid any time)
  adapter transports transport ... 
        Declare transports the adapter supports. (configuration command)
  adapter usb
        usb adapter command group (command valid any time)
    adapter usb location [<bus>-port[.port]...]
          display or set the USB bus location of the USB device
          (configuration command)
add_help_text command_name helptext_string
      Add new command help text; Command can be multiple tokens. (command
      valid any time)
add_script_search_dir <directory>
      dir to search for config files and scripts (command valid any time)
add_usage_text command_name usage_string
      Add new command usage text; command can be multiple tokens. (command
      valid any time)
arm
      ARM command group (command valid any time)
  arm core_state ['arm'|'thumb']
        display/change ARM core state
  arm disassemble address [count ['thumb']]
        disassemble instructions
  arm mcr cpnum op1 CRn CRm op2 value
        write coprocessor register
  arm mrc cpnum op1 CRn CRm op2
        read coprocessor register
  arm reg
        display ARM core registers
  arm semihosting ['enable'|'disable']
        activate support for semihosting operations
  arm semihosting_cmdline arguments
        command line arguments to be passed to program
  arm semihosting_fileio ['enable'|'disable']
        activate support for semihosting fileio operations
  arm semihosting_resexit ['enable'|'disable']
        activate support for semihosting resumable exit
bindto [name]
      Specify address by name on which to listen for incoming TCP/IP
      connections (configuration command)
capture command
      Capture progress output and return as tcl return value. If the
      progress output was empty, return tcl return value. (command valid
      any time)
command
      core command group (introspection) (command valid any time)
  command mode [command_name ...]
        Returns the command modes allowed by a command: 'any', 'config', or
        'exec'. If no command is specified, returns the current command
        mode. Returns 'unknown' if an unknown command is given. Command can
        be multiple tokens. (command valid any time)
cti
      CTI commands (configuration command)
  cti create name '-chain-position' name [options ...]
        Creates a new CTI object (command valid any time)
  cti names
        Lists all registered CTI objects by name (command valid any time)
dap
      DAP commands (configuration command)
  dap create name '-chain-position' name
        Creates a new DAP instance (command valid any time)
  dap info [ap_num]
        display ROM table for MEM-AP of current target (default currently
        selected AP)
  dap init
        Initialize all registered DAP instances (command valid any time)
  dap names
        Lists all registered DAP instances by name (command valid any time)
debug_level number
      Sets the verbosity level of debugging output. 0 shows errors only; 1
      adds warnings; 2 (default) adds other info; 3 adds debugging; 4 adds
      extra verbose debugging. (command valid any time)
echo [-n] string
      Logs a message at "user" priority. Output message to stdout. Option
      "-n" suppresses trailing newline (command valid any time)
exit
      exit telnet session
find <file>
      print full path to file according to OpenOCD search rules (command
      valid any time)
flash
      NOR flash command group (command valid any time)
  flash bank bank_id driver_name base_address size_bytes chip_width_bytes
            bus_width_bytes target [driver_options ...]
        Define a new bank with the given name, using the specified NOR
        flash driver. (configuration command)
  flash banks
        Display table with information about flash banks. (command valid
        any time)
  flash init
        Initialize flash devices. (configuration command)
  flash list
        Returns a list of details about the flash banks. (command valid any
        time)
gdb_breakpoint_override ('hard'|'soft'|'disable')
      Display or specify type of breakpoint to be used by gdb 'break'
      commands. (command valid any time)
gdb_flash_program ('enable'|'disable')
      enable or disable flash program (configuration command)
gdb_memory_map ('enable'|'disable')
      enable or disable memory map (configuration command)
gdb_port [port_num]
      Normally gdb listens to a TCP/IP port. Each subsequent GDB server
      listens for the next port number after the base port number
      specified. No arguments reports GDB port. "pipe" means listen to
      stdin output to stdout, an integer is base port number, "disabled"
      disables port. Any other string is are interpreted as named pipe to
      listen to. Output pipe is the same name as input pipe, but with 'o'
      appended. (configuration command)
gdb_report_data_abort ('enable'|'disable')
      enable or disable reporting data aborts (configuration command)
gdb_report_register_access_error ('enable'|'disable')
      enable or disable reporting register access errors (configuration
      command)
gdb_save_tdesc
      Save the target description file
gdb_sync
      next stepi will return immediately allowing GDB to fetch register
      state without affecting target state (command valid any time)
gdb_target_description ('enable'|'disable')
      enable or disable target description (configuration command)
help [command_name]
      Show full command help; command can be multiple tokens. (command
      valid any time)
hla
      perform hl adapter actions (command valid any time)
  hla newtap basename tap_type '-irlen' count ['-expected_id' number]
        Create a new TAP instance named basename.tap_type, and appends it
        to the scan chain. (configuration command)
hla_command hla_command <command>
      execute a custom adapter-specific command
hla_device_desc description_string
      set the a device description of the adapter (configuration command)
hla_layout layout_name
      set the layout of the adapter (configuration command)
hla_serial serial_string
      set the serial number of the adapter (configuration command)
hla_vid_pid (vid pid)*
      the vendor and product ID of the adapter (configuration command)
init
      Initializes configured targets and servers.  Changes command mode
      from CONFIG to EXEC.  Unless 'noinit' is called, this command is
      called automatically at the end of startup. (command valid any time)
itm
      itm command group (command valid any time)
  itm port <port> (0|1|on|off)
        Enable or disable ITM stimulus port (command valid any time)
  itm ports (0|1|on|off)
        Enable or disable all ITM stimulus ports (command valid any time)
jsp_port [port_num]
      Specify port on which to listen for incoming JSP telnet connections.
      (command valid any time)
jtag
       (command valid any time)
  jtag arp_init
         (command valid any time)
  jtag arp_init-reset
         (command valid any time)
  jtag cget
  jtag configure
  jtag init
         (command valid any time)
  jtag names
         (command valid any time)
  jtag tapdisable
  jtag tapenable
  jtag tapisenabled
jtag_ntrst_delay
       (command valid any time)
log_output [file_name | "default"]
      redirect logging to a file (default: stderr) (command valid any time)
measure_clk
      Runs a test to measure the JTAG clk. Useful with RCLK / RTCK.
      (command valid any time)
mmw address setbits clearbits
      Modify word in memory. new_val = (old_val & ~clearbits) | setbits;
      (command valid any time)
mrb address
      Returns value of byte in memory. (command valid any time)
mrh address
      Returns value of halfword in memory. (command valid any time)
mrw address
      Returns value of word in memory. (command valid any time)
ms
      Returns ever increasing milliseconds. Used to calculuate differences
      in time. (command valid any time)
nand
      NAND flash command group (command valid any time)
  nand device bank_id driver target [driver_options ...]
        defines a new NAND bank (configuration command)
  nand drivers
        lists available NAND drivers (command valid any time)
  nand init
        initialize NAND devices (configuration command)
noinit
      Prevent 'init' from being called at startup. (configuration command)
ocd_find file
      find full path to file (command valid any time)
pld
      programmable logic device commands (command valid any time)
  pld device driver_name [driver_args ... ]
        configure a PLD device (configuration command)
  pld init
        initialize PLD devices (configuration command)
poll_period
      set the servers polling period (command valid any time)
power_restore
      Overridable procedure run when power restore is detected. Runs 'reset
      init' by default. (command valid any time)
program <filename> [address] [pre-verify] [verify] [reset] [exit]
      write an image to flash, address is only required for binary images.
      verify, reset, exit are optional (command valid any time)
reset_config [none|trst_only|srst_only|trst_and_srst]
          [srst_pulls_trst|trst_pulls_srst|combined|separate]
          [srst_gates_jtag|srst_nogate] [trst_push_pull|trst_open_drain]
          [srst_push_pull|srst_open_drain]
          [connect_deassert_srst|connect_assert_srst]
      configure adapter reset behavior (command valid any time)
script <file>
      filename of OpenOCD script (tcl) to run (command valid any time)
shutdown
      shut the server down (command valid any time)
sleep milliseconds ['busy']
      Sleep for specified number of milliseconds.  "busy" will busy wait
      instead (avoid this). (command valid any time)
srst_deasserted
      Overridable procedure run when srst deassert is detected. Runs 'reset
      init' by default. (command valid any time)
stellaris
      Stellaris flash command group
  stellaris mass_erase <bank>
        erase entire device
  stellaris recover
        recover (and erase) locked device
target
      configure target (configuration command)
  target create name type '-chain-position' name [options ...]
        Creates and selects a new target (configuration command)
  target current
        Returns the currently selected target (command valid any time)
  target init
        initialize targets (configuration command)
  target names
        Returns the names of all targets as a list of strings (command
        valid any time)
  target smp targetname1 targetname2 ...
        gather several target in a smp list (command valid any time)
  target types
        Returns the available target types as a list of strings (command
        valid any time)
targets [target]
      change current default target (one parameter) or prints table of all
      targets (no parameters) (command valid any time)
tcl_notifications [on|off]
      Target Notification output
tcl_port [port_num]
      Specify port on which to listen for incoming Tcl syntax.  Read help
      on 'gdb_port'. (configuration command)
tcl_trace [on|off]
      Target trace output
telnet_port [port_num]
      Specify port on which to listen for incoming telnet connections.
      Read help on 'gdb_port'. (configuration command)
tm4c123gh6pm.cpu
      target command group (command valid any time)
  tm4c123gh6pm.cpu arm
        ARM command group (command valid any time)
    tm4c123gh6pm.cpu arm core_state ['arm'|'thumb']
          display/change ARM core state
    tm4c123gh6pm.cpu arm disassemble address [count ['thumb']]
          disassemble instructions 
    tm4c123gh6pm.cpu arm mcr cpnum op1 CRn CRm op2 value
          write coprocessor register
    tm4c123gh6pm.cpu arm mrc cpnum op1 CRn CRm op2
          read coprocessor register
    tm4c123gh6pm.cpu arm reg
          display ARM core registers
    tm4c123gh6pm.cpu arm semihosting ['enable'|'disable']
          activate support for semihosting operations
    tm4c123gh6pm.cpu arm semihosting_cmdline arguments
          command line arguments to be passed to program
    tm4c123gh6pm.cpu arm semihosting_fileio ['enable'|'disable']
          activate support for semihosting fileio operations
    tm4c123gh6pm.cpu arm semihosting_resexit ['enable'|'disable']
          activate support for semihosting resumable exit
  tm4c123gh6pm.cpu arp_examine ['allow-defer']
        used internally for reset processing
  tm4c123gh6pm.cpu arp_halt
        used internally for reset processing
  tm4c123gh6pm.cpu arp_halt_gdb
        used internally for reset processing to halt GDB
  tm4c123gh6pm.cpu arp_poll
        used internally for reset processing
  tm4c123gh6pm.cpu arp_reset
        used internally for reset processing
  tm4c123gh6pm.cpu arp_waitstate
        used internally for reset processing
  tm4c123gh6pm.cpu array2mem arrayname bitwidth address count
        Writes Tcl array of 8/16/32 bit numbers to target memory
  tm4c123gh6pm.cpu cget target_attribute
        returns the specified target attribute (command valid any time)
  tm4c123gh6pm.cpu configure [target_attribute ...]
        configure a new target for use (command valid any time)
  tm4c123gh6pm.cpu curstate
        displays the current state of this target
  tm4c123gh6pm.cpu eventlist
        displays a table of events defined for this target
  tm4c123gh6pm.cpu examine_deferred
        used internally for reset processing
  tm4c123gh6pm.cpu invoke-event event_name
        invoke handler for specified event
  tm4c123gh6pm.cpu itm
        itm command group (command valid any time)
    tm4c123gh6pm.cpu itm port <port> (0|1|on|off)
          Enable or disable ITM stimulus port (command valid any time)
    tm4c123gh6pm.cpu itm ports (0|1|on|off)
          Enable or disable all ITM stimulus ports (command valid any time)
  tm4c123gh6pm.cpu mdb address [count]
        Display target memory as 8-bit bytes
  tm4c123gh6pm.cpu mdd address [count]
        Display target memory as 64-bit words
  tm4c123gh6pm.cpu mdh address [count]
        Display target memory as 16-bit half-words
  tm4c123gh6pm.cpu mdw address [count]
        Display target memory as 32-bit words
  tm4c123gh6pm.cpu mem2array arrayname bitwidth address count
        Loads Tcl array of 8/16/32 bit numbers from target memory
  tm4c123gh6pm.cpu mwb address data [count]
        Write byte(s) to target memory
  tm4c123gh6pm.cpu mwd address data [count]
        Write 64-bit word(s) to target memory
  tm4c123gh6pm.cpu mwh address data [count]
        Write 16-bit half-word(s) to target memory
  tm4c123gh6pm.cpu mww address data [count]
        Write 32-bit word(s) to target memory
  tm4c123gh6pm.cpu tpiu
        tpiu command group (command valid any time)
    tm4c123gh6pm.cpu tpiu config (disable | ((external | internal <filename>) (sync <port width> |
              ((manchester | uart) <formatter enable>)) <TRACECLKIN freq>
              [<trace freq>]))
          Configure TPIU features (command valid any time)
  tm4c123gh6pm.cpu was_examined
        used internally for reset processing
tm4c123gh6pm.dap
      dap instance command group (command valid any time)
tpiu
      tpiu command group (command valid any time)
  tpiu config (disable | ((external | internal <filename>) (sync <port width> |
            ((manchester | uart) <formatter enable>)) <TRACECLKIN freq>
            [<trace freq>]))
        Configure TPIU features (command valid any time)
transport
      Transport command group (command valid any time)
  transport init
        Initialize this session's transport (command valid any time)
  transport list
        list all built-in transports (command valid any time)
  transport select [transport_name]
        Select this session's transport (command valid any time)
usage [command_name]
      Show basic command usage; command can be multiple tokens. (command
      valid any time)
version
      show program version (command valid any time)
```
