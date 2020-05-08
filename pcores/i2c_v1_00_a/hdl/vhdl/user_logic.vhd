------------------------------------------------------------------------------
-- user_logic.vhd - entity/architecture pair
------------------------------------------------------------------------------
--
-- ***************************************************************************
-- ** Copyright (c) 1995-2012 Xilinx, Inc.  All rights reserved.            **
-- **                                                                       **
-- ** Xilinx, Inc.                                                          **
-- ** XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS"         **
-- ** AS A COURTESY TO YOU, SOLELY FOR USE IN DEVELOPING PROGRAMS AND       **
-- ** SOLUTIONS FOR XILINX DEVICES.  BY PROVIDING THIS DESIGN, CODE,        **
-- ** OR INFORMATION AS ONE POSSIBLE IMPLEMENTATION OF THIS FEATURE,        **
-- ** APPLICATION OR STANDARD, XILINX IS MAKING NO REPRESENTATION           **
-- ** THAT THIS IMPLEMENTATION IS FREE FROM ANY CLAIMS OF INFRINGEMENT,     **
-- ** AND YOU ARE RESPONSIBLE FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE      **
-- ** FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY DISCLAIMS ANY              **
-- ** WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE               **
-- ** IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR        **
-- ** REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF       **
-- ** INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS       **
-- ** FOR A PARTICULAR PURPOSE.                                             **
-- **                                                                       **
-- ***************************************************************************
--
------------------------------------------------------------------------------
-- Filename:          user_logic.vhd
-- Version:           1.00.a
-- Description:       User logic.
-- Date:              Fri Jun 06 15:19:56 2014 (by Create and Import Peripheral Wizard)
-- VHDL Standard:     VHDL'93
------------------------------------------------------------------------------
-- Naming Conventions:
--   active low signals:                    "*_n"
--   clock signals:                         "clk", "clk_div#", "clk_#x"
--   reset signals:                         "rst", "rst_n"
--   generics:                              "C_*"
--   user defined types:                    "*_TYPE"
--   state machine next state:              "*_ns"
--   state machine current state:           "*_cs"
--   combinatorial signals:                 "*_com"
--   pipelined or register delay signals:   "*_d#"
--   counter signals:                       "*cnt*"
--   clock enable signals:                  "*_ce"
--   internal version of output port:       "*_i"
--   device pins:                           "*_pin"
--   ports:                                 "- Names begin with Uppercase"
--   processes:                             "*_PROCESS"
--   component instantiations:              "<ENTITY_>I_<#|FUNC>"
------------------------------------------------------------------------------

-- DO NOT EDIT BELOW THIS LINE --------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

library proc_common_v3_00_a;
use proc_common_v3_00_a.proc_common_pkg.all;

-- DO NOT EDIT ABOVE THIS LINE --------------------

--USER libraries added here

------------------------------------------------------------------------------
-- Entity section
------------------------------------------------------------------------------
-- Definition of Generics:
--   C_SLV_DWIDTH                 -- Slave interface data bus width
--   C_NUM_REG                    -- Number of software accessible registers
--
-- Definition of Ports:
--   Bus2IP_Clk                   -- Bus to IP clock
--   Bus2IP_Reset                 -- Bus to IP reset
--   Bus2IP_Data                  -- Bus to IP data bus
--   Bus2IP_BE                    -- Bus to IP byte enables
--   Bus2IP_RdCE                  -- Bus to IP read chip enable
--   Bus2IP_WrCE                  -- Bus to IP write chip enable
--   IP2Bus_Data                  -- IP to Bus data bus
--   IP2Bus_RdAck                 -- IP to Bus read transfer acknowledgement
--   IP2Bus_WrAck                 -- IP to Bus write transfer acknowledgement
--   IP2Bus_Error                 -- IP to Bus error response
--   IP2RFIFO_WrReq               -- IP to RFIFO : IP write request
--   IP2RFIFO_Data                -- IP to RFIFO : IP write data bus
--   RFIFO2IP_WrAck               -- RFIFO to IP : RFIFO write acknowledge
--   RFIFO2IP_AlmostFull          -- RFIFO to IP : RFIFO almost full
--   RFIFO2IP_Full                -- RFIFO to IP : RFIFO full
--   IP2WFIFO_RdReq               -- IP to WFIFO : IP read request
--   WFIFO2IP_Data                -- WFIFO to IP : WFIFO read data
--   WFIFO2IP_RdAck               -- WFIFO to IP : WFIFO read acknowledge
--   WFIFO2IP_AlmostEmpty         -- WFIFO to IP : WFIFO almost empty
--   WFIFO2IP_Empty               -- WFIFO to IP : WFIFO empty
------------------------------------------------------------------------------

