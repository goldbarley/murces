#ifndef MTUI_MINECRAFT_H
#define MTUI_MINECRAFT_H

#include <stdint.h>

#define MC_MAKEV_X(major) (((uint32_t)(major)) << 22U)
#define MC_MAKEV_Y(minor) (((uint32_t)(minor)) << 12U)
#define MC_MAKEV_Z(patch) ((uint32_t)(patch))

#define MC_MAKE_VERSION(x, y, z) \
	(MC_MAKEV_X(x) | MC_MAKEV_Y(y) | MC_MAKEV_Z(z))

#define MC_VERSION_X(version) (((uint32_t)(version)) >> 22U)
#define MC_VERSION_Y(version) (((((uint32_t))(version)) >> 12U) & 0x3FFU)
#define MC_VERSION_Z(version) (((uint32_t)(version)) & 0xFFFU)

/* Change this as you please. */
#define MAX_VTOMD_ELEM_COUNT (256U)

extern char *mcstdvtomd[MAX_VTOMD_ELEM_COUNT];

#endif /* MTUI_MINECRAFT_H */