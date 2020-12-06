unsigned int __ctype[32];
unsigned int *_ctype = (unsigned int *) __ctype;

#include <cstdio>


// dirty kludge: define missing functions from libcmini that the std c++ library requires
extern "C" {
    typedef long ssize_t;
    ssize_t readv(int fd, const struct iovec *iov, int iovcnt)
    {
        return 0;
    }

    ssize_t writev(int fd, const struct iovec *iov, int iovcnt)
    {
        return 0;
    }

    int ioctl(int fd, unsigned long request, ...)
    {
        return 0;
    };

    typedef long nfds_t;

    int poll(struct pollfd *fds, nfds_t nfds, int timeout)
    {
        return 0;
    }

}
