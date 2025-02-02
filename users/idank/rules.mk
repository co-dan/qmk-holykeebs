VALID_POINTING_DEVICE_CONFIGURATIONS := trackball cirque35 cirque35_cirque35 trackball_trackball trackball_cirque35 cirque35_trackball trackpoint
ifdef POINTING_DEVICE
    ifeq ($(filter $(POINTING_DEVICE),$(VALID_POINTING_DEVICE_CONFIGURATIONS)),)
        $(call CATASTROPHIC_ERROR,Invalid POINTING_DEVICE,POINTING_DEVICE="$(POINTING_DEVICE)" is not a valid pointing device configuration)
	endif
endif

SERIAL_DRIVER = vendor
# SRC += $(USER_PATH)/idank.c

# Disable things we don't support that take up unnecessary space.
RGBLIGHT_SUPPORTED = no
RGB_MATRIX_SUPPORTED = no

ifeq ($(strip $(POINTING_DEVICE_POSITION)), left)
	OPT_DEFS += -DPOINTING_DEVICE_POSITION_LEFT
else ifeq ($(strip $(POINTING_DEVICE_POSITION)), thumb)
	OPT_DEFS += -DPOINTING_DEVICE_POSITION_THUMB
else ifeq ($(strip $(POINTING_DEVICE_POSITION)), thumb_inner)
	OPT_DEFS += -DPOINTING_DEVICE_POSITION_THUMB_INNER
else ifeq ($(strip $(POINTING_DEVICE_POSITION)), thumb_outer)
	OPT_DEFS += -DPOINTING_DEVICE_POSITION_THUMB_OUTER
else ifeq ($(strip $(POINTING_DEVICE_POSITION)), middle)
	OPT_DEFS += -DPOINTING_DEVICE_POSITION_MIDDLE
else
	OPT_DEFS += -DPOINTING_DEVICE_POSITION_RIGHT
endif

ifeq ($(strip $(POINTING_DEVICE)), trackball)
	OPT_DEFS += -DPOINTING_DEVICE_CONFIGURATION_PIMORONI
	POINTING_DEVICE_ENABLE = yes
	POINTING_DEVICE_DRIVER = pimoroni_trackball

	ifeq ($(strip $(TRACKBALL_RGB_RAINBOW)), yes)
		SRC += quantum/color.c $(USER_PATH)/trackball_rgb_rainbow.c
	endif
endif

ifeq ($(strip $(POINTING_DEVICE)), cirque35)
	OPT_DEFS += -DPOINTING_DEVICE_CONFIGURATION_CIRQUE35
	POINTING_DEVICE_ENABLE = yes
	POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c
endif

ifeq ($(strip $(POINTING_DEVICE)), cirque35_cirque35)
	OPT_DEFS += -DSPLIT_POINTING_ENABLE
	OPT_DEFS += -DPOINTING_DEVICE_COMBINED
	OPT_DEFS += -DPOINTING_DEVICE_CONFIGURATION_CIRQUE35_CIRQUE35

	POINTING_DEVICE_ENABLE = yes
	POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c
endif

ifeq ($(strip $(POINTING_DEVICE)), trackball_trackball)
	OPT_DEFS += -DSPLIT_POINTING_ENABLE
	OPT_DEFS += -DPOINTING_DEVICE_COMBINED
	OPT_DEFS += -DPOINTING_DEVICE_CONFIGURATION_PIMORONI_PIMORONI

	POINTING_DEVICE_ENABLE = yes
	POINTING_DEVICE_DRIVER = pimoroni_trackball

	ifeq ($(strip $(TRACKBALL_RGB_RAINBOW)), yes)
		SRC += quantum/color.c $(USER_PATH)/trackball_rgb_rainbow.c
	endif
endif

ifeq ($(strip $(POINTING_DEVICE)), trackball_cirque35)
	OPT_DEFS += -DSPLIT_POINTING_ENABLE
	OPT_DEFS += -DPOINTING_DEVICE_COMBINED
	OPT_DEFS += -DPOINTING_DEVICE_CONFIGURATION_PIMORONI_CIRQUE35
	POINTING_DEVICE_ENABLE = yes

	ifeq ($(strip $(SIDE)), left)
		POINTING_DEVICE_DRIVER = pimoroni_trackball

		ifeq ($(strip $(TRACKBALL_RGB_RAINBOW)), yes)
			SRC += quantum/color.c $(USER_PATH)/trackball_rgb_rainbow.c
		endif
	endif
	ifeq ($(strip $(SIDE)), right)
		POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c
	endif
endif

ifeq ($(strip $(POINTING_DEVICE)), cirque35_trackball)
	OPT_DEFS += -DSPLIT_POINTING_ENABLE
	OPT_DEFS += -DPOINTING_DEVICE_COMBINED
	OPT_DEFS += -DPOINTING_DEVICE_CONFIGURATION_CIRQUE35_PIMORONI
	POINTING_DEVICE_ENABLE = yes

	ifeq ($(strip $(SIDE)), right)
		POINTING_DEVICE_DRIVER = pimoroni_trackball

		ifeq ($(strip $(TRACKBALL_RGB_RAINBOW)), yes)
			SRC += quantum/color.c $(USER_PATH)/trackball_rgb_rainbow.c
		endif
	endif
	ifeq ($(strip $(SIDE)), left)
		POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c
	endif
endif

ifeq ($(strip $(POINTING_DEVICE)), trackpoint)
	PS2_MOUSE_ENABLE = yes
	PS2_ENABLE = yes
	PS2_DRIVER = vendor
	OPT_DEFS += -DPOINTING_DEVICE_CONFIGURATION_TRACKPOINT
endif

MOUSEKEY_ENABLE = yes

ifeq ($(strip $(OLED)), yes)
	OPT_DEFS += -DOLED_ENABLE
	OLED_ENABLE     = yes
	OLED_DRIVER     = ssd1306
else
	OLED_ENABLE     = no
endif

ifeq ($(strip $(OLED_FLIP)), yes)
	OPT_DEFS += -DOLED_FLIP
endif
