CC = gcc
CFLAGS = -pedantic -Wall -g
EXE = shm_concurrence
EXE2 = shm_producer shm_consumer shm_producer_file shm_consumer_file
EXE3 = mq_injector mq_workers_pool mq_workers_pool_timed


all : $(EXE) shm_concurrence_solved $(EXE2) $(EXE3)

.PHONY : clean
clean :
	rm -f *.o core $(EXE) $(EXE2) shm_concurrence_solved $(EXE3)

$(EXE) : % : %.o
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depends on $^"
	@echo "# has changed $< "
	$(CC) $(CFLAGS) -o $@ $@.o -lrt -lm

$(EXE2) : % : %.o cola_prod_consum.o
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depends on $^"
	@echo "# has changed $< "
	$(CC) $(CFLAGS) -pthread -o $@ $@.o cola_prod_consum.o -lrt -lm

$(EXE3) : % : %.o
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depends on $^"
	@echo "# has changed $< "
	$(CC) $(CFLAGS) -o $@ $@.o -lrt

shm_concurrence_solved : % : %.o
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depends on $^"
	@echo "# has changed $< "
	$(CC) $(CFLAGS) -pthread -o $@ $@.o -lrt -lm

shm_concurrence.o : shm_concurrence.c
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	@echo "# has changed $<"
	$(CC) $(CFLAGS) -c $<

shm_concurrence_solved.o : shm_concurrence_solved.c
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	@echo "# has changed $<"
	$(CC) $(CFLAGS) -c $<

shm_consumer.o : shm_consumer.c
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	@echo "# has changed $<"
	$(CC) $(CFLAGS) -pthread -c $<

shm_producer.o : shm_producer.c
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	@echo "# has changed $<"
	$(CC) $(CFLAGS) -pthread -c $<

cola_prod_consum.o :  cola_prod_consum.c cola_prod_consum.h
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	@echo "# has changed $<"
	$(CC) $(CFLAGS) -c $<

shm_consumer_file.o : shm_consumer_file.c
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	@echo "# has changed $<"
	$(CC) $(CFLAGS) -pthread -c $<

shm_producer_file.o : shm_producer_file.c
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	@echo "# has changed $<"
	$(CC) $(CFLAGS) -pthread -c $<

mq_injector.o : mq_injector.c
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	@echo "# has changed $<"
	$(CC) $(CFLAGS) -c $<
mq_workers_pool.o : mq_workers_pool.c
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	@echo "# has changed $<"
	$(CC) $(CFLAGS) -c $<

mq_workers_pool_timed.o : mq_workers_pool_timed.c
	@echo "#---------------------------"
	@echo "# Generating $@"
	@echo "# Depends on $^"
	@echo "# has changed $<"
	$(CC) $(CFLAGS) -c $<