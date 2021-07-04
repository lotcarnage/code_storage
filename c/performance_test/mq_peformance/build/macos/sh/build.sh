clang++ -c ../../../code/compare_mq_qsq.cpp ../../../code/random_numbers.c -I ../../../code/ -I ../../../../../container/ ../../../../../container/median_queue.c ../../../../../container/qs_queue.c
ld compare_mq_qsq.o median_queue.o qs_queue.o random_numbers.o -lc++ -lc
