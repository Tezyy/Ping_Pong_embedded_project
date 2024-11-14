#ifndef __CAN__
#define __CAN__

#include <stdint.h>

typedef struct CanInit CanInit_t;
__attribute__((packed)) struct CanInit
{
	union
	{
		struct
		{
			uint32_t phase2 : 4; // Phase 2 segment
			uint32_t propag : 4; // Propagation time segment
			uint32_t phase1 : 4; // Phase 1 segment
			uint32_t sjw : 4;    // Synchronization jump width
			uint32_t brp : 8;    // Baud rate prescaler
			uint32_t smp : 8;    // Sampling mode
		};
		uint32_t reg;
	};
};

void can_init(CanInit_t init, uint8_t rxInterrupt);

#define union_cast(type, x)                                                    \
(((union {                                                                   \
	typeof(x) a;                                                              \
	type b;                                                                   \
})x)                                                                        \
.b)

// Dummy type for use with `union_cast`, see below
typedef struct Byte8 Byte8;
struct Byte8
{
	uint8_t bytes[8];
};

// CAN message data type
// Data fields have 3 access methods (via union):
//  8 bytes
//  2 double words (32-bit ints)
//  1 Byte8 dummy struct
// The dummy struct allows for convenient construction of a CAN message from
// another type
//
// Example:
//    typedef struct {
//        uint16_t  a;
//        uint8_t   b;
//        float     c;
//    } __attribute__((packed)) YourStruct ;
//
//    CanMsg m = (CanMsg){
//        .id = 1,
//        .length = sizeof(YourStruct),
//        .byte8 = union_cast(Byte8, ((YourStruct){
//            .a = 10,
//            .b = 20,
//            .c = -30.0,
//        })),
//    };
//    can_printmsg(m);
//    // Should print: CanMsg(id:1, length:7, data:{10, 0, 20, 0, 0, 240, 193})

typedef struct CanMsg CanMsg;
struct CanMsg
{
	uint8_t id;
	uint8_t length;
	union
	{
		uint8_t byte[8];
		uint32_t dword[2];
		Byte8 byte8;
	};
};

typedef enum
{
	JOYSTICK_DATA_ID = 42
} can_id_t;

// Send a CAN message on the bus.
// Blocks if the bus does not receive the message (typically because one of the
// receiving nodes has not cleared a buffer)
void can_tx(CanMsg m);

// Receive a CAN message.
// Does not block. Returns 0 if there is no message, 1 otherwise
uint8_t can_rx(CanMsg *m);

// Print a CAN message (using `printf`)
void can_printmsg(CanMsg m);

#endif // __CAN__
