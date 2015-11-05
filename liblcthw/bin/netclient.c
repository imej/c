#undef NDEBUG
#include <stdlib.h>
#include <sys/select.h>
#include <stdio.h>
#include <lcthw/ringbuffer.h>
#include <lcthw/dbg.h>
#include <lcthw/bstrlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>

struct tagbstring NL = bsStatic("\n");
struct tagbstring CRLF = bsStatic("\r\n");

int nonblock(int fd) {
    /**
     * fcntl() perform one of the operations(F_GETFL/F_SETFL) to the open file 
     * descripter (fd)
     *
     * F_GETFL - read the file descriptor flags
     * F_SETFL - set the file descriptor flags
     */
    int flags = fcntl(fd, F_GETFL, 0);
    check(flags >= 0, "Invalid flags on nonblock.");

    int rc = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    check(rc == 0, "Can't set nonblocking.");

    return 0;
error:
    return -1;
}

int client_connect(char *host, char *port)
{
    int rc = 0;
    struct addrinfo *addr = NULL;
    /**
     * struct addrinfo {
     *     int              ai_flags;
     *     int              ai_family;
     *     int              ai_socktype;
     *     int              ai_protocol;
     *     size_t           ai_addrlen;
     *     struct sockaddr *ai_addr;
     *     char            *ai_cannonname;
     *     struct addrinfo *ai_next;
     * }
     */

    rc = getaddrinfo(host, port, NULL, &addr);
    /**
     * getaddrinfo: Given node ('host') and service ('port'), which identity an 
     * Internet host and a service, getaddrinfo() returns one or more addrinfo
     * structures, each of which contains an Internet address that can be specified 
     * in a call to bind or connect.
     */
    check(rc == 0, "Failed to lookup %s:%s", host, port);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    /**
     * socket() creates an endpoint for communication and returns a descriptor.
     *
     * AF_INET     - IPv4 Internet protocols
     * SOCK_STREAM - Provides sequenced, reliable, two-way, connection-baed byte
     *               streams
     * 0           - A particular protocol
     */
    check(sock >= 0, "Cannot create a socket.");

    rc = connect(sock, addr->ai_addr, addr->ai_addrlen);
    /**
     * connect() connects the socket(sock) to the address specified by addr->ai_addr
     */
    check(rc == 0, "Connect failed.");

    rc = nonblock(sock);
    check(rc == 0, "Can't set nonblocking.");

    freeaddrinfo(addr);
    return sock;

error:
    freeaddrinfo(addr);
    return -1;
}

int read_some(RingBuffer *buffer, int fd, int is_socket)
{
    int rc = 0;

    if (RingBuffer_available_data(buffer) == 0) {
        buffer->start = buffer->end = 0;
    }

    if (is_socket) {
        rc = recv(fd, RingBuffer_starts_at(buffer), RingBuffer_available_space(buffer), 0);
	/**
	 * recv() is used to receive messages from a socket. 
	 */
    } else {
        rc = read(fd, RingBuffer_starts_at(buffer), RingBuffer_available_space(buffer));
	/**
	 * #include <fcntl.h>
	 * int read(int handle, void *buffer, int nbyte)
	 * Attempts to read nbytes from the file associated with handle, and palces the 
	 * characters read into buffer. The function returns the number of bytes read.
	 */
    }

    check(rc >= 0, "Failed to read from fd: %d", fd);
    
    RingBuffer_commit_write(buffer, rc);

    return rc;
error:
    return -1;
}

int write_some(RingBuffer *buffer, int fd, int is_socket)
{
    int rc = 0;
    bstring data = RingBuffer_get_all(buffer);

    check(data != NULL, "Failed to get from the buffer.");
    check(bfindreplace(data, &NL, &CRLF, 0) == BSTR_OK, "Failed to replace NL.");

    if (is_socket) {
        rc = send(fd, bdata(data), blength(data), 0);
    } else {
        rc = write(fd, bdata(data), blength(data));
    }

    check(rc == blength(data), "Failed to write everything to fd: %d.", fd);

    bdestroy(data);

    return rc;
error:
    return -1;
}

int main(int argc, char *argv[])
{
    fd_set allreads; // the fd_set data type represents file descriptor sets for the 
                     // select function. It is actually a bit array.
    fd_set readmask;

    int socket = 0;
    int rc = 0;
    RingBuffer *in_rb = RingBuffer_create(1024 *10);
    RingBuffer *sock_rb = RingBuffer_create(1024 *10);

    check(argc == 3, "USAGE: netclient host port.");

    socket = client_connect(argv[1], argv[2]);
    check(socket >= 0, "connect to %s:%s failed.", argv[1], argv[2]);

    FD_ZERO(&allreads); // clears allreads
    FD_SET(socket, &allreads); // add socket (file descriptor)
    FD_SET(0, &allreads); // add stdin

    while (1) {
        readmask = allreads;
	rc = select(socket + 1, &readmask, NULL, NULL, NULL);
	/**
	 * select() allows a program to monitor multiple file descriptors, waiting
	 * until one or more of the file descriptors become "ready" for some class
	 * of I/O operation.
	 */
	check(rc >= 0, "select failed.");

	if (FD_ISSET(0, &readmask)) {
	/**
	 * FD_ISSET() tests to see if a file descriptor is part of the set.
	 */
	    rc = read_some(in_rb, 0, 0);
	    check_debug(rc != -1, "Failed to read from stdin.");
	}

	if (FD_ISSET(socket, &readmask)) {
	    rc = read_some(sock_rb, socket, 1);
	    check_debug(rc != -1, "Failed to read from socket.");
	}

	while (!RingBuffer_empty(sock_rb)) {
	    rc = write_some(sock_rb, 1, 0);
	    check_debug(rc != -1, "Failed to write to stdout.");
	}

	while (!RingBuffer_empty(in_rb)) {
	    rc = write_some(in_rb, socket, 1);
	    check_debug(rc != -1, "Failed to write to socket.");
	}
    }

    return 0;

error:
    return -1;
}
