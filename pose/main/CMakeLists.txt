set(srcs "main.cpp"
	"tft.c"
	"mpu6050.cpp"
	"spiffs.c"
	)

idf_component_register(SRCS ${srcs} INCLUDE_DIRS ".")
