#ifndef DEFINE_MICRO_H
#define DEFINE_MICRO_H

//websocket server listen port
#define WEBSOCKET_SERVER_PORT     19527

//tcp server listen port
#define TCP_SERVER_PORT           19528

//broadcast self ip port
#define UDP_BROADCAST_SELF_IP     59527

/*** some of the json rpc method******************************************************************/

//the client has closed
#define JSRPC_METHOD_INNER_CLIENT_CLOSED              "dobot.inner.clientClosed"

//the current process will be exit
#define JSRPC_METHOD_INNER_EXIT                       "dobot.inner.exit"

#endif // DEFINE_MICRO_H
