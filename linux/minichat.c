#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_CLIENT_NUM      100
#define MAX_CLIENT_NAME_LEN 32

struct ChatClient {
    int sock;
    char name[MAX_CLIENT_NAME_LEN + 1];
};

struct ChatServer {
    int sock;
    int efd;
    struct ChatClient clients[MAX_CLIENT_NUM];
};

ssize_t client_sent(struct ChatClient* client, void* data, size_t size)
{
    ssize_t ret = write(client->sock, data, size);
    if (ret == -1) {
        perror("client write failed");
    }
    return ret;
}

ssize_t client_recv(struct ChatClient* client, void* data, size_t size)
{
    ssize_t ret = read(client->sock, data, size);
    if (ret == -1) {
        perror("client read failed");
    }
    return ret;
}

struct ChatServer* server_create(int port)
{
    struct ChatServer* server = malloc(sizeof(struct ChatServer));
    if (!server) {
        perror("malloc failed\n");
        return NULL;
    }
    memset(server, 0, sizeof(struct ChatServer));

    if ((server->sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("create socket failed");
        goto err;
    }

    struct sockaddr_in sa;
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(server->sock, (struct sockaddr*)&sa, sizeof(sa)) == -1) {
        perror("bind failed");
        goto err;
    }

    if (listen(server->sock, SOMAXCONN) == -1) {
        perror("listen failed");
        goto err;
    }

    return server;
err:
    free(server);
    return NULL;
}

int server_destroy(struct ChatServer* server)
{
    if (!server) {
        return -1;
    }
    close(server->sock);
    free(server);
    return 0;
}

int server_add_client(struct ChatServer* server, int client_fd)
{
    for (int index = 0; index < MAX_CLIENT_NUM; ++index) {
        if (server->clients[index].sock == 0) {
            struct epoll_event client_event = {
                .events = EPOLLIN,
                .data.ptr = &server->clients[index],
            };
            int ret = epoll_ctl(server->efd, EPOLL_CTL_ADD, client_fd,
                                &client_event);
            if (ret == -1) {
                perror("epoll_ctl failed");
                goto err;
            }

            server->clients[index].sock = client_fd;
            return index;
        }
    }

err:
    return -1;
}

int server_del_client(struct ChatServer* server, struct ChatClient* client)
{
    for (int index = 0; index < MAX_CLIENT_NUM; ++index) {
        if (client == server->clients + index) {
            struct epoll_event event = { .events = EPOLLIN };
            epoll_ctl(server->efd, EPOLL_CTL_DEL, client->sock, &event);
            close(client->sock);
            memset(server->clients + index, 0, sizeof(struct ChatClient));
        }
    }
    return 0;
}

int server_send_client_msg(struct ChatServer* server, struct ChatClient* client,
                           void* data, size_t size)
{
    int send_num = 0;
    for (int index = 0; index < MAX_CLIENT_NUM; ++index) {
        if (server->clients[index].sock > 0
            && server->clients[index].sock != client->sock) {
            ssize_t ret = write(server->clients[index].sock, client->name,
                                strlen(client->name));
            ret += write(server->clients[index].sock, ">", 1);
            ret += write(server->clients[index].sock, data, size);
            ++send_num;
        }
    }
    return send_num;
}

int server_run(struct ChatServer* server)
{
    server->efd = epoll_create1(EPOLL_CLOEXEC);

    struct epoll_event server_event = {
        .events = EPOLLIN | EPOLLERR,
        .data.ptr = server,
    };
    epoll_ctl(server->efd, EPOLL_CTL_ADD, server->sock, &server_event);

    while (true) {
        struct epoll_event events[10] = {};

        int ep_ret
            = epoll_wait(server->efd, events,
                         sizeof(events) / sizeof(struct epoll_event), -1);

        for (int index = 0; index < ep_ret; ++index) {
            struct epoll_event* event = &events[index];
            if (event->events & EPOLLIN && event->data.ptr == server) {
                struct sockaddr_in sa;
                socklen_t addr_len = sizeof(sa);

                int client_fd
                    = accept(server->sock, (struct sockaddr*)&sa, &addr_len);
                if (client_fd == -1) {
                    perror("accept failed");
                    continue;
                }
                printf("client online ip: %d\n", sa.sin_addr.s_addr);
                int client_index = server_add_client(server, client_fd);
                if (client_index == -1) {
                    close(client_fd);
                    printf("server max is full\n");
                    continue;
                }
                char welcome_str[] = "hi, please set your name\n";
                client_sent(&server->clients[client_index], welcome_str,
                            sizeof(welcome_str));
            } else if (event->events & EPOLLERR && event->data.ptr == server) {
                return -1;
            } else if (event->events & EPOLLIN) {
                struct ChatClient* client = event->data.ptr;

                char buff[512] = { 0 };
                ssize_t recv_len = client_recv(client, buff, sizeof(buff));
                if (strlen(client->name) == 0) {
                    if (recv_len > MAX_CLIENT_NAME_LEN) {
                        recv_len = MAX_CLIENT_NAME_LEN;
                    }
                    memcpy(client->name, buff, recv_len - 1);
                    printf("client: %d set name: %s\n", client->sock,
                           client->name);
                    char str[] = "name set ok\n";
                    client_sent(client, str, sizeof(str));
                } else if (recv_len == 0) {
                    printf("client: %d,%s offline\n", client->sock,
                           client->name);
                    server_del_client(server, client);
                } else {
                    server_send_client_msg(server, client, buff, recv_len);
                }
            }
        }
    }
    return 0;
}

int main(int argc, char* argv[])
{
    struct ChatServer* server = server_create(8866);
    if (server) {
        server_run(server);
        server_destroy(server);
    }
    return 0;
}