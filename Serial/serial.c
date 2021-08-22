#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#define SERIAL_DEVICE_NAME "/dev/ttyS0"



/**
 * This enum value is used for storing the parity mode of a serial interface.
 * It is used in the following functions.
 *
 * The special enum UART_CFG_PARITY_INVALID is used if the parity setting
 * of a UART cannot be determined or is unknown (not yet initialized).
 */
typedef enum {
    UART_CFG_PARITY_INVALID, /**< unknown / uninitialized */
    UART_CFG_PARITY_NONE,    /**< none */
    UART_CFG_PARITY_EVEN,    /**< even */
    UART_CFG_PARITY_ODD      /**< odd */
} uart_cfg_parity_t;


/**
 * This enum value is used for storing the parity mode of a serial interface.
 * It is used in the functions described in the following sections.
 *
 * The special enum UART_CFG_STOPBITS_INVALID is used if the stop bits setting
 * of a UART cannot be determined or is unknown (not yet initialized).
 */
typedef enum {
    UART_CFG_STOPBITS_INVALID, /**< unknown / uninitialized */
    UART_CFG_STOPBITS_1,       /**< 1 stop bit */
    UART_CFG_STOPBITS_1_5,     /**< 1.5 stop bits */
    UART_CFG_STOPBITS_2        /**< 2 stop bits */
} uart_cfg_stopbits_t;

/** File descriptor of the serial device */
static int g_serial_fd = 0;

/*****************************************************************************/
int serial_open(int baudrate,
                int databits,
                uart_cfg_parity_t parity,
                uart_cfg_stopbits_t stopbits)
{
    struct termios serial_settings;

    /* check if the serial-port was already opened */
    if (g_serial_fd > 0)
    {
        /*serial_close();*/
        return g_serial_fd;
    }

    /*  open the serial port read-/writeable, in nonblocking modus */
    g_serial_fd = open(SERIAL_DEVICE_NAME, O_RDWR | O_NOCTTY | O_NONBLOCK);

    if (g_serial_fd < 0)
        return g_serial_fd;                        /* open of port failed */

    /* get actual setting of serial port */
    tcgetattr(g_serial_fd, &serial_settings);
    serial_settings.c_cflag = B57600 | CS8  | CLOCAL | CREAD;

    /*
     * set to raw-mode
     *
     * manpage of cfmakeraw :
     * cfmakeraw() sets the terminal attributes as follows:
     * termios_p->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
     *                       | INLCR | IGNCR | ICRNL | IXON);
     * termios_p->c_oflag &= ~OPOST;
     * termios_p->c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
     * termios_p->c_cflag &= ~(CSIZE | PARENB);
     * termios_p->c_cflag |= CS8;
     */
    tcsetattr(g_serial_fd, TCSANOW, &serial_settings);
    cfmakeraw(&serial_settings);

    /* set parameters of serial port again */
    serial_settings.c_cflag &= ~(CBAUD | CSIZE | PARENB | PARODD | CSTOPB);
    switch (databits)
    {
        case 5:  serial_settings.c_cflag |= CS5; break;
        case 6:  serial_settings.c_cflag |= CS6; break;
        case 7:  serial_settings.c_cflag |= CS7; break;
        case 8:
        default: serial_settings.c_cflag |= CS8; break;
    }

    switch (parity)
    {
        case UART_CFG_PARITY_EVEN:
            serial_settings.c_cflag |= PARENB;
            break;
        case UART_CFG_PARITY_ODD:
            serial_settings.c_cflag |= (PARENB | PARODD);
            break;
        case UART_CFG_PARITY_NONE:
        default:
            break;
    }

    if (stopbits != UART_CFG_STOPBITS_1)
        serial_settings.c_cflag |= CSTOPB;

    serial_settings.c_cflag |= baudrate;

    /* make settings active */
    return tcsetattr(g_serial_fd, TCSANOW, &serial_settings);
}


/*****************************************************************************/
int serial_close()
{
    int result;
    if (!(result = close(g_serial_fd)))
        g_serial_fd = 0;
    return result;
}

/*****************************************************************************/
int serial_read(u_int8_t *buffer, u_int32_t len)
{
    return read(g_serial_fd, buffer, len);
}

/*****************************************************************************/
int serial_read_with_timeout(u_int8_t *buffer, u_int32_t len,
                                     u_int32_t timeout)
{
    struct timeval tv;
    fd_set fds;
    int res;

    FD_ZERO(&fds);
    FD_SET(g_serial_fd, &fds);
    tv.tv_sec  = (timeout / 1000);
    tv.tv_usec = (timeout % 1000) * 1000;
    res = select(g_serial_fd + 1, &fds, 0, 0, &tv);

    return (res > 0) ? read(g_serial_fd, buffer, len) : res;
}

/*****************************************************************************/
int serial_write(u_int8_t *buffer, u_int32_t len)
{
    return write(g_serial_fd, buffer, len);
}

/*****************************************************************************/
int serial_input_flush()
{
    return tcflush(g_serial_fd, TCIFLUSH);
}

/*****************************************************************************/
int serial_ouput_flush()
{
    return tcflush(g_serial_fd, TCOFLUSH);
}


/*****************************************************************************/
int main()
{
    int i,retval;

    u_int8_t write_buffer[256];

    u_int8_t read_buffer[256] = {0} ;

    retval=serial_open(B115200,8,UART_CFG_PARITY_NONE,UART_CFG_STOPBITS_1);

    printf("Serial open status=%d--fd=%d\n",retval,g_serial_fd);

    if(g_serial_fd<0)
    {
		return 0;
    }

    serial_input_flush();
    serial_ouput_flush();

    /*get device status*/
    strcpy(write_buffer,"I am writing data\n");

    serial_write(write_buffer,strlen("I am writing data\n"));

    serial_close();

    return 0;
}