entity user_logic is
  generic
  (
    -- ADD USER GENERICS BELOW THIS LINE ---------------
    --USER generics added here
	 input_clk : INTEGER := 50000000; --input clock speed from user logic in Hz
	 bus_clk   : INTEGER := 100000;   --speed the i2c bus (scl) will run at in Hz	 
    -- ADD USER GENERICS ABOVE THIS LINE ---------------

    -- DO NOT EDIT BELOW THIS LINE ---------------------
    -- Bus protocol parameters, do not add to or delete
    C_SLV_DWIDTH                   : integer              := 32;
    C_NUM_REG                      : integer              := 1
    -- DO NOT EDIT ABOVE THIS LINE ---------------------
  );
  port
  (
    -- ADD USER PORTS BELOW THIS LINE ------------------
    --USER ports added here
--    sda       : INOUT  STD_LOGIC;                    --serial data output of i2c bus
    sda_I       : IN   STD_LOGIC;                    --serial data input of i2c bus
    sda_O       : OUT  STD_LOGIC;                    --serial data output of i2c bus
    sda_T       : OUT  STD_LOGIC;                    --serial data three state of i2c bus
--    scl       : INOUT  STD_LOGIC;                   --serial clock output of i2c bus
    scl_I       : IN   STD_LOGIC;                    --serial data input of i2c bus
    scl_O       : OUT  STD_LOGIC;                    --serial data output of i2c bus
    scl_T       : OUT  STD_LOGIC;                   --serial data three state of i2c bus
--	 LEDs		    : OUT    STD_LOGIC_VECTOR(7 DOWNTO 0);
    -- ADD USER PORTS ABOVE THIS LINE ------------------
    -- DO NOT EDIT BELOW THIS LINE ---------------------
    -- Bus protocol ports, do not add to or delete
    Bus2IP_Clk                     : in  std_logic;
    Bus2IP_Reset                   : in  std_logic;
    Bus2IP_Data                    : in  std_logic_vector(0 to C_SLV_DWIDTH-1);
    Bus2IP_BE                      : in  std_logic_vector(0 to C_SLV_DWIDTH/8-1);
    Bus2IP_RdCE                    : in  std_logic_vector(0 to C_NUM_REG-1);
    Bus2IP_WrCE                    : in  std_logic_vector(0 to C_NUM_REG-1);
    IP2Bus_Data                    : out std_logic_vector(0 to C_SLV_DWIDTH-1);
    IP2Bus_RdAck                   : out std_logic;
    IP2Bus_WrAck                   : out std_logic;
    IP2Bus_Error                   : out std_logic;
    IP2RFIFO_WrReq                 : out std_logic;
    IP2RFIFO_Data                  : out std_logic_vector(0 to C_SLV_DWIDTH-1);
    RFIFO2IP_WrAck                 : in  std_logic;
    RFIFO2IP_AlmostFull            : in  std_logic;
    RFIFO2IP_Full                  : in  std_logic;
    IP2WFIFO_RdReq                 : out std_logic;
    WFIFO2IP_Data                  : in  std_logic_vector(0 to C_SLV_DWIDTH-1);
    WFIFO2IP_RdAck                 : in  std_logic;
    WFIFO2IP_AlmostEmpty           : in  std_logic;
    WFIFO2IP_Empty                 : in  std_logic
    -- DO NOT EDIT ABOVE THIS LINE ---------------------
  );

  attribute MAX_FANOUT : string;
  attribute SIGIS : string;

  attribute SIGIS of Bus2IP_Clk    : signal is "CLK";
  attribute SIGIS of Bus2IP_Reset  : signal is "RST";

end entity user_logic;

------------------------------------------------------------------------------
-- Architecture section
------------------------------------------------------------------------------

