
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
/* BSD support */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <board.h>
static unsigned int sockfd;
#include <ti/net/slnetutils.h>

#include <ti/display/Display.h>

#define UDPPACKETSIZE 1472

extern Display_Handle display;

extern void fdOpenSession();
extern void fdCloseSession();
extern void *TaskSelf();
union buffertype{
    int data;
    char message[256];
};
typedef struct hostent
      {
          char  *h_name;              /* Host name */
          char **h_aliases;           /* alias list */
          int    h_addrtype;          /* host address type */
          int    h_length;            /* length of address */
          char **h_addr_list;         /* list of addresses */
      #define h_addr  h_addr_list[0]  /* Address, for backward compatibility.  */
      }hostent_t;
/* For sleep() */
#include <unistd.h>
static struct SlNetSock_AddrIn_t serv_addr;
/* Driver Header files */
#include <ti/drivers/ADCBuf.h>
#include <ti/drivers/UART.h>
#define ADCBUFFERSIZE    (50)
#define UARTBUFFERSIZE   ((20 * ADCBUFFERSIZE) + 24)

uint16_t sampleBufferOne[ADCBUFFERSIZE];
uint16_t sampleBufferTwo[ADCBUFFERSIZE];
uint32_t microVoltBuffer[ADCBUFFERSIZE];
static char buffer[256];
uint32_t buffersCompletedCounter = 0;
char uartTxBuffer[UARTBUFFERSIZE];

/* Driver handle shared between the task and the callback function */
UART_Handle uart;
/*code to run adc*/
void adcBufCallback(ADCBuf_Handle handle, ADCBuf_Conversion *conversion,
    void *completedADCBuffer, uint32_t completedChannel);

/*
 * Callback function to use the UART in callback mode. It does nothing.
 */
void uartCallback(UART_Handle handle, void *buf, size_t count) {
   return;
}

/*end of code to run adc*/

/*
 *  ======== echoFxn ========
 *  Echoes UDP messages.
 *
 */
