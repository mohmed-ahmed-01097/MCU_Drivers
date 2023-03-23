#ifndef GPIO_H
#define GPIO_H

typedef enum{
    INPUT = 0u,
    OUTPUT = 1u
}IO_Pin_type;

typedef enum{
    Low = 0u,
    High = 1u
}PORT_type;

/** Data Direction Register as input/Output **/
/** Pull-up Configuration **/
/** Port Data Register **/
/** Port Input Pins I/O location is read only **/

#endif // GPIO_H