architecture IMP of user_logic is

  --USER signal declarations added here, as needed for user logic

	COMPONENT i2c_master
	  GENERIC(
		 input_clk : INTEGER := 50000000; --input clock speed from user logic in Hz
		 bus_clk   : INTEGER := 100000);   --speed the i2c bus (scl) will run at in Hz
	  PORT(
		 clk       : IN     STD_LOGIC;                    --system clock
		 reset     : IN     STD_LOGIC;                    --active high reset
		 ena       : IN     STD_LOGIC;                    --latch in command
		 addr      : IN     STD_LOGIC_VECTOR(6 DOWNTO 0); --address of target slave
		 rw        : IN     STD_LOGIC;                    --'0' is write, '1' is read
		 data_wr   : IN     STD_LOGIC_VECTOR(7 DOWNTO 0); --data to write to slave
		 busy      : OUT    STD_LOGIC;                    --indicates transaction in progress
		 data_rd   : OUT    STD_LOGIC_VECTOR(7 DOWNTO 0); --data read from slave
		 ack_error : BUFFER STD_LOGIC;                    --flag if improper acknowledge from slave
	--    sda       : INOUT  STD_LOGIC;                    --serial data output of i2c bus
		 sda_I       : IN   STD_LOGIC;                    --serial data input of i2c bus
		 sda_O       : OUT  STD_LOGIC;                    --serial data output of i2c bus
		 sda_T       : OUT  STD_LOGIC;                    --serial data three state of i2c bus
	--    scl       : INOUT  STD_LOGIC);                   --serial clock output of i2c bus
		 scl_I       : IN   STD_LOGIC;                    --serial data input of i2c bus
		 scl_O       : OUT  STD_LOGIC;                    --serial data output of i2c bus
		 scl_T       : OUT  STD_LOGIC);                   --serial data three state of i2c bus
	END COMPONENT;


	type EstadosControlI2c is (estadoEsperaComando, estadoLecturaOEscritura, estadoLectura1,estadoLectura2, espero_datos, estadoEscritura1,estadoEscritura2, estadoEscrituraFIFO);
	type EstadosLecturaFifo is (estadoEsperaOrden, estadoArrancaLecturaDato,estadoArrancaLecturaComando, estadoEsperaLecturaDato,estadoEsperaLecturaComando);
	signal EstadoActualControlI2C, SigEstadoControlI2C : EstadosControlI2c;
	signal EstadoActualLecturaFifo, SigEstadoLecturaFifo : EstadosLecturaFifo;
	SIGNAL i2c_clk 		: STD_LOGIC;
	SIGNAL i2c_reset  	: STD_LOGIC;
	SIGNAL i2c_ena 		: STD_LOGIC;
	SIGNAL i2c_addr		: STD_LOGIC_VECTOR(6 DOWNTO 0);
	SIGNAL i2c_rw 			: STD_LOGIC; -- señal de lectura/escritura
	SIGNAL i2c_data_wr  	: STD_LOGIC_VECTOR(7 downto 0);--dato escritura que se pasa al driver (big endian)
	SIGNAL i2c_data_rd 	: STD_LOGIC_VECTOR(7 DOWNTO 0); -- dato lectura que se lee del driver (big endian)
	SIGNAL  i2c_data_wr_le, i2c_data_rd_le  	: STD_LOGIC_VECTOR(0 to 7); -- dato escritura y lectura  little endian
	SIGNAL  i2c_data_rd_32_le  	: STD_LOGIC_VECTOR(0 to 31); -- datos intermedio de 32 bits little endian
	
	SIGNAL i2c_busy 		: STD_LOGIC;
	
	SIGNAL i2c_ack_error	: STD_LOGIC;
	SIGNAL Num_bytes: STD_LOGIC_VECTOR(7 DOWNTO 0); -- Numero bytes de lectura o escritura
	SIGNAL cuenta_bytes, cuenta_bytes_next: STD_LOGIC_VECTOR(7 DOWNTO 0); 
	signal nbyte, nbyte_next: std_logic_vector (1 downto 0); -- Numero byte dentro de una palabra
	signal nuevo_dato, nuevo_comando, dato_val, comando_val	: STD_LOGIC;
	SIGNAL lecturaEscritura : STD_LOGIC;
	SIGNAL cargar_byte : STD_LOGIC;
	SIGNAL busy_prev : STD_LOGIC;

	SIGNAL WFIFO2IP_Command_REG, WFIFO2IP_Data_REG : STD_LOGIC_VECTOR(0 TO 31);

  ------------------------------------------
  -- Signals for read/write fifo loopback example
  ------------------------------------------
  type FIFO_CNTL_SM_TYPE is (IDLE, RD_REQ, WR_REQ);
  signal fifo_cntl_ns                   : FIFO_CNTL_SM_TYPE;
  signal fifo_cntl_cs                   : FIFO_CNTL_SM_TYPE;
  signal fifo_rdreq_cmb                 : std_logic;
  signal fifo_wrreq_cmb                 : std_logic;