void *echoFxn(void *arg0)
{

        ADCBuf_Handle adcBuf;
        ADCBuf_Params adcBufParams;
        ADCBuf_Conversion continuousConversion;

        /* Call driver init functions */
        ADCBuf_init();
        unsigned int  portno, n;
        fdOpenSession(TaskSelf());

            Display_printf(display, 0, 0, "UDP Echo example started\n");


            /*my code start*/


             struct hostent *server;
               Display_printf(display, 0, 0, "Ubefore socket\n");
               portno = 2001;
               /* Create a socket point */
               sockfd = socket(AF_INET, SOCK_STREAM, 0);
               if (sockfd < 0) {
                  perror("ERROR opening socket");
                  exit(1);
               }
               const char *name;
               name="dyn229225.shef.ac.uk";
                         static struct  hostent Hostent;
                         static uint32_t    Addr[5];
                         uint16_t       AddrLen = 5;

                         unsigned int result1[1];
                         result1[0]=2410145279;
                         char *result=(char *)result1;

                         Display_printf(display, 0, 0, "before connect1\n");

                         int RetVal = 0;


                             /* Clear the reused buffer */
                         memset(&Hostent, 0, sizeof(struct hostent));
                         memset(&Addr, 0, sizeof(Addr));

                             /* Set the host name */








               serv_addr.sin_family=AF_INET;
               serv_addr.sin_port=htons(2001);
               serv_addr.sin_addr.s_addr=inet_addr("143.167.229.255");
               //serv_addr.sin_port = htons(portno);
               /* Now connect to the server */
               Display_printf(display, 0, 0, "before connect2\n");
               int a;
               a=SlNetSock_connect((int16_t)sockfd, (const SlNetSock_Addr_t *)&serv_addr,(SlNetSocklen_t) sizeof(serv_addr));
               //a=SlNetSock_connectUrl(sockfd, "dyn229225.shef.ac.uk:2001");
               if ( a< 0) {
                   Display_printf(display, 1, 0, "after connect %d\n",a );
                   perror("ERROR connecting");
                   exit(1);
               }
               Display_printf(display, 1, 0, "after connect%d\n",sockfd);
               *buffer=*("test");

                          /* Send message to the server */
                    a=SlNetSock_send(sockfd, buffer, strlen(buffer),0);
                    Display_printf(display, 1, 0, "after sendto%d\n",a);
                    if (a < 0) {
                                  perror("ERROR writing to socket");
                                  exit(1);
                               }
                    SlNetSock_recv(sockfd, buffer, 255,0);
               /* Now ask for a message from the user, this message
                  * will be read by server
               */


        /* Create a UART with data processing off. */


        /* Set up an ADCBuf peripheral in ADCBuf_RECURRENCE_MODE_CONTINUOUS */
        ADCBuf_Params_init(&adcBufParams);
        adcBufParams.callbackFxn = adcBufCallback;
        adcBufParams.recurrenceMode = ADCBuf_RECURRENCE_MODE_CONTINUOUS;
        adcBufParams.returnMode = ADCBuf_RETURN_MODE_CALLBACK;
        adcBufParams.samplingFrequency = 200;
        adcBuf = ADCBuf_open(Board_ADCBUF0, &adcBufParams);

        /* Configure the conversion struct */
        continuousConversion.arg = NULL;
        continuousConversion.adcChannel = Board_ADCBUF0CHANNEL0;
        continuousConversion.sampleBuffer = sampleBufferOne;
        continuousConversion.sampleBufferTwo = sampleBufferTwo;
        continuousConversion.samplesRequestedCount = ADCBUFFERSIZE;

        if (adcBuf == NULL){
            /* ADCBuf failed to open. */
            while(1);
        }
        /* Start converting. */
                          if (ADCBuf_convert(adcBuf, &continuousConversion, 1) !=
                              ADCBuf_STATUS_SUCCESS) {
                              /* Did not start conversion process correctly. */
                              while(1);
                          }

                          /*
                           * Go to sleep in the foreground thread forever. The ADC hardware will
                           * perform conversions and invoke the callback function when a buffer is
                           * full.
                           */
                          while(1) {
                              sleep(1000);
                          }



                    /*my code end*/

                    //fdCloseSession(TaskSelf());
                    return (NULL);



}
/*call back function*/
void adcBufCallback(ADCBuf_Handle handle, ADCBuf_Conversion *conversion,
    void *completedADCBuffer, uint32_t completedChannel)
{
    int error;
    uint_fast16_t i;
    uint_fast16_t uartTxBufferOffset = 0;
    /* Adjust raw ADC values and convert them to microvolts */
    ADCBuf_adjustRawValues(handle, completedADCBuffer, ADCBUFFERSIZE,
        completedChannel);
    ADCBuf_convertAdjustedToMicroVolts(handle, completedChannel,
        completedADCBuffer, microVoltBuffer, ADCBUFFERSIZE);
    bzero(buffer,256);
    *buffer=*("test");

           /* Send message to the server */
    error=SlNetSock_send(sockfd, buffer, strlen(buffer),0);
    Display_printf(display, 1, 0, "after write %d\n",error);
           if (error < 0) {
              perror("ERROR writing to socket");
              exit(1);
           }
           int n=0;
           /* Now read server response */
           bzero(buffer,256);
           *buffer=*("");
           while(*buffer==*("")){
               if(n<1000){
                   SlNetSock_recv(sockfd, buffer, 255,0);
                              Display_printf(display, 1, 0, "after read%s\n",buffer);
                              n++;
               }else{
                   SlNetSock_send(sockfd, microVoltBuffer, 200,0);
                   SlNetSock_recv(sockfd, buffer, 255,0);
                   n=0;
               }

           }
           if (n < 0) {
              perror("ERROR reading from socket");
              exit(1);
           }

           Display_printf(display, 1, 0, "after read%s\n",buffer);
          }


