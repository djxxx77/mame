/***************************************************************************

    Sega System 32/Multi 32 hardware

***************************************************************************/


typedef void (*sys32_output_callback)(int which, UINT16 data);
struct layer_info
{
	bitmap_t *	bitmap;
	UINT8 *					transparent;
};


class segas32_state : public driver_device
{
public:
	segas32_state(running_machine &machine, const driver_device_config_base &config)
		: driver_device(machine, config) { }

	UINT8 *z80_shared_ram;
	UINT8 v60_irq_control[0x10];
	timer_device *v60_irq_timer[2];
	UINT8 sound_irq_control[4];
	UINT8 sound_irq_input;
	UINT8 sound_dummy_value;
	UINT16 sound_bank;
	UINT8 misc_io_data[2][0x10];
	read16_space_func custom_io_r[2];
	write16_space_func custom_io_w[2];
	UINT8 analog_bank;
	UINT8 analog_value[4];
	UINT8 sonic_last[6];
	sys32_output_callback sw1_output;
	sys32_output_callback sw2_output;
	sys32_output_callback sw3_output;
	UINT16* dual_pcb_comms;
	UINT8 *ga2_dpram;
	UINT16 *system32_workram;
	UINT16 *system32_protram;
	UINT16 *system32_videoram;
	UINT16 *system32_spriteram;
	UINT16 *system32_paletteram[2];
	UINT16 system32_displayenable[2];
	UINT16 system32_tilebank_external;
	UINT16 arescue_dsp_io[6];
	UINT8 is_multi32;
	struct cache_entry *cache_head;
	struct layer_info layer_data[11];
	UINT16 mixer_control[2][0x40];
	UINT16 *solid_0000;
	UINT16 *solid_ffff;
	UINT8 sprite_render_count;
	UINT8 sprite_control_latched[8];
	UINT8 sprite_control[8];
	UINT32 *spriteram_32bit;
	void (*system32_prot_vblank)(device_t *device);
};


/*----------- defined in machine/segas32.c -----------*/

READ16_HANDLER( arabfgt_protection_r );
READ16_HANDLER( arf_wakeup_protection_r );
WRITE16_HANDLER( arabfgt_protection_w );

READ16_HANDLER( brival_protection_r );
WRITE16_HANDLER( brival_protection_w );

READ16_HANDLER( darkedge_protection_r );
WRITE16_HANDLER( darkedge_protection_w );
void darkedge_fd1149_vblank(device_t *device);
WRITE16_HANDLER( jleague_protection_w );

READ16_HANDLER( dbzvrvs_protection_r );
WRITE16_HANDLER( dbzvrvs_protection_w );

extern const UINT8 ga2_v25_opcode_table[];
void decrypt_ga2_protrom(running_machine *machine);
READ16_HANDLER( ga2_dpram_r );
WRITE16_HANDLER( ga2_dpram_w );

WRITE16_HANDLER(sonic_level_load_protection);

READ16_HANDLER( arescue_dsp_r );
WRITE16_HANDLER( arescue_dsp_w );


/*----------- defined in video/segas32.c -----------*/

VIDEO_START(system32);
VIDEO_START(multi32);
VIDEO_UPDATE(system32);
VIDEO_UPDATE(multi32);
void system32_set_vblank(running_machine *machine, int state);

READ16_HANDLER( system32_videoram_r );
WRITE16_HANDLER( system32_videoram_w );
READ32_HANDLER( multi32_videoram_r );
WRITE32_HANDLER( multi32_videoram_w );

READ16_HANDLER( system32_spriteram_r );
WRITE16_HANDLER( system32_spriteram_w );
READ32_HANDLER( multi32_spriteram_r );
WRITE32_HANDLER( multi32_spriteram_w );

READ16_HANDLER( system32_paletteram_r );
WRITE16_HANDLER( system32_paletteram_w );
READ32_HANDLER( multi32_paletteram_0_r );
WRITE32_HANDLER( multi32_paletteram_0_w );
READ32_HANDLER( multi32_paletteram_1_r );
WRITE32_HANDLER( multi32_paletteram_1_w );

READ16_HANDLER( system32_sprite_control_r );
WRITE16_HANDLER( system32_sprite_control_w );
READ32_HANDLER( multi32_sprite_control_r );
WRITE32_HANDLER( multi32_sprite_control_w );

WRITE16_HANDLER( system32_mixer_w );
READ16_HANDLER( system32_mixer_r );
WRITE32_HANDLER( multi32_mixer_0_w );
WRITE32_HANDLER( multi32_mixer_1_w );