begin

  --USER logic implementation added here

	i2c_master_i : i2c_master
	  GENERIC MAP (
		 input_clk => input_clk, --input clock speed from user logic in Hz
		 bus_clk   => bus_clk)    --speed the i2c bus (scl) will run at in Hz
	  PORT MAP (
		 clk       => i2c_clk,
		 reset     => i2c_reset,
		 ena       => i2c_ena,
		 addr      => i2c_addr,
		 rw        => i2c_rw,
		 data_wr   => i2c_data_wr,
		 busy      => i2c_busy,
		 data_rd   => i2c_data_rd,
		 ack_error => i2c_ack_error,
		 sda_I     => sda_I,
		 sda_O     => sda_O,
		 sda_T     => sda_T,
		 scl_I     => scl_I,
		 scl_O     => scl_O,
		 scl_T     => scl_T);

	i2c_clk <= Bus2IP_Clk;
	i2c_reset <= Bus2IP_Reset;
	
-- En un comando, los 32 bits de la fifo se dividen en número de bytes (bits 8 al 15) dirección de 
-- lectura/escritura (bits 24-30) y señal de lectura/escritura (bit 31)
-- Al copiarlo damos la vuelta al dato para que sea big-endian
	
	lecturaEscritura <= WFIFO2IP_Command_REG(31);
	
	Num_bytes(0) <= WFIFO2IP_Command_REG(15);
	Num_bytes(1) <= WFIFO2IP_Command_REG(14);
	Num_bytes(2) <= WFIFO2IP_Command_REG(13);
	Num_bytes(3) <= WFIFO2IP_Command_REG(12);
	Num_bytes(4) <= WFIFO2IP_Command_REG(11);
	Num_bytes(5) <= WFIFO2IP_Command_REG(10);
	Num_bytes(6) <= WFIFO2IP_Command_REG(9);
	Num_bytes(7) <= WFIFO2IP_Command_REG(8);
	
	i2c_addr(0) <= WFIFO2IP_Command_REG(30);
	i2c_addr(1) <= WFIFO2IP_Command_REG(29);
	i2c_addr(2) <= WFIFO2IP_Command_REG(28);
	i2c_addr(3) <= WFIFO2IP_Command_REG(27);
	i2c_addr(4) <= WFIFO2IP_Command_REG(26);
	i2c_addr(5) <= WFIFO2IP_Command_REG(25);
	i2c_addr(6) <= WFIFO2IP_Command_REG(24);
	
	
	
	
-- En un dato, los 32 bits de la fifo se dividen en 4 bytes siendo 0 el más significativo 
-- y 3 el menos significativo
	i2c_data_wr_le(0 to 7) <=  WFIFO2IP_Data_REG(24 to 31) when nbyte =3 
	else WFIFO2IP_Data_REG(16 to 23) when nbyte =2 
	else WFIFO2IP_Data_REG(8  to 15) when nbyte =1 
	else WFIFO2IP_Data_REG(0 to 7);

