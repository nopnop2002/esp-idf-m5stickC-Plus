set(srcs "main.c"
	"st7789.c"
	"Light_PWM.c"
	"axp192.c"
	"fontx.c"
	"decode_jpeg.c"
	"decode_png.c"
	"pngle.c"
	)

idf_component_register(SRCS ${srcs} INCLUDE_DIRS ".")
