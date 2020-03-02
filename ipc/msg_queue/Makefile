client_=client
server_=server

cc=gcc

clientSrc=client.c msg_common.c
serverSrc=server.c msg_common.c

.PHONY:all
all:$(client_) $(server_)

$(client_):$(clientSrc)
	$(cc) -o  $@ $^
$(server_):$(serverSrc)
	 $(cc) -o  $@ $^


.PHONY:clean
clean:
	rm -f $(client_) $(server_) 