-- Demos las vuelta a los bits para que sean big-endian	
	i2c_data_wr(0) <= i2c_data_wr_le(7);
	i2c_data_wr(1) <= i2c_data_wr_le(6);
	i2c_data_wr(2) <= i2c_data_wr_le(5);
	i2c_data_wr(3) <= i2c_data_wr_le(4);
	i2c_data_wr(4) <= i2c_data_wr_le(3);
	i2c_data_wr(5) <= i2c_data_wr_le(2);
	i2c_data_wr(6) <= i2c_data_wr_le(1);
	i2c_data_wr(7) <= i2c_data_wr_le(0);
	
	
		
	i2c_data_rd_le(0) <= i2c_data_rd(7);
	i2c_data_rd_le(1) <= i2c_data_rd(6);
	i2c_data_rd_le(2) <= i2c_data_rd(5);
	i2c_data_rd_le(3) <= i2c_data_rd(4);
	i2c_data_rd_le(4) <= i2c_data_rd(3);
	i2c_data_rd_le(5) <= i2c_data_rd(2);
	i2c_data_rd_le(6) <= i2c_data_rd(1);
	i2c_data_rd_le(7) <= i2c_data_rd(0);
	
	
	
	
	IP2RFIFO_Data <= i2c_data_rd_32_le;
	
	
	
	controlFifo: process (EstadoActualLecturaFifo, WFIFO2IP_empty, WFIFO2IP_RdAck, WFIFO2IP_Data, nuevo_dato, nuevo_comando) 
	begin
	SigEstadoLecturaFifo <= EstadoActualLecturaFifo;
	fifo_rdreq_cmb <= '0';
	dato_val <= '0';
	comando_val <= '0';
	
		case EstadoActualLecturaFifo is
			when estadoEsperaOrden =>
				if nuevo_dato='1' then
					SigEstadoLecturaFifo <= estadoArrancaLecturaDato;
				elsif nuevo_comando='1' then
					SigEstadoLecturaFifo <= estadoArrancaLecturaComando;
				end if;	
			when 	estadoArrancaLecturaDato =>
				if (WFIFO2IP_empty = '0') then
					fifo_rdreq_cmb <= '1';
					SigEstadoLecturaFifo   <= estadoEsperaLecturaDato;
				end if;
			when 	estadoArrancaLecturaComando =>
				if (WFIFO2IP_empty = '0') then
					fifo_rdreq_cmb <= '1';
					SigEstadoLecturaFifo   <= estadoEsperaLecturaComando;
				end if;
			when estadoEsperaLecturaDato =>
				if (WFIFO2IP_RdAck = '1')  then
					dato_val <= '1';
					SigEstadoLecturaFifo <= estadoEsperaOrden;
				end if;
			when estadoEsperaLecturaComando =>
				if (WFIFO2IP_RdAck = '1')  then
					comando_val <= '1';
					SigEstadoLecturaFifo <= estadoEsperaOrden;
				end if;
		end case;
	end process controlFifo;
	
	-- Maquinas de estados		
	unidadDeControlI2C: process(EstadoActualControlI2C, WFIFO2IP_empty, WFIFO2IP_RdAck, WFIFO2IP_Data, RFIFO2IP_WrAck,  busy_prev, i2c_busy, lecturaEscritura)
	begin
	
		SigEstadoControlI2C <= EstadoActualControlI2C;
		fifo_wrreq_cmb <= '0';	
		i2c_ena <= '0';
		i2c_rw <= '1'; 
		cuenta_bytes_next<=cuenta_bytes;
		nbyte_next <= nbyte;
		cargar_byte <= '0';
		nuevo_comando <= '0';
		nuevo_dato <= '0';
		
		case EstadoActualControlI2C is
		
			when estadoEsperaComando =>
				nuevo_comando <= '1';
				if (comando_val='1') then
					SigEstadoControlI2C   <= estadoLecturaOEscritura;
				end if;

			when estadoLecturaOEscritura =>
				nbyte_next <= "00";
				cuenta_bytes_next <= Num_bytes;	-- inicializamos el número de bytes
				if (lecturaEscritura = '0') then  --command is a read
					SigEstadoControlI2C <=estadoLectura1 ;
				else
					SigEstadoControlI2C <= espero_datos ;					
				end if;
				
											
				when espero_datos =>		-- leemos los datos para escribir en el I2C
				nuevo_dato<='1';
				if (dato_val = '1') then
					SigEstadoControlI2C   <= estadoEscritura1;
				end if;
				
				when estadoEscritura1 =>
				i2c_rw <= '0';  					--command is a write	
				i2c_ena <= '1';
				if (busy_prev = '0' AND i2c_busy = '1') then   --i2c busy just went high
					if nbyte = "11" then				-- se escribe el siguiente byte
						nbyte_next <= "00";
					else 
						nbyte_next <= nbyte +1;
					end if; 
					cuenta_bytes_next<= cuenta_bytes -'1';
					if ((nbyte = "11" ) and not(cuenta_bytes = "00000001" ))then 
						nuevo_dato <= '1';		-- si no es el último byte a transferir y se ha terminado de escribir la palabra actual
					end if;							-- se solicita la siguiente palabra a la FIFO
					SigEstadoControlI2C <= estadoEscritura2;
				end if;
				
			when estadoEscritura2 =>
					i2c_rw <= '0';
					if cuenta_bytes="00000000"  then		-- es el último byte
						i2c_ena <= '0';
					else
						i2c_ena <= '1';
					end if;		
					if (busy_prev = '1' AND i2c_busy = '0') then 
						if cuenta_bytes="00000000"  then
							SigEstadoControlI2C <= estadoEsperaComando;
						else
							SigEstadoControlI2C <= estadoEscritura1;
						end if; 
					end if;	
			when estadoLectura1 =>
					i2c_rw <= '1';  							
					i2c_ena <= '1';
					if (busy_prev = '0' AND i2c_busy = '1') then   --i2c busy just went high
						if nbyte = "11" then
						    nbyte_next <= "00";
						else 
						   nbyte_next <= nbyte +1;
						end if; 
						cuenta_bytes_next <= cuenta_bytes -'1';
						SigEstadoControlI2C <= estadoLectura2;
					 end if;
				
				
			when estadoLectura2 =>	
					i2c_rw <= '1';  
					if cuenta_bytes="00000000"  then -- es el último byte
							i2c_ena <= '0';
						else
								i2c_ena <= '1';
						end if;							
				IF (busy_prev = '1' AND i2c_busy = '0') THEN		
				  cargar_byte <= '1';	-- se escribe el dato leido en el registro
					if cuenta_bytes = "00000000" then 
						fifo_wrreq_cmb <= '1';	-- se hace una petición de escritura en la FIFO
						SigEstadoControlI2C <= estadoEscrituraFIFO;
					else	
						if nbyte = "00" then
						  	fifo_wrreq_cmb <= '1';	-- se hace una petición de escritura en la FIFO
							SigEstadoControlI2C <= estadoEscrituraFIFO;
						else 
						 	SigEstadoControlI2C <= estadoLectura1;
						end if; 
					end if; 
				END IF;				
	
		
				
			when estadoEscrituraFIFO =>
					i2c_rw <= '1';  	
					if cuenta_bytes = "00000000" then 
						i2c_ena <= '0';
					else
						i2c_ena <= '1';
						end if;
				IF (RFIFO2IP_WrAck = '1') THEN
				 if cuenta_bytes="00000000" then
					SigEstadoControlI2C <= estadoEsperaComando;
				 else
					SigEstadoControlI2C <= estadoLectura1;
				 end if; 
				end if;
							
							
		end case;
	end process unidadDeControlI2C;
	
			
	state: process (Bus2IP_Clk)
	begin			  
		  if Bus2IP_Clk'EVENT and Bus2IP_Clk='1' then
			 if Bus2IP_Reset = '1' then
				EstadoActualControlI2C <= estadoEsperaComando;
				EstadoActualLecturaFifo <= estadoEsperaOrden;
				IP2WFIFO_RdReq <= '0';
				IP2RFIFO_WrReq <= '0';
				busy_prev <= '0';
				nbyte <= "00";
				cuenta_bytes <= (others => '0');
				i2c_data_rd_32_le <= (others => '0');
				WFIFO2IP_Data_REG <= (others => '0');
					WFIFO2IP_Command_REG <= (others => '0');
			 else
				EstadoActualControlI2C <= SigEstadoControlI2C;
				EstadoActualLecturaFifo <= SigEstadoLecturaFifo;
				IP2WFIFO_RdReq <= fifo_rdreq_cmb;
				IP2RFIFO_WrReq <= fifo_wrreq_cmb;
				busy_prev <= i2c_busy;  --capture the value of the previous i2c busy signal  
				nbyte <= nbyte_next;	
				cuenta_bytes <= cuenta_bytes_next;
				if dato_val = '1' then
					WFIFO2IP_Data_REG <= WFIFO2IP_Data;
				end if;	
				if comando_val = '1' then
					WFIFO2IP_Command_REG <= WFIFO2IP_Data;
				end if;
				if cargar_byte = '1' then
					case nbyte is  -- nbyte vale 1 más que el último byte leído
						when "01" => i2c_data_rd_32_le(0 to 7) <= 	i2c_data_rd_le;	
									 i2c_data_rd_32_le(8 to 31)<= (others => '0');	--como es el primer byte se inicializa el resto a 0
						when "10" => i2c_data_rd_32_le(8 to 15) <= 	i2c_data_rd_le;	
						when "11" => i2c_data_rd_32_le(16 to 23) <= 	i2c_data_rd_le;	
						when "00" => i2c_data_rd_32_le(24 to 31) <= 	i2c_data_rd_le;	
										
						when others		=>		i2c_data_rd_32_le	<= (others => '0');	
					end case;
				end if;				
			 end if;
		  end if;
	end process state;


	

  ------------------------------------------
  -- Example code to drive IP to Bus signals
  ------------------------------------------
  IP2Bus_Data  <= (others => '0');

  IP2Bus_WrAck <= '0';
  IP2Bus_RdAck <= '0';
  IP2Bus_Error <= '0';

end IMP;
