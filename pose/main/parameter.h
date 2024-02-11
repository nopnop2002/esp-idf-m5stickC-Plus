typedef enum {SENDER_IMU, SENDER_BUTTON} SENDER;

typedef struct {
	float quatx;
	float quaty;
	float quatz;
	float quatw;
	float roll;
	float pitch;
	float yaw;
} POSE_t;

typedef struct {
	int sender;
	float accX;
	float accY;
	float accZ;
	float gyroX;
	float gyroY;
	float gyroZ;
} MOTION6_t;
