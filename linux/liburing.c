#include <fcntl.h>
#include <liburing.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FILE_PATH "/tmp/io_uring_example.txt"

int main()
{
    struct io_uring ring;

    int ret = io_uring_queue_init(32, &ring, 0);
    if (ret < 0) {
        perror("io_uring_queue_init");
        return 1;
    }

    int fd = open(FILE_PATH, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        io_uring_queue_exit(&ring);
        return 1;
    }

    const char* data = "Hello, io_uring!";
    struct iovec iov = { .iov_base = (void*)data, .iov_len = strlen(data) };

    struct io_uring_sqe* sqe = io_uring_get_sqe(&ring);
    io_uring_prep_writev(sqe, fd, &iov, 1, 0);
    io_uring_submit(&ring);

    struct io_uring_cqe* cqe;
    io_uring_wait_cqe(&ring, &cqe);
    io_uring_cqe_seen(&ring, cqe);

    close(fd);
    io_uring_queue_exit(&ring);

    printf("数据已写入文件：%s\n", FILE_PATH);
    return 0;
}