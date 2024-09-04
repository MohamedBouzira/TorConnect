/*toralize.h*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <sys/socket.h>  //socket() , connect()
#include <arpa/inet.h>   //htons() , inet_addr()
#include <netinet/in.h> 

#define PROXYIP "127.0.0.1"
#define PROXYPORT 4444   //you need to host socks service on this port (sudo service tor start)
#define REQSIZE sizeof(struct proxy_request)
#define RESSIZE sizeof(struct proxy_response)
#define USERID "user001"


typedef unsigned char int8;
typedef unsigned short int16;
typedef unsigned int int32;

/*
 REQUEST_CONNECT: request client to socks server(proxy)
    +----+----+----+----+----+----+----+----+----+----+....+----+
    | VN | CD | DSTPORT |      DSTIP        | USERID       |NULL|
	 +----+----+----+----+----+----+----+----+----+----+....+----+
      1    1      2              4           variable       1

*/

struct proxy_request {
    int8 vn;
    int8 cd;
    int16 dstport;
    int32 dstip;
    unsigned char userid[8];  //userid[7] + 1 null
};


typedef struct proxy_request Req;

/*
 RESPONSE_CONNECT: response of socks server to the client        
        +----+----+----+----+----+----+----+----+
		| VN | CD | DSTPORT |      DSTIP        |
		+----+----+----+----+----+----+----+----+
     	   1    1      2              4
*/

struct proxy_response{
    int8 vn;  //vn = 0;
    int8 cd;  //90 success , 91 92 93 reject;
    int16 _;  //ignored;
    int32 __; //ignored;
};

typedef struct proxy_response Res;

Req  *request(const char*,const int);
