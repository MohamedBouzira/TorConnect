/*TorConnect.c*/

/*DNS is not involved*/
/*you can send any request, i sent a http request to google.com*/

/* 
./TorConnect 147.168.12.43 80
*/

#include "torconnect.h"

Req *request(const char *dstip, const int dstport){
    Req *req;
    req = malloc(REQSIZE);

    req->vn = 4;
    req->cd = 1;
    req->dstport = htons(dstport);
    req->dstip = inet_addr(dstip);
    strncpy(req->userid, USERID, 8);

    return req;
}

int main(int argc ,char *argv[])
{
    char *host;
    int port ,s;
    Req *req;
    Res *res;
    char buf[RESSIZE];
    int success; 
    char tmp[512];


    if (argc != 3){
        printf("Usage : %s <host> <port>" ,argv[0]);
        return -1;
    }

    host = argv[1];
    port = atoi(argv[2]);

    struct sockaddr_in sock;

    s = socket(AF_INET, SOCK_STREAM,0);

    if (s < 0){
        perror("socket");
        return -1;
    }



    sock.sin_family = AF_INET;
    sock.sin_port = htons(PROXYPORT);
    sock.sin_addr.s_addr = inet_addr(PROXYIP);

    if(connect(s, (struct sockaddr *)&sock, sizeof(sock))){
        perror("connect");
        return -1;
    }

    printf("connect to proxy\n");

    req = request(host, port);
    write(s, req, REQSIZE);
    
    sleep(1);

    memset(buf, 0, RESSIZE);

    if(read(s, buf, RESSIZE) < 1){
        perror("read");
        free(req);
        close(s);
        return -1;
    }

    res = (Res *)buf;
    success = (res->cd == 90);

    if (!success){
        fprintf(stderr, "Unable to traverse the proxy, error code: %d\n" ,res->cd);
        close(s);
        free(req);
        return -1;
    }

    printf("Successfully connected through the proxy to %s:%d \n" ,host,port);
    
    memset(tmp, 0 ,512);

    //http request: 
    snprintf(tmp, 511, 
        "HEAD / HTTP/1.0\r\n"
        "Host: www.google.com\r\n"
        "\r\n"
    );

    write(s, tmp, strlen(tmp));

    sleep(1);
    memset(tmp, 0, 512);
    read(s, tmp, 511);
    printf("%s\n",tmp );
    
    
    close(s);
    free(req);
 

    return 0;
}
