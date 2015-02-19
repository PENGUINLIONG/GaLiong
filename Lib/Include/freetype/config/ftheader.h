#ifndef __FT_HEADER_H__
#define __FT_HEADER_H__

#ifdef __cplusplus
#define FT_BEGIN_HEADER  extern "C" {
#else
#define FT_BEGIN_HEADER  /* nothing */
#endif

#ifdef __cplusplus
#define FT_END_HEADER  }
#else
#define FT_END_HEADER  /* nothing */
#endif

#ifndef FT_CONFIG_CONFIG_H
#define FT_CONFIG_CONFIG_H  "freetype\config\ftconfig.h"
#endif

#ifndef FT_CONFIG_STANDARD_LIBRARY_H
#define FT_CONFIG_STANDARD_LIBRARY_H  "freetype\config\ftstdlib.h"
#endif

#ifndef FT_CONFIG_OPTIONS_H
#define FT_CONFIG_OPTIONS_H  "freetype\config\ftoption.h"
#endif

#ifndef FT_CONFIG_MODULES_H
#define FT_CONFIG_MODULES_H  "freetype\config\ftmodule.h"
#endif

#define FT_FREETYPE_H			"freetype\freetype.h"
#define FT_ERRORS_H				"freetype\fterrors.h"
#define FT_MODULE_ERRORS_H		"freetype\ftmoderr.h"
#define FT_SYSTEM_H				"freetype\ftsystem.h"
#define FT_IMAGE_H				"freetype\ftimage.h"
#define FT_TYPES_H				"freetype\fttypes.h"
#define FT_OUTLINE_H			"freetype\ftoutln.h"
#define FT_SIZES_H				"freetype\ftsizes.h"
#define FT_MODULE_H				"freetype\ftmodapi.h"
#define FT_RENDER_H				"freetype\ftrender.h"
#define FT_AUTOHINTER_H			"freetype\ftautoh.h"
#define FT_CFF_DRIVER_H			"freetype\ftcffdrv.h"
#define FT_TRUETYPE_DRIVER_H	"freetype\ftttdrv.h"
#define FT_TYPE1_TABLES_H		"freetype\t1tables.h"
#define FT_TRUETYPE_IDS_H		"freetype\ttnameid.h"
#define FT_TRUETYPE_TABLES_H	"freetype\tttables.h"
#define FT_TRUETYPE_TAGS_H		"freetype\tttags.h"
#define FT_BDF_H				"freetype\ftbdf.h"
#define FT_CID_H				"freetype\ftcid.h"
#define FT_GZIP_H				"freetype\ftgzip.h"
#define FT_LZW_H				"freetype\ftlzw.h"
#define FT_BZIP2_H				"freetype\ftbzip2.h"
#define FT_WINFONTS_H			"freetype\ftwinfnt.h"
#define FT_GLYPH_H				"freetype\ftglyph.h"
#define FT_BITMAP_H				"freetype\ftbitmap.h"
#define FT_BBOX_H				"freetype\ftbbox.h"
#define FT_CACHE_H				"freetype\ftcache.h"
#define FT_CACHE_IMAGE_H  FT_CACHE_H
#define FT_CACHE_SMALL_BITMAPS_H  FT_CACHE_H
#define FT_CACHE_CHARMAP_H  FT_CACHE_H
#define FT_MAC_H				"freetype\ftmac.h"
#define FT_MULTIPLE_MASTERS_H	"freetype\ftmm.h"
#define FT_SFNT_NAMES_H			"freetype\ftsnames.h"
#define FT_OPENTYPE_VALIDATE_H  "freetype\ftotval.h"
#define FT_GX_VALIDATE_H		"freetype\ftgxval.h"
#define FT_PFR_H				"freetype\ftpfr.h"
#define FT_STROKER_H			"freetype\ftstroke.h"
#define FT_SYNTHESIS_H			"freetype\ftsynth.h"
#define FT_XFREE86_H			"freetype\ftxf86.h"
#define FT_TRIGONOMETRY_H		"freetype\fttrigon.h"
#define FT_LCD_FILTER_H			"freetype\ftlcdfil.h"
#define FT_UNPATENTED_HINTING_H	"freetype\ttunpat.h"
#define FT_INCREMENTAL_H		"freetype\ftincrem.h"
#define FT_GASP_H				"freetype\ftgasp.h"
#define FT_ADVANCES_H			"freetype\ftadvanc.h"
#define FT_ERROR_DEFINITIONS_H  "freetype\fterrdef.h"

#define FT_CACHE_MANAGER_H           "freetype\ftcache.h"
#define FT_CACHE_INTERNAL_MRU_H      "freetype\ftcache.h"
#define FT_CACHE_INTERNAL_MANAGER_H  "freetype\ftcache.h"
#define FT_CACHE_INTERNAL_CACHE_H    "freetype\ftcache.h"
#define FT_CACHE_INTERNAL_GLYPH_H    "freetype\ftcache.h"
#define FT_CACHE_INTERNAL_IMAGE_H    "freetype\ftcache.h"
#define FT_CACHE_INTERNAL_SBITS_H    "freetype\ftcache.h"

#define FT_INCREMENTAL_H          "freetype\ftincrem.h"

#define FT_TRUETYPE_UNPATENTED_H  "freetype\ttunpat.h"

#endif /* __FT2_BUILD_H__ */


/* END */
