#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

// W is the Window Size
#define W 5

char a[10];
char b[10];

// Function - Integer to character string
void int_to_string(int z)
{
    int k,i=0,j,g;
    k=z;
    while(k>0)
    {
        i++;
        k=k/10;
    }
    g=i;
    i--;
    while(z>0)
    {
        k=z%10;
        a[i]=k+48; // ASCII conversion
        i--;
        z=z/10;
    }
    a[g]='\0';
}

// Main Function
int main()
{
    int s,f,wl,c=1,x,i=0,j,n,p=0,e=0;
    
    /****************** Configuration ****************/
    struct sockaddr_in ser;
    s=socket(AF_INET,SOCK_STREAM,0);
    ser.sin_family=AF_INET;
    ser.sin_port=6500;
    ser.sin_addr.s_addr=inet_addr("127.0.0.1");
    connect(s,(struct sockaddr *) &ser, sizeof(ser));
    /**************************************************/

    /*********** Input Frame number ******************/
    printf("\nConnection Established.\n");
    printf("\nNumber of frames to send : ");
    scanf("%d",&f);  // Input for number of frames
    int_to_string(f);
    send(s,a,sizeof(a),0);
    strcpy(b,"Time Out ");
    /**************************************************/

    while(1)
    {
        // Send frames with size that of the Window
        for(i=0;i<W;i++)
        {
            int_to_string(c);
            send(s,a,sizeof(a),0);
            if(c<=f)
            {
                printf("\nFrame Sent :: %d",c);
                c++;
            }
        }

        // Check for acknowledgement received
        i=0;
        wl=W;

        while(i<W)
        {
            recv(s,a,sizeof(a),0);
            p = atoi(a); // Character to int conversion
            if(strcmp(a,b)==0) // Compare if we receive time out
            {
                e=c-wl;
		        if(e<f)
		        {
		           printf("\n***Time Out occured, resend Frame %d onwards",e);
		        }
		    break;
            }
            else
            {
                if(p<=f)
                {
                    printf("\nAcknowledgement of Frame received : %s",a);
                    wl--;
                }
                else
                {
                    break;
                }
            }
            if(p>f)
            {
                break;
            }
            i++;
        }

        if(wl==0 && c>f)
        {
            send(s,b,sizeof(b),0);
            break;
        }
        else
        {
            c = c-wl;
            wl = W;
        }
    }
    close(s);
    return 0;
}


